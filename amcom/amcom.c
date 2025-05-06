#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include "amcom.h"

/// Start of packet character
const uint8_t  AMCOM_SOP         = 0xA1;
const uint16_t AMCOM_INITIAL_CRC = 0xFFFF;

static uint16_t AMCOM_UpdateCRC(uint8_t byte, uint16_t crc)
{
	byte ^= (uint8_t)(crc & 0x00ff);
	byte ^= (uint8_t)(byte << 4);
	return ((((uint16_t)byte << 8) | (uint8_t)(crc >> 8)) ^ (uint8_t)(byte >> 4) ^ ((uint16_t)byte << 3));
}


void AMCOM_InitReceiver(AMCOM_Receiver* receiver, AMCOM_PacketHandler packetHandlerCallback, void* userContext) {
	// TODO ==================
	assert(receiver);
    assert(packetHandlerCallback);

    // zerowanie stanu odbiornika
    receiver->receivedPacketState = AMCOM_PACKET_STATE_EMPTY;
    receiver->payloadCounter      = 0;
    // rejestracja callback i kontekst
    receiver->packetHandler       = packetHandlerCallback;
    receiver->userContext         = userContext;
    // TODO ========END=======
}

size_t AMCOM_Serialize(uint8_t packetType, const void* payload, size_t payloadSize, uint8_t* destinationBuffer) {
	// TODO ==================
	// walidacja argumentów
    if (!destinationBuffer) return 0;
    if (payloadSize > AMCOM_MAX_PAYLOAD_SIZE) return 0;
    if ((payloadSize > 0) && !payload) return 0;

    // SOP, TYPE, LENGTH
    destinationBuffer[0] = AMCOM_SOP;
    destinationBuffer[1] = packetType;
    destinationBuffer[2] = (uint8_t)payloadSize;

    // liczenie CRC
    uint16_t crc = AMCOM_INITIAL_CRC;
    crc = AMCOM_UpdateCRC(packetType, crc);
    crc = AMCOM_UpdateCRC((uint8_t)payloadSize, crc);
    if (payloadSize) {
        const uint8_t* p = (const uint8_t*)payload;
        for (size_t i = 0; i < payloadSize; i++) {
            crc = AMCOM_UpdateCRC(p[i], crc);
        }
    }

    // zapisanie CRC w little-endian
    destinationBuffer[3] = (uint8_t)(crc & 0xFF);
    destinationBuffer[4] = (uint8_t)((crc >> 8) & 0xFF);

    // dane payload
    if (payloadSize) {
        memcpy(&destinationBuffer[5], payload, payloadSize);
    }

    // zwrócenie łącznej długości pakietu (minimalnie 5)
    return 5 + payloadSize;
    // TODO ========END=======
}

void AMCOM_Deserialize(AMCOM_Receiver* receiver, const void* data, size_t dataSize) {
    // TODO ==================
    assert(receiver);
    if (!data || dataSize == 0) return;

    const uint8_t* bytes = (const uint8_t*)data;
    for (size_t i = 0; i < dataSize; i++) {
        uint8_t b = bytes[i];

        switch (receiver->receivedPacketState) {
        case AMCOM_PACKET_STATE_EMPTY:
            if (b == AMCOM_SOP) {
                receiver->receivedPacket.header.sop = b;
                receiver->receivedPacketState = AMCOM_PACKET_STATE_GOT_SOP;
            }
            break;

        case AMCOM_PACKET_STATE_GOT_SOP:
            receiver->receivedPacket.header.type = b;
            receiver->receivedPacketState = AMCOM_PACKET_STATE_GOT_TYPE;
            break;

        case AMCOM_PACKET_STATE_GOT_TYPE:
            receiver->receivedPacket.header.length = b;
            if (b <= AMCOM_MAX_PAYLOAD_SIZE) {
                receiver->receivedPacketState = AMCOM_PACKET_STATE_GOT_LENGTH;
            } else {
                // niepoprawna długość -> zacznij od nowa
                receiver->receivedPacketState = AMCOM_PACKET_STATE_EMPTY;
            }
            break;

        case AMCOM_PACKET_STATE_GOT_LENGTH:
            // pierwszy bajt CRC (LSB)
            receiver->receivedPacket.header.crc = b;
            receiver->receivedPacketState = AMCOM_PACKET_STATE_GOT_CRC_LO;
            break;

        case AMCOM_PACKET_STATE_GOT_CRC_LO:
            // drugi bajt CRC (MSB)
            receiver->receivedPacket.header.crc |= ((uint16_t)b << 8);
            if (receiver->receivedPacket.header.length == 0) {
                // brak payload -> od razu cały pakiet gotowy
                receiver->receivedPacketState = AMCOM_PACKET_STATE_GOT_WHOLE_PACKET;
            } else {
                // zaczyna czytać payload
                receiver->payloadCounter = 0;
                receiver->receivedPacketState = AMCOM_PACKET_STATE_GETTING_PAYLOAD;
            }
            break;

        case AMCOM_PACKET_STATE_GETTING_PAYLOAD:
            receiver->receivedPacket.payload[receiver->payloadCounter++] = b;
            if (receiver->payloadCounter >= receiver->receivedPacket.header.length) {
                receiver->receivedPacketState = AMCOM_PACKET_STATE_GOT_WHOLE_PACKET;
            }
            break;

        default:
            // w każdym innym wypadku – reset
            receiver->receivedPacketState = AMCOM_PACKET_STATE_EMPTY;
            break;
        }

        // jeżeli udało się zbudować cały pakiet – weryfikacja CRC i wywołanie callback
        if (receiver->receivedPacketState == AMCOM_PACKET_STATE_GOT_WHOLE_PACKET) {
            // liczenie CRC od nowa
            uint16_t crc = AMCOM_INITIAL_CRC;
            crc = AMCOM_UpdateCRC(receiver->receivedPacket.header.type, crc);
            crc = AMCOM_UpdateCRC(receiver->receivedPacket.header.length, crc);
            for (size_t j = 0; j < receiver->receivedPacket.header.length; j++) {
                crc = AMCOM_UpdateCRC(receiver->receivedPacket.payload[j], crc);
            }

            // porównanie z odebranym
            if (crc == receiver->receivedPacket.header.crc) {
                // wywołanie funkcji użytkownika
                if (receiver->packetHandler) {
                    receiver->packetHandler(&receiver->receivedPacket,
                                            receiver->userContext);
                }
            }
            // reset do EMPTY
            receiver->receivedPacketState = AMCOM_PACKET_STATE_EMPTY;
        }
    }
    // TODO ========END=======
}
