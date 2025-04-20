/*
 * main.c
 *
 *  Created on: Sep 10, 2024
 *      Authors: Anas Dorgham
 */

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../LIB/PIN_CONFIG.h"
#include "../HAL/LCD/LCD.h"
#include "../MCAL/DIO/DIO.h"
#include "../MCAL/TIMER/TIMER.h"
#include "../MCAL/INTERRUPT/INTERRUPT.h"
#include "../MCAL/EEPROM/EEPROM.h"
#include "../HAL/SERVO/SERVO.h"
#include "../MCAL/SPI/SPI.h"
#include "../HAL/NRF24L01/NRF24L01.h"
#include "../LIB/DELAY/DELAY.h"

#define PIR1_PORT		PORT_D
#define PIR1_PIN		PIN_0

#define PIR2_PORT		PORT_D
#define PIR2_PIN		PIN_3


#define LED_PORT		PORT_D
#define LED_PIN			PIN_1

#define NO_MOTION		0
#define MOTION			1

u8_t motion_state = NO_MOTION;
u8_t number_of_violations = 0;


u8_t hour = 0;
u8_t minute = 0;
u8_t second = 0;
u32_t seconds_counter = 0;
u16_t write_index = 0;

u8_t time[9];

void time_as_text(u8_t* time_buffer, u8_t hour, u8_t minute, u8_t second){
	time_buffer[0] = hour/10 + '0';
	time_buffer[1] = hour%10 + '0';
	time_buffer[2] = ':';
	time_buffer[3] = minute/10 + '0';
	time_buffer[4] = minute%10 + '0';
	time_buffer[5] = ':';
	time_buffer[6] = second/10 + '0';
	time_buffer[7] = second%10 + '0';
	time_buffer[8] = '\0';
}

void TIME(void) {
	EEPROM_Enable();
	seconds_counter++;						// Increment the counter
	hour = seconds_counter / 3600;			// Calculate hours
	minute = (seconds_counter / 60) % 60;   // Calculate minutes
	second = seconds_counter % 60;          // Calculate seconds
	TIMER_Timer1_OCR1A_Set(15625);
}


int main(){
	DIO_SetPinDirection(PIR1_PORT, PIR1_PIN, PIN_INPUT);
	DIO_SetPinDirection(PIR2_PORT, PIR2_PIN, PIN_INPUT);
	INTERRUPT_EnableGlobalInterrupt();
	TIMER_Timer1_OCA_SetCallBack(TIME);		// Call function TIME in compare match
	EEPROM_Enable();
	LCD_Init(_4bits);
	TIMER_Timer1_OCR1A_Set(15625);			// Set compare match to be 1s
	TIMER_Timer1_Init(TIMER1_CTC_OCR1, TIMER1_PRESCALER_1024);
	TIMER_Timer1_OCA_EnableInterrupt();


	DIO_SetPinDirection(PORT_B, PIN_0, PIN_INPUT);		// Push Button
	DIO_SetPinDirection(PORT_D, PIN_6, PIN_INPUT);		// Push Button
	DIO_SetPinDirection(PORT_D, PIN_2, PIN_INPUT);		// Push Button

	while(1){
		/* If no motion for both sensors */
		if ((DIO_GetPinValue(PIR1_PORT, PIR1_PIN) == PIN_LOW) && (DIO_GetPinValue(PIR2_PORT, PIR2_PIN) == PIN_LOW)){
			if (motion_state == MOTION){
				DIO_SetPinValue(LED_PORT, LED_PIN, PIN_LOW);			// Turn off the LED
				motion_state = NO_MOTION;
			}
		}
		/* If there is a motion */
		else{
			if (motion_state == NO_MOTION){
				DIO_SetPinValue(LED_PORT, LED_PIN, PIN_HIGH);			// Turn on the LED
				LCD_Clear();
				motion_state = MOTION;
				number_of_violations++;									// Increment number of violation
				time_as_text(time, hour, minute, second);				// Convert timestamp to text format
				EEPROM_WriteArray(write_index, (u8_t*) time, 8);		// Store the timestamp at EEPROM
				write_index += 8;										// Increse write index for the next 8 characters (HH:MM:SS)
			}
		}

		/* If Push Button B0 is pressed */
		if ((DIO_GetPinValue(PORT_B, PIN_0) == PIN_HIGH)){
			DELAY_Timer2_ms(50);
			while((DIO_GetPinValue(PORT_B, PIN_0) == PIN_HIGH)){
				LCD_GoToPosition(UPPER_ROW, 0);
				LCD_SendString("No of Violations");
				LCD_GoToPosition(LOWER_ROW, 13);
				LCD_SendNumber(number_of_violations);
			}
			DELAY_Timer2_ms(50);
			LCD_Clear();
		}

		/* If Push Button D6 is pressed */
		else if ((DIO_GetPinValue(PORT_D, PIN_6) == PIN_HIGH)){
			DELAY_Timer2_ms(50);
			while ((DIO_GetPinValue(PORT_D, PIN_6) == PIN_HIGH)){
				for(u8_t i = 0; i < number_of_violations; i++){
					u8_t arr[9];
					EEPROM_ReadArray(i*8, arr, 8);
					if (i % 2 == 0){
						LCD_GoToPosition(UPPER_ROW, 0);
					}
					else{
						LCD_GoToPosition(LOWER_ROW, 0);
					}
					LCD_SendString(arr);								// Print the timestamps
					DELAY_Timer2_s(1);
				}
				LCD_Clear();
			}
		}

		/* If Push Button D2 is pressed */
		else if ((DIO_GetPinValue(PORT_D, PIN_2) == PIN_HIGH)){
			SERVO_90_CW();												// Rotate Servo 90 degrees CW
			TIMER_Timer1_OCA_SetCallBack(TIME);		// Call function TIME in compare match
			TIMER_Timer1_OCA_EnableInterrupt();
			TIMER_Timer1_Init(TIMER1_CTC_OCR1, TIMER1_PRESCALER_1024);
			LCD_GoToPosition(UPPER_ROW, 0);
		}
	}
}





