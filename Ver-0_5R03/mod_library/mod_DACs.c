/*
 * mod_spi.c
 *
 *  Created on: Apr 7, 2016
 *      Author: semm
 */


#include "mod_DACs.h"


void dacTLV5638Init(void){
    pinModeOutput(DAC_DIN1);pinModeOutput(DAC_SCLK1);pinModeOutput(DAC_CS1);
	pinDigLow(DAC_SCLK1);pinDigHigh(DAC_CS1);pinDigHigh(DAC_DIN1);
}


#ifdef DAC_DIN2
uint16_t dacTLV5638Write2(uint16_t dataToSend){
   	uint8_t var;
         for(var=0;var<16;var++){
             pinDigHigh(DAC_SCLK2);   //clk
             __delay_cycles(DCO_frec_MHz/2 +1);
             if(dataToSend & 0x8000){pinDigHigh(DAC_DIN2);} // simo
             else{pinDigLow(DAC_DIN2); }	//simo

             dataToSend = (dataToSend<<1);
             pinDigLow(DAC_SCLK2);   //low clk

             __delay_cycles(DCO_frec_MHz/2 +1);
         }
         return dataToSend;
}
#endif

 uint16_t dacTLV5638Write(uint16_t dataToSend){
    	uint8_t var;
         for(var=0;var<16;var++){
             pinDigHigh(DAC_SCLK1);   //clk
             __delay_cycles(DCO_frec_MHz/8 +1);
             if(dataToSend & 0x8000){pinDigHigh(DAC_DIN1);} // simo
             else{pinDigLow(DAC_DIN1); }	//simo

             dataToSend = (dataToSend<<1);
             pinDigLow(DAC_SCLK1);   //low clk
             __delay_cycles(DCO_frec_MHz/8 +1);
          }
         return dataToSend;
 }

 void dacTLV5638Load(uint16_t dataDacA,uint16_t dataDacB){

     pinDigLow(DAC_CS1);__delay_cycles(DCO_frec_MHz/4 + 1);
     dacTLV5638Write(TLV_SPD_FAST + TLV_PWR_NORMAL + TLV_REG_CONTROL + TLV_REF_2048); //configuracion de control del DAC -- 0xD002
     __delay_cycles(DCO_frec_MHz/4 + 1);pinDigHigh(DAC_CS1);

     __delay_cycles(DCO_frec_MHz);

     pinDigLow( DAC_CS1 );__delay_cycles(DCO_frec_MHz/4 + 1);
     dacTLV5638Write(TLV_OUT_B +  dataDacB);       // cargar al buffer
     __delay_cycles(DCO_frec_MHz/4 + 1);pinDigHigh(DAC_CS1);

     __delay_cycles(DCO_frec_MHz);
     pinDigLow( DAC_CS1 );__delay_cycles(DCO_frec_MHz/4 + 1);
     dacTLV5638Write(TLV_OUT_A +  dataDacA);       // cargar a salida a y actualiza el buffer
     __delay_cycles(DCO_frec_MHz/4 + 1); pinDigHigh( DAC_CS1 );

 }

