/****************************************************************/
/*  * @file     pwarn.c                                         */
/*  * @brief    -                                               */
/*  * @domain   -                                               */
/*  * @date     2026/09/09                                      */
/*  * @(c)      2026 ocml                                       */
/****************************************************************/

/****************************************************************/
/*  * include                                                   */
/****************************************************************/
#include "../../inc/common.h"
#include "../psimbrdgif.h" /* u16gPsimbrdgifRpmval */

#include "../pwarnif.h"

/****************************************************************/
/*  * external public variables contains macros                 */
/****************************************************************/
uint8_t u8gPwarnifOvrhet;
uint8_t u8gPwarnifSnserr;

/****************************************************************/
/*  * internal public variables contains macros                 */
/****************************************************************/
/* 仕様書に閾値の記載が無いため妥当な仮値を設定(要調整) */
#define u16s_PWARN_OVRHET_RPM5000   ((uint16_t)5000)
#define u8s_PWARN_OVRHET_DURCNT47   ((uint8_t)47)  /* 64ms x 47 ≒ 仮想約3秒の高回転継続 */

static uint8_t u8sPwarnOvrhetCntO;

/****************************************************************/
/*  * external function                                         */
/****************************************************************/

/****************************************************************/
/*  * @func     vdgPwarnifInit( void )                          */
/*  * @scope    external                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgPwarnifInit( void )
{
    u8gPwarnifOvrhet   = (uint8_t)OFF;
    u8gPwarnifSnserr   = (uint8_t)OFF;
    u8sPwarnOvrhetCntO = (uint8_t)0;
}

/****************************************************************/
/*  * @func     vdgPwarnif64msin( void )                        */
/*  * @scope    external                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgPwarnif64msin( void )
{
    uint8_t u8tCnt;

    u8tCnt = u8sPwarnOvrhetCntO;
    if ( u16gPsimbrdgifRpmval > u16s_PWARN_OVRHET_RPM5000 )
    {
        if ( u8tCnt < u8g_MAX )
        {
            u8tCnt++;
        }
    }
    else
    {
        u8tCnt = (uint8_t)0;
    }
    u8sPwarnOvrhetCntO = u8tCnt;

    u8gPwarnifOvrhet = ( u8tCnt > u8s_PWARN_OVRHET_DURCNT47 ) ? (uint8_t)ON : (uint8_t)OFF;

    /* センサー異常は故障注入の仕組みがまだ無いためプレースホルダ */
    u8gPwarnifSnserr = (uint8_t)OFF;
}

/****************************************************************/
/*  * internal function                                         */
/****************************************************************/

/****************************************************************/
/*  * end of file                                               */
/****************************************************************/
