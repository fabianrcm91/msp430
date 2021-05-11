#ifndef MOD_LIBRARY_MOD_NRF24L01_H_
#define MOD_LIBRARY_MOD_NRF24L01_H_

#include "../mod_user_defs.h"
#include "mod_core.h"
#include "mod_spi.h"

/** @name - Instruction Set - */
//@{
/* nRF24L01 Instruction Definitions */
#define NRF24L01_WReg        0x20  /**< Register write command */
#define NRF24L01_RRxPload    0x61  /**< Read RX payload command */
#define NRF24L01_WTxPload    0xA0  /**< Write TX payload command */
#define NRF24L01_FlushTx     0xE1  /**< Flush TX register command */
#define NRF24L01_FlushRx     0xE2  /**< Flush RX register command */
#define NRF24L01_Nop         0xFF  /**< No Operation command, used for reading status register */
#define NRF24L01_ReuseTxPl   0xE3  /**< Reuse TX payload command */

#define RD_RX_PLOAD_W        0x60  /**< Read RX payload command */
#define WR_ACK_PLOAD         0xA8  /**< Write ACK payload command */
#define WR_NAC_TX_PLOAD      0xB0  /**< Write ACK payload command */
#define LOCK_UNLOCK          0x50  /**< Lock/unlcok exclusive features */
//@}

/** @name  - Register Memory Map - */
//@{
/* nRF24L01 * Register Definitions * */
#define NRF24L01_Config   0x00  /**< nRF24L01 config register */
#define NRF24L01_EnAA     0x01  /**< nRF24L01 enable Auto-Acknowledge register */
#define NRF24L01_EnRxAd   0x02  /**< nRF24L01 enable RX addresses register */
#define NRF24L01_SetAW    0x03  /**< nRF24L01 setup of address width register */
#define NRF24L01_SetRetr  0x04  /**< nRF24L01 setup of automatic retransmission register */
#define NRF24L01_RfCh     0x05  /**< nRF24L01 RF channel register */
#define NRF24L01_RfSetUp  0x06  /**< nRF24L01 RF setup register */
#define NRF24L01_Status   0x07  /**< nRF24L01 status register */
#define NRF24L01_ObsTx    0x08  /**< nRF24L01 transmit observe register */
#define NRF24L01_CarDet   0x09  /**< nRF24L01 carrier detect register */
#define NRF24L01_RxAdP0   0x0A  /**< nRF24L01 receive address data pipe0 */
#define NRF24L01_RxAdP1   0x0B  /**< nRF24L01 receive address data pipe1 */
#define NRF24L01_RxAdP2   0x0C  /**< nRF24L01 receive address data pipe2 */
#define NRF24L01_RxAdP3   0x0D  /**< nRF24L01 receive address data pipe3 */
#define NRF24L01_RxAdP4   0x0E  /**< nRF24L01 receive address data pipe4 */
#define NRF24L01_RxAdP5   0x0F  /**< nRF24L01 receive address data pipe5 */
#define NRF24L01_TxAd     0x10  /**< nRF24L01 transmit address */
#define NRF24L01_nRxPl0   0x11  /**< nRF24L01 \# of bytes in rx payload for pipe0 */
#define NRF24L01_nRxPl1   0x12  /**< nRF24L01 \# of bytes in rx payload for pipe1 */
#define NRF24L01_nRxPl2   0x13  /**< nRF24L01 \# of bytes in rx payload for pipe2 */
#define NRF24L01_nRxPl3   0x14  /**< nRF24L01 \# of bytes in rx payload for pipe3 */
#define NRF24L01_nRxPl4   0x15  /**< nRF24L01 \# of bytes in rx payload for pipe4 */
#define NRF24L01_nRxPl5   0x16  /**< nRF24L01 \# of bytes in rx payload for pipe5 */
#define NRF24L01_FifoSt   0x17  /**< nRF24L01 FIFO status register */
#define DYNPD             0x1C  /**< nRF24L01 Dynamic payload setup */
#define FEATURE           0x1D  /**< nRF24L01 Exclusive feature setu*/



//CONFIG - 0x00    -> IrqCrcPwrPrimary
#define nRFRegConfig     0x00  /**< nRF24L01 config register */

#define NRF24IntRxOff     BIT6
#define NRF24IntTxOff     BIT5
#define NRF24IntMaxRetOff BIT4
#define NRF24CrcEna       BIT3 //Enable CRC
#define NRF24Crc16Bits    BIT2 // CRC two bytes
#define NRF24PwrUp        BIT1
#define NRF24PrimRx       BIT0
#define NRF24IntRxOn      0x00 //Interrupt reflected on the IRQ pin
#define NRF24IntTxOn      0x00 //Interrupt reflected on the IRQ pin
#define NRF24IntMaxRetOn  0x00 //Interrupt by max number off retries made
#define NRF24CrcDis       0x00
#define NRF24Crc8Bits     0x00 // CRC One Byte
#define NRF24PwrDown      0x00
#define NRF24PrimTx       0x00


#define IrqIntByRxOff   BIT6
#define IrqIntByRxOn    0x00
#define IrqIntByTxOff   BIT5
#define IrqIntByTxOn    0x00
#define IrqIntByMaxRetriesOff BIT4
#define IrqIntByMaxRetriesOn  0x00
#define CrcEnable         BIT3 //Enable CRC
#define CrcDisable        0x00 //Enable CRC
#define Crc16Bits         BIT2 // CRC two bytes
#define Crc8Bits          0x00 // CRC two bytes
#define PwrUp             BIT1
#define PwrDown           0x00
#define PrimaryRxMode     BIT0
#define PrimaryTxMode     0x00


//0x01 EN_AA      ->AutoAck
#define nRFRegEN_AA       0x01  /**< nRF24L01 enable Auto-Acknowledge register */

#define NRF24EnaAAPipe5   BIT5 //Enable Auto Acknowledgment
#define NRF24EnaAAPipe4   BIT4 //Enable Auto Acknowledgment
#define NRF24EnaAAPipe3   BIT3 //Enable Auto Acknowledgment
#define NRF24EnaAAPipe2   BIT2 //Enable Auto Acknowledgment
#define NRF24EnaAAPipe1   BIT1 //Enable Auto Acknowledgment
#define NRF24EnaAAPipe0   BIT0 //Enable Auto Acknowledgment

#define AutoAckForP5   BIT5 //Enable Auto Acknowledgment
#define AutoAckForP4   BIT4 //Enable Auto Acknowledgment
#define AutoAckForP3   BIT3 //Enable Auto Acknowledgment
#define AutoAckForP2   BIT2 //Enable Auto Acknowledgment
#define AutoAckForP1   BIT1 //Enable Auto Acknowledgment
#define AutoAckForP0   BIT0 //Enable Auto Acknowledgment

//0x02 EN_RXADDR  -> Pipes
#define nRFRegEN_RXADDR   0x02

#define NRF24EnaRxPipe5   BIT5 //Enable data pipes
#define NRF24EnaRxPipe4   BIT4 //Enable data pipes
#define NRF24EnaRxPipe3   BIT3 //Enable data pipes
#define NRF24EnaRxPipe2   BIT2 //Enable data pipes
#define NRF24EnaRxPipe1   BIT1 //Enable data pipes
#define NRF24EnaRxPipe0   BIT0 //Enable data pipes

#define Pipe5RxOn   BIT5 //Enable data pipes
#define Pipe4RxOn   BIT4 //Enable data pipes
#define Pipe3RxOn   BIT3 //Enable data pipes
#define Pipe2RxOn   BIT2 //Enable data pipes
#define Pipe1RxOn   BIT1 //Enable data pipes
#define Pipe0RxOn   BIT0 //Enable data pipes

//0x03 SETUP_AW     -> AddressWidth
#define nRFRegSETUP_AW    0x03  /**< nRF24L01 setup of address width register */

#define NRF24AdWidth3B    BIT0 //Setup of Address Widths
#define NRF24AdWidth4B    BIT1 //Setup of Address Widths
#define NRF24AdWidth5B    (BIT1+BIT0) //Setup of Address Widths

#define AddressWidth3B    BIT0 //Setup of Address Widths
#define AddressWidth4B    BIT1 //Setup of Address Widths
#define AddressWidth5B    (BIT1+BIT0) //Setup of Address Widths

//0x04 SETUP_RETR   -> Retries
#define nRFRegSETUP_RETR  0x04  /**< nRF24L01 setup of automatic retransmission register */

#define NRF24RetDelay(n)  ((n)<<4) //250n + 86 usDelay defined from end of transmission to start of next transmission
#define NRF24RetDelay0    0x00 //250n + 86 usDelay defined from end of transmission to start of next transmission
#define NRF24RetCount(n)  (n&(0x0f))// Auto Retransmit Count
#define NRF24RetCount0    0x03//Auto Retransmit Count

#define RetriesDelay(n)   ((n)<<4) //250n + 86 usDelay defined from end of transmission to start of next transmission
#define RetriesDelay0     0x00 //250n + 86 usDelay defined from end of transmission to start of next transmission
#define RetriesCount(n)   (n&(0x0f))// Auto Retransmit Count
#define RetriesCount0     0x03//Auto Retransmit Count

//0x05 RF_CH  -> ChannelF
#define nRFRegRF_CH       0x05  /**< nRF24L01 RF channel register */

#define NRF24ChFreq(n)    (n&(0x7F))//Sets the frequency channel nRF24L01 operates on
#define NRF24ChFreq0      BIT1

#define ChannelFreq(n)    (n&(0x7F))//Sets the frequency channel nRF24L01 operates on
#define ChannelFreq0      BIT1

//0x06 RF_SETUP   -> RatePowerLna
#define nRFRegRF_SETUP    0x06  /**< nRF24L01 RF setup register */

#define NRF24DRate2Mbps   BIT3 // 2MBps
#define NRF24DRate1Mbps   0x00 // 1MBps
#define NRF24Pwr18dBm     0x00 // Set RF output power in TX mode
#define NRF24Pwr12dBm     BIT1 // Set RF output power in TX mode
#define NRF24Pwr6dBm      BIT2 // Set RF output power in TX mode
#define NRF24Pwr0dBm      (BIT2+BIT1) // Set RF output power in TX mode
#define NRF24LnaHcurr     BIT0

#define Rate2Mbps         BIT3 // 2MBps
#define Rate1Mbps         0x00 // 1MBps
#define PowerMinus18dB    0x00 // Set RF output power in TX mode
#define PowerMinus12dB    BIT1 // Set RF output power in TX mode
#define PowerMinus6dB     BIT2 // Set RF output power in TX mode
#define Power0dB          (BIT2+BIT1) // Set RF output power in TX mode
#define LnaGain           BIT0

//0x07 STATUS
#define nRFRegSTATUS      0x07  /**< nRF24L01 status register */

#define NRF24RxDataReady  BIT6 // Data Ready RX FIFO interrupt
#define NRF24TxDataSent   BIT5 // Data Sent TX FIFO interrupt
#define NRF24RetMax       BIT4 // Maximum number of TX retries interrupt
#define NRF24DataFromPipe (BIT3+BIT2+BIT1) //Read Only - Data pipe number for the payload available for reading from RX_FIFO
#define NRF24TxFifoFull   BIT0 // Read Only

#define DataRxReceived    BIT6 // Data Ready RX FIFO interrupt
#define DataTxSent        BIT5 // Data Sent TX FIFO interrupt
#define RetriesDrained    BIT4 // Maximum number of TX retries interrupt
#define DataFromPipe      (BIT3+BIT2+BIT1) //Read Only - Data pipe number for the payload available for reading from RX_FIFO
#define NRF24TxFifoFull   BIT0 // Read Only

//0x08 OBSERVE_TX
#define nRFRegOBSERVE_TX  0x08     /**< nRF24L01 transmit observe register */
#define NRF24PacksLost    0xF0
#define NRF24PacksResent  0x0F

#define PacksLost(y)      ((y&0xF0)>>4)
#define PacksResent(y)    (y&0x0F)

//0x11   RX_PW_P0
#define nRFRegRX_PW_P0 0x11  /**< nRF24L01 \# of bytes in rx payload for pipe0 */


//0x17 FIFO_STATUS
#define nRFRegFIFO_STATUS 0x09  /**< nRF24L01 carrier detect register */

#define NRF24TxReuse      BIT6//Read Only.
#define NRF24TxFull       BIT5//Read Only --- 1: TX FIFO full.   0 :Available locations in TX FIFO.
#define NRF24TxEmpty      BIT4//Read Only --- 1: TX FIFO empty.  0: Data in TX FIFO.
#define NRF24RxFull       BIT1//Read Only --- 1: RX FIFO full.   0 :Available locations in TX FIFO.
#define NRF24RxEmpty      BIT0//Read Only --- 1: RX FIFO empty.  0: Data in TX FIFO.

#define TxReuse      BIT6//Read Only.
#define TxFull       BIT5//Read Only --- 1: TX FIFO full.   0 :Available locations in TX FIFO.
#define TxEmpty      BIT4//Read Only --- 1: TX FIFO empty.  0: Data in TX FIFO.
#define RxFull       BIT1//Read Only --- 1: RX FIFO full.   0 :Available locations in TX FIFO.
#define RxEmpty      BIT0//Read Only --- 1: RX FIFO empty.  0: Data in TX FIFO.






void nrf24l01CEOn();
void nrf24l01CEOff();
void nrf24l01CSNOn();
void nrf24l01CSNOff();


void nrf24l01InitTx(void);
void nrf24l01InitRx(void);

uint8_t nrf24l01SpiTrans(uint8_t varIn);
uint8_t nrf24l01RegWrite(uint8_t regVal, uint8_t valIn);
uint8_t nrf24l01RegRead(uint8_t regVal);
uint8_t nrf24l01BufferWrite(uint8_t regVal,uint8_t *pBuf,uint8_t nBytes);
uint8_t nrf24l01BufferRead (uint8_t regVal,uint8_t *pBuf,uint8_t nBytes);
void nrf24l01ToRx(void);
void nrf24l01ToTx(void);


uint8_t nrf24l01GetPacket(uint8_t* rxBuf);
void nrf24l01PutPacket(uint8_t* txBuf);
void nrf24l01SendPacket(void);
uint8_t nrf24l01HasNewPacket();


// IrqCrcPwrPrimary  AutoAck    Pipes   AddressWidth   Retries    ChannelF    RatePowerLna  TxAddress   RxAddress

void nrf24l01Init(uint8_t IrqCrcPwrPrimary, uint8_t AutoAck, uint8_t Pipes, uint8_t AddressWidth, uint8_t Retries, uint8_t ChannelF, uint8_t RatePowerLna, uint8_t *pBufTxAddress, uint8_t *pBufRxAddress, uint8_t *pBufRxAddress1);

void nrf24l01IrqClear(uint8_t irqReason);
uint8_t nrf24l01IrqGetReasons(void);
uint8_t nrf24l01IrqIfReasonIs(uint8_t irqReason);
void nrf24l01FlushTx(void);
void nrf24l01FlushRx(void);
void nrf24l01CEPulse(void);
void nrf24l01ToPowerDown(void);
void nrf24l01ToStandby(void);


#endif /* MOD_LIBRARY_MOD_NRF24L01_H_ */
