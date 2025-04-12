#include "event_manager.h"
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

// Maximum number of events handled by the event manager
#define MAX_NUMBER_OF_EVENTS 10

// Table of Event handles
static Event* events[MAX_NUMBER_OF_EVENTS];


void EVENT_MANAGER_Init(void) {
    memset(events, 0, sizeof(events));
}


bool EVENT_MANAGER_RegisterEvent(Event* event, OnEventHandler onEvent, void* context) {
    for (int j = 0; j < MAX_NUMBER_OF_EVENTS; j++) {
        if (events[j] == NULL) {
            events[j] = event;
	        events[j]->isScheduled = false;
	        //events[j]->scheduledTime = 0;
	        events[j]->onEvent = onEvent;
	        events[j]->context = context;
	        return true;
        }
    }
	return false;
}


void EVENT_MANAGER_UnregisterEvent(Event* event) {
    for (int j = 0; j < MAX_NUMBER_OF_EVENTS; j++) {
        if (events[j] == event) {
            events[j] = NULL;
        }
    }
    
}


bool EVENT_MANAGER_ScheduleEvent(Event* event, uint64_t time) {
    for (int j = 0; j < MAX_NUMBER_OF_EVENTS; j++) {
        if (events[j] == event) {
            event->scheduledTime = time;
            event->isScheduled = true;
            return true;
        }
    }
	return false;
}


void EVENT_MANAGER_Proc(uint64_t currentTime) {
    for (int j = 0; j < MAX_NUMBER_OF_EVENTS; j++) {
        if ((events[j] != NULL) && (events[j]->isScheduled==true) && (currentTime >= events[j]->scheduledTime)) {
	        events[j]->isScheduled = false;
	        events[j]->onEvent(events[j],events[j]->scheduledTime,events[j]->context);
	        //events[j]->scheduledTime = 0;
	        //events[j]->onEvent = onEvent;
	        //events[j]->context = context;
        }
    }
}

