/******************************************************************************
  * @file     kensa_manual.c
  * @brief    real-time manual keyboard control (Windows console)
  * @domain   debug
  * @date     2026/09/10
  * @(c)      2026 ocml
******************************************************************************/

/******************************************************************************
  * include
******************************************************************************/
#include <windows.h> /* GetAsyncKeyState() */

#ifdef TRUE
#undef TRUE
#endif
#ifdef FALSE
#undef FALSE
#endif

#include <stdio.h>   /* printf()  - controls legend               */
#include <stdlib.h>  /* exit()    - ESC to quit                   */

#include "./main.h"                    /* common.h, bios2bswif.h(u8gBios2bswif*) */
#include "../../src/apl/psimbrdgif.h"  /* s8gPsimbrdgifGearpos, u16gPsimbrdgifVelspd, u16gPsimbrdgifRpmval */
#include "../log/print_log.h"          /* vdgLogArgPrint()                       */

#include "./kensa_manual.h"

/******************************************************************************
  * external public variables contains macros
******************************************************************************/

/******************************************************************************
  * internal public variables contains macros
******************************************************************************/
/* ペダルは押しっぱなし/離しっぱなしをアナログ的に近似する。1ティックあたりの */
/* 増減量(仮の調整値、要チューニング)                                       */
#define u8s_KENSAMANUAL_PEDAL_RAMPSTEP3 ((uint8_t)3)
/* ステータス表示の間引き間隔(このティック数に1回だけ表示する) */
#define u16s_KENSAMANUAL_PRINT_DIV15    ((uint16_t)15)

static uint16_t u16sKensaManualPrintCntO;
static uint8_t  u8sKensaManualIgswKeyPrevO; /* Iキーのエッジ検出用(前回押下状態) */

/******************************************************************************
  * external function
******************************************************************************/

/******************************************************************************
  * @func     vdgKensaManualInit( void )
  * @scope    external
  * @brief    manual control init function
  * @param    -
  * @return   -
******************************************************************************/
void
vdgKensaManualInit( void )
{
    u8gBios2bswifIgsw    = (uint8_t)OFF;
    u8gBios2bswifAcelthl = (uint8_t)0;
    u8gBios2bswifBrkpdl  = (uint8_t)0;
    u8gBios2bswifClthpdl = (uint8_t)0;
    s8gBios2bswifGear    = (int8_t)0;

    u16sKensaManualPrintCntO   = (uint16_t)0;
    u8sKensaManualIgswKeyPrevO = (uint8_t)0;

    printf( "==================================================\n" );
    printf( " ZUN-DRIVE manual control (console prototype)\n" );
    printf( "==================================================\n" );
    printf( "  W          : accel (hold)\n" );
    printf( "  S          : brake (hold)\n" );
    printf( "  A          : clutch(hold, press pedal in)\n" );
    printf( "  0-5        : gear N/1st..5th\n" );
    printf( "  R          : gear reverse\n" );
    printf( "  I          : toggle ignition on/off\n" );
    printf( "  ESC        : quit\n" );
    printf( "==================================================\n" );
}

/******************************************************************************
  * @func     vdgKensaManual4msin( void )
  * @scope    external
  * @brief    poll keyboard every 4ms tick, ramp pedals, print status
  * @param    -
  * @return   -
******************************************************************************/
void
vdgKensaManual4msin( void )
{
    uint8_t u8tAcelTarget;
    uint8_t u8tBrkTarget;
    uint8_t u8tClthTarget;
    uint8_t u8tIgswKeyNow;
    uint16_t u16tPrintCnt;

    if ( ( GetAsyncKeyState( VK_ESCAPE ) & 0x8000 ) != 0 )
    {
        exit( 0 );
    }

    /* --- ペダル(押している間だけ100%側へ、離すと0%側へアナログ的に近づく) --- */
    u8tAcelTarget = ( ( GetAsyncKeyState( (int)'W' ) & 0x8000 ) != 0 ) ? (uint8_t)100 : (uint8_t)0;
    u8tBrkTarget  = ( ( GetAsyncKeyState( (int)'S' ) & 0x8000 ) != 0 ) ? (uint8_t)100 : (uint8_t)0;
    u8tClthTarget = ( ( GetAsyncKeyState( (int)'A' ) & 0x8000 ) != 0 ) ? (uint8_t)100 : (uint8_t)0;

    if ( u8gBios2bswifAcelthl < u8tAcelTarget )
    {
        u8gBios2bswifAcelthl = (uint8_t)( ( u8tAcelTarget - u8gBios2bswifAcelthl > u8s_KENSAMANUAL_PEDAL_RAMPSTEP3 )
                                         ? u8gBios2bswifAcelthl + u8s_KENSAMANUAL_PEDAL_RAMPSTEP3 : u8tAcelTarget );
    }
    else if ( u8gBios2bswifAcelthl > u8tAcelTarget )
    {
        u8gBios2bswifAcelthl = (uint8_t)( ( u8gBios2bswifAcelthl - u8tAcelTarget > u8s_KENSAMANUAL_PEDAL_RAMPSTEP3 )
                                         ? u8gBios2bswifAcelthl - u8s_KENSAMANUAL_PEDAL_RAMPSTEP3 : u8tAcelTarget );
    }

    if ( u8gBios2bswifBrkpdl < u8tBrkTarget )
    {
        u8gBios2bswifBrkpdl = (uint8_t)( ( u8tBrkTarget - u8gBios2bswifBrkpdl > u8s_KENSAMANUAL_PEDAL_RAMPSTEP3 )
                                        ? u8gBios2bswifBrkpdl + u8s_KENSAMANUAL_PEDAL_RAMPSTEP3 : u8tBrkTarget );
    }
    else if ( u8gBios2bswifBrkpdl > u8tBrkTarget )
    {
        u8gBios2bswifBrkpdl = (uint8_t)( ( u8gBios2bswifBrkpdl - u8tBrkTarget > u8s_KENSAMANUAL_PEDAL_RAMPSTEP3 )
                                        ? u8gBios2bswifBrkpdl - u8s_KENSAMANUAL_PEDAL_RAMPSTEP3 : u8tBrkTarget );
    }

    if ( u8gBios2bswifClthpdl < u8tClthTarget )
    {
        u8gBios2bswifClthpdl = (uint8_t)( ( u8tClthTarget - u8gBios2bswifClthpdl > u8s_KENSAMANUAL_PEDAL_RAMPSTEP3 )
                                         ? u8gBios2bswifClthpdl + u8s_KENSAMANUAL_PEDAL_RAMPSTEP3 : u8tClthTarget );
    }
    else if ( u8gBios2bswifClthpdl > u8tClthTarget )
    {
        u8gBios2bswifClthpdl = (uint8_t)( ( u8gBios2bswifClthpdl - u8tClthTarget > u8s_KENSAMANUAL_PEDAL_RAMPSTEP3 )
                                         ? u8gBios2bswifClthpdl - u8s_KENSAMANUAL_PEDAL_RAMPSTEP3 : u8tClthTarget );
    }

    /* --- ギア(押されているキーがあればそれを即反映、無ければ前回値を維持) --- */
    if      ( ( GetAsyncKeyState( (int)'0' ) & 0x8000 ) != 0 ) { s8gBios2bswifGear = (int8_t)0; }
    else if ( ( GetAsyncKeyState( (int)'1' ) & 0x8000 ) != 0 ) { s8gBios2bswifGear = (int8_t)1; }
    else if ( ( GetAsyncKeyState( (int)'2' ) & 0x8000 ) != 0 ) { s8gBios2bswifGear = (int8_t)2; }
    else if ( ( GetAsyncKeyState( (int)'3' ) & 0x8000 ) != 0 ) { s8gBios2bswifGear = (int8_t)3; }
    else if ( ( GetAsyncKeyState( (int)'4' ) & 0x8000 ) != 0 ) { s8gBios2bswifGear = (int8_t)4; }
    else if ( ( GetAsyncKeyState( (int)'5' ) & 0x8000 ) != 0 ) { s8gBios2bswifGear = (int8_t)5; }
    else if ( ( GetAsyncKeyState( (int)'R' ) & 0x8000 ) != 0 ) { s8gBios2bswifGear = (int8_t)-1; }

    /* --- イグニッション(Iキーの押下エッジでON/OFF切替) --- */
    u8tIgswKeyNow = ( ( GetAsyncKeyState( (int)'I' ) & 0x8000 ) != 0 ) ? (uint8_t)1 : (uint8_t)0;
    if ( ( u8tIgswKeyNow == (uint8_t)1 ) && ( u8sKensaManualIgswKeyPrevO == (uint8_t)0 ) )
    {
        u8gBios2bswifIgsw = ( u8gBios2bswifIgsw == (uint8_t)ON ) ? (uint8_t)OFF : (uint8_t)ON;
    }
    u8sKensaManualIgswKeyPrevO = u8tIgswKeyNow;

    /* --- ステータス表示(間引き。詳細トレース用のPRINT_LOG_SETTING_CONFとは独立) --- */
    u16tPrintCnt = u16sKensaManualPrintCntO;
    u16tPrintCnt++;
    if ( u16tPrintCnt >= u16s_KENSAMANUAL_PRINT_DIV15 )
    {
        u16tPrintCnt = (uint16_t)0;

        vdgLogArgPrint( "IG=%d",           (int32_t)u8gBios2bswifIgsw );
        vdgLogArgPrint( "  cmd gear   = %d", (int32_t)s8gBios2bswifGear );
        vdgLogArgPrint( "  cmd accel  = %d", (int32_t)u8gBios2bswifAcelthl );
        vdgLogArgPrint( "  cmd brake  = %d", (int32_t)u8gBios2bswifBrkpdl );
        vdgLogArgPrint( "  cmd clutch = %d", (int32_t)u8gBios2bswifClthpdl );
        vdgLogArgPrint( "  -> sim gear      = %d", (int32_t)s8gPsimbrdgifGearpos );
        vdgLogArgPrint( "  -> sim speed[kmh]= %d", (int32_t)u16gPsimbrdgifVelspd );
        vdgLogArgPrint( "  -> sim rpm       = %d", (int32_t)u16gPsimbrdgifRpmval );
    }
    u16sKensaManualPrintCntO = u16tPrintCnt;
}

/******************************************************************************
  * internal function
******************************************************************************/

/******************************************************************************
  * end of file
******************************************************************************/
