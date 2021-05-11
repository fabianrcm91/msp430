#include "mod_lora.h"


uint8_t sx1278SpiTrans(uint8_t varIn){
    uint8_t varOut=spiUCB0Transfer(varIn);
    return(varOut);
}
uint8_t sx1278Init(uint32_t frf){
    //frf=f_RF*0.016384=32E6/2^19

    pinModeOutput(sx1278_nss);pinDigHigh(sx1278_nss);
    pinModeOutput(sx1278_rst);pinDigLow(sx1278_rst);delay_ms(10);pinDigHigh(sx1278_rst);delay_ms(10);

#ifdef sx1278_dio0
    pinModeInput(sx1278_dio0);pinEnaIntHighLow(sx1278_dio0);
#endif

    ///Puede cambiar y usar UCA0
    spiUCB0Init(FIRST_CAPTURE + IDDLE_LOW + MSB_FIRST + MODE_MASTER + DATA_8BITS, 16);

    uint8_t version=0;
    version = sx1278RegRead(REG_VERSION);
    if (version != 0x12) {
      return 0;
    }
    sx1278Sleep();
    sx1278setFrequency(frf);
    // set base addresses
    sx1278RegWrite(REG_FIFO_TX_BASE_ADDR, 0);
    sx1278RegWrite(REG_FIFO_RX_BASE_ADDR, 0);
    // set LNA boost
    sx1278RegWrite(REG_LNA, sx1278RegRead(REG_LNA) | 0x03);
    // set auto AGC
    sx1278RegWrite(REG_MODEM_CONFIG_3, 0x04);
    // set output power to 17 dBm
    sx1278SetTxPower(17);
    // put in standby mode
    sx1278Idle();
    return 1;
}
uint8_t sx1278RegWrite(uint8_t regVal, uint8_t valIn){
    pinDigLow(sx1278_nss);
    sx1278SpiTrans(0x80 | regVal);
    uint8_t status = sx1278SpiTrans(valIn);
    pinDigHigh(sx1278_nss);
    return (status);
}
uint8_t sx1278RegRead(uint8_t regVal){
    pinDigLow(sx1278_nss);
    sx1278SpiTrans(0x7f & regVal);
    uint8_t regValue = sx1278SpiTrans(0);
    pinDigHigh(sx1278_nss);
    return (regValue);
}
void sx1278Sleep(void){
    sx1278RegWrite(REG_OP_MODE, MODE_LONG_RANGE_MODE | MODE_SLEEP);
}
void sx1278setFrequency(uint32_t frf){
    //frf=f_RF*0.016384=32E6/2^19

    sx1278RegWrite(REG_FRF_MSB, (uint8_t)((frf >> 16)&0xff));
    sx1278RegWrite(REG_FRF_MID, (uint8_t)((frf >> 8)&0xff));
    sx1278RegWrite(REG_FRF_LSB, (uint8_t)((frf >> 0)&0xff));
}

void sx1278SetTxPower(uint16_t level){
#if sx1278PTxMax==1
    //uint8_t outputPin = PA_OUTPUT_PA_BOOST_PIN;
    // PA BOOST
    if (level < 2){
      level = 2;
    }else if (level > 17){
      level = 17;
    }
    sx1278RegWrite(REG_PA_CONFIG, PA_BOOST | (level - 2));
#endif
#if sx1278PTxMax==0
    //uint8_t outputPin = PA_OUTPUT_RFO_PIN;
    // RFO
    if (level < 0){
      level = 0;
    }else if (level > 14){
      level = 14;
    }
    sx1278RegWrite(REG_PA_CONFIG, 0x70 | level);
#endif

}
void sx1278SetSpreadingFactor(uint16_t sf){

}
void sx1278SetSignalBandwidth(uint32_t sbw){

}
void sx1278SetCodingRate4(uint16_t denominator){

}
void sx1278SetPreambleLength(uint32_t length){

}

void sx1278SetSyncWord(uint16_t sw){
    sx1278RegWrite(REG_SYNC_WORD, sw);
}
void sx1278EnableCrc(void){

}
void sx1278DisableCrc(void){

}

void sx1278Idle(void){
    sx1278RegWrite(REG_OP_MODE, MODE_LONG_RANGE_MODE | MODE_STDBY);
}

uint8_t sx1278BeginPacket(uint8_t implicitHeader){
  // put in standby mode
    sx1278Idle();
    if (implicitHeader) {
        sx1278ImplicitHeaderMode();
    }else{
        sx1278ExplicitHeaderMode();
    }
    // reset FIFO address and paload length
    sx1278RegWrite(REG_FIFO_ADDR_PTR, 0);
    sx1278RegWrite(REG_PAYLOAD_LENGTH, 0);
  return 1;
}
void sx1278ImplicitHeaderMode(void){
    sx1278RegWrite(REG_MODEM_CONFIG_1, sx1278RegRead(REG_MODEM_CONFIG_1) | 0x01);
}
void sx1278ExplicitHeaderMode(void){
    sx1278RegWrite(REG_MODEM_CONFIG_1, sx1278RegRead(REG_MODEM_CONFIG_1) & 0xfe);
}
uint8_t sx1278EndPacket(void){
    sx1278RegWrite(REG_OP_MODE, MODE_LONG_RANGE_MODE | MODE_TX);// put in TX mode
    while ((sx1278RegRead(REG_IRQ_FLAGS) & IRQ_TX_DONE_MASK) == 0) {}// wait for TX done
    sx1278RegWrite(REG_IRQ_FLAGS, IRQ_TX_DONE_MASK);// clear IRQ's
    return 1;
}
void sx1278PutBuffer(uint8_t* txBuf,uint16_t txBufSize){
    // txBufSize no puede ser mayor a 255
    if (txBufSize>MAX_PKT_LENGTH) {
        txBufSize = MAX_PKT_LENGTH;
    }
    uint16_t i=0;
    for (i = 0; i < txBufSize; i++) {
        sx1278RegWrite(REG_FIFO, txBuf[i]);
    }
    sx1278RegWrite(REG_PAYLOAD_LENGTH,txBufSize);
}

uint16_t sx1278IsDataAvailable(uint16_t size){
    uint16_t packetLength = 0;
    uint16_t irqFlags = sx1278RegRead(REG_IRQ_FLAGS);
    uint8_t _implicitHeaderMode = 0;
    if (size > 0) {
        _implicitHeaderMode = 1;
        sx1278ImplicitHeaderMode();
        sx1278RegWrite(REG_PAYLOAD_LENGTH, size & 0xff);
    } else {
        _implicitHeaderMode = 0;
        sx1278ExplicitHeaderMode();
    }
    // clear IRQ's
    sx1278RegWrite(REG_IRQ_FLAGS, irqFlags);
    if ((irqFlags & IRQ_RX_DONE_MASK) && (irqFlags & IRQ_PAYLOAD_CRC_ERROR_MASK) == 0) {
        // read packet length
        if (_implicitHeaderMode) {
          packetLength = sx1278RegRead(REG_PAYLOAD_LENGTH);
        } else {
          packetLength = sx1278RegRead(REG_RX_NB_BYTES);
        }
        // set FIFO address to current RX address
        sx1278RegWrite(REG_FIFO_ADDR_PTR, sx1278RegRead(REG_FIFO_RX_CURRENT_ADDR));
        sx1278Idle();
    } else if (sx1278RegRead(REG_OP_MODE) != (MODE_LONG_RANGE_MODE | MODE_RX_SINGLE)) {
        // not currently in RX mode
        sx1278RegWrite(REG_FIFO_ADDR_PTR, 0);// reset FIFO address
        sx1278RegWrite(REG_OP_MODE, MODE_LONG_RANGE_MODE | MODE_RX_SINGLE);// put in single RX mode
    }
    return packetLength;
}

uint16_t sx1278GetPacket(uint8_t* rxBuf,uint16_t rxBufSize){
    if (rxBufSize) {
        uint16_t i=0;
        for (i = 0; i < rxBufSize; i++) {
            rxBuf[i] = sx1278RegRead(REG_FIFO);
        }
        return(1);
    }else{
        return(0);
    }
}
void sx1278SendExplicitPacket(uint8_t* txBuf,uint16_t txBufSize){
    sx1278BeginPacket(sx1278Header_Explicit);
    sx1278PutBuffer(txBuf, txBufSize);
    sx1278EndPacket();
}
