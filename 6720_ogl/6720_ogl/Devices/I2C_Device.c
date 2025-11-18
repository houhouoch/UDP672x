#include "I2C_Device.h"

void delay(void)
{
    uint16_t i;
    for(i = 0; i < 100; i++);
}

//I2C开始信号
void i2c_Start(I2C_Dev_Def *i2c_dev)
{
    gpio_set(i2c_dev->clk, 0);
    delay();
    gpio_set(i2c_dev->sda, 1);
    gpio_set(i2c_dev->clk, 1);
    delay();
    gpio_set(i2c_dev->sda, 0);
}

//I2C停止信号
void i2c_Stop(I2C_Dev_Def *i2c_dev)
{
    gpio_set(i2c_dev->clk, 0);
    gpio_set(i2c_dev->sda, 0);
    delay();
    gpio_set(i2c_dev->clk, 1);
    gpio_set(i2c_dev->sda, 1);
}

//I2C发送单字节数据
void i2c_SendByte(I2C_Dev_Def *i2c_dev, uint8_t byte)
{
    uint8_t bit = 0x80;
    for(uint8_t i = 0; i < 8; i++)
    {
        gpio_set(i2c_dev->clk, 0);
        delay();
        gpio_set(i2c_dev->sda, byte & bit);
        delay();
        gpio_set(i2c_dev->clk, 1);
        delay();
        bit >>= 1;
    }
   
}

//I2C接收单字节数据
uint8_t i2c_ReadByte(I2C_Dev_Def *i2c_dev)
{
    uint8_t byte = 0;
    for(uint8_t i = 0; i < 8; ++i)
    {
        byte <<= 1;
        uint8_t bit;
        gpio_set(i2c_dev->clk, 0);
        delay();
        gpio_set(i2c_dev->sda, 1);
        delay();
        gpio_set(i2c_dev->clk, 1);
        delay();
        bit = gpio_get(i2c_dev->sda);
        byte |= bit;
    }
    return byte;
}

//I2C获取ACK信号  1:NOACK  0:ACK
uint8_t i2c_GetAck(I2C_Dev_Def *i2c_dev)
{
    gpio_set(i2c_dev->clk, 0);
    delay();
    gpio_set(i2c_dev->sda, 1);
    delay();
    gpio_set(i2c_dev->clk, 1);
    delay();
    return gpio_get(i2c_dev->sda);
}

//I2C发送ACK信号  1:NOACK  0:ACK
void i2c_SendAck(I2C_Dev_Def *i2c_dev, uint8_t ack)
{
    gpio_set(i2c_dev->clk, 0);
    delay();
    gpio_set(i2c_dev->sda, ack);
    delay();
    gpio_set(i2c_dev->clk, 1);
    delay();
}
