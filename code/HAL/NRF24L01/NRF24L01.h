/*
 * NRF24L01.h
 *
 *  Created on: Dec 30, 2024
 *      Author: Dorgham
 */

#ifndef HAL_NRF24L01_NRF24L01_H_
#define HAL_NRF24L01_NRF24L01_H_

// nRF24L01 Register Addresses
#define CONFIG_REG      0x00    // CONFIG Register (used for mode and power settings)
#define EN_AA_REG       0x01    // EN_AA Register (Auto Acknowledgement)
#define EN_RXADDR_REG   0x02    // EN_RXADDR Register (Enable RX Addresses)
#define SETUP_AW_REG    0x03    // SETUP_AW Register (Address Width Setup)
#define SETUP_RETR_REG  0x04    // SETUP_RETR Register (Automatic Retransmit Setup)
#define RF_SETUP_REG    0x06    // RF_SETUP Register (Data Rate and Power Control)
#define STATUS_REG      0x07    // STATUS Register (Status Flags)
#define RX_ADDR_P0_REG  0x0A    // RX_ADDR_P0 Register (RX Pipe 0 Address)
#define TX_ADDR_REG     0x10    // TX_ADDR Register (TX Address)
#define RX_PW_P0_REG    0x11    // RX_PW_P0 Register (Payload Width for Pipe 0)
#define FIFO_STATUS_REG 0x17    // FIFO_STATUS Register (FIFO Status)

typedef enum{
	R_REGISTER = 0b00000000,
	W_REGISTER = 0b00100000,
	R_RX_PAYLOAD = 0b01100001,
	W_TX_PAYLOAD = 0b10100000,
	FLUSH_TX = 0b11100001,
	FLUSH_RX = 0b11100010
} NRF24L01_command;

void NRF24L01_WriteRegister(u8_t reg, u8_t value);
u8_t NRF24L01_ReadRegister(u8_t reg);
void NRF24L01_CE(u8_t state);
void NRF24L01_Init_Transmit(void);
void NRF24L01_Init_Receive(void);

// Select CE Pin
void NRF24L01_CE_SelectPin(u8_t port, u8_t pin);

// Example of transmitting data
void NRF24L01_TransmitData(u8_t* data, u8_t length) ;

// Example of receiving data
void NRF24L01_ReceiveData(u8_t* buffer, u8_t length);



#endif /* HAL_NRF24L01_NRF24L01_H_ */
