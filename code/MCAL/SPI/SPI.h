/*
 * SPI.h
 *
 *  Created on: Dec 30, 2024
 *      Author: Dorgham
 */

#ifndef MCAL_SPI_SPI_H_
#define MCAL_SPI_SPI_H_

#define SPCR		(*(volatile u8_t*)0x2D)
#define SPSR		(*(volatile u8_t*)0x2E)
#define SPDR		(*(volatile u8_t*)0x2F)

typedef enum{
	SLAVE,
	MASTER
} SPI_MASTER_SLAVE;

#define	SPIE		7
#define	SPE			6
#define	DORD		5
#define	MSTR		4
#define	CPOL		3
#define	CPHA		2
#define	SPR1		1
#define	SPR0		0

#define	SPI2X		0
#define	WCOL		6
#define	SPIF		7




void SPI_Init(SPI_MASTER_SLAVE mode);
void SPI_Transmit(u8_t data);
u8_t SPI_Receive(void);
void SPI_Slave_CE_SelectPin(u8_t port, u8_t pin);


#endif /* MCAL_SPI_SPI_H_ */
