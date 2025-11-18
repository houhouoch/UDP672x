#include "EEPROM_Device.h"
#include "FreeRTOS.h"  // 必须先包含这个
#include "task.h"      // 然后再包含 task.h
#include "cmsis_os.h"   // 如果你在用 CMSIS-RTOS 的 osDelay
#include <string.h>
#include <stdbool.h>

uint16_t eeprom_writeCount = 0;

EEPROM_Dev_Def eeprom =
{
    .i2c = {
        .sda = {ROM_SDA_GPIO_Port, ROM_SDA_Pin},
        .clk = {ROM_SCL_GPIO_Port, ROM_SCL_Pin},
    },
    .addr = 0xA0,
};



// 可能需要增加更多的延时以确保 I2C 信号稳定
void __eeprom_delay(uint16_t time)
{
    for (uint16_t i = 0; i < time; i++) {
        for (volatile uint16_t j = 0; j < 1000; j++) {  // 增加延时
            __NOP();  // 只是做一些空操作来延时
        }
    }
}



/*
 * @brief       uint8_t eeprom_WriteArrary(EEPROM_Dev_Def* eeprom ,uint16_t page,
                            uint8_t* pdata,uint16_t len)
 * @details     向EEPROM写入一组数据
 * @param[in]
 * @param[out]
 * @retval
 */
uint8_t eeprom_WriteArrary(EEPROM_Dev_Def *eeprom, uint16_t str_addr,
                           uint8_t *pdata, uint16_t write_n)
{
    eeprom_writeCount += 1;
    taskENTER_CRITICAL();
    uint8_t result = EEPROM_NO_ERROR;
    const uint8_t *buffer = pdata;

    while(write_n)
    {
        uint8_t  page_write_n = 4;
        if(page_write_n > write_n)
        {
            page_write_n = write_n;
        }

        if(((str_addr) / 64) != ((str_addr + page_write_n) / 64)) {
            page_write_n = ((str_addr + page_write_n) / 64) * 64 - str_addr;
        }
  
        // 重试机制，使用 while 循环代替 goto
        bool retry = true;
        while (retry)
        {
            i2c_Start(&eeprom->i2c);
            i2c_SendByte(&eeprom->i2c, eeprom->addr | I2C_WRITE);
            if(i2c_GetAck(&eeprom->i2c))
            {
                result = EEPROM_ADDR_NOACK;
                i2c_Stop(&eeprom->i2c);
                continue;  // 重试
            }
            retry = false;
        }

        // 发送页地址
        i2c_SendByte(&eeprom->i2c, str_addr >> 8);
        if(i2c_GetAck(&eeprom->i2c))
        {
            result = EEPROM_PAGE_NOACK;
            i2c_Stop(&eeprom->i2c);
            goto ERROR;
        }
        i2c_SendByte(&eeprom->i2c, str_addr & 0xFF);
        if(i2c_GetAck(&eeprom->i2c))
        {
            result = EEPROM_PAGE_NOACK;
            i2c_Stop(&eeprom->i2c);
            goto ERROR;
        }

        // 发送数据
        for(uint16_t i = 0; i < page_write_n; ++i)
        {
            i2c_SendByte(&eeprom->i2c, (*(uint8_t *)(buffer++)));
            if(i2c_GetAck(&eeprom->i2c))
            {
                result = EEPROM_DATA_NOACK;
                goto ERROR;
            }
        }

        i2c_Stop(&eeprom->i2c);
        str_addr += page_write_n;
        write_n  -= page_write_n;
        __eeprom_delay(10);
    }

ERROR:
    taskEXIT_CRITICAL();
    __eeprom_delay(2);
    return result;
}


/*
 * @brief       uint8_t eeprom_ReadArrary(EEPROM_Dev_Def* eeprom ,uint16_t str_addr,
                            uint8_t* pdata,uint16_t len)
 * @details     从EEPROM读取一组数据
 * @param[in]
 * @param[out]
 * @retval
 */
uint8_t eeprom_ReadArrary(EEPROM_Dev_Def *eeprom, uint16_t str_addr,
                          uint8_t *pdata, uint16_t len)
{


    taskENTER_CRITICAL();
    uint8_t result = EEPROM_NO_ERROR;
    {
RETRY:
        i2c_Start(&eeprom->i2c);
        //发送设备地址
        i2c_SendByte(&eeprom->i2c, eeprom->addr | I2C_WRITE);
        if(i2c_GetAck(&eeprom->i2c))
        {
            result = EEPROM_ADDR_NOACK;
            i2c_Stop(&eeprom->i2c);
            goto RETRY;
        }
        //发送页地址
        i2c_SendByte(&eeprom->i2c, str_addr >> 8);
        if(i2c_GetAck(&eeprom->i2c))
        {
            result = EEPROM_PAGE_NOACK;
            goto ERROR;
        }
        i2c_SendByte(&eeprom->i2c, str_addr & 0xFF);
        if(i2c_GetAck(&eeprom->i2c))
        {
            result = EEPROM_PAGE_NOACK;
            goto ERROR;
        }
        i2c_Start(&eeprom->i2c);
        //发送设备地址
        i2c_SendByte(&eeprom->i2c, eeprom->addr | I2C_READ);
        if(i2c_GetAck(&eeprom->i2c))
        {
            result = EEPROM_ADDR_NOACK;
            goto ERROR;
        }
        //读取数据
        for(uint16_t i = 0; i < len; ++i)
        {
            pdata[i] = i2c_ReadByte(&eeprom->i2c);
            if(i != len - 1)
            {
                i2c_SendAck(&eeprom->i2c, I2C_ACK);
            }
            else
            {
                i2c_SendAck(&eeprom->i2c, I2C_NOACK);
            }
        }
    }
ERROR:
    i2c_Stop(&eeprom->i2c);
   taskEXIT_CRITICAL();
    return result;

}


void eeprom_GetValibRom(EEPROM_Dev_Def *eeprom)
{
    uint16_t addr = 2;
    while(1)
    {
        eeprom_WriteArrary(eeprom, addr, (uint8_t *)&addr, 2);
        uint16_t readTemp = 0;
        eeprom_ReadArrary(eeprom, addr, (uint8_t *)&readTemp, 2);
        if(readTemp != addr) {
            while(1) {
                __eeprom_delay(200);
            }
        }
        addr += 2;
        if(addr > 100)
        {
            break;
        }
    }
}


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
    uint16_t testAddr = 0x0030;  // 故意选在页边界附近，顺便测试翻页逻辑

    // 准备测试数据：0x10, 0x11, 0x12, ...
    for(uint16_t i = 0; i < sizeof(txBuf); i++)
    {
        txBuf[i] = (uint8_t)(0x10 + i);
    }

    // 1. 写入一段数据
    uint8_t ret = eeprom_WriteArrary(&eeprom, testAddr, txBuf, sizeof(txBuf));
    if(ret != EEPROM_NO_ERROR)
    {
        printf("EEPROM  write  error\r\n"); 
        return 0xF0;   // 写过程就失败了
    }

    // 给 EEPROM 一点写入时间
    __eeprom_delay(10);

    // 2. 读出刚才那段地址的数据
    memset(rxBuf, 0, sizeof(rxBuf));
    ret = eeprom_ReadArrary(&eeprom, testAddr, rxBuf, sizeof(rxBuf));
    if(ret != EEPROM_NO_ERROR)
    {
       printf("EEPROM  read  error\r\n"); 
        return 0xF0;   // 读过程失败
    }

    // 3. 比对写入的数据和读出的数据
    if(memcmp(txBuf, rxBuf, sizeof(txBuf)) != 0)
    {
         printf("EEPROM  read & write error\r\n"); 
        return 0xF1;   // 数据不一致，说明有问题
    }

    // 一切正常
    return EEPROM_NO_ERROR;
}
