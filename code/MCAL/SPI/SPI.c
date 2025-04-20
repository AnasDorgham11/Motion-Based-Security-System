/*
 * SPI.c
 *
 *  Created on: Dec 30, 2024
 *      Author: Dorgham
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/PIN_CONFIG.h"
#include "SPI.h"

u8_t SPI_mode;
u8_t SPI_CE_port;
u8_t SPI_CE_pin;

void SPI_Init(SPI_MASTER_SLAVE mode) {
    SET_BIT(SPCR, SPE);  // Enable SPI
    SPI_mode = mode;
    if (mode == SLAVE) {
        CLEAR_BIT(SPCR, MSTR);  // Set as Slave
        DIO_SetPinDirection(SCK_PORT, SCK, PIN_INPUT);   // SCK: Input
        DIO_SetPinDirection(MOSI_PORT, MOSI, PIN_INPUT); // MOSI: Input
        DIO_SetPinDirection(MISO_PORT, MISO, PIN_OUTPUT); // MISO: Output
        DIO_SetPinDirection(SS_PORT, SS, PIN_INPUT);     // SS: Input
    } else if (mode == MASTER) {
        SET_BIT(SPCR, MSTR);  // Set as Master
        DIO_SetPinDirection(SCK_PORT, SCK, PIN_OUTPUT);  // SCK: Output
        DIO_SetPinDirection(MOSI_PORT, MOSI, PIN_OUTPUT); // MOSI: Output
        DIO_SetPinDirection(MISO_PORT, MISO, PIN_INPUT); // MISO: Input
        DIO_SetPinDirection(SS_PORT, SS, PIN_OUTPUT);    // SS: Output
        DIO_SetPinValue(SS_PORT, SS, PIN_HIGH);         // Ensure SS is high initially
    }
}

void SPI_Transmit(u8_t data) {
    if (SPI_mode == MASTER) {
        DIO_SetPinValue(SS_PORT, SS, PIN_LOW);  // Pull SS low
    }

    SPDR = data;  // Load data into SPI data register
    while (!(GET_BIT(SPSR, SPIF)));  // Wait for transmission to complete

    if (SPI_mode == MASTER) {
        DIO_SetPinValue(SS_PORT, SS, PIN_HIGH);  // Release SS
    }
}

u8_t SPI_Receive(void) {
    if (SPI_mode == MASTER) {
        DIO_SetPinValue(SS_PORT, SS, PIN_LOW);  // Pull SS low
        SPDR = 0xFF;  // Send dummy data to generate clock
    }

    while (!(GET_BIT(SPSR, SPIF)));  // Wait for reception to complete
    u8_t received_data = SPDR;      // Read received data

    if (SPI_mode == MASTER) {
        DIO_SetPinValue(SS_PORT, SS, PIN_HIGH);  // Release SS
    }

    return received_data;
}


void SPI_Slave_CE_SelectPin(u8_t port, u8_t pin) {
    SPI_CE_port = port;
    SPI_CE_pin = pin;
    DIO_SetPinDirection(SPI_CE_port, SPI_CE_pin, PIN_OUTPUT);  // Set CE as output
}
