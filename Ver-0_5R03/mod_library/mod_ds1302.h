#ifndef DS1302MODULE_H_
#define DS1302MODULE_H_

#include "../mod_user_defs.h"
#include "mod_core.h"
#include "mod_nostdio.h"

//===========================================================================================================================

void writeByteDs1302(uint8_t cmd);
void writeDs1302(uint8_t cmd, uint8_t data);
uint8_t readDs1302(uint8_t cmd);

void ds1302Init(void);
void ds1302SetDateTime(uint8_t day, uint8_t mth, uint8_t year, uint8_t dow, uint8_t hr, uint8_t min, uint8_t sec);
void ds1302GetDate(uint8_t *day, uint8_t *mth, uint8_t *year, uint8_t *dow);
void ds1302GetTime(uint8_t *hr, uint8_t *min, uint8_t *sec);

uint8_t readNvramDs1302(uint8_t addr);
void writeNvramDs1302(uint8_t addr, uint8_t value);

//===========================================================================================================================

uint8_t getBcdDs1302(uint8_t data);
uint8_t rmBcdDs1302(uint8_t data);

//===========================================================================================================================

#endif
