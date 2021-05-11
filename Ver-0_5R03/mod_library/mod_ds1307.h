/*
 * mod_ds1307.h
 *
 *  Created on: Nov 27, 2017
 *      Author: frcm
 */

#ifndef MOD_LIBRARY_MOD_DS1307_H_
#define MOD_LIBRARY_MOD_DS1307_H_


#include "../mod_user_defs.h"
#include "mod_core.h"
#include "mod_nostdio.h"
#include "mod_i2c.h"

void ds3231Init(void);
void ds3231SetDate(uint8_t *pBuf);
void ds3231GetDate(uint8_t *pBuf);
uint8_t binary2BCD(uint8_t varIn);
uint8_t BCD2Binary(uint8_t varIn);




#endif /* MOD_LIBRARY_MOD_DS1307_H_ */
