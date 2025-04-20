/*
 * EEPROM.c
 *
 *  Created on: Jan 1, 2025
 *      Author: Dorgham
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/PIN_CONFIG.h"
#include "EEPROM.h"
#include <stdlib.h>
#include <avr/delay.h>

volatile u8_t EEPROM_buffer[1024];
volatile u16_t EEPROM_write_index = 0;
volatile u16_t EEPROM_write_size = 0;
volatile EEPROM_WRITE_BUSY_OR_NOT EEPROM_write_busy = NOT_BUSY;

/* Function Pointer */
void (*EEPROM_function_pointer)(void) = NULL;

void EEPROM_Enable(void) {
    SET_BIT(EECR, EERIE);
}

void EEPROM_Write(u16_t address, u8_t data) {
    /* Wait for completion of previous write */
    while (EECR & (1 << EEWE))
        ;
    /* Set up address and data registers */
    EEPROM_EEAR_Set(address);
    EEDR = data;
    /* Write logical one to EEMWE */
    EECR |= (1 << EEMWE);
    /* Start eeprom write by setting EEWE */
    EECR |= (1 << EEWE);
}

u8_t EEPROM_Read(u16_t address) {
    /* Wait for completion of previous write */
    while (EECR & (1 << EEWE))
        ;
    /* Set up address register */
    EEPROM_EEAR_Set(address);
    /* Start eeprom read by writing EERE */
    EECR |= (1 << EERE);
    /* Return data from data register */
    return EEDR;
}

void EEPROM_EEAR_Set(u16_t address) {
    EEARL = (u8_t)(address & 0xFF);  // Set low byte of address
    EEARH = (u8_t)(address >> 8);    // Set high byte of address
}

void EEPROM_WriteArray(u16_t start_address, u8_t *data, u16_t length) {
    for (u16_t i = 0; i < length; i++) {
        /* Write each byte to the EEPROM */
        EEPROM_Write(start_address + i, data[i]);

    }
}

void EEPROM_ReadArray(u16_t start_address, u8_t* array, u16_t length) {
    for (u16_t i = 0; i < length; i++) {
        array[i] = EEPROM_Read(start_address+i);                     // Store the data
        //LCD_SendChar(array[i]);
    }
//    LCD_SendChar(array[2]);
//    LCD_SendChar(array[2]);
//    LCD_SendChar(array[3]);
//    LCD_SendString(array);
    array[length] = '\0';
    //LCD_SendString(array);

}


void __vector_17(void) __attribute__((signal, used, externally_visible));
void __vector_17(void) {
    /* Check if there is data to write */
    if (EEPROM_write_size > 0) {
        /* Set EEAR to the current address */
        EEPROM_EEAR_Set(EEPROM_write_index);

        /* Set EEDR to the data to be written */
        EEDR = EEPROM_buffer[EEPROM_write_index];

        /* Start EEPROM Write: Set EEMWE and then EEWE */
        EECR |= (1 << EEMWE);  // Master write enable
        EECR |= (1 << EEWE);   // Start the write operation

        /* Update buffer index */
        EEPROM_write_index++;
        EEPROM_write_size--;

        /* If all writes are complete, mark as not busy */
        if (EEPROM_write_size == 0) {
            EEPROM_write_busy = NOT_BUSY;  // Writing done
        }
    } else {
        /* No pending write operation, disable interrupt */
        EECR &= ~(1 << EERIE);  // Disable EEPROM Ready Interrupt
    }
}
