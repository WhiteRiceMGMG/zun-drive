/****************************************************************/
/*  * @file     pvehstsjdg.c                                    */
/*  * @brief    -                                               */
/*  * @domain   -                                               */
/*  * @date     2026/09/09                                      */
/*  * @(c)      2026 ocml                                       */
/****************************************************************/

/****************************************************************/
/*  * include                                                   */
/****************************************************************/
#include "../../inc/common.h"
#include "../psimbrdgif.h" /* u16gPsimbrdgifVelspd, u16gPsimbrdgifRpmval, u8gPsimbrdigIgswsts */

#include "../pvehstsjdgif.h"

/****************************************************************/
/*  * external public variables contains macros                 */
/****************************************************************/
uint8_t u8gPvehstsjdgifStop;
uint8_t u8gPvehstsjdgifRun;
uint8_t u8gPvehstsjdgifSpdup;
uint8_t u8gPvehstsjdgifSpddw;
uint8_t u8gPvehstsjdgifEnst;

/****************************************************************/
/*  * internal public variables contains macros                 */
/****************************************************************/
#define u16s_PVEHSTSJDG_STALL_RPM400 ((uint16_t)400)

static uint16_t u16sPvehstsjdgVelspdO;

/****************************************************************/
/*  * external function                                         */
/****************************************************************/

/****************************************************************/
/*  * @func     vdgPvehstsjdgifInit( void )                     */
/*  * @scope    external                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgPvehstsjdgifInit( void )
{
    u8gPvehstsjdgifStop   = (uint8_t)ON;
    u8gPvehstsjdgifRun    = (uint8_t)OFF;
    u8gPvehstsjdgifSpdup  = (uint8_t)OFF;
    u8gPvehstsjdgifSpddw  = (uint8_t)OFF;
    u8gPvehstsjdgifEnst   = (uint8_t)OFF;
    u16sPvehstsjdgVelspdO = (uint16_t)0;
}

/****************************************************************/
/*  * @func     vdgPvehstsjdgif64msin( void )                   */
/*  * @scope    external                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgPvehstsjdgif64msin( void )
{
    uint16_t u16tSpd;

    u16tSpd = u16gPsimbrdgifVelspd;

    u8gPvehstsjdgifStop  = ( u16tSpd == (uint16_t)0 )          ? (uint8_t)ON : (uint8_t)OFF;
    u8gPvehstsjdgifRun   = ( u16tSpd >  (uint16_t)0 )          ? (uint8_t)ON : (uint8_t)OFF;
    u8gPvehstsjdgifSpdup = ( u16tSpd >  u16sPvehstsjdgVelspdO ) ? (uint8_t)ON : (uint8_t)OFF;
    u8gPvehstsjdgifSpddw = ( u16tSpd <  u16sPvehstsjdgVelspdO ) ? (uint8_t)ON : (uint8_t)OFF;

    /* pprtctのエンスト判定とは独立に同条件で再判定する(モジュール間の */
    /* 読み合いを避け、疎結合にするため)                              */
    u8gPvehstsjdgifEnst = ( ( u8gPsimbrdigIgswsts == (uint8_t)ON )
                         && ( u16gPsimbrdgifRpmval < u16s_PVEHSTSJDG_STALL_RPM400 ) )
                        ? (uint8_t)ON : (uint8_t)OFF;

    u16sPvehstsjdgVelspdO = u16tSpd;
}

/****************************************************************/
/*  * internal function                                         */
/****************************************************************/

/****************************************************************/
/*  * end of file                                               */
/****************************************************************/
