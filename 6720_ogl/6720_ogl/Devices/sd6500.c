#include "sd6500.h"
#include <stdio.h>
#include <main.h>
#include "I2C_Device.h"
/* 你要的全局实例（只定义一次，其他文件用 extern） */
sd6500_t g_sd;

I2C_Dev_Def g_i2c_sd = {
    .clk = { .port = ADC_SCL_GPIO_Port, .pin = ADC_SCL_Pin },
    .sda = { .port = ADC_SDA_GPIO_Port, .pin = ADC_SDA_Pin },
};

static void delay(void)
{
    uint16_t i;
    for(i = 0; i < 20; i++);
}

static inline void sda_set_dly(I2C_Dev_Def *b, int v)
{
    gpio_set(b->sda, v ? 1 : 0);
    delay();
}

static inline void clk_set_dly(I2C_Dev_Def *b, int v)
{
    gpio_set(b->clk, v ? 1 : 0);
    delay();
}

/* 语义更清晰的别名 */
static inline void sda_hi(I2C_Dev_Def *b){ sda_set_dly(b, 1); }
static inline void sda_lo(I2C_Dev_Def *b){ sda_set_dly(b, 0); }
static inline void clk_hi(I2C_Dev_Def *b){ clk_set_dly(b, 1); }
static inline void clk_lo(I2C_Dev_Def *b){ clk_set_dly(b, 0); }
/* 常用组合 */
static inline int  sda_read(I2C_Dev_Def *b){ return gpio_get(b->sda); } // 只读，不延时

/* —— 接收：遵循“无ACK、第二字节=长度-1、bit7=R/W” —— */
static inline void i2c_send_byte(I2C_Dev_Def *b, uint8_t x)
{
    __disable_irq();
    for (int i = 7; i >= 0; --i) {
        clk_hi(b);                               // ↑
        sda_set_dly(b, (x >> i) & 1u);           // 放当前位
        clk_lo(b);                               // ↓ 锁存
        sda_hi(b);                               // 释放SDA（开漏=1）
    }
    __enable_irq();
}

static inline uint8_t i2c_read_byte(I2C_Dev_Def *b)
{
    uint8_t r = 0;
    sda_hi(b);                                   // 释放 SDA，让从机驱动
    __disable_irq();
    for (int i = 7; i >= 0; --i) {
        clk_hi(b);                               // ↑
        r |= (sda_read(b) ? 1u : 0u) << i;       // 采样
        clk_lo(b);                               // ↓
    }
    __enable_irq();
    return r;
}

/* —— 协议首字节：bit6..0 = reg 地址；bit7 = R/W（1读0写） —— */
static inline uint8_t sd6500_addr_byte(uint8_t reg, bool rd)
{
    return rd ? (uint8_t)(reg | 0x80u) : (uint8_t)(reg & 0x7Fu);
}

/* ========= 写寄存器：Start → [addr|W(bit7=0)] → [len-1] → data... → Stop ========= */
int sd6500_write_regs(sd6500_t *dev, uint8_t reg, const uint8_t *src, uint8_t len)
{
    if (!dev || !dev->bus || !src || !len) return -1;


    i2c_send_byte(dev->bus, sd6500_addr_byte(reg, false));
    i2c_send_byte(dev->bus, (uint8_t)(len - 1u));   /* 注意：长度-1 */
    for (uint8_t i=0;i<len;i++) i2c_send_byte(dev->bus, src[i]);

    return 0;
}

/* ========= 读寄存器：Start → [addr|R(bit7=1)] → [len-1] → 读len字节 → Stop ========= */
int sd6500_read_regs(sd6500_t *dev, uint8_t reg, uint8_t *dst, uint8_t len)
{
    if (!dev || !dev->bus || !dst || !len) return -1;

 
    i2c_send_byte(dev->bus, sd6500_addr_byte(reg, true));
    i2c_send_byte(dev->bus, (uint8_t)(len - 1u));   /* 注意：长度-1 */
    for (uint8_t i=0;i<len;i++) dst[i] = i2c_read_byte(dev->bus);
 
    return 0;
}

/* ========= 复位序列（按你的 hpp） ========= */
static void sd6500_reset_lines(sd6500_t *dev)
{
    //init
    sda_hi(dev->bus);
    clk_hi(dev->bus);
    //reset
    clk_hi(dev->bus);
    HAL_Delay(20);
    sda_lo(dev->bus);
    clk_lo(dev->bus);
    HAL_Delay(2);
}


static void sd6500_dump_regs(void)
{
    uint8_t r[8]={0}, mux2=0;
    if (sd6500_read_regs(&g_sd, 0x00, r, 8)==0) {
        printf("00..07: %02X %02X %02X %02X %02X %02X %02X %02X\r\n",
               r[0],r[1],r[2],r[3],r[4],r[5],r[6],r[7]);
    } else {
        printf("read 00..07 FAIL\r\n");
    }
    if (sd6500_read_regs(&g_sd, 0x04, &mux2, 1)==0)
        printf("ASPMUXS2=0x%02X\r\n", mux2);
}




/* ========= 初始化 ========= */
int sd6500_init(sd6500_t *dev, I2C_Dev_Def *bus)
{
    if (!dev || !bus) return -1;
    dev->bus   = bus;
    dev->mux   = SD6500_SEL_VOL;
    dev->sum   = 0;
    dev->num   = 0;
    dev->delay = 0;

    sd6500_reset_lines(dev);

    /* 逐块写入（与 hpp 完全一致） */
    sd6500_write_regs(dev, SD6500_REG_OPASEL, Reg12H, sizeof(Reg12H));
    sd6500_write_regs(dev, SD6500_REG_DASEL,  Reg14H, sizeof(Reg14H));
    sd6500_write_regs(dev, SD6500_REG_AVDDR,  Reg17H, sizeof(Reg17H));
    sd6500_write_regs(dev, SD6500_REG_SYSCON, Reg00H, sizeof(Reg00H));

    /* 初始化后保持 VOL 通道 */
    dev->sum = 0; dev->num = 0; dev->delay = 0; dev->mux = SD6500_SEL_VOL;
  
  //检验sd6500是否按时应答
    //sd6500_dump_regs();
  
      return 0;
  
}

/* ========= 通道切换（写 0x04） ========= */
int sd6500_toggle_mux(sd6500_t *dev)
{
    if (!dev || !dev->bus) return -1;
    uint8_t reg = (dev->mux == SD6500_SEL_VOL) ? (uint8_t)REG_ASPMUXS2_AMP
                                               : (uint8_t)REG_ASPMUXS2_VOL;
    if (sd6500_write_regs(dev, SD6500_REG_ASPMUXS2, &reg, 1)) return -2;
    dev->mux = (dev->mux == SD6500_SEL_VOL) ? SD6500_SEL_AMP : SD6500_SEL_VOL;
    dev->sum = 0; dev->num = 0; dev->delay = 0;
    return 0;
}

/* ========= 等待 ADIF ========= */
int sd6500_wait_ready_poll(sd6500_t *dev, uint32_t timeout_ms)
{
    if (!dev || !dev->bus) return -1;
    uint32_t t0 = HAL_GetTick();
    for (;;) {
        uint8_t sys = 0;
        if (sd6500_read_regs(dev, SD6500_REG_SYSCON, &sys, 1) == 0) {
            if (sys & BIT_ADIF) return 0;
        }
        if ((HAL_GetTick() - t0) >= timeout_ms) break;
    }
    return -2; /* 超时 */
}

/* ========= 读 24bit 数据（H→M→L），并做有符号扩展 ========= */
int sd6500_read_adc24(sd6500_t *dev, int32_t *code24)
{
    if (!dev || !dev->bus || !code24) return -1;

    uint8_t b[3];
    if (sd6500_read_regs(dev, SD6500_REG_ADCDH, b, 3)) return -2;

    int32_t v = ((int32_t)b[0] << 16) | ((int32_t)b[1] << 8) | (int32_t)b[2];
    if (v & 0x800000) v |= 0xFF000000; /* 24bit 补码扩展到 32bit */
    *code24 = v;
    return 0;
}

/* ========= 读并换算为物理量（按你的 hpp 的系数） ========= */
int sd6500_get_val(sd6500_t *dev, uint8_t *who, float *fval)
{
    if (!dev || !who || !fval) return -1;

  #if 0
    /* 可选：先看 DFM 是否按期望（与 hpp 一致的健壮性检查） */
    uint8_t dfm = 0;
    if (sd6500_read_regs(dev, SD6500_REG_DFM, &dfm, 1) == 0) {
        if ( (dfm & 0x0Fu) != (REG_DFM & 0x0Fu) ) {
            /* 若配置跑飞，可考虑重新 init，这里只做提示 */
            /* sd6500_init(dev, dev->bus); */
        }
    }
    #endif
  
    int32_t code = 0;
    if (sd6500_read_adc24(dev, &code)) return -2;

    *who  = (uint8_t)dev->mux;
    *fval = (float)code * 3.3f * 1.33f / 8388608.0f;  /* 2^23 */
    return 0;
}
