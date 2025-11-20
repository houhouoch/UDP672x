#include "EEPROM_Device.h"

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include <string.h>
#include <stdio.h>

uint16_t eeprom_writeCount = 0;

/* 软件 I2C 引脚配置，根据你的原工程保持不变 */
EEPROM_Dev_Def eeprom =
{
    .i2c = {
        .sda = {ROM_SDA_GPIO_Port, ROM_SDA_Pin},
        .clk = {ROM_SCL_GPIO_Port, ROM_SCL_Pin},
    },
    .addr = 0xA0,   /* AT24C256，A2~A0 都接地时为 0xA0 */
    .bit_fault = 0,
};

/* RTOS / 非 RTOS 下通用的延时 */
// 可能需要增加更多的延时以确保 I2C 信号稳定
void __eeprom_delay(uint16_t time)
{
    for (uint16_t i = 0; i < time; i++) {
        for (volatile uint16_t j = 0; j < 1000; j++) {  // 增加延时
            __NOP();  // 只是做一些空操作来延时
        }
    }
}


/*-------------------- 内部 I2C 辅助函数：16bit 地址写一页 --------------------*/
static uint8_t eeprom_i2c_write16(EEPROM_Dev_Def *dev,
                                  uint16_t mem_addr,
                                  const uint8_t *buf,
                                  uint8_t len)
{
    I2C_Dev_Def *i2c = &dev->i2c;

    /* Start + 设备地址 + 写 */
    i2c_Start(i2c);
    i2c_SendByte(i2c, dev->addr | I2C_WRITE);
    if (i2c_GetAck(i2c))
    {   
        i2c_Stop(i2c);
        return EEPROM_ADDR_NOACK;
    }

    /* 发送高 8 位地址 */
    i2c_SendByte(i2c, (uint8_t)(mem_addr >> 8));
    if (i2c_GetAck(i2c))
    {       
        i2c_Stop(i2c);
        return EEPROM_PAGE_NOACK;
    }

    /* 发送低 8 位地址 */
    i2c_SendByte(i2c, (uint8_t)(mem_addr & 0xFF));
    if (i2c_GetAck(i2c))
    {    
        i2c_Stop(i2c);
        return EEPROM_PAGE_NOACK;
    }

    /* 发送数据 */
    for (uint8_t i = 0; i < len; i++)
    {
        i2c_SendByte(i2c, buf[i]);
        if (i2c_GetAck(i2c))
        {
            i2c_Stop(i2c);
            return EEPROM_DATA_NOACK;
        }
    }

    i2c_Stop(i2c);
    return EEPROM_NO_ERROR;
}


/*-------------------- 内部 I2C 辅助函数：16bit 地址读任意长度 --------------------*/
static uint8_t eeprom_i2c_read16(EEPROM_Dev_Def *dev,
                                 uint16_t mem_addr,
                                 uint8_t *buf,
                                 uint16_t len)
{
    I2C_Dev_Def *i2c = &dev->i2c;

    /* 先写入要读的 16bit 地址 */
    i2c_Start(i2c);
    i2c_SendByte(i2c, dev->addr | I2C_WRITE);
    if (i2c_GetAck(i2c))
    {
        i2c_Stop(i2c);
        return EEPROM_ADDR_NOACK;
    }

    /* 高地址 */
    i2c_SendByte(i2c, (uint8_t)(mem_addr >> 8));
    if (i2c_GetAck(i2c))
    {
        i2c_Stop(i2c);
        return EEPROM_PAGE_NOACK;
    }

    /* 低地址 */
    i2c_SendByte(i2c, (uint8_t)(mem_addr & 0xFF));
    if (i2c_GetAck(i2c))
    {
        i2c_Stop(i2c);
        return EEPROM_PAGE_NOACK;
    }

    /* 重新起始 + 读 */
    i2c_Start(i2c);
    i2c_SendByte(i2c, dev->addr | I2C_READ);
    if (i2c_GetAck(i2c))
    {
        i2c_Stop(i2c);
        return EEPROM_ADDR_NOACK;
    }

    /* 连续读 len 个字节，最后一个发 NACK */
    for (uint16_t i = 0; i < len; i++)
    {
        buf[i] = i2c_ReadByte(i2c);
        if (i != (len - 1))
        {
            i2c_SendAck(i2c, I2C_ACK);
        }
        else
        {
            i2c_SendAck(i2c, I2C_NOACK);
        }
    }

    i2c_Stop(i2c);
    return EEPROM_NO_ERROR;
}

/*-------------------------- 公共 API：写数组（按页拆） --------------------------*/
uint8_t eeprom_WriteArrary(EEPROM_Dev_Def *dev,
                           uint16_t str_addr,
                           uint8_t *pdata,
                           uint16_t write_n)
{
    if (pdata == NULL || write_n == 0)
    {
        return EEPROM_NO_ERROR;
    }

    /* 越界检查（按 32KB ROM） */
    if ((uint32_t)str_addr + (uint32_t)write_n > EEPROM_TOTAL_SIZE)
    {
        return EEPROM_DATA_NOACK;   /* 这里简单返回一个错误码，你也可以新加一个“越界”码 */
    }

    eeprom_writeCount++;

    taskENTER_CRITICAL();
    uint8_t ret = EEPROM_NO_ERROR;

    while (write_n)
    {
        uint8_t page_offset  = (uint8_t)(str_addr % EEPROM_PAGE_SIZE);
        uint8_t page_remain  = (uint8_t)(EEPROM_PAGE_SIZE - page_offset);
        uint8_t this_len     = (write_n < page_remain) ? (uint8_t)write_n : page_remain;

        /* 打印调试信息，确认每个地址和数据 */
      //新加  不然会报错（等待电压稳定）
      __eeprom_delay(1);
      
        ret = eeprom_i2c_write16(dev, str_addr, pdata, this_len);
        if (ret != EEPROM_NO_ERROR)
        {
         //   printf("EEPROM write failed at address 0x%04X, error code: 0x%02X\n", str_addr, ret);
            break;
        }

        /* 每页写完后给 EEPROM 一点时间 */
        __eeprom_delay(5);

        str_addr += this_len;
        pdata    += this_len;
        write_n  -= this_len;
    }

    taskEXIT_CRITICAL();

    return ret;
}

/*-------------------------- 公共 API：读数组 --------------------------*/
/* AT24C 系列顺序读可以跨页，这里简单一次读完 */
uint8_t eeprom_ReadArrary(EEPROM_Dev_Def *dev,
                          uint16_t str_addr,
                          uint8_t *pdata,
                          uint16_t len)
{
    if (pdata == NULL || len == 0)
    {
        return EEPROM_NO_ERROR;
    }

    if ((uint32_t)str_addr + (uint32_t)len > EEPROM_TOTAL_SIZE)
    {
        return EEPROM_DATA_NOACK;
    }

    taskENTER_CRITICAL();
    uint8_t ret = eeprom_i2c_read16(dev, str_addr, pdata, len);
    taskEXIT_CRITICAL();

    return ret;
}

/*-------------------------- 自检函数（保留你的逻辑） --------------------------*/
/**
  * @brief  简单自检：写一段数据到 EEPROM，然后再读出来比对
  * @retval EEPROM_NO_ERROR     一切正常
  *         0xF0                写/读过程返回错误（比如 ACK 出错）
  *         0xF1                数据不一致（写进去和读出来不一样）
  */
uint8_t eeprom_SimpleTest(void)
{
    uint8_t  txBuf[32];
    uint8_t  rxBuf[32];
    uint16_t testAddr = 0x0030;  /* 故意离页边界不远，顺便测试翻页 */

    for (uint16_t i = 0; i < sizeof(txBuf); i++)
    {
        txBuf[i] = (uint8_t)(0x10 + i);
    }

    /* 1. 写入一段数据 */
    uint8_t ret = eeprom_WriteArrary(&eeprom, testAddr, txBuf, sizeof(txBuf));
    if (ret != EEPROM_NO_ERROR)
    {
        printf("EEPROM write error, code: 0x%02X\r\n", ret);
        return 0xF0;
    }

    /* 2. 一点写入时间（其实上面的写每一页已经 delay 了，这里再保险一下） */
   // __eeprom_delay(10);

    /* 3. 读回数据 */
    memset(rxBuf, 0, sizeof(rxBuf));
    ret = eeprom_ReadArrary(&eeprom, testAddr, rxBuf, sizeof(rxBuf));
    if (ret != EEPROM_NO_ERROR)
    {
        printf("EEPROM read error, code: 0x%02X\r\n", ret);
        return 0xF0;
    }

    /* 4. 对比 */
    if (memcmp(txBuf, rxBuf, sizeof(txBuf)) != 0)
    {
        printf("EEPROM verify failed\r\n");
        return 0xF1;
    }

    printf("EEPROM self-test OK\r\n");
    return EEPROM_NO_ERROR;
}
