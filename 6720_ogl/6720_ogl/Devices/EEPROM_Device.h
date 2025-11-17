#ifndef _EEPROM_DEVICE_H_
#define _EEPROM_DEVICE_H_

#include "main.h"
#include "I2C_Device.h"
#include "Task_Manager.h"



#define CAL_BASE_ADDR   (0*1024UL)
#define CAL_VOL_ADDR    (CAL_BASE_ADDR+0)
#define CAL_AMP_ADDR    (CAL_BASE_ADDR+512UL)


typedef struct
{
    I2C_Dev_Def i2c;
    uint8_t addr;
    uint8_t bit_fault;
} EEPROM_Dev_Def;


extern EEPROM_Dev_Def eeprom;

enum
{
    EEPROM_NO_ERROR,
    EEPROM_ADDR_NOACK,
    EEPROM_PAGE_NOACK,
    EEPROM_DATA_NOACK,
};

/*
 * @brief       uint8_t eeprom_WriteArrary(EEPROM_Dev_Def* eeprom ,uint16_t page,
                            uint8_t* pdata,uint16_t len)
 * @details     向EEPROM写入一组数据
 * @param[in]
 * @param[out]
 * @retval
 */
uint8_t eeprom_WriteArrary(EEPROM_Dev_Def *eeprom, uint16_t str_addr,
                           uint8_t *pdata, uint16_t write_n);

/*
 * @brief       uint8_t eeprom_ReadArrary(EEPROM_Dev_Def* eeprom ,uint16_t str_addr,
                            uint8_t* pdata,uint16_t len)
 * @details     从EEPROM读取一组数据
 * @param[in]
 * @param[out]
 * @retval
 */
uint8_t eeprom_ReadArrary(EEPROM_Dev_Def *eeprom, uint16_t str_addr,
                          uint8_t *pdata, uint16_t len);

#endif
