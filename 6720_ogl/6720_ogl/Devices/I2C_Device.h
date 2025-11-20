#ifndef _IIC_DEVICE_H_
#define _IIC_DEVICE_H_

#include "main.h"
#include "GPIO_Device.h"

typedef struct
{
    GPIO_Def clk;
    GPIO_Def sda;
} I2C_Dev_Def;

enum
{
    I2C_ACK = 0,
    I2C_NOACK = 1,
};

#ifndef I2C_WRITE
    #define I2C_WRITE 0
#endif
#ifndef I2C_READ
    #define I2C_READ 1
#endif

//I2C开始信号
void i2c_Start(I2C_Dev_Def *i2c_dev);

//I2C停止信号
void i2c_Stop(I2C_Dev_Def *i2c_dev);

//I2C发送单字节数据
void i2c_SendByte(I2C_Dev_Def *i2c_dev, uint8_t byte);

//I2C接收单字节数据
uint8_t i2c_ReadByte(I2C_Dev_Def *i2c_dev);

//I2C获取ACK信号  1:NOACK  0:ACK
uint8_t i2c_GetAck(I2C_Dev_Def *i2c_dev);

//I2C发送ACK信号  1:NOACK  0:ACK
void i2c_SendAck(I2C_Dev_Def *i2c_dev, uint8_t ack);
void delay(void);
#endif
