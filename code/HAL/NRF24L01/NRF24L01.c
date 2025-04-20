#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/PIN_CONFIG.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/SPI/SPI.h"

#include "../../HAL/LCD/LCD.h"

#include "NRF24L01.h"

#define CONFIG_TX_MODE  0x0E  // PRIM_RX=0, PWR_UP=1
#define CONFIG_RX_MODE  0x0F  // PRIM_RX=1, PWR_UP=1

// CE Pin Configuration
u8_t nRF24L01_CE_port;
u8_t nRF24L01_CE_pin;

// Write to nRF24L01 Register
void NRF24L01_WriteRegister(u8_t reg, u8_t value) {
    DIO_SetPinValue(SS_PORT, SS, PIN_LOW);  // Pull CSN low
    SPI_Transmit(W_REGISTER | (reg & 0b00011111)); // Write command
    SPI_Transmit(value);                           // Write data
    DIO_SetPinValue(SS_PORT, SS, PIN_HIGH); // Pull CSN high
}

// Read from nRF24L01 Register
u8_t NRF24L01_ReadRegister(u8_t reg) {
    DIO_SetPinValue(SS_PORT, SS, PIN_LOW);  // Pull CSN low
    SPI_Transmit(R_REGISTER | (reg & 0b00011111)); // Read command
    u8_t value = SPI_Receive();                   // Read data
    DIO_SetPinValue(SS_PORT, SS, PIN_HIGH); // Pull CSN high
    return value;
}

// Set CE Pin State
void NRF24L01_CE(u8_t state) {
    if (state) {
        DIO_SetPinValue(nRF24L01_CE_port, nRF24L01_CE_pin, PIN_HIGH); // Enable CE pin
    } else {
        DIO_SetPinValue(nRF24L01_CE_port, nRF24L01_CE_pin, PIN_LOW);  // Disable CE pin
    }
}

// Initialize nRF24L01 for Transmit Mode
void NRF24L01_Init_Transmit(void) {
    NRF24L01_CE(0);  // Disable CE temporarily
    NRF24L01_WriteRegister(CONFIG_REG, CONFIG_TX_MODE);  // TX mode configuration
    NRF24L01_WriteRegister(RF_SETUP_REG, 0x07);          // 1Mbps, 0dBm power
    NRF24L01_WriteRegister(STATUS_REG, 0x70);            // Clear interrupts
    NRF24L01_CE(1);  // Enable CE to activate TX mode
}

// Initialize nRF24L01 for Receive Mode
void NRF24L01_Init_Receive(void) {
    NRF24L01_CE(0);  // Disable CE temporarily
    NRF24L01_WriteRegister(CONFIG_REG, CONFIG_RX_MODE);  // RX mode configuration
    NRF24L01_WriteRegister(RF_SETUP_REG, 0x07);          // 1Mbps, 0dBm power
    NRF24L01_WriteRegister(STATUS_REG, 0x70);            // Clear interrupts
    NRF24L01_CE(1);  // Enable CE to activate RX mode
    LCD_Clear();
}

// Select CE Pin
void NRF24L01_CE_SelectPin(u8_t port, u8_t pin) {
    nRF24L01_CE_port = port;
    nRF24L01_CE_pin = pin;
    DIO_SetPinDirection(port, pin, PIN_OUTPUT);  // Set CE pin as output
}

// Example of transmitting data
void NRF24L01_TransmitData(u8_t* data, u8_t length) {
    // Wait for TX buffer to be ready
    while (!(NRF24L01_ReadRegister(STATUS_REG) & 0x20)); // Check TX_DS flag (Data Sent)

    // Load the data into the TX payload register
    for (u8_t i = 0; i < length; i++) {
        SPI_Transmit(data[i]); // Transmit each byte of data
    }

    // Start transmission by setting CE high
    NRF24L01_CE(1);

    // Wait until the transmission is complete (check TX_DS flag)
    while (!(NRF24L01_ReadRegister(STATUS_REG) & 0x20));  // Check TX_DS flag

    // Clear the TX_DS flag by writing 1 to it
    NRF24L01_WriteRegister(STATUS_REG, 0x20);

    // Optionally, you can disable CE here if you are done transmitting
    NRF24L01_CE(0);
    LCD_Clear();
    LCD_SendString("NRF2");
}

// Example of receiving data
void NRF24L01_ReceiveData(u8_t* buffer, u8_t length) {
    // Wait for data to be received (check RX_DR flag)
    while (!(NRF24L01_ReadRegister(STATUS_REG) & 0x40)); // Check RX_DR flag (Data Ready)

    // Read received data from RX FIFO
    for (u8_t i = 0; i < length; i++) {
        buffer[i] = SPI_Receive();  // Read each byte of received data
    }

    // Clear the RX_DR flag by writing 1 to it
    NRF24L01_WriteRegister(STATUS_REG, 0x40);
}
