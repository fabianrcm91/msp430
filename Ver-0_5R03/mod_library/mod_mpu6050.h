#include <stdint.h>
#include "../mod_user_defs.h"
#include "mod_core.h"
#include "mod_nostdio.h"
#include "mod_i2c.h"

#ifndef MOD_LIBRARY_MOD_MPU6050_H_
#define MOD_LIBRARY_MOD_MPU6050_H_



#define MPU6050_Address 0x68
#define MPU6050_AdAxH   59
#define MPU6050_AdAxL   60
#define MPU6050_AdAyH   61
#define MPU6050_AdAyL   62
#define MPU6050_AdAzH   63
#define MPU6050_AdAzL   64
#define MPU6050_AdTH    63
#define MPU6050_AdTL    64
#define MPU6050_AdGxH   67
#define MPU6050_AdGxL   68
#define MPU6050_AdGyH   69
#define MPU6050_AdGyL   70
#define MPU6050_AdGzH   71
#define MPU6050_AdGzL   72


#define MPU6050_REG_ACCEL_XOFFS_H     (0x06)
#define MPU6050_REG_ACCEL_XOFFS_L     (0x07)
#define MPU6050_REG_ACCEL_YOFFS_H     (0x08)
#define MPU6050_REG_ACCEL_YOFFS_L     (0x09)
#define MPU6050_REG_ACCEL_ZOFFS_H     (0x0A)
#define MPU6050_REG_ACCEL_ZOFFS_L     (0x0B)
#define MPU6050_REG_GYRO_XOFFS_H      (0x13)
#define MPU6050_REG_GYRO_XOFFS_L      (0x14)
#define MPU6050_REG_GYRO_YOFFS_H      (0x15)
#define MPU6050_REG_GYRO_YOFFS_L      (0x16)
#define MPU6050_REG_GYRO_ZOFFS_H      (0x17)
#define MPU6050_REG_GYRO_ZOFFS_L      (0x18)
#define MPU6050_REG_CONFIG            (0x1A)
#define MPU6050_REG_GYRO_CONFIG       (0x1B) // Gyroscope Configuration
#define MPU6050_REG_ACCEL_CONFIG      (0x1C) // Accelerometer Configuration
#define MPU6050_REG_FF_THRESHOLD      (0x1D)
#define MPU6050_REG_FF_DURATION       (0x1E)
#define MPU6050_REG_MOT_THRESHOLD     (0x1F)
#define MPU6050_REG_MOT_DURATION      (0x20)
#define MPU6050_REG_ZMOT_THRESHOLD    (0x21)
#define MPU6050_REG_ZMOT_DURATION     (0x22)
#define MPU6050_REG_INT_PIN_CFG       (0x37) // INT Pin. Bypass Enable Configuration
#define MPU6050_REG_INT_ENABLE        (0x38) // INT Enable
#define MPU6050_REG_INT_STATUS        (0x3A)
#define MPU6050_REG_ACCEL_XOUT_H      (0x3B)
#define MPU6050_REG_ACCEL_XOUT_L      (0x3C)
#define MPU6050_REG_ACCEL_YOUT_H      (0x3D)
#define MPU6050_REG_ACCEL_YOUT_L      (0x3E)
#define MPU6050_REG_ACCEL_ZOUT_H      (0x3F)
#define MPU6050_REG_ACCEL_ZOUT_L      (0x40)
#define MPU6050_REG_TEMP_OUT_H        (0x41)
#define MPU6050_REG_TEMP_OUT_L        (0x42)
#define MPU6050_REG_GYRO_XOUT_H       (0x43)
#define MPU6050_REG_GYRO_XOUT_L       (0x44)
#define MPU6050_REG_GYRO_YOUT_H       (0x45)
#define MPU6050_REG_GYRO_YOUT_L       (0x46)
#define MPU6050_REG_GYRO_ZOUT_H       (0x47)
#define MPU6050_REG_GYRO_ZOUT_L       (0x48)
#define MPU6050_REG_MOT_DETECT_STATUS (0x61)
#define MPU6050_REG_MOT_DETECT_CTRL   (0x69)
#define MPU6050_REG_USER_CTRL         (0x6A) // User Control
#define MPU6050_REG_PWR_MGMT_1        (0x6B) // Power Management 1
#define MPU6050_REG_WHO_AM_I          (0x75) // Who Am I

#define    MPU6050_CLOCK_KEEP_RESET     0b111
#define    MPU6050_CLOCK_EXTERNAL_19MHZ 0b101
#define    MPU6050_CLOCK_EXTERNAL_32KHZ 0b100
#define    MPU6050_CLOCK_PLL_ZGYRO      0b011
#define    MPU6050_CLOCK_PLL_YGYRO      0b010
#define    MPU6050_CLOCK_PLL_XGYRO      0b001
#define    MPU6050_CLOCK_INTERNAL_8MHZ  0b000

#define    MPU6050_SCALE_2000DPS        0b11
#define    MPU6050_SCALE_1000DPS        0b10
#define    MPU6050_SCALE_500DPS         0b01
#define    MPU6050_SCALE_250DPS         0b00

#define    MPU6050_RANGE_16G            0b11
#define    MPU6050_RANGE_8G             0b10
#define    MPU6050_RANGE_4G             0b01
#define    MPU6050_RANGE_2G             0b00

#define    MPU6050_DELAY_3MS            0b11
#define    MPU6050_DELAY_2MS            0b10
#define    MPU6050_DELAY_1MS            0b01
#define    MPU6050_NO_DELAY             0b00

#define    MPU6050_DHPF_HOLD            0b111
#define    MPU6050_DHPF_0_63HZ          0b100
#define    MPU6050_DHPF_1_25HZ          0b011
#define    MPU6050_DHPF_2_5HZ           0b010
#define    MPU6050_DHPF_5HZ             0b001
#define    MPU6050_DHPF_RESET           0b000

#define    MPU6050_DLPF_6               0b110
#define    MPU6050_DLPF_5               0b101
#define    MPU6050_DLPF_4               0b100
#define    MPU6050_DLPF_3               0b011
#define    MPU6050_DLPF_2               0b010
#define    MPU6050_DLPF_1               0b001
#define    MPU6050_DLPF_0               0b000

#define MPU6050_TestX   13
#define MPU6050_TestY   14
#define MPU6050_TestZ   15
#define MPU6050_TestA   16





/*-----------------------------------------------------------------------------*/
/* Constant definitions  */
/*-----------------------------------------------------------------------------*/
#define MPU6050_ADDRESS         0x68 // Address MPU6050 0b01101000  0b10100100
#define MPU6050_XG_OFFS_TC      0x00 //[7] PWR_MODE, [6:1] XG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU6050_YG_OFFS_TC      0x01 //[7] PWR_MODE, [6:1] YG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU6050_ZG_OFFS_TC      0x02 //[7] PWR_MODE, [6:1] ZG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU6050_X_FINE_GAIN     0x03 //[7:0] X_FINE_GAIN
#define MPU6050_Y_FINE_GAIN     0x04 //[7:0] Y_FINE_GAIN
#define MPU6050_Z_FINE_GAIN     0x05 //[7:0] Z_FINE_GAIN
#define MPU6050_XA_OFFS_H       0x06 //[15:0] XA_OFFS
#define MPU6050_XA_OFFS_L_TC    0x07
#define MPU6050_YA_OFFS_H       0x08 //[15:0] YA_OFFS
#define MPU6050_YA_OFFS_L_TC    0x09
#define MPU6050_ZA_OFFS_H       0x0A //[15:0] ZA_OFFS
#define MPU6050_ZA_OFFS_L_TC    0x0B
#define MPU6050_XG_OFFS_USRH    0x13 //[15:0] XG_OFFS_USR
#define MPU6050_XG_OFFS_USRL    0x14
#define MPU6050_YG_OFFS_USRH    0x15 //[15:0] YG_OFFS_USR
#define MPU6050_YG_OFFS_USRL    0x16
#define MPU6050_ZG_OFFS_USRH    0x17 //[15:0] ZG_OFFS_USR
#define MPU6050_ZG_OFFS_USRL    0x18
#define MPU6050_SMPLRT_DIV      0x19
#define MPU6050_CONFIG          0x1A
#define MPU6050_GYRO_CONFIG     0x1B
#define MPU6050_ACCEL_CONFIG    0x1C
#define MPU6050_FF_THR          0x1D
#define MPU6050_FF_DUR          0x1E
#define MPU6050_MOT_THR         0x1F
#define MPU6050_MOT_DUR         0x20
#define MPU6050_ZRMOT_THR       0x21
#define MPU6050_ZRMOT_DUR       0x22
#define MPU6050_FIFO_EN         0x23
#define MPU6050_I2C_MST_CTRL    0x24
#define MPU6050_I2C_SLV0_ADDR   0x25
#define MPU6050_I2C_SLV0_REG    0x26
#define MPU6050_I2C_SLV0_CTRL   0x27
#define MPU6050_I2C_SLV1_ADDR   0x28
#define MPU6050_I2C_SLV1_REG    0x29
#define MPU6050_I2C_SLV1_CTRL   0x2A
#define MPU6050_I2C_SLV2_ADDR   0x2B
#define MPU6050_I2C_SLV2_REG    0x2C
#define MPU6050_I2C_SLV2_CTRL   0x2D
#define MPU6050_I2C_SLV3_ADDR   0x2E
#define MPU6050_I2C_SLV3_REG    0x2F
#define MPU6050_I2C_SLV3_CTRL   0x30
#define MPU6050_I2C_SLV4_ADDR   0x31
#define MPU6050_I2C_SLV4_REG    0x32
#define MPU6050_I2C_SLV4_DO     0x33
#define MPU6050_I2C_SLV4_CTRL   0x34
#define MPU6050_I2C_SLV4_DI     0x35
#define MPU6050_I2C_MST_STATUS  0x36
#define MPU6050_INT_PIN_CFG     0x37
#define MPU6050_INT_ENABLE      0x38
#define MPU6050_DMP_INT_STATUS  0x39
#define MPU6050_INT_STATUS      0x3A
#define MPU6050_ACCEL_XOUT_H    0x3B
#define MPU6050_ACCEL_XOUT_L    0x3C
#define MPU6050_ACCEL_YOUT_H    0x3D
#define MPU6050_ACCEL_YOUT_L    0x3E
#define MPU6050_ACCEL_ZOUT_H    0x3F
#define MPU6050_ACCEL_ZOUT_L    0x40
#define MPU6050_TEMP_OUT_H      0x41
#define MPU6050_TEMP_OUT_L      0x42
#define MPU6050_GYRO_XOUT_H     0x43
#define MPU6050_GYRO_XOUT_L     0x44
#define MPU6050_GYRO_YOUT_H     0x45
#define MPU6050_GYRO_YOUT_L     0x46
#define MPU6050_GYRO_ZOUT_H     0x47
#define MPU6050_GYRO_ZOUT_L     0x48
#define MPU6050_EXT_SENS_DATA_00 0x49
#define MPU6050_EXT_SENS_DATA_01 0x4A
#define MPU6050_EXT_SENS_DATA_02 0x4B
#define MPU6050_EXT_SENS_DATA_03 0x4C
#define MPU6050_EXT_SENS_DATA_04 0x4D
#define MPU6050_EXT_SENS_DATA_05 0x4E
#define MPU6050_EXT_SENS_DATA_06 0x4F
#define MPU6050_EXT_SENS_DATA_07 0x50
#define MPU6050_EXT_SENS_DATA_08 0x51
#define MPU6050_EXT_SENS_DATA_09 0x52
#define MPU6050_EXT_SENS_DATA_10 0x53
#define MPU6050_EXT_SENS_DATA_11 0x54
#define MPU6050_EXT_SENS_DATA_12 0x55
#define MPU6050_EXT_SENS_DATA_13 0x56
#define MPU6050_EXT_SENS_DATA_14 0x57
#define MPU6050_EXT_SENS_DATA_15 0x58
#define MPU6050_EXT_SENS_DATA_16 0x59
#define MPU6050_EXT_SENS_DATA_17 0x5A
#define MPU6050_EXT_SENS_DATA_18 0x5B
#define MPU6050_EXT_SENS_DATA_19 0x5C
#define MPU6050_EXT_SENS_DATA_20 0x5D
#define MPU6050_EXT_SENS_DATA_21 0x5E
#define MPU6050_EXT_SENS_DATA_22 0x5F
#define MPU6050_EXT_SENS_DATA_23 0x60
#define MPU6050_MOT_DETECT_STATUS   0x61
#define MPU6050_I2C_SLV0_DO         0x63
#define MPU6050_I2C_SLV1_DO         0x64
#define MPU6050_I2C_SLV2_DO         0x65
#define MPU6050_I2C_SLV3_DO         0x66
#define MPU6050_I2C_MST_DELAY_CTRL  0x67
#define MPU6050_SIGNAL_PATH_RESET   0x68
#define MPU6050_MOT_DETECT_CTRL     0x69
#define MPU6050_USER_CTRL           0x6A
#define MPU6050_PWR_MGMT_1          0x6B
#define MPU6050_PWR_MGMT_2          0x6C
#define MPU6050_BANK_SEL            0x6D
#define MPU6050_MEM_START_ADDR      0x6E
#define MPU6050_MEM_R_W             0x6F
#define MPU6050_DMP_CFG_1           0x70
#define MPU6050_DMP_CFG_2           0x71
#define MPU6050_FIFO_COUNTH         0x72
#define MPU6050_FIFO_COUNTL         0x73
#define MPU6050_FIFO_R_W            0x74
#define MPU6050_WHO_AM_I            0x75
/*---------- CONFIG VALUE----------*/
/* MPU6050_PWR_MGMT_1 REG */
#define CLKSEL_0 0x00 //Internal 8MHz Osilator
#define CLKSEL_1 0x01 //PLL with X axis gyroscope reference
#define CLKSEL_2 0x02 //PLL with Y axis gyroscope reference
#define CLKSEL_3 0x03 //PLL with Z axis gyroscope reference
#define CLKSEL_4 0x04 //PLL with external 32.768kHz reference
#define CLKSEL_5 0x05 //PLL with external 19.2MHz reference
#define CLKSEL_6 0x06 //Reserved
#define CLKSEL_7 0x07 //Stops the clock and keeps the timing generator in reset

#define TEMP_DIS     (0x01 << 3) //disables the temperature sensor
#define CYCLE        (0x01 << 5) //
#define SLEEP        (0x01 << 6) //
#define DEVICE_RESET (0x01 << 7) //

/*----------MPU6050_CONFIG----------*/
#define EXT_SYNC_SET_INPUT_DISABLE  (0x00 << 3)// Input disabled
#define EXT_SYNC_SET_TEMP_OUT       (0x01 << 3)// TEMP_OUT_L[0]
#define EXT_SYNC_SET_GYRO_XOUT      (0x02 << 3)// GYRO_XOUT_L[0]
#define EXT_SYNC_SET_GYRO_YOUT      (0x03 << 3)// GYRO_YOUT_L[0]
#define EXT_SYNC_SET_GYRO_ZOUT      (0x04 << 3)// GYRO_ZOUT_L[0]
#define EXT_SYNC_SET_ACCEL_XOUT     (0x05 << 3)// ACCEL_XOUT_L[0]
#define EXT_SYNC_SET_ACCEL_YOUT     (0x06 << 3)// ACCEL_YOUT_L[0]
#define EXT_SYNC_SET_ACCEL_ZOUT     (0x07 << 3)// ACCEL_ZOUT_L[0]

#define DLPF_CFG_BAND_WIDTH_260HZ       0x00// BandWidth 260Hz
#define DLPF_CFG_BAND_WIDTH_184HZ       0x01// BandWidth 184Hz
#define DLPF_CFG_BAND_WIDTH_94HZ        0x02// BandWidth 94Hz
#define DLPF_CFG_BAND_WIDTH_44HZ        0x03// BandWidth 44Hz
#define DLPF_CFG_BAND_WIDTH_21HZ        0x04// BandWidth 21Hz
#define DLPF_CFG_BAND_WIDTH_10HZ        0x05// BandWidth 10Hz
#define DLPF_CFG_BAND_WIDTH_5HZ         0x06// BandWidth 5Hz

/*---------MPU6050_GYRO_CONFIG-------*/
#define PS_SEL_SCALE_250    (0x00 << 3)
#define PS_SEL_SCALE_500    (0x01 << 3)
#define PS_SEL_SCALE_1000   (0x02 << 3)
#define PS_SEL_SCALE_2000   (0x03 << 3)

#define ZG_ST   (0x01 << 5)
#define YG_ST   (0x01 << 6)
#define XG_ST   (0x01 << 7)

/*---------MPU6050_ACCEL_CONFIG------*/
#define AFS_SEL_SCALE_2G    (0x00 << 3)
#define AFS_SEL_SCALE_4G    (0x01 << 3)
#define AFS_SEL_SCALE_8G    (0x02 << 3)
#define AFS_SEL_SCALE_16G   (0x03 << 3)

#define ZA_ST   (0x01 << 5)
#define YA_ST   (0x01 << 6)
#define XA_ST   (0x01 << 7)
/*---------MPU6050_SMPLRT_DIV_CONFIG---*/
#define SET_SAMPLE_RATE_1000HZ   0x07













#if mpu6050_Scale==MPU6050_SCALE_250DPS
#define MPU6050_dpsPerDigit 0.007633
#endif
#if mpu6050_Scale==MPU6050_SCALE_500DPS
#define MPU6050_dpsPerDigit 0.015267
#endif
#if mpu6050_Scale==MPU6050_SCALE_1000DPS
#define MPU6050_dpsPerDigit 0.030487
#endif
#if mpu6050_Scale==MPU6050_SCALE_2000DPS
#define MPU6050_dpsPerDigit 0.060975
#endif

#if mpu6050_Range==MPU6050_RANGE_2G
#define MPU6050_rangePerDigit 0.000061
#endif
#if mpu6050_Range==MPU6050_RANGE_4G
#define MPU6050_rangePerDigit 0.000122
#endif
#if mpu6050_Range==MPU6050_RANGE_8G
#define MPU6050_rangePerDigit 0.000244
#endif
#if mpu6050_Range==MPU6050_RANGE_16G
#define MPU6050_rangePerDigit 0.0004882
#endif


void mpu6050Init();
void mpu6050Calibrate(uint16_t *pBuf);
uint8_t mpu6050ReadReg8Bit(uint8_t reg, uint8_t pos);
uint8_t mpu6050ReadReg8(uint8_t regIn);
int16_t mpu6050ReadReg16(uint8_t regIn);
void mpu6050Read(int* pBuf);
void mpu6050ReadA8(uint8_t* pBuf);
void mpu6050NormalizeAccel(int* pBuf,float pBf[3]);
void mpu6050NormalizeGyro(int* pBuf,float pBf[3]);
float mpu6050NormalizeTemp(int* pBuf);
void mpu6050WriteRegBit(uint8_t reg, uint8_t pos, uint8_t state);
void mpu6050WriteReg(uint8_t mpuReg,uint8_t mpuRegValue);
void mpu6050WriteReg16(uint8_t mpuReg,uint16_t mpuRegValue);
void mpu6050SetClockSource(uint8_t source);
void mpu6050SetScale(uint8_t scale);
void mpu6050SetRange(uint8_t range);
void mpu6050SetSleepEnabled(uint8_t state);



#endif /* MOD_LIBRARY_MOD_MPU6050_H_ */
