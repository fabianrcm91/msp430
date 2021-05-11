

#include "mod_i2c.h"

void i2cUCB0Init(uint8_t regConf, uint8_t clkDiv,uint8_t addressOwn){
      /*
       *i2cUCB0Init(I2C_SingleMaster | I2C_SlaveAddr7Bit | I2C_MasterAddr7Bit | I2C_MasterMode,160,0);
       */
      pinEnaFunc01(i2c_scl);pinEnaFunc01(i2c_sda);

      bitHigh(UCB0CTL1, UCSSEL_2| UCSWRST);
      UCB0CTL0 = regConf + UCMODE_3 + UCSYNC;  //
      UCB0BR0 |= clkDiv;                          //
      UCB0BR1 = 0;                              //
      UCB0I2COA = addressOwn;
      UCB0I2CSA = 0;                         // Set slave address
      UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}

uint8_t i2cUCB0Write(uint8_t varIn){
    while((UCB0STAT & BUSY)!=0);
    UCB0TXBUF = varIn;
    while((IFG2 & UCB0TXIFG) == 0);
    if(UCB0STAT & UCNACKIFG)
        return 0;
    else
        return 1;
}
uint8_t i2cUCB0Read(void){
    while((UCB0STAT & BUSY)!=0);
    while((IFG2 & UCB0RXIFG) == 0);  //IntFlagRegister is set when TxBuffer is empty
    return(UCB0RXBUF);
}
void i2cUCB0StartWrite(uint8_t slaveAddress){
    while((UCB0STAT & BUSY)!=0);
    UCB0I2CSA = slaveAddress;
    UCB0CTL1 |= (UCTR + UCTXSTT);       //i2c TX, Start Condition
}
void i2cUCB0StartRead(uint8_t slaveAddress){
    while((UCB0STAT & BUSY)!=0);
    UCB0I2CSA = slaveAddress;
    UCB0CTL1 &= ~UCTR;      //i2cRx
    UCB0CTL1 |= UCTXSTT;    //Start Condition
}
void i2cUCB0Stop(void){
    while((UCB0STAT & BUSY)!=0);
    UCB0CTL1 |= UCTXSTP;
}
void i2cUCB0StopEnd(void){
    UCB0CTL1 |= UCTXNACK;
    i2cUCB0Stop();
    i2cUCB0Read();
    __delay_cycles(DCO_frec_MHz);
    i2cUCB0Stop();
}
