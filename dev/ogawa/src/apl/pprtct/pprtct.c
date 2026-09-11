/****************************************************************/
/*  * @file     pprtct.c                                        */
/*  * @brief    -                                               */
/*  * @domain   -                                               */
/*  * @date     2026/09/09                                      */
/*  * @(c)      2026 ocml                                       */
/****************************************************************/

/****************************************************************/
/*  * include                                                   */
/****************************************************************/
#include "../../inc/common.h"
#include "../psimbrdgif.h" /* u16gPsimbrdgifRpmval, u8gPsimbrdigIgswsts */

#include "../pprtctif.h"

/****************************************************************/
/*  * external public variables contains macros                 */
/****************************************************************/
uint8_t u8gPprtctifOvrvsts;
uint8_t u8gPprtctifClthszsts;
uint8_t u8gPprtctifBrkszsts;
uint8_t u8gPprtctifEnststs;

/****************************************************************/
/*  * internal public variables contains macros                 */
/****************************************************************/
/* 仕様書に閾値の記載が無いため妥当な仮値を設定(要調整) */
#define u16s_PPRTCT_OVRREV_RPM6000 ((uint16_t)6000)
#define u16s_PPRTCT_STALL_RPM400   ((uint16_t)400)
/* エンジン始動直後(回転数がまだ0からの立ち上がり途中)を誤ってエンストと */
/* 判定しないよう、低回転が一定時間継続した場合のみエンストとして扱う。   */
/* (meng.cのスルーレート15rpm/4mstickだと0->400rpmの立ち上がりに仮想約   */
/*  107msかかるため、それより十分長い時間を要求する)                     */
#define u8s_PPRTCT_STALL_DURCNT15  ((uint8_t)15) /* 16ms x 15 ≒ 仮想240ms継続 */

static uint8_t u8sPprtctStallCntO;

/****************************************************************/
/*  * external function                                         */
/****************************************************************/

/****************************************************************/
/*  * @func     vdgPprtctifInit( void )                         */
/*  * @scope    external                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgPprtctifInit( void )
{
    u8gPprtctifOvrvsts   = (uint8_t)OFF;
    u8gPprtctifClthszsts = (uint8_t)OFF;
    u8gPprtctifBrkszsts  = (uint8_t)OFF;
    u8gPprtctifEnststs   = (uint8_t)OFF;
    u8sPprtctStallCntO   = (uint8_t)0;
}

/****************************************************************/
/*  * @func     vdgPprtctif16msin( void )                       */
/*  * @scope    external                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgPprtctif16msin( void )
{
    uint8_t u8tCnt;

    u8gPprtctifOvrvsts = ( u16gPsimbrdgifRpmval > u16s_PPRTCT_OVRREV_RPM6000 ) ? (uint8_t)ON : (uint8_t)OFF;

    u8tCnt = u8sPprtctStallCntO;
    if ( ( u8gPsimbrdigIgswsts == (uint8_t)ON ) && ( u16gPsimbrdgifRpmval < u16s_PPRTCT_STALL_RPM400 ) )
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
    u8sPprtctStallCntO = u8tCnt;

    u8gPprtctifEnststs = ( u8tCnt > u8s_PPRTCT_STALL_DURCNT15 ) ? (uint8_t)ON : (uint8_t)OFF;

    /* クラッチ/ブレーキ焼付は故障注入の仕組みがまだ無いためプレースホルダ */
    u8gPprtctifClthszsts = (uint8_t)OFF;
    u8gPprtctifBrkszsts  = (uint8_t)OFF;
}

/****************************************************************/
/*  * internal function                                         */
/****************************************************************/

/****************************************************************/
/*  * end of file                                               */
/****************************************************************/
