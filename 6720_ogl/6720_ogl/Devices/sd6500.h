#ifndef SD6500_H
#define SD6500_H

#include <stdint.h>
#include <stdbool.h>
#include "main.h"
#include "I2C_Device.h"
#include "GPIO_Device.h"
#include "I2C_Device.h"

/* 寄存器表 */
#define SD6500_REG_SYSCON     0x00
#define SD6500_REG_ASPM       0x01
#define SD6500_REG_IAOS       0x02
#define SD6500_REG_ASPMUXS1   0x03
#define SD6500_REG_ASPMUXS2   0x04
#define SD6500_REG_DFM        0x05
#define SD6500_REG_ASPCK1     0x06
#define SD6500_REG_ASPCK2     0x07
#define SD6500_REG_ADCDH      0x08
#define SD6500_REG_ADCDM      0x09
#define SD6500_REG_ADCDL      0x0A
#define SD6500_REG_OPASEL     0x12
#define SD6500_REG_DASEL      0x14
#define SD6500_REG_AVDDR      0x17

/* 位定义（按你的 hpp） */
#define BIT_ADIF              (1u << 1)   /* SYSCON 中的转换完成标志 */

#define BIT_ADCEN_OFF         (0u << 0)
#define BIT_ADCEN_ON          (1u << 0)
#define BIT_BUFO_OFF          (1u << 2)
#define BIT_BUFO_ON           (0u << 2)
#define REG_ASPM              (BIT_ADCEN_ON | BIT_BUFO_OFF)

#define REG_IAOS              (0x00)

#define BIT_RCS_OFF           (1u << 0)
#define BIT_RCS_ON            (2u << 0)
#define BIT_VREFS_AVDD        (0u << 2)
#define BIT_VREFS_ACM         (1u << 2)
#define BIT_VREFG_12          (2u << 4)
#define BIT_VREFG_1           (3u << 4)
#define REG_ASPMUXS1          (BIT_RCS_OFF | BIT_VREFS_AVDD | BIT_VREFG_1)

#define BIT_IAINNS_VSS        (9u << 0)
#define BIT_IAINPS_VOL        (0u << 4)   /* AI0 */
#define BIT_IAINPS_AMP        (1u << 4)   /* AI1 */
#define REG_ASPMUXS2_VOL      (BIT_IAINNS_VSS | BIT_IAINPS_VOL)
#define REG_ASPMUXS2_AMP      (BIT_IAINNS_VSS | BIT_IAINPS_AMP)

#define BIT_OSR_128           (0u << 0)
#define BIT_OSR_256           (1u << 0)
#define BIT_OSR_512           (2u << 0)
#define BIT_OSR_1024          (3u << 0)
#define BIT_OSR_2048          (4u << 0)
#define BIT_OSR_4096          (5u << 0)
#define BIT_OSR_8192          (6u << 0)
#define BIT_OSR_16384         (7u << 0)
#define BIT_DCSET             (0u << 4)
#define REG_DFM               (BIT_OSR_1024 | BIT_DCSET)

#define BIT_ASPCK1_128K       (248u)
#define BIT_ASPCK1_512K       (254u)
#define REG_ASPCK1            (BIT_ASPCK1_128K)
#define REG_ASPCK2            (0x00)

#define BIT_AVDD_24           (0u << 4)
#define BIT_AVDD_27           (1u << 4)
#define BIT_AVDD_30           (2u << 4)
#define BIT_AVDD_33           (3u << 4)

/* 初始化表（与 hpp 完全一致） */
static const uint8_t Reg12H[] = {0x00};
static const uint8_t Reg14H[] = {0x00, 0x00};
static const uint8_t Reg17H[] = {(uint8_t)BIT_AVDD_33};
static const uint8_t Reg00H[] = {
    0x00,              /* SYSCON */
    REG_ASPM,          /* ASPM */
    REG_IAOS,          /* IAOS */
    REG_ASPMUXS1,      /* ASPMUXS1 */
    REG_ASPMUXS2_VOL,  /* ASPMUXS2(先选电压通道) */
    REG_DFM,           /* DFM */
    REG_ASPCK1,        /* ASPCK1 */
    REG_ASPCK2         /* ASPCK2 */
};

/* 通道 */
typedef enum {
    SD6500_SEL_NULL = 0,
    SD6500_SEL_VOL  = 1,
    SD6500_SEL_AMP  = 2,
} sd6500_mux_t;

/* 设备对象 */
typedef struct {
    I2C_Dev_Def *bus;
    sd6500_mux_t mux;
    int32_t      sum;
    uint16_t     num;
    uint16_t     delay;
} sd6500_t;

/* 导出一个全局实例（你工程里已经这么用） */
extern sd6500_t    g_sd;
extern I2C_Dev_Def g_i2c_sd;

/* 低层（二线制，无 ACK；第二字节=长度-1） */
int sd6500_write_regs(sd6500_t *dev, uint8_t reg, const uint8_t *data, uint8_t len);
int sd6500_read_regs (sd6500_t *dev, uint8_t reg,       uint8_t *data, uint8_t len);

/* 高层 API */
int  sd6500_init(sd6500_t *dev, I2C_Dev_Def *bus);
int  sd6500_toggle_mux(sd6500_t *dev);
int  sd6500_wait_ready_poll(sd6500_t *dev, uint32_t timeout_ms);
int  sd6500_read_adc24(sd6500_t *dev, int32_t *code24);
int  sd6500_get_val(sd6500_t *dev, uint8_t *who, float *fval);

#endif /* SD6500_H */
