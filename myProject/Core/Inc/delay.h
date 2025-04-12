/*
 * delay.h
 *
 *  Created on: Mar 18, 2025
 *      Author: admin
 */

#ifndef INC_DELAY_H_
#define INC_DELAY_H_

#include <stdint.h>
// to do main extern uint64_t ticks; // To działa ale uint64_t ticks; nie zadziała

/**
 * Delays execution for a given number of milliseconds based on SysTick timer.
 * @param[in] ms requested delay in milliseconds
 */
void msDelay(uint64_t ms);

/**
 * Gets the number of milliseconds elapsed since the SysTick was started.
 * @return current 64-bit tick counter value
 */
uint64_t msGetTicks(void);

#endif /* INC_DELAY_H_ */
