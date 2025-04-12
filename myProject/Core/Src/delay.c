/*
 * delay.c
 *
 *  Created on: Mar 18, 2025
 *      Author: admin
 */

#include <stdint.h>
#include <stdio.h>

static volatile uint64_t ticks;

uint64_t msGetTicks(void){
	return ticks;
}

void SysTick_Handler(void) {
	ticks++;
}

void msDelay(uint64_t ms) {
	uint64_t start_tick = ticks;
	//printf("Start Tick: %d\n", (int)ticks);
	while (ticks-start_tick<ms) {
	}
	//printf("End Tick: %d\n", (int)ticks);

	/* wersja z zajęć
	 * PROBLEM że system 32bit a dwie instrukcje potrzebujemy bo uint64 blok atomowy trzeba wylaczyc przerwanie na moment odczytu tej zmiennej
	 void msDelay(uint64_t ms) {
	 uint64_t timeout = ticks + ms;
	 while (ticks < timeout) {
	 	 ;
	 }
	 */
}
