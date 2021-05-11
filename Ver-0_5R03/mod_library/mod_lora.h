#ifndef MOD_LIBRARY_MOD_LORA_H_
#define MOD_LIBRARY_MOD_LORA_H_

#include "../mod_user_defs.h"
#include "mod_core.h"
#include "mod_spi.h"
#define REG_FIFO                 0x00
#define REG_OP_MODE              0x01
#define REG_FRF_MSB              0x06
#define REG_FRF_MID              0x07
#define REG_FRF_LSB              0x08
#define REG_PA_CONFIG            0x09
#define REG_LNA                  0x0c
#define REG_FIFO_ADDR_PTR        0x0d
#define REG_FIFO_TX_BASE_ADDR    0x0e
#define REG_FIFO_RX_BASE_ADDR    0x0f
#define REG_FIFO_RX_CURRENT_ADDR 0x10
#define REG_IRQ_FLAGS            0x12
#define REG_RX_NB_BYTES          0x13
#define REG_PKT_SNR_VALUE        0x19
#define REG_PKT_RSSI_VALUE       0x1a
#define REG_MODEM_CONFIG_1       0x1d
#define REG_MODEM_CONFIG_2       0x1e
#define REG_PREAMBLE_MSB         0x20
#define REG_PREAMBLE_LSB         0x21
#define REG_PAYLOAD_LENGTH       0x22
#define REG_MODEM_CONFIG_3       0x26
#define REG_FREQ_ERROR_MSB       0x28
#define REG_FREQ_ERROR_MID       0x29
#define REG_FREQ_ERROR_LSB       0x2a
#define REG_RSSI_WIDEBAND        0x2c
#define REG_DETECTION_OPTIMIZE   0x31
#define REG_DETECTION_THRESHOLD  0x37
#define REG_SYNC_WORD            0x39
#define REG_DIO_MAPPING_1        0x40
#define REG_VERSION              0x42

// modes
#define MODE_LONG_RANGE_MODE     0x80
#define MODE_SLEEP               0x00
#define MODE_STDBY               0x01
#define MODE_TX                  0x03
#define MODE_RX_CONTINUOUS       0x05
#define MODE_RX_SINGLE           0x06
#define sx1278Header_Explicit    0
#define sx1278Header_Implicit    1

// PA config
#define PA_BOOST                 0x80

// IRQ masks
#define IRQ_TX_DONE_MASK           0x08
#define IRQ_PAYLOAD_CRC_ERROR_MASK 0x20
#define IRQ_RX_DONE_MASK           0x40

#define MAX_PKT_LENGTH           255

#define PA_OUTPUT_RFO_PIN          0
#define PA_OUTPUT_PA_BOOST_PIN     1


uint8_t sx1278Init(uint32_t frf);
uint8_t sx1278SpiTrans(uint8_t varIn);
uint8_t sx1278RegWrite(uint8_t regVal, uint8_t valIn);
uint8_t sx1278RegRead(uint8_t regVal);
void sx1278Sleep(void);
void sx1278setFrequency(uint32_t frf);
void sx1278SetTxPower(uint16_t level);
void sx1278SetSpreadingFactor(uint16_t sf);
void sx1278SetSignalBandwidth(uint32_t sbw);
void sx1278SetCodingRate4(uint16_t denominator);
void sx1278SetPreambleLength(uint32_t length);
void sx1278SetSyncWord(uint16_t sw);
void sx1278EnableCrc(void);
void sx1278DisableCrc(void);
void sx1278Idle(void);
uint8_t sx1278SetBeginPacket(uint8_t implicitHeader);
void sx1278ImplicitHeaderMode(void);
void sx1278ExplicitHeaderMode(void);
uint8_t sx1278EndPacket(void);
void sx1278PutBuffer(uint8_t* txBuf,uint16_t txBufSize);
uint16_t sx1278IsDataAvailable(uint16_t size);
uint16_t sx1278GetPacket(uint8_t* rxBuf,uint16_t rxBufSize);
void sx1278SendExplicitPacket(uint8_t* txBuf,uint16_t txBufSize);




#endif /* MOD_LIBRARY_MOD_LORA_H_ */
