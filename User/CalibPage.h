#ifndef _CALIB_PAGE_H_
#define _CALIB_PAGE_H_

#include "Commd.h"

uint8_t CalibPage_isVisable(void);

/*
 * @brief       void CalibPage_Enter(void)
 * @details     进入Menu页面
 */
void CalibPage_Enter(void);

/*
 * @brief       void CalibPage_Exit(void)
 * @details     退出Menu页面
 */
void CalibPage_Exit(void);

#endif