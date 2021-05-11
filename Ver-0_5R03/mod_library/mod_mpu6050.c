#include "mod_mpu6050.h"

void mpu6050Init(){
    i2cUCB0Init(I2C_SingleMaster | I2C_SlaveAddr7Bit | I2C_MasterAddr7Bit | I2C_MasterMode,40,0);

    //mpu6050WriteReg(107,BIT1);delay_ms(1);

    mpu6050WriteReg(MPU6050_PWR_MGMT_1,MPU6050_CLOCK_PLL_XGYRO);

    mpu6050WriteReg(MPU6050_SIGNAL_PATH_RESET,0x07);
    mpu6050WriteReg(MPU6050_PWR_MGMT_1,DEVICE_RESET);
    mpu6050WriteReg(MPU6050_SMPLRT_DIV,SET_SAMPLE_RATE_1000HZ);
    mpu6050WriteReg(MPU6050_CONFIG,EXT_SYNC_SET_INPUT_DISABLE + DLPF_CFG_BAND_WIDTH_10HZ);

    mpu6050WriteReg(MPU6050_ACCEL_CONFIG,mpu6050_Range);
    mpu6050WriteReg(MPU6050_GYRO_CONFIG,mpu6050_Scale);
    mpu6050WriteReg(MPU6050_PWR_MGMT_1,CLKSEL_0);

    delay_ms(1);

    //mpu6050SetClockSource(MPU6050_CLOCK_PLL_XGYRO);
    //mpu6050SetScale(mpu6050_Scale);
    //mpu6050SetRange(mpu6050_Range);
    //mpu6050SetSleepEnabled(0);
    //mpu6050WriteReg(107,BIT1);//Register 107: Power Management 1. PLL with X axis gyroscope reference
    //mpu6050WriteReg(27,0);//Register 27 : Gyroscope Configuration
}
void mpu6050Calibrate(uint16_t *pBuf){

}
uint8_t mpu6050ReadReg8Bit(uint8_t reg, uint8_t pos){
    uint8_t value = mpu6050ReadReg8(reg);
    return ((value >> pos) & 1);
}
uint8_t mpu6050ReadReg8(uint8_t regIn){
    i2cUCB0StartWrite(MPU6050_Address);
    i2cUCB0Write(regIn);
    i2cUCB0StartRead(MPU6050_Address);
    uint8_t xha = i2cUCB0Read();
    i2cUCB0StopEnd();
    return(xha);
}
int16_t mpu6050ReadReg16(uint8_t regIn){
    i2cUCB0StartWrite(MPU6050_Address);
    i2cUCB0Write(regIn);
    i2cUCB0StartRead(MPU6050_Address);
    uint8_t xha = i2cUCB0Read();
    uint8_t xla = i2cUCB0Read();
    i2cUCB0StopEnd();
    return((xha<<8) | xla);

}
void mpu6050Read(int* pBuf){
    i2cUCB0StartWrite(MPU6050_Address);
    i2cUCB0Write(MPU6050_REG_ACCEL_XOUT_H);
    i2cUCB0StartRead(MPU6050_Address);
    uint8_t xha = i2cUCB0Read();
    uint8_t xla = i2cUCB0Read();
    uint8_t yha = i2cUCB0Read();
    uint8_t yla = i2cUCB0Read();
    uint8_t zha = i2cUCB0Read();
    uint8_t zla = i2cUCB0Read();
    uint8_t Tha = i2cUCB0Read();
    uint8_t Tla = i2cUCB0Read();
    pBuf[0] = (xha<<8) | xla;
    pBuf[1] = (yha<<8) | yla;
    pBuf[2] = (zha<<8) | zla;
    xha = i2cUCB0Read();
    xla = i2cUCB0Read();
    yha = i2cUCB0Read();
    yla = i2cUCB0Read();
    zha = i2cUCB0Read();
    zla = i2cUCB0Read();
    pBuf[3] = (xha<<8) | xla;
    pBuf[4] = (yha<<8) | yla;
    pBuf[5] = (zha<<8) | zla;
    pBuf[6] = (Tha<<8) | Tla;
    i2cUCB0StopEnd();
}
void mpu6050ReadA8(uint8_t* pBuf){
    i2cUCB0StartWrite(MPU6050_Address);
    i2cUCB0Write(MPU6050_REG_ACCEL_XOUT_H);
    i2cUCB0StartRead(MPU6050_Address);
    pBuf[0] = i2cUCB0Read();
    pBuf[1] = i2cUCB0Read();
    pBuf[2] = i2cUCB0Read();
    pBuf[3] = i2cUCB0Read();
    pBuf[4] = i2cUCB0Read();
    pBuf[5] = i2cUCB0Read();
    pBuf[12] = i2cUCB0Read();
    pBuf[13] = i2cUCB0Read();
    pBuf[6] = i2cUCB0Read();
    pBuf[7] = i2cUCB0Read();
    pBuf[8] = i2cUCB0Read();
    pBuf[9] = i2cUCB0Read();
    pBuf[10] = i2cUCB0Read();
    pBuf[11] = i2cUCB0Read();
    i2cUCB0StopEnd();
}
void mpu6050NormalizeAccel(int* pBuf,float pBf[3]){

    pBf[0] = ((float) pBuf[0]) * MPU6050_rangePerDigit * 9.80665;
    pBf[1] = ((float) pBuf[1]) * MPU6050_rangePerDigit * 9.80665;
    pBf[2] = ((float) pBuf[2]) * MPU6050_rangePerDigit * 9.80665;
}
void mpu6050NormalizeGyro(int* pBuf,float pBf[3]){
    pBf[0] = ((float) pBuf[3]) * MPU6050_dpsPerDigit;
    pBf[1] = ((float) pBuf[4]) * MPU6050_dpsPerDigit;
    pBf[2] = ((float) pBuf[5]) * MPU6050_dpsPerDigit;
}
float mpu6050NormalizeTemp(int* pBuf){
    return(((float)pBuf[6])/340.0 + 36.53);
}
void mpu6050SetClockSource(uint8_t source){
    uint8_t value;
    value = mpu6050ReadReg8(MPU6050_REG_PWR_MGMT_1);
    value &= 0b11111000;
    value |= source;
    mpu6050WriteReg(MPU6050_REG_PWR_MGMT_1, value);
}

void mpu6050WriteRegBit(uint8_t reg, uint8_t pos, uint8_t state){
    uint8_t value = mpu6050ReadReg8(reg);
    if (state) {
        value |= (1 << pos);
    }else {
        value &= ~(1 << pos);
    }
    mpu6050WriteReg(reg, value);
}
void mpu6050WriteReg(uint8_t mpuReg,uint8_t mpuRegValue){
    i2cUCB0StartWrite(MPU6050_Address);
    i2cUCB0Write(mpuReg);
    i2cUCB0Write(mpuRegValue);
    i2cUCB0Stop();
}
void mpu6050WriteReg16(uint8_t mpuReg,uint16_t mpuRegValue){
    i2cUCB0StartWrite(MPU6050_Address);
    i2cUCB0Write(mpuReg);
    i2cUCB0Write((uint8_t)(mpuRegValue>>8));
    i2cUCB0Write((uint8_t)(mpuRegValue & 0x00FF));
    i2cUCB0Stop();
}
void mpu6050SetScale(uint8_t scale){
    uint8_t value;
    value = mpu6050ReadReg8(MPU6050_REG_GYRO_CONFIG);
    value &= 0b11100111;
    value |= (scale << 3);
    mpu6050WriteReg(MPU6050_REG_GYRO_CONFIG, value);
}
void mpu6050SetRange(uint8_t range){
    uint8_t value;
    value = mpu6050ReadReg8(MPU6050_REG_ACCEL_CONFIG);
    value &= 0b11100111;
    value |= (range << 3);
    mpu6050WriteReg(MPU6050_REG_ACCEL_CONFIG, value);
}
void mpu6050SetSleepEnabled(uint8_t state){
    mpu6050WriteRegBit(MPU6050_REG_PWR_MGMT_1, 6, state);
}

