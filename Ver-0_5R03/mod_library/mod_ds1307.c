/*
 * mod_ds1307.c
 *
 *  Created on: Nov 27, 2017
 *      Author: frcm
 */

#include "mod_ds1307.h"



void ds3231Init(void){
    i2cUCB0Init(I2C_SingleMaster | I2C_SlaveAddr7Bit | I2C_MasterAddr7Bit | I2C_MasterMode,12*DCO_frec_MHz,0);
}
void ds3231SetDate(uint8_t *pBuf){

    i2cUCB0StartWrite(0x68);
    i2cUCB0Write(0x00);
    i2cUCB0Write(binary2BCD(pBuf[0]));//Seg
    i2cUCB0Write(binary2BCD(pBuf[1]));//Min
    i2cUCB0Write(0x3F & binary2BCD(pBuf[2]));//Hora
    i2cUCB0Write(binary2BCD(pBuf[3]));//DOW
    i2cUCB0Write(binary2BCD(pBuf[4]));//Day
    i2cUCB0Write(binary2BCD(pBuf[5]));//Mo
    i2cUCB0Write(binary2BCD(pBuf[6]));//Ye

    i2cUCB0Write(0x10);
    i2cUCB0Stop();
}
void ds3231GetDate(uint8_t *pBuf){
    i2cUCB0StartWrite(0x68);
    i2cUCB0Write(0x00);
    i2cUCB0StartRead(0x68);

    pBuf[0] = BCD2Binary(i2cUCB0Read());//seg
    pBuf[1] = BCD2Binary(i2cUCB0Read());//min
    pBuf[2] = BCD2Binary(0x3F & i2cUCB0Read());//ho
    pBuf[3] = BCD2Binary(0x07 & i2cUCB0Read());//dow
    pBuf[4] = BCD2Binary(0x3F & i2cUCB0Read());//day
    pBuf[5] = BCD2Binary(0x1F & i2cUCB0Read());//mo
    pBuf[6] = BCD2Binary(i2cUCB0Read());//ye

    //i2cUCB0Stop();


    // para que funcione en proteus
    UCB0CTL1 |= UCTXNACK;
    i2cUCB0Stop();
    i2cUCB0Read();
    delay_us(1);
    i2cUCB0Stop();

}
uint8_t binary2BCD(uint8_t varIn){
    return (((varIn / 10) << 4) & 0xF0) | ((varIn % 10) & 0x0F);
}
uint8_t BCD2Binary(uint8_t varIn){
    return ((varIn & 0x0F) + (((varIn & 0xF0) >> 4) * 10));
}
