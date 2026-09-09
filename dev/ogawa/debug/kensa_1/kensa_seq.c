/******************************************************************************
  * @file     kensa_seq.c
  * @brief    scripted test-input sequence (no real input device exists yet)
  * @domain   debug
  * @date     2026/09/09
  * @(c)      2026 ocml
******************************************************************************/

/******************************************************************************
  * include
******************************************************************************/
#include "./main.h"               /* common.h, bios2bswif.h(u8gBios2bswif*) */
#include "../../src/apl/psimbrdgif.h" /* s8gPsimbrdgifGearpos, u16gPsimbrdgifVelspd, u16gPsimbrdgifRpmval */

#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
#include "../log/print_log.h"
#endif

#include "./kensa_seq.h"

/******************************************************************************
  * external public variables contains macros
******************************************************************************/

/******************************************************************************
  * internal public variables contains macros
******************************************************************************/
static uint16_t u16sKensaSeqFrameO;

/******************************************************************************
  * external function
******************************************************************************/

/******************************************************************************
  * @func     vdgKensaSeqInit( void )
  * @scope    external
  * @brief    test sequence init function
  * @param    -
  * @return   -
******************************************************************************/
void
vdgKensaSeqInit( void )
{
    u16sKensaSeqFrameO = (uint16_t)0;
}

/******************************************************************************
  * @func     vdgKensaSeq64msin( void )
  * @scope    external
  * @brief    plays back one scripted driving frame per call, then prints the
  * @brief    resulting sim state. 21 frames x virtual-64ms(~3.2 real sec via
  * @brief    conf.h's time scale) = a full launch/upshift/brake/stop cycle.
  * @param    -
  * @return   -
******************************************************************************/
void
vdgKensaSeq64msin( void )
{
    uint16_t u16tFrame;

    u16tFrame = u16sKensaSeqFrameO;

    switch ( u16tFrame )
    {
        case 0:  u8gBios2bswifIgsw = OFF; s8gBios2bswifGear = (int8_t)0; break; /* 電源投入直後 */
        case 1:  u8gBios2bswifIgsw = ON;  u8gBios2bswifClthpdl = (uint8_t)100; break; /* IG-ON、クラッチ全踏み */
        case 2:  s8gBios2bswifGear = (int8_t)1; break;                         /* 1速へ */
        case 3:  u8gBios2bswifAcelthl = (uint8_t)20; u8gBios2bswifClthpdl = (uint8_t)80; break; /* 発進開始 */
        case 4:  u8gBios2bswifAcelthl = (uint8_t)35; u8gBios2bswifClthpdl = (uint8_t)55; break;
        case 5:  u8gBios2bswifAcelthl = (uint8_t)50; u8gBios2bswifClthpdl = (uint8_t)30; break;
        case 6:  u8gBios2bswifAcelthl = (uint8_t)60; u8gBios2bswifClthpdl = (uint8_t)10; break;
        case 7:  u8gBios2bswifAcelthl = (uint8_t)70; u8gBios2bswifClthpdl = (uint8_t)0;  break; /* 完全につながった */
        case 8:  break; /* このまま少し加速させる */
        case 9:  u8gBios2bswifAcelthl = (uint8_t)5; u8gBios2bswifClthpdl = (uint8_t)60; s8gBios2bswifGear = (int8_t)2; break; /* 2速へシフト準備 */
        case 10: u8gBios2bswifAcelthl = (uint8_t)40; u8gBios2bswifClthpdl = (uint8_t)0; break;
        case 11: u8gBios2bswifAcelthl = (uint8_t)50; break;
        case 12: u8gBios2bswifAcelthl = (uint8_t)5; u8gBios2bswifClthpdl = (uint8_t)60; s8gBios2bswifGear = (int8_t)3; break; /* 3速へシフト準備 */
        case 13: u8gBios2bswifAcelthl = (uint8_t)45; u8gBios2bswifClthpdl = (uint8_t)0; break;
        case 14: break;
        case 15: u8gBios2bswifAcelthl = (uint8_t)0; u8gBios2bswifBrkpdl = (uint8_t)30; break; /* 減速開始(エンジンブレーキ併用) */
        case 16: u8gBios2bswifBrkpdl = (uint8_t)60; break;
        case 17: u8gBios2bswifBrkpdl = (uint8_t)80; u8gBios2bswifClthpdl = (uint8_t)100; break; /* 停止直前、クラッチ切る */
        case 18: s8gBios2bswifGear = (int8_t)0; u8gBios2bswifBrkpdl = (uint8_t)40; break; /* ニュートラルへ */
        case 19: u8gBios2bswifBrkpdl = (uint8_t)0; u8gBios2bswifClthpdl = (uint8_t)0; break; /* 完全停止 */
        case 20: u8gBios2bswifIgsw = OFF; break; /* IG-OFF */
        default: break; /* 以降は最終状態を保持 */
    }

    /* この検査シーケンス自身の状態表示は、内部モジュールの詳細トレース用      */
    /* フラグ(PRINT_LOG_SETTING_CONF)とは独立に常時出力する(検査ハーネスの   */
    /* 本来の目的である「車がどう動いているか」を、詳細ログの大量出力に      */
    /* 埋もれさせずに確認できるようにするため)                              */
    vdgLogArgPrint( "KENSA frame = %d",       (int32_t)u16tFrame );
    vdgLogArgPrint( "  cmd gear   = %d",      (int32_t)s8gBios2bswifGear );
    vdgLogArgPrint( "  cmd accel  = %d",      (int32_t)u8gBios2bswifAcelthl );
    vdgLogArgPrint( "  cmd brake  = %d",      (int32_t)u8gBios2bswifBrkpdl );
    vdgLogArgPrint( "  cmd clutch = %d",      (int32_t)u8gBios2bswifClthpdl );
    vdgLogArgPrint( "  -> sim gear      = %d", (int32_t)s8gPsimbrdgifGearpos );
    vdgLogArgPrint( "  -> sim speed[kmh]= %d", (int32_t)u16gPsimbrdgifVelspd );
    vdgLogArgPrint( "  -> sim rpm       = %d", (int32_t)u16gPsimbrdgifRpmval );

    if ( u16tFrame < (uint16_t)20 )
    {
        u16tFrame++;
    }
    u16sKensaSeqFrameO = u16tFrame;
}

/******************************************************************************
  * internal function
******************************************************************************/

/******************************************************************************
  * end of file
******************************************************************************/
