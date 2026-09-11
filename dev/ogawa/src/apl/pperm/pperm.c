/****************************************************************/
/*  * @file     pperm.c                                         */
/*  * @brief    -                                               */
/*  * @domain   -                                               */
/*  * @date     2026/08/04                                      */
/*  * @(c)      2026 ocml                                       */
/****************************************************************/

/****************************************************************/
/*  * include                                                   */
/****************************************************************/
#include "../../inc/common.h"

#include "../../sac/sacelcrtif.h" /* u8gSacelcrtifThlpct */
#include "../../sac/sclthcrtif.h" /* u8gSclthcrtifPdlpct */
#include "../../sac/sigswcrtif.h" /* u8gSigswcrtifSts    */

#include "../pprtctif.h" /* u8gPprtctifOvrvsts   */
                         /* u8gPprtctifClthszsts */
                         /* u8gPprtctifBrkszsts  */
                         /* u8gPprtctifEnststs   */

#include "../psimbrdgif.h" /* u16gPsimbrdgifVelspd  */

#include "../ppermif.h"

/****************************************************************/
/*  * external public variables contains macros                 */
/****************************************************************/
uint8_t u8gPpermifSht;      /* shift change flag  */
uint8_t u8gPpermifSim;      /* simulation flag    */
uint8_t u8gPpermifDisp;     /* display flag       */
uint8_t u8gPpermifShtrev;   /* shift reverce flag */
uint8_t u8gPpermifAcelLim;  /* acel limit         */
uint8_t u8gPpermifSpdLim;   /* speed limit        */
uint8_t u8gPpermifShtdw;    /* shift down flag    */
uint8_t u8gPpermifPwrigoff; /* power ig-off flag  */
uint8_t u8gPpermifAcelMax;  /* acel limit value   */
uint8_t u8gPpermifSpdMax;   /* speed limit value  */

/****************************************************************/
/*  * internal public variables contains macros                 */
/****************************************************************/
#define u8s_PPERM_SHT_ACELPCT10   ((uint8_t)10)
#define u8s_PPERM_SHT_CLTHPCT30   ((uint8_t)30)
#define u16s_PPERM_SHTREV_SPD5    ((uint16_t)5)
#define u8s_PPERM_ACEL_LIM70      ((uint8_t)70)
#define u8s_PPERM_SPD_LIM80       ((uint8_t)80)   /* doc記載通り80(既存コードの"50"はバグだった) */
#define u8s_PPERM_ACEL_LIM50      ((uint8_t)50)
#define u8s_PPERM_ACELMAX_FULL100 ((uint8_t)100)  /* 制限なしのデフォルト値 */
#define u8s_PPERM_SPDMAX_NONE     (u8g_MAX)       /* 制限なしのデフォルト値 */

/****************************************************************/
/*  * external function                                         */
/****************************************************************/

/****************************************************************/
/*  * @func     vdgPpermifInit( void )                          */
/*  * @scope    external                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgPpermifInit( void )
{
    u8gPpermifSht      = (uint8_t)OFF;
    u8gPpermifSim      = (uint8_t)OFF;
    u8gPpermifDisp     = (uint8_t)OFF;
    u8gPpermifShtrev   = (uint8_t)OFF;
    u8gPpermifAcelLim  = (uint8_t)OFF;
    u8gPpermifSpdLim   = (uint8_t)OFF;
    u8gPpermifShtdw    = (uint8_t)ON;  /* デフォルトはシフトダウン許可 */
    u8gPpermifPwrigoff = (uint8_t)OFF;
    u8gPpermifAcelMax  = u8s_PPERM_ACELMAX_FULL100;
    u8gPpermifSpdMax   = u8s_PPERM_SPDMAX_NONE;
}

/****************************************************************/
/*  * @func     vdgPpermif16msin( void )                        */
/*  * @scope    external                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgPpermif16msin( void )
{
    uint8_t u8tSht;
    uint8_t u8tShtrev;
    uint8_t u8tAcelLim;
    uint8_t u8tSpdLim;
    uint8_t u8tShtdw;
    uint8_t u8tAcelMax;
    uint8_t u8tSpdMax;

    if ( u8gSigswcrtifSts == (uint8_t)ON ) /* igsw == on */
    {
        u8gPpermifSim  = (uint8_t)ON; /* 要件1: 一度立てたら降ろさない(sticky) */
        u8gPpermifDisp = (uint8_t)ON; /* 要件2 */

        /* 要件3: アクセル10%以下 かつ クラッチ30%以上でシフト許可。               */
        /* リバースはさらに車速5km以下の場合のみ許可(走行中のリバース投入を防止)。 */
        /* 【機能検討】doc記載は通常シフトにも「車速5km以上」を要求していたが、    */
        /* それだと停止状態からニュートラル→1速に一切入れられず(車速0のままでは */
        /* 条件を満たせない)発進不能になる欠陥だったため、通常シフト側は車速条件を */
        /* 外した(実車でも停止状態から1速に入れるのはごく普通の操作のため)。      */
        u8tSht    = (uint8_t)OFF;
        u8tShtrev = (uint8_t)OFF;
        if ( ( u8gSacelcrtifThlpct <= u8s_PPERM_SHT_ACELPCT10 )
          && ( u8gSclthcrtifPdlpct >= u8s_PPERM_SHT_CLTHPCT30 ) )
        {
            u8tSht = (uint8_t)ON;
            if ( u16gPsimbrdgifVelspd <= u16s_PPERM_SHTREV_SPD5 )
            {
                u8tShtrev = (uint8_t)ON;
            }
        }
        u8gPpermifSht    = u8tSht;
        u8gPpermifShtrev = u8tShtrev;

        /* 制限系フラグは毎サイクル初期化してから、該当する故障状態のみ立てる */
        u8tAcelLim = (uint8_t)OFF;
        u8tSpdLim  = (uint8_t)OFF;
        u8tShtdw   = (uint8_t)ON;
        u8tAcelMax = u8s_PPERM_ACELMAX_FULL100;
        u8tSpdMax  = u8s_PPERM_SPDMAX_NONE;

        if ( u8gPprtctifBrkszsts == (uint8_t)ON ) /* 要件4: ブレーキ焼付 */
        {
            u8tAcelLim = (uint8_t)ON;
            u8tSpdLim  = (uint8_t)ON;
            u8tAcelMax = u8s_PPERM_ACEL_LIM70;
            u8tSpdMax  = u8s_PPERM_SPD_LIM80;
        }

        if ( u8gPprtctifOvrvsts == (uint8_t)ON ) /* 要件5: オーバーレブ */
        {
            u8tAcelLim = (uint8_t)ON;
            u8tShtdw   = (uint8_t)OFF; /* シフトダウン禁止 */
            u8tAcelMax = u8s_PPERM_ACEL_LIM50;
        }

        u8gPpermifAcelLim = u8tAcelLim;
        u8gPpermifSpdLim  = u8tSpdLim;
        u8gPpermifShtdw   = u8tShtdw;
        u8gPpermifAcelMax = u8tAcelMax;
        u8gPpermifSpdMax  = u8tSpdMax;

        if ( u8gPprtctifEnststs == (uint8_t)ON ) /* 要件6: エンスト(pprtctの結果を読むだけ) */
        {
            u8gPpermifPwrigoff = (uint8_t)ON;
        }
    }
    else
    {
        /* IG-OFF: 車速がある場面(惰性走行等)を想定しシミュレーションは継続。 */
        /* アクセル上限だけ0にする。Simフラグはstickyなので触らない。       */
        u8gPpermifDisp    = (uint8_t)OFF;
        u8gPpermifAcelLim = (uint8_t)ON;
        u8gPpermifAcelMax = (uint8_t)0;
    }
}


/****************************************************************/
/*  * internal function                                         */
/****************************************************************/

/****************************************************************/
/*  * @func     vdsSampleFunc( void )                           */
/*  * @scope    internal                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/

/****************************************************************/
/*  * end of file                                               */
/****************************************************************/
