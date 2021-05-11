/*
 * mod_user_defs.h
 *
 *  Created on: Mar 7, 2014
 *      Author: wondartinf-01
 */

#ifndef MOD_USER_DEFS_H_
#define MOD_USER_DEFS_H_

#include "mod_library/mod_pins_io.h"


#define DCO_frec_MHz  16





/*Pin IO Definition*/
#define dLin0     P2_6
#define dLin1     P2_7
#define dLin2     P3_1
#define dLin3     P3_0



///////////////////////////////////////


///////////////////////////////////////
/*PWM Pins*/
#define pinPWM_01 P3_2
#define pinPWM_02 P3_3
#define pinPWM_03 P3_5
#define pinPWM_04 P3_6
///////////////////////////////////////


///////////////////////////////////////
/*Analog Pins*/
/* Se puede reemplazar la definición
 * (Parte Izquierda) a conveniencia
 * Ej:
 * #define PinSensorPresion PinChannelA0
 * #define SensorPresion ChannelA0
 */

#define pinSh00 PinChannelA0
#define pinSh01 PinChannelA1
#define pinSh03 PinChannelA2
#define pinSh02 PinChannelA3
#define pinSh04 PinChannelA4
#define pinSh06 PinChannelA5
#define pinSh07 PinChannelA6
#define pinSh05 PinChannelA7


#define Sh00 ChannelA0
#define Sh01 ChannelA1
#define Sh03 ChannelA2
#define Sh02 ChannelA3
#define Sh04 ChannelA4
#define Sh06 ChannelA5
#define Sh07 ChannelA6
#define Sh05 ChannelA7




#define Pot1 ChannelA3
#define Pot2 ChannelA4
////////////////////////////////////


///////////////////////////////////////
/*LCD*/
#define lcd_rs			P2_6
#define lcd_ena			P2_7
#define lcd_dato4		P3_7
#define lcd_dato5		P3_6
#define lcd_dato6		P3_5
#define lcd_dato7		P2_5
///////////////////////////////////////


///////////////////////////////////////
/*Keypad*/
#define keypad_col1		lcd_dato4//LCD D
#define keypad_col2		lcd_dato6//LCD B
#define keypad_col3		lcd_dato5//LCD
#define keypad_col4		lcd_dato7//LCD
#define keypad_row1		P3_0//Entradas
#define keypad_row2		P3_0//Entradas
#define keypad_row3		P3_0//Entradas
#define keypad_row4		P3_0//Entradas
///////////////////////////////////////


//////////////////////////////////////
/*UART*/

/*
 * Para Uart Por Software:
 * uart_software_tx/uart_software_rx se escogen los pines a conveniencia
 *uart_swd_frec se escribe El Baudrate a trabajar (Solo Por Software)
 */
#define uart_swd_frec 9600//max=>dco_frec_MHz*1000000/uart_s1_frec-14, el resultado debe ser mayor 10
#define uart_software_tx 	P3_7
#define uart_software_rx 	P3_6

/*
 * Para Uart Por Hardware:
 */
/* 
#ifdef __msp430x22x2
#define uart_tx 	P3_4
#define uart_rx 	P3_5
#else
#endif*/
#define uart_tx 	P1_2
#define uart_rx 	P1_1

//////////////////////////////////////
/*
 * SPI Definiciones de pines
 */
#define spi_simo 	P1_2
#define spi_somi 	P1_1
#define spi_clk 	P1_4
#define spi_cs      P2_4


/////////////////////////////////////
/*
 * I2C
 */

#define i2c_sda    P1_7
#define i2c_scl    P1_6



/////////////////////////////////////////
/*
 * NRF24L01
 */
#define NRF2L01_RxPayloadSize 32
#define NRF2L01_TxPayloadSize 32

#define NrfCe       P3_1
#define NrfSck      P1_4  //SPI Hardware
#define NrfMiso     P1_1  //SPI Hardware
#define NrfIrq      P2_0
#define NrfMosi     P1_2  //SPI Hardware
#define NrfCsn      P3_0


///////////////////////////////////////////
/*
 * LCD 5110
 */

#define lcd5110_cs      P2_4
#define lcd5110_dc      P2_5
#define lcd5110_rst     lcd5110_cs
#define lcd5110_data    P3_5
#define lcd5110_clk     P3_6


/////////////////////////////////////////
/*
 * TLV5638
 */

#define tlv5638_sclk     P1_1
#define tlv5638_din      P1_2
#define tlv5638_cs       P1_0


/////////////////////////////////////////
/*
 * LoRa1278
 */
#define sx1278_mosi     P1_7
#define sx1278_miso     P1_6
#define sx1278_sck      P1_5
#define sx1278_nss      P2_0
//#define sx1278_dio0     P2_1// Si se activa este pin, se activan las interrupciones
#define sx1278_rst      P2_2
#define sx1278PTxMax    1


/////////////////////////////////////////
/*
 * DS1302
 */
#define Ds1302_Clk   P1_4
#define Ds1302_Dat   P1_5
#define Ds1302_Rst   P2_0

/////////////////////////////////////////
/*
 * MPU6050
 */


#define mpu6050_sda  i2c_sda
#define mpu6050_scl  i2c_scl
#define mpu6050_Scale   MPU6050_SCALE_2000DPS
#define mpu6050_Range   MPU6050_RANGE_2G
#endif /* MOD_USER_DEFS_H_ */
