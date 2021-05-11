#include "mod_nrf24l01.h"

uint8_t NRF24L01AddressTx[5]  = "NRF00";
uint8_t NRF24L01AddressRx0[5] = "NRF00";
uint8_t NRF24L01AddressRx1[5] = "NRF01";
uint8_t NRF24L01AddressRx2    =     '2';
uint8_t NRF24L01AddressRx3    =     '3';
uint8_t NRF24L01AddressRx4    =     '4';
uint8_t NRF24L01AddressRx5    =     '5';


void nrf24l01SpiInit(){
    spiUCA0Init(FIRST_CAPTURE + IDDLE_LOW + MSB_FIRST + MODE_MASTER + DATA_8BITS, 2);
    pinModeOutput(NrfCe);pinModeOutput(NrfCsn);
    pinModeInput(NrfIrq);pinEnaIntLowHigh(NrfIrq);
    pinDigHigh(NrfCsn);pinDigLow(NrfCe);
}

void nrf24l01CSNOn(){
    pinDigHigh(NrfCsn);
}
void nrf24l01CSNOff(){
    pinDigLow(NrfCsn);
}
void nrf24l01CEOn(){
    pinDigHigh(NrfCe);
}
void nrf24l01CEOff(){
    pinDigLow(NrfCe);
}
uint8_t nrf24l01SpiTrans(uint8_t varIn){
    uint8_t varOut=spiUCA0Transfer(varIn);

    return(varOut);
}

uint8_t nrf24l01RegWrite(uint8_t regVal, uint8_t valIn){
    nrf24l01CSNOff();
    uint8_t status=nrf24l01SpiTrans(regVal);
    nrf24l01SpiTrans(valIn);
    nrf24l01CSNOn();
    return (status);
}
uint8_t nrf24l01RegRead(uint8_t regVal){
    nrf24l01CSNOff();
    nrf24l01SpiTrans(regVal);
    uint8_t regValue = nrf24l01SpiTrans(0);
    nrf24l01CSNOn();
    return (regValue);
}
uint8_t nrf24l01BufferWrite(uint8_t regVal,uint8_t *pBuf,uint8_t nBytes){
    uint8_t cntByte=0;
    nrf24l01CSNOff();// Set CSN low, init SPI tranaction
    uint8_t status=nrf24l01SpiTrans(NRF24L01_WReg | regVal);// Select register to write to and read status byte
    for (cntByte = 0; cntByte < nBytes; cntByte++) {
        nrf24l01SpiTrans(*pBuf++);
    }
    nrf24l01CSNOn();
    return(status);
}
uint8_t nrf24l01BufferRead (uint8_t regVal,uint8_t *pBuf,uint8_t nBytes){
    uint8_t cntByte=0;
    nrf24l01CSNOff();// Set CSN low, init SPI tranaction
    uint8_t status=nrf24l01SpiTrans(regVal);// Select register to write to and read status byte
    for (cntByte = 0; cntByte < nBytes; cntByte++) {
        pBuf[cntByte] = nrf24l01SpiTrans(0x00);
    }
    nrf24l01CSNOn();
    return(status);
}


void nrf24l01InitTx(void){
    nrf24l01SpiInit();delay_ms(1);
    nrf24l01CSNOn();
    nrf24l01CEOff();
    nrf24l01BufferWrite(NRF24L01_TxAd,NRF24L01AddressTx,5);
    nrf24l01BufferWrite(NRF24L01_RxAdP0,NRF24L01AddressRx0,5);
    nrf24l01RegWrite(NRF24L01_EnAA,NRF24EnaAAPipe0);
    nrf24l01RegWrite(NRF24L01_EnRxAd,NRF24EnaRxPipe0);
    //nrf24l01RegWrite(NRF24L01_SetRetr,NRF24RetDelay(5) + NRF24RetCount(4));
    nrf24l01RegWrite(NRF24L01_RfCh,NRF24ChFreq(1));
    nrf24l01RegWrite(NRF24L01_RfSetUp,NRF24DRate1Mbps + NRF24Pwr0dBm + NRF24LnaHcurr);
    nrf24l01RegWrite(NRF24L01_nRxPl0,NRF2L01_RxPayloadSize);
    nrf24l01RegWrite(NRF24L01_Config,NRF24CrcEna + NRF24Crc16Bits + NRF24PwrUp + NRF24PrimTx);
}



uint8_t nrf24l01GetPacket(uint8_t* rxBuf){
    uint8_t varOut=0;
    if (nrf24l01RegRead(nRFRegSTATUS) & NRF24RxDataReady){
        nrf24l01CEOff();
        nrf24l01BufferRead(NRF24L01_RRxPload, rxBuf, NRF2L01_RxPayloadSize);
        nrf24l01CEOn();varOut = 1;
    }
    nrf24l01IrqClear(0x70);nrf24l01FlushRx();
    return (varOut);
}

void nrf24l01PutPacket(uint8_t* txBuf){
    if (nrf24l01RegRead(nRFRegSTATUS) & NRF24RetMax) {
        nrf24l01RegWrite(NRF24L01_WReg | nRFRegSTATUS,0x70);nrf24l01FlushTx();
    }
    nrf24l01BufferWrite(NRF24L01_WTxPload, txBuf, NRF2L01_TxPayloadSize);
    nrf24l01CEPulse();
}
void nrf24l01SendPacket(void){
    nrf24l01CEPulse();
}

uint8_t nrf24l01HasNewPacket(){
    return(nrf24l01RegRead(NRF24L01_Status) & NRF24RxDataReady);
}

void nrf24l01Init(uint8_t IrqCrcPwrPrimary, uint8_t AutoAck, uint8_t Pipes, uint8_t AddressWidth, uint8_t Retries, uint8_t ChannelF, uint8_t RatePowerLna, uint8_t *pBufTxAddress, uint8_t *pBufRxAddress, uint8_t *pBufRxAddress1){
    /*
     *
    nrf24l01Init(IrqIntByMaxRetriesOff | IrqIntByRxOn | IrqIntByTxOff | PwrUp | PrimaryRxMode,
                  AutoAckForP0,
                  Pipe0RxOn,
                  AddressWidth5B,
                  RetriesCount(10) | RetriesDelay(5),
                  ChannelFreq(5),
                  Rate1Mbps | PowerMinus6dB,
                  "NRF00",  // Address for Tx
                  "NRF00",  // Address for Rx pipe 0
                  "NRF01"); // Address for Rx pipe 1

     To Use:
     Rx: nrf24l01GetPacket(bufferIn);
     Tx: nrf24l01PutPacket(bufferOut);
     *
     *
     *
     */

    nrf24l01SpiInit();
    nrf24l01CSNOn();
    nrf24l01CEOff();
    delay_ms(12);
    nrf24l01IrqClear(0x70);// Forget any outstanding IRQs

    nrf24l01RegWrite(NRF24L01_WReg | nRFRegEN_RXADDR, 0x00);//Reset All Pipes
    nrf24l01RegWrite(NRF24L01_WReg | nRFRegEN_AA, 0x00); // Reset All Pipes
    delay_ms(10);

    nrf24l01RegWrite(NRF24L01_WReg | nRFRegEN_AA,AutoAck);
    nrf24l01RegWrite(NRF24L01_WReg | nRFRegEN_RXADDR,Pipes);
    nrf24l01RegWrite(NRF24L01_WReg | nRFRegSETUP_AW,AddressWidth);
    nrf24l01RegWrite(NRF24L01_WReg | nRFRegSETUP_RETR,Retries);
    nrf24l01RegWrite(NRF24L01_WReg | nRFRegRF_CH,ChannelF);
    nrf24l01RegWrite(NRF24L01_WReg | nRFRegRF_SETUP,RatePowerLna);
    nrf24l01RegWrite(NRF24L01_WReg | nRFRegRX_PW_P0  ,NRF2L01_RxPayloadSize);
    nrf24l01RegWrite(NRF24L01_WReg | nRFRegRX_PW_P0+1,NRF2L01_RxPayloadSize);
    nrf24l01RegWrite(NRF24L01_WReg | nRFRegRX_PW_P0+2,NRF2L01_RxPayloadSize);
    nrf24l01RegWrite(NRF24L01_WReg | nRFRegRX_PW_P0+3,NRF2L01_RxPayloadSize);
    nrf24l01RegWrite(NRF24L01_WReg | nRFRegRX_PW_P0+4,NRF2L01_RxPayloadSize);
    nrf24l01RegWrite(NRF24L01_WReg | nRFRegRX_PW_P0+5,NRF2L01_RxPayloadSize);

    uint8_t adSize = AddressWidth + 2;
    uint8_t adPos  = AddressWidth + 1;

    nrf24l01BufferWrite(NRF24L01_TxAd  , pBufTxAddress, adSize);
    nrf24l01BufferWrite(NRF24L01_RxAdP0, pBufRxAddress, adSize);
    nrf24l01BufferWrite(NRF24L01_RxAdP1, pBufRxAddress1, adSize);

    uint8_t np = pBufRxAddress1[adPos];

    nrf24l01RegWrite(NRF24L01_WReg | NRF24L01_RxAdP2,np + 1);
    nrf24l01RegWrite(NRF24L01_WReg | NRF24L01_RxAdP3,np + 2);
    nrf24l01RegWrite(NRF24L01_WReg | NRF24L01_RxAdP4,np + 3);
    nrf24l01RegWrite(NRF24L01_WReg | NRF24L01_RxAdP5,np + 4);


    nrf24l01RegWrite(NRF24L01_WReg | nRFRegConfig,IrqCrcPwrPrimary);

    if (IrqCrcPwrPrimary & PrimaryRxMode) {
        nrf24l01CEOn();
    }

    delay_ms(2);//datasheet suggest 130uS With external cristal, or 1.5ms for internal crystal

}

void nrf24l01IrqClear(uint8_t irqReason){
    nrf24l01CSNOff();
    uint8_t varStatus = nrf24l01SpiTrans(NRF24L01_WReg | nRFRegSTATUS);
    nrf24l01SpiTrans(varStatus | irqReason);
    nrf24l01CSNOn();
}
uint8_t nrf24l01IrqGetReasons(void){
    return(nrf24l01RegRead(NRF24L01_Status));
}

uint8_t nrf24l01IrqIfReasonIs(uint8_t irqReason){
    uint8_t varOut=0;
    if(nrf24l01IrqGetReasons() & irqReason){
        varOut = 0;
    }else {
        varOut = 1;
    }
    return (varOut);
}
void nrf24l01FlushTx(void) {
    nrf24l01CSNOff();
    nrf24l01SpiTrans(NRF24L01_FlushTx);
    nrf24l01CSNOn();
}
void nrf24l01FlushRx(void) {
    nrf24l01CSNOff();
    nrf24l01SpiTrans(NRF24L01_FlushRx);
    nrf24l01CSNOn();
}
void nrf24l01CEPulse(void) {
    pinDigHigh(NrfCe);
    __delay_cycles(15*DCO_frec_MHz);
    pinDigLow(NrfCe);
}

void nrf24l01ToRx(void){
    nrf24l01CEOff();
    nrf24l01FlushRx();
    nrf24l01IrqClear(0x70);
    uint8_t conf0 = nrf24l01RegRead(NRF24L01_Config);
    nrf24l01RegWrite(NRF24L01_WReg | NRF24L01_Config,bitHigh(conf0,PrimaryRxMode|NRF24PwrUp));
    nrf24l01CEOn();
    __delay_cycles(135*DCO_frec_MHz);// 135us From Standy by To Tx mode
}
void nrf24l01ToTx(void){
    nrf24l01CEOff();
    nrf24l01FlushTx();
    nrf24l01IrqClear(0x70);
    uint8_t conf0 = nrf24l01RegRead(NRF24L01_Config);
    nrf24l01RegWrite(NRF24L01_WReg | NRF24L01_Config,(bitLow(conf0,PrimaryRxMode))|NRF24PwrUp);
    __delay_cycles(135*DCO_frec_MHz);// 135us From Standy by To Tx mode
}
void nrf24l01ToStandby(void){
    nrf24l01CEOff();
    uint8_t conf0 = nrf24l01RegRead(NRF24L01_Config);
    nrf24l01RegWrite(NRF24L01_WReg | NRF24L01_Config, bitHigh(conf0,NRF24PwrUp));
    __delay_cycles(135*DCO_frec_MHz);// 135us From Standy by To Tx mode
}
void nrf24l01ToPowerDown(void){
    nrf24l01CEOff();
    uint8_t conf0 = nrf24l01RegRead(NRF24L01_Config);
    nrf24l01RegWrite(NRF24L01_WReg | NRF24L01_Config, bitLow(conf0,NRF24PwrUp));
    delay_ms(2);
}
