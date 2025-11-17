#include "EEPROM_Device.h"
#include "Task_Manager.h"

uint16_t eeprom_writeCount = 0;
extern osMutexId_t I2C_MutexHandle;
EEPROM_Dev_Def eeprom =
{
    .i2c = {
        .sda = {I2C_SDA_GPIO_Port, I2C_SDA_Pin},
        .clk = {I2C_SCL_GPIO_Port, I2C_SCL_Pin},
    },
    .addr = 0xA0,
};

static void __eeprom_delay(uint16_t time)
{
    if(xTaskGetSchedulerState() == taskSCHEDULER_RUNNING) {
        osDelay(time);
    } else {
        HAL_Delay(time);
    }
}


#include "i2c.h"
#define I2C_HW



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
    #ifndef I2C_HW
    OS_LOCK();
    uint8_t result = EEPROM_NO_ERROR;
    const uint8_t *buffer = pdata;
    while(write_n)
    {
        uint8_t  page_write_n = 4;
        if(page_write_n > write_n)
        {
            page_write_n = write_n;
        }
        //两个地址出现在不同页
        if(((str_addr) / 64) != ((str_addr + page_write_n) / 64)) {
            page_write_n = ((str_addr + page_write_n) / 64) * 64 - str_addr;
        }
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
        //发送数据
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
        __eeprom_delay(5);
    }
ERROR:
    OS_UNLOCK();
    __eeprom_delay(2);
    return result;
    #else
    if(eeprom == NULL) { return EEPROM_DATA_NOACK; }
    //    if(I2C_MutexHandle == NULL) return EEPROM_DATA_NOACK;
    while(1)
    {
        uint8_t writeCount = 0;
        if(write_n > 8) {
            writeCount = 8;
        } else {
            writeCount = write_n;
        }
        //两个地址出现在不同页
        if((str_addr / 64) != ((str_addr + writeCount) / 64)) {
            writeCount = ((str_addr + writeCount) / 64) * 64 - str_addr;
        }
        write_n -= writeCount;
        if(xTaskGetSchedulerState() == taskSCHEDULER_RUNNING) { osMutexAcquire(I2C_MutexHandle, osWaitForever); }
//        HAL_StatusTypeDef state = HAL_I2C_Mem_Write(&hi2c2, eeprom->addr | I2C_WRITE, str_addr, I2C_MEMADD_SIZE_16BIT, pdata, writeCount, 100);
        
        while(HAL_I2C_STATE_READY != HAL_I2C_GetState(&hi2c2)) __eeprom_delay(1);
        HAL_StatusTypeDef state = HAL_I2C_Mem_Write_DMA(&hi2c2, eeprom->addr | I2C_WRITE, str_addr, I2C_MEMADD_SIZE_16BIT, pdata, writeCount);
        while(HAL_I2C_STATE_READY != HAL_I2C_GetState(&hi2c2)) __eeprom_delay(1);
        if(xTaskGetSchedulerState() == taskSCHEDULER_RUNNING) { osMutexRelease(I2C_MutexHandle); }
        if(HAL_OK != state) {
            eeprom->bit_fault |= 1;
            return EEPROM_DATA_NOACK;
        }
        pdata += writeCount;
        str_addr += writeCount;
        //        #if defined(UDP6942B)
        __eeprom_delay(5);
        //        #else
        //        #endif
        if(write_n == 0) {
            break;
        }
    }
    return EEPROM_NO_ERROR;
    #endif
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
    #ifndef I2C_HW
    HAL_Delay(2);
    OS_LOCK();
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
    OS_UNLOCK();
    return result;
    #else
    if(eeprom == NULL) { return EEPROM_DATA_NOACK; }
    //    if(I2C_MutexHandle == NULL) return EEPROM_DATA_NOACK;
    if(xTaskGetSchedulerState() == taskSCHEDULER_RUNNING) { osMutexAcquire(I2C_MutexHandle, osWaitForever); }
    #if 0
    HAL_StatusTypeDef state = HAL_I2C_Mem_Read(&hi2c2, eeprom->addr | I2C_READ, str_addr, I2C_MEMADD_SIZE_16BIT, pdata, len, 100);
    #else
    while(HAL_I2C_STATE_READY != HAL_I2C_GetState(&hi2c2)) __eeprom_delay(1);
    HAL_StatusTypeDef state = HAL_I2C_Mem_Read_DMA(&hi2c2, eeprom->addr | I2C_READ, str_addr, I2C_MEMADD_SIZE_16BIT, pdata, len);
    while(HAL_I2C_STATE_READY != HAL_I2C_GetState(&hi2c2)) __eeprom_delay(1);
    #endif
    if(xTaskGetSchedulerState() == taskSCHEDULER_RUNNING) { osMutexRelease(I2C_MutexHandle); }
    if(HAL_OK == state) {
        return EEPROM_NO_ERROR;
    } else {
        eeprom->bit_fault |= 1;
        return EEPROM_DATA_NOACK;
    }
    #endif
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
