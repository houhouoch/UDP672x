#ifndef _EEPROM_DEVICE_H_
#define _EEPROM_DEVICE_H_

#include "main.h"
#include "I2C_Device.h"

/* 根据你实际用途自己调 */
#define CAL_BASE_ADDR   (0*1024UL)
#define CAL_VOL_ADDR    (CAL_BASE_ADDR+0)
#define CAL_AMP_ADDR    (CAL_BASE_ADDR+512UL)

/* AT24C256 容量相关常量（按 at24cxx 的定义） */
#define EEPROM_TOTAL_SIZE   (32U * 1024U)  /* 32K Bytes */
#define EEPROM_PAGE_SIZE    64U            /* AT24C256 实际页大小 64 Bytes */

typedef struct
{
    I2C_Dev_Def i2c;   /* 软件 I2C 引脚 */
    uint8_t     addr;  /* 设备地址高 7bit + R/W 位最低 bit 由 I2C_WRITE/I2C_READ 控制 */
    uint8_t     bit_fault; /* 预留，用不到可以不管 */
} EEPROM_Dev_Def;

extern EEPROM_Dev_Def eeprom;

enum
{
    EEPROM_NO_ERROR = 0,
    EEPROM_ADDR_NOACK,
    EEPROM_PAGE_NOACK,
    EEPROM_DATA_NOACK,
};

/* 写 / 读接口保持不变 */
uint8_t eeprom_WriteArrary(EEPROM_Dev_Def *eeprom, uint16_t str_addr,
                           uint8_t *pdata, uint16_t write_n);

uint8_t eeprom_ReadArrary(EEPROM_Dev_Def *eeprom, uint16_t str_addr,
                          uint8_t *pdata, uint16_t len);

/* 自检函数 */
uint8_t eeprom_SimpleTest(void);

#endif
