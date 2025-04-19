/* Includes ------------------------------------------------------------------*/
#include <assert.h>
#include "ring_buffer.h"


bool RingBuffer_Init(RingBuffer *ringBuffer, char *dataBuffer, size_t dataBufferSize) 
{
	assert(ringBuffer);
	assert(dataBuffer);
	assert(dataBufferSize > 0);
	
	if ((ringBuffer) && (dataBuffer) && (dataBufferSize > 0)) {
	    //TODO
	    ringBuffer->data = dataBuffer;
    	ringBuffer->capacity = dataBufferSize;
    	ringBuffer->head = 0;
    	ringBuffer->tail = 0;
    	ringBuffer->isFull = false;
    	return true;
	}
	
	return false;
}

bool RingBuffer_Clear(RingBuffer *ringBuffer)
{
	assert(ringBuffer);
	
	if (ringBuffer) {
	    //TODO
    	ringBuffer->head = 0;
    	ringBuffer->tail = 0;
    	ringBuffer->isFull = false;
    	return true;
	}
	return false;
}

bool RingBuffer_IsEmpty(const RingBuffer *ringBuffer)
{
  assert(ringBuffer);	
	//TODO
	if ((ringBuffer->head == ringBuffer->tail) && (!ringBuffer->isFull))
	    return true;
	else
	    return false;
}

size_t RingBuffer_GetLen(const RingBuffer *ringBuffer)
{
	assert(ringBuffer);
	
	if (ringBuffer) {
	    // TODO
	    if (ringBuffer->isFull) {
	        return ringBuffer->capacity;
	    }
	    else if (ringBuffer->head >= ringBuffer->tail) {
	        return ringBuffer->head - ringBuffer->tail;
	    }
	    else {
	        return ringBuffer->capacity - ringBuffer->tail + ringBuffer->head;
	    }
	}
	return 0;
	
}

size_t RingBuffer_GetCapacity(const RingBuffer *ringBuffer)
{
	assert(ringBuffer);
	
	if (ringBuffer) {
		// TODO
		return ringBuffer->capacity;
	}
	return 0;	
}


bool RingBuffer_PutChar(RingBuffer *ringBuffer, char c)
{
	assert(ringBuffer);
	
	if (ringBuffer) {
	    //TODO
        if (ringBuffer->isFull) {
            return false;
        }
		ringBuffer->data[ringBuffer->head] = c;
		ringBuffer->head = (ringBuffer->head + 1);
		if (ringBuffer->head % ringBuffer->capacity == 0) {
		    ringBuffer->head = 0;
		}
    
		
        if (ringBuffer->head == ringBuffer->tail) {
            ringBuffer->isFull = true;
        }
		return true;
	}
	return false;
}

bool RingBuffer_GetChar(RingBuffer *ringBuffer, char *c)
{
	assert(ringBuffer);
	assert(c);
	
  if ((ringBuffer) && (c)) {
		//TODO
		if (RingBuffer_IsEmpty(ringBuffer)) {
		    return false;
		}
		*c = ringBuffer->data[ringBuffer->tail];
		ringBuffer->tail = (ringBuffer->tail + 1);
		if (ringBuffer->tail % ringBuffer->capacity == 0) {
		    ringBuffer->tail = 0;
		}
		ringBuffer->isFull = false;
		return true;
	}
	return false;
}
