/*
 * EEPROM.h
 *
 *  Created on: Jan 1, 2025
 *      Author: Dorgham
 */

#ifndef MCAL_EEPROM_EEPROM_H_
#define MCAL_EEPROM_EEPROM_H_

#define	EEARH			(*(volatile u8_t*)0x3F)
#define	EEARL			(*(volatile u8_t*)0x3E)
#define	EEDR			(*(volatile u8_t*)0x3D)
#define	EECR			(*(volatile u8_t*)0x3C)

/* EECR */
#define	EERIE			3
#define	EEMWE			2
#define	EEWE			1
#define	EERE			0

typedef enum{
	NOT_BUSY,
	BUSY
} EEPROM_WRITE_BUSY_OR_NOT;


void EEPROM_Enable(void);
void EEPROM_Write(u16_t address, u8_t data);
u8_t EEPROM_Read(u16_t address);
void EEPROM_WriteArray(u16_t start_address, u8_t *data, u16_t length);
void EEPROM_ReadArray(u16_t start_address, u8_t* arr, u16_t length);
void EEPROM_EEAR_Set(u16_t address);





#endif /* MCAL_EEPROM_EEPROM_H_ */
