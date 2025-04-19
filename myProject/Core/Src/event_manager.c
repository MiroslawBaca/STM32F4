#include "event_manager.h"
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

// First element on the event list or NULL if list if empty
static Event* head = NULL;


void EVENT_MANAGER_Init(void) {
    head = NULL;
    //memset(events, 0, sizeof(events));
}


bool EVENT_MANAGER_RegisterEvent(Event* event, OnEventHandler onEvent, void* context) {
    event->isScheduled = false;
    event->onEvent = onEvent;
    event->context = context;
	if (head == NULL) {
        head = event;
        return true;
    } else {
        Event* testing_previous = NULL;
        Event* testing_next = head;
        while (testing_next != NULL) {
            if (testing_next==event) {
                return true;
            }
            testing_previous = testing_next;
            testing_next = testing_next->next;
        }
        testing_previous->next = event;
        return true;
    }

	return false;
}


void EVENT_MANAGER_UnregisterEvent(Event* event) {
    Event* testing_previous = NULL;
    Event* testing_next = head;
    while (testing_next != event) {
        testing_previous = testing_next;
        testing_next = testing_next->next;
    }
    if (testing_previous != NULL) {
        testing_previous->next = event->next;
    } else {
        if (head == event) {
            head = NULL;
        }
    }
}


bool EVENT_MANAGER_ScheduleEvent(Event* event, uint64_t time) {
    event->scheduledTime = time;
    event->isScheduled = true;
    return true;
}


void EVENT_MANAGER_Proc(uint64_t currentTime) {
    Event* testing_next = head;
    while (testing_next != NULL) {
        if ((testing_next->isScheduled==true) && (currentTime >= testing_next->scheduledTime)) {
            testing_next->isScheduled = false;
            testing_next->onEvent(testing_next,testing_next->scheduledTime,testing_next->context);
        }
        testing_next = testing_next->next;
    }

}

