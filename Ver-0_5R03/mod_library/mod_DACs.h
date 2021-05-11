
#include <stdint.h>
#include "../mod_user_defs.h"
#include "mod_core.h"
#include "mod_usci_xx.h"


#define TLV_SPD_FAST   			0x4000
#define TLV_SPD_LOW    			0x0000
#define TLV_PWR_DOWN   			0x2000
#define TLV_PWR_NORMAL 			0x0000

#define TLV_REG_CONTROL   		0x9000

#define TLV_OUT_A				0x8000
#define TLV_OUT_B				0x1000
#define TLV_OUT_C				0x8000
#define TLV_OUT_D				0x1000

#define TLV_BUFFER				0x1000

#define TLV_REF_EXT				0x0000
#define TLV_REF_1024			0x0001
#define TLV_REF_2048			0x0002

//#define DAC_DIN2 	P2_7
//#define DAC_SCLK2 P3_5
//#define DAC_CS2   P3_3
#define DAC_DIN1	tlv5638_din
#define DAC_SCLK1 	tlv5638_sclk
#define DAC_CS1     tlv5638_cs


void dacTLV5638Init(void);
#ifdef DAC_DIN2
uint16_t dacTLV5638Write2(uint16_t dataToSend);
#endif
uint16_t dacTLV5638Write(uint16_t dataToSend);
void dacTLV5638Load(uint16_t dataDacA,uint16_t dataDacB);

