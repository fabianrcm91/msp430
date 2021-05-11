/**
 *  @file lcd5110Module.c
 *  @brief Module SPI LCD Module Nokia 1100
 *  @date 30/03/2012
 *  @version 1.0.1
 *
 *  C Toolkit For MSP430 Texas Instrument Microcontroller
 *  Copyright (C) 2012  Leandro Perez Guatibonza
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "mod_lcd5110.h"

#define LCD5110_SELECT 		pinDigLow(lcd5110_cs);
#define LCD5110_DESELECT 	pinDigHigh(lcd5110_cs);
#define LCD5110_SET_COMMAND pinDigLow(lcd5110_dc);
#define LCD5110_SET_DATA 	pinDigHigh(lcd5110_dc);

#define LCD5110_RESET_ON	pinDigLow(lcd5110_rst);
#define LCD5110_RESET_OFF 	pinDigHigh(lcd5110_rst);

#define SPI_MSB_FIRST		VALUE_SPI = 0x80;
#define SPI_LSB_FIRST 		VALUE_SPI = 0x01;

uint8_t VALUE_SPI = 0x80;

// lookup table, here you can modify the font
uint8_t const font[][5] = {		// basic font
		{ 0x00, 0x00, 0x00, 0x00, 0x00 } // 20
				, { 0x00, 0x00, 0x5f, 0x00, 0x00 } // 21 !
				, { 0x00, 0x07, 0x00, 0x07, 0x00 } // 22 "
				, { 0x14, 0x7f, 0x14, 0x7f, 0x14 } // 23 #
				, { 0x24, 0x2a, 0x7f, 0x2a, 0x12 } // 24 $
				, { 0x23, 0x13, 0x08, 0x64, 0x62 } // 25 %
				, { 0x36, 0x49, 0x55, 0x22, 0x50 } // 26 &
				, { 0x00, 0x05, 0x03, 0x00, 0x00 } // 27 '
				, { 0x00, 0x1c, 0x22, 0x41, 0x00 } // 28 (
				, { 0x00, 0x41, 0x22, 0x1c, 0x00 } // 29 )
				, { 0x14, 0x08, 0x3e, 0x08, 0x14 } // 2a *
				, { 0x08, 0x08, 0x3e, 0x08, 0x08 } // 2b +
				, { 0x00, 0x50, 0x30, 0x00, 0x00 } // 2c ,
				, { 0x08, 0x08, 0x08, 0x08, 0x08 } // 2d -
				, { 0x00, 0x60, 0x60, 0x00, 0x00 } // 2e .
				, { 0x20, 0x10, 0x08, 0x04, 0x02 } // 2f /
				, { 0x3e, 0x51, 0x49, 0x45, 0x3e } // 30 0
				, { 0x00, 0x42, 0x7f, 0x40, 0x00 } // 31 1
				, { 0x42, 0x61, 0x51, 0x49, 0x46 } // 32 2
				, { 0x21, 0x41, 0x45, 0x4b, 0x31 } // 33 3
				, { 0x18, 0x14, 0x12, 0x7f, 0x10 } // 34 4
				, { 0x27, 0x45, 0x45, 0x45, 0x39 } // 35 5
				, { 0x3c, 0x4a, 0x49, 0x49, 0x30 } // 36 6
				, { 0x01, 0x71, 0x09, 0x05, 0x03 } // 37 7
				, { 0x36, 0x49, 0x49, 0x49, 0x36 } // 38 8
				, { 0x06, 0x49, 0x49, 0x29, 0x1e } // 39 9
				, { 0x00, 0x36, 0x36, 0x00, 0x00 } // 3a :
				, { 0x00, 0x56, 0x36, 0x00, 0x00 } // 3b ;
				, { 0x08, 0x14, 0x22, 0x41, 0x00 } // 3c <
				, { 0x14, 0x14, 0x14, 0x14, 0x14 } // 3d =
				, { 0x00, 0x41, 0x22, 0x14, 0x08 } // 3e >
				, { 0x02, 0x01, 0x51, 0x09, 0x06 } // 3f ?
				, { 0x32, 0x49, 0x79, 0x41, 0x3e } // 40 @
				, { 0x7e, 0x11, 0x11, 0x11, 0x7e } // 41 A
				, { 0x7f, 0x49, 0x49, 0x49, 0x36 } // 42 B
				, { 0x3e, 0x41, 0x41, 0x41, 0x22 } // 43 C
				, { 0x7f, 0x41, 0x41, 0x22, 0x1c } // 44 D
				, { 0x7f, 0x49, 0x49, 0x49, 0x41 } // 45 E
				, { 0x7f, 0x09, 0x09, 0x09, 0x01 } // 46 F
				, { 0x3e, 0x41, 0x49, 0x49, 0x7a } // 47 G
				, { 0x7f, 0x08, 0x08, 0x08, 0x7f } // 48 H
				, { 0x00, 0x41, 0x7f, 0x41, 0x00 } // 49 I
				, { 0x20, 0x40, 0x41, 0x3f, 0x01 } // 4a J
				, { 0x7f, 0x08, 0x14, 0x22, 0x41 } // 4b K
				, { 0x7f, 0x40, 0x40, 0x40, 0x40 } // 4c L
				, { 0x7f, 0x02, 0x0c, 0x02, 0x7f } // 4d M
				, { 0x7f, 0x04, 0x08, 0x10, 0x7f } // 4e N
				, { 0x3e, 0x41, 0x41, 0x41, 0x3e } // 4f O
				, { 0x7f, 0x09, 0x09, 0x09, 0x06 } // 50 P
				, { 0x3e, 0x41, 0x51, 0x21, 0x5e } // 51 Q
				, { 0x7f, 0x09, 0x19, 0x29, 0x46 } // 52 R
				, { 0x46, 0x49, 0x49, 0x49, 0x31 } // 53 S
				, { 0x01, 0x01, 0x7f, 0x01, 0x01 } // 54 T
				, { 0x3f, 0x40, 0x40, 0x40, 0x3f } // 55 U
				, { 0x1f, 0x20, 0x40, 0x20, 0x1f } // 56 V
				, { 0x3f, 0x40, 0x38, 0x40, 0x3f } // 57 W
				, { 0x63, 0x14, 0x08, 0x14, 0x63 } // 58 X
				, { 0x07, 0x08, 0x70, 0x08, 0x07 } // 59 Y
				, { 0x61, 0x51, 0x49, 0x45, 0x43 } // 5a Z
				, { 0x00, 0x7f, 0x41, 0x41, 0x00 } // 5b [
				, { 0x02, 0x04, 0x08, 0x10, 0x20 } // 5c �
				, { 0x00, 0x41, 0x41, 0x7f, 0x00 } // 5d ]
				, { 0x04, 0x02, 0x01, 0x02, 0x04 } // 5e ^
				, { 0x40, 0x40, 0x40, 0x40, 0x40 } // 5f _
				, { 0x00, 0x01, 0x02, 0x04, 0x00 } // 60 `
				, { 0x20, 0x54, 0x54, 0x54, 0x78 } // 61 a
				, { 0x7f, 0x48, 0x44, 0x44, 0x38 } // 62 b
				, { 0x38, 0x44, 0x44, 0x44, 0x20 } // 63 c
				, { 0x38, 0x44, 0x44, 0x48, 0x7f } // 64 d
				, { 0x38, 0x54, 0x54, 0x54, 0x18 } // 65 e
				, { 0x08, 0x7e, 0x09, 0x01, 0x02 } // 66 f
				, { 0x0c, 0x52, 0x52, 0x52, 0x3e } // 67 g
				, { 0x7f, 0x08, 0x04, 0x04, 0x78 } // 68 h
				, { 0x00, 0x44, 0x7d, 0x40, 0x00 } // 69 i
				, { 0x20, 0x40, 0x44, 0x3d, 0x00 } // 6a j
				, { 0x7f, 0x10, 0x28, 0x44, 0x00 } // 6b k
				, { 0x00, 0x41, 0x7f, 0x40, 0x00 } // 6c l
				, { 0x7c, 0x04, 0x18, 0x04, 0x78 } // 6d m
				, { 0x7c, 0x08, 0x04, 0x04, 0x78 } // 6e n
				, { 0x38, 0x44, 0x44, 0x44, 0x38 } // 6f o
				, { 0x7c, 0x14, 0x14, 0x14, 0x08 } // 70 p
				, { 0x08, 0x14, 0x14, 0x18, 0x7c } // 71 q
				, { 0x7c, 0x08, 0x04, 0x04, 0x08 } // 72 r
				, { 0x48, 0x54, 0x54, 0x54, 0x20 } // 73 s
				, { 0x04, 0x3f, 0x44, 0x40, 0x20 } // 74 t
				, { 0x3c, 0x40, 0x40, 0x20, 0x7c } // 75 u
				, { 0x1c, 0x20, 0x40, 0x20, 0x1c } // 76 v
				, { 0x3c, 0x40, 0x30, 0x40, 0x3c } // 77 w
				, { 0x44, 0x28, 0x10, 0x28, 0x44 } // 78 x
				, { 0x0c, 0x50, 0x50, 0x50, 0x3c } // 79 y
				, { 0x44, 0x64, 0x54, 0x4c, 0x44 } // 7a z
				, { 0x00, 0x08, 0x36, 0x41, 0x00 } // 7b {
				, { 0x00, 0x00, 0x7f, 0x00, 0x00 } // 7c |
				, { 0x00, 0x41, 0x36, 0x08, 0x00 } // 7d }
				, { 0x10, 0x08, 0x08, 0x10, 0x08 } // 7e ~
				, { 0x00, 0x06, 0x09, 0x09, 0x06 } // 7f Deg Symbol
				, { 0x08, 0x08, 0x2A, 0x1C, 0x08 } // 80 ->
				, { 0x08, 0x1C, 0x2A, 0x08, 0x08 } // 81 <-
		};

void lcd5110Init(void) {
	pinModeOutput(lcd5110_cs);
	pinModeOutput(lcd5110_dc);
	pinModeOutput(lcd5110_rst);
	pinModeOutput(lcd5110_clk);
	pinModeOutput(lcd5110_data);

	pinDigHigh(lcd5110_cs);
	pinDigHigh(lcd5110_dc);
	pinDigHigh(lcd5110_rst);
	pinDigHigh(lcd5110_clk);
	pinDigHigh(lcd5110_data);

	SPI_MSB_FIRST

	LCD5110_RESET_ON
	//__delay_cycles(16*500000); // 5mS so says the stop watch(less than 5ms will not work)
	LCD5110_RESET_OFF

	writeToLCD5110(LCD5110_COMMAND,
			PCD8544_FUNCTIONSET | PCD8544_EXTENDEDINSTRUCTION);
	writeToLCD5110(LCD5110_COMMAND, PCD8544_SETVOP | 0x3F);
	writeToLCD5110(LCD5110_COMMAND, PCD8544_SETTEMP | 0x02);
	writeToLCD5110(LCD5110_COMMAND, PCD8544_SETBIAS | 0x03);
	writeToLCD5110(LCD5110_COMMAND, PCD8544_FUNCTIONSET);
	writeToLCD5110(LCD5110_COMMAND,
			PCD8544_DISPLAYCONTROL | PCD8544_DISPLAYNORMAL);
}

void writeToLCD5110(uint8_t dataCommand, uint8_t data) {
	LCD5110_SELECT
	if (dataCommand) {
		LCD5110_SET_DATA
	} else {
		LCD5110_SET_COMMAND
	}

	uint8_t i;
	for (i = 0; i < 8; i++) {
		pinDigLow(lcd5110_clk);
		if ((data & VALUE_SPI)) {
			pinDigHigh(lcd5110_data);
		} else {
			pinDigLow(lcd5110_data);
		}
		pinDigHigh(lcd5110_clk);
		data <<= 1;
		__delay_cycles(1);
	}

	LCD5110_DESELECT
}

void lcd5110Clear() {
	lcd5110Gotoxy(0,0);
	    int c = 0;
	    while(c < PCD8544_MAXBYTES) {
	        writeToLCD5110(LCD5110_DATA, 0);
	        c++;
	    }
	    lcd5110Gotoxy(0,0);
}

void lcd5110Gotoxy(uint8_t xAddr, uint8_t yAddr) {
	writeToLCD5110(LCD5110_COMMAND, PCD8544_SETXADDR | xAddr);
	writeToLCD5110(LCD5110_COMMAND, PCD8544_SETYADDR | yAddr);
}

void writeCharToLCD5110(uint8_t c) {
	uint8_t i;
	for (i = 0; i < 5; i++) {
		writeToLCD5110(LCD5110_DATA, font[c - 0x20][i]);
	}
	writeToLCD5110(LCD5110_DATA, 0);
}

void writeStringToLCD5110(const uint8_t message[]) {
	uint8_t i = 0;

	while (message[i] != 0) {
		writeCharToLCD5110(message[i]);
		i++;
	}
}

void clearBankLCD5110(uint8_t bank) {
	lcd5110Gotoxy(0, bank);
	uint8_t c = 0;
	while (c < PCD8544_HPIXELS) {
		writeToLCD5110(LCD5110_DATA, 0);
		c++;
	}
	lcd5110Gotoxy(0, bank);
}

void writeBlockToLCD5110(uint8_t *byte, uint8_t length) {
	uint8_t c = 0;
	while (c < length) {
		writeToLCD5110(LCD5110_DATA, *byte++);
		c++;
	}
}

void lcd5110WriteSetPosition(uint8_t row, uint8_t column, uint8_t exportData) {
	lcd5110Gotoxy(row, column);
	writeCharToLCD5110(exportData);
}

void lcd5110WriteMessage(uint8_t row, uint8_t column, const uint8_t message[]) {
	uint8_t i = 0;
	lcd5110Gotoxy(row, column);

	while (message[i] != 0) {
		writeCharToLCD5110(message[i]);
		i++;
	}
}

void lcd5110PrintInt16(uint16_t varin) {
	uint8_t varBuffer[10] = "Void";
	printInt16((char*)varBuffer, varin);
	writeStringToLCD5110(varBuffer);
}

void lcd5110PrintInt32(uint32_t varin) {
	uint8_t varBuffer[10] = "Void";
	printInt32((char*)varBuffer, varin);
	writeStringToLCD5110(varBuffer);
}

void lcd5110PrintFloat(float varin, uint8_t FracDigits) {
	uint8_t varBuffer[15] = "Void";
	printFloat((char*)varBuffer, varin, FracDigits);
	writeStringToLCD5110(varBuffer);
}