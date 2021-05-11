#include "mod_ds1302.h"

#if defined(Ds1302_Dat)&&defined(Ds1302_Rst)&&defined(Ds1302_Clk)

void writeByteDs1302(uint8_t cmd)
{
 uint8_t i;

 pinModeOutput(Ds1302_Dat);

 for (i = 8; i > 0; i--)
    {
	 if ((cmd & BIT0)==0)
	   { pinDigLow(Ds1302_Dat); }
	 else
	   { pinDigHigh(Ds1302_Dat);  }

	 cmd = cmd >> 1;

	 pinDigHigh(Ds1302_Clk);
	 pinDigLow(Ds1302_Clk);
    }
}

void writeDs1302(uint8_t cmd, uint8_t data)
{
 pinDigHigh(Ds1302_Rst);
 writeByteDs1302(cmd);
 writeByteDs1302(data);
 pinDigLow(Ds1302_Rst);
}

uint8_t readDs1302(uint8_t cmd)
{
 uint8_t i;
 uint8_t data = 0x00;
 uint8_t byte = 0x01;

 pinDigHigh(Ds1302_Rst);
 writeByteDs1302(cmd);

 pinModeInput(Ds1302_Dat);

 for (i = 8; i > 0; i--)
    {
	 if (pinDigRead(Ds1302_Dat))
	   { data |= byte; }

	 byte = byte << 1;

	 pinDigHigh(Ds1302_Clk);
	 pinDigLow(Ds1302_Clk);
    }
 pinDigLow(Ds1302_Rst);

 return(data);
}

void ds1302Init(void)
{
 uint8_t x;

 pinModeOutput(Ds1302_Dat);
 pinModeOutput(Ds1302_Rst);
 pinModeOutput(Ds1302_Clk);

 pinDigLow(Ds1302_Rst);

 delay_us(2);

 pinDigLow(Ds1302_Clk);

 writeDs1302(0x8e,0);
 writeDs1302(0x90,0xa4);

 x=readDs1302(0x81);

 if ((x & 0x80)!=0)
   { writeDs1302(0x80,0); }
}

void ds1302SetDateTime(uint8_t day, uint8_t mth, uint8_t year, uint8_t dow, uint8_t hr, uint8_t min, uint8_t sec)
{
 writeDs1302(0x80,getBcdDs1302(0));
 writeDs1302(0x82,getBcdDs1302(min));
 writeDs1302(0x84,getBcdDs1302(hr));
 writeDs1302(0x86,getBcdDs1302(day));
 writeDs1302(0x88,getBcdDs1302(mth));
 writeDs1302(0x8a,getBcdDs1302(dow));
 writeDs1302(0x8c,getBcdDs1302(year));
}

void ds1302GetDate(uint8_t *day, uint8_t *mth, uint8_t *year, uint8_t *dow)
{
 *day = rmBcdDs1302(readDs1302(0x87));
 *mth = rmBcdDs1302(readDs1302(0x89));
 *year = rmBcdDs1302(readDs1302(0x8d));
 *dow = rmBcdDs1302(readDs1302(0x8b));
}

void ds1302GetTime(uint8_t *hr, uint8_t *min, uint8_t *sec)
{
 *hr = rmBcdDs1302(readDs1302(0x85));
 *min = rmBcdDs1302(readDs1302(0x83));
 *sec = rmBcdDs1302(readDs1302(0x81));
}

uint8_t readNvramDs1302(uint8_t addr)
{
 return(readDs1302(addr|0xc1));
}

void writeNvramDs1302(uint8_t addr, uint8_t value)
{
 writeDs1302(addr|0xc0,value);
}

uint8_t getBcdDs1302(uint8_t data)
{
 uint8_t nibh;
 uint8_t nibl;

 nibh=(uint8_t)(data/10);
 nibl=(uint8_t)(data-(nibh*10));

 return((uint8_t)((nibh<<4)|nibl));
}

uint8_t rmBcdDs1302(uint8_t data)
{
 uint8_t i;

 i=data;
 data=(uint8_t)((i>>4)*10);
 data=(uint8_t)(data+(i&0x0F));

 return data;
}

#endif
