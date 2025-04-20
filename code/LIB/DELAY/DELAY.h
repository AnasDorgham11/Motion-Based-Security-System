/*
 * DELAY.h
 *
 *  Created on: Jul 17, 2024
 *      Author: Anas Dorgham
 */

#ifndef LIB_DELAY_DELAY_H_
#define LIB_DELAY_DELAY_H_

#define DELAY_OFF		0
#define DELAY_ON		1

void DELAY_Timer0_us(u32_t time_in_us);
void DELAY_Timer0_ms(float time_in_ms);
void DELAY_Timer0_s(float time_in_s);

void DELAY_Timer1_us(u32_t time_in_us);
void DELAY_Timer1_ms(float time_in_ms);
void DELAY_Timer1_s(float time_in_s);

void DELAY_Timer2_us(u32_t time_in_us);
void DELAY_Timer2_ms(float time_in_ms);
void DELAY_Timer2_s(float time_in_s);

void DELAY_Timer0_InterruptFunction(void);

#endif /* LIB_DELAY_DELAY_H_ */
