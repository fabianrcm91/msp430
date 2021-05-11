#ifndef PCD8544_H_
#define PCD8544_H_

#include <stdint.h>
#include "../mod_user_defs.h"
#include "mod_core.h"
#include "mod_nostdio.h"

#define LCD5110_COMMAND 0
#define LCD5110_DATA 1

#define PCD8544_POWERDOWN 		0x04
#define PCD8544_ENTRYMODE 		0x02
#define PCD8544_EXTENDEDINSTRUCTION 	0x01

#define PCD8544_DISPLAYBLANK 		0x00
#define PCD8544_DISPLAYNORMAL 		0x04
#define PCD8544_DISPLAYALLON 		0x01
#define PCD8544_DISPLAYINVERTED 	0x05

// H = 0
#define PCD8544_FUNCTIONSET 	0x20
#define PCD8544_DISPLAYCONTROL 	0x08
#define PCD8544_SETYADDR 		0x40
#define PCD8544_SETXADDR 		0x80
#define PCD8544_HPIXELS			84
#define PCD8544_VBANKS			6
#define PCD8544_MAXBYTES 		504 // PCD8544_HPIXELS * PCD8544_VBANKS
// H = 1
#define PCD8544_SETTEMP 		0x04
#define PCD8544_SETBIAS 		0x10
#define PCD8544_SETVOP 			0x80

//transform
#define NONE 				0x00
#define FLIP_H 				0x01
#define FLIP_V 				0x02
#define ROTATE 				0x04 // 90 deg CW#define ROTATE_90_CW 			ROTATE
#define ROTATE_90_CCW 			(FLIP_H | FLIP_V | ROTATE)
#define ROTATE_180 			(FLIP_H | FLIP_V)

#define LCD_X 				84 //columns#define LCD_Y 				48 //rows
void lcd5110Init(void);
void writeToLCD5110(uint8_t dataCommand, uint8_t data);
void lcd5110Clear(void);
void lcd5110Gotoxy(uint8_t xAddr, uint8_t yAddr);
void writeCharToLCD5110(uint8_t c);
void writeStringToLCD5110(const uint8_t message[]);
void clearBankLCD5110(uint8_t bank);
void writeBlockToLCD5110(uint8_t *byte, uint8_t length);
void lcd5110WriteSetPosition(uint8_t row, uint8_t column, uint8_t exportData);
void lcd5110WriteMessage(uint8_t row, uint8_t column, const uint8_t message[]);
void lcd5110PrintInt16(uint16_t varin);
void lcd5110PrintInt32(uint32_t varin);
void lcd5110PrintFloat(float varin, uint8_t FracDigits);
#endif
