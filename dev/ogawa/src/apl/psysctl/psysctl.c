/****************************************************************/
/*  * @file     psysctl.c                                       */
/*  * @brief    apl system control                              */
/*  * @domain   apllication                                     */
/*  * @date     2026/08/11                                      */
/*  * @(c)      2026 ocml                                       */
/****************************************************************/

/****************************************************************/
/*  * include                                                   */
/****************************************************************/
#include "../../inc/common.h" /* 共通ライブラリ */
#include "../../inc/shrmcr.h" /* 共通マクロ     */
                              /* s8g_SHAREMACROIF_GEAR_REVERSE */
#include "../ppermif.h"  /* u8gPpermifSht     */
                         /* u8gPpermifShtre   */
                         /* u8gPpermifAcelLim */
                         /* u8gPpermifAcelMax */
                         /* u8gPpermifSpdLim  */

/* ▼▼▼ 以下，SAC各部品からの入力はpioifを使用するため削除予定 ▼▼▼ */
/* #include "../../sac/sigswcrtif.h" */ /* u8gSigswcrtifSts    */
/* #include "../../sac/sgearcrtif.h" */ /* s8gSgearcrtifPos    */
                                        /* s8g_SGEARIF_REVERSE */
/* #include "../../sac/sbrkcrtif.h"  */ /* u8gSbrkcrtifPdlpct  */
/* #include "../../sac/sacelcrtif.h" */ /* u8gSclthcrtifPdlpct */
/* #include "../../sac/sclthcrtif.h" */ /* u8gSacelcrtifThlpct */
/* ▲▲▲ ------------------------ここまで---------------------- ▲▲▲ */
#include "../pioif.h"  /* u8gPioifIgsw */
                       /* u8gPioifAcel */
                       /* u8gPioifBrk  */
                       /* u8gPioifClth */
                       /* s8gPioifGear */
                       /* u16gPioifSpd */
                       /* u16gPioifRpm */
                       /* u16gPioifAcc */

#include "../psysctlif.h" /* 自ヘッダ */

/****************************************************************/
/*  * external public variables contains macros                 */
/****************************************************************/
int8_t s8gPsysctlGearpos;   /* ギア情報 R,N,1,2,3,4,5[-]    */
uint8_t u8gPsysctlAcelpct;  /* アクセル開度 0 - 100[%]      */
uint8_t u8gPsysctlBrkpct;   /* ブレーキ開度 0 - 100[%]      */
uint8_t u8gPsysctlClthpct;  /* クラッチ開度 0 - 100[%]      */

/****************************************************************/
/*  * internal public variables contains macros                  */
/****************************************************************/
#define s8g_PSYSCTL_INITGEAR  ((int8_t)0)  /* イグニッション状態 OFF[-] */
#define s8g_PSYSCTL_ACEL_NONE ((uint8_t)0) /* アクセル開度 0[%]         */

#define u8s_PSYSCTL_BRK_ADD  ((uint8_t)((50.)/((100.)/(256.)))

/****************************************************************/
/*  * external function                                         */
/****************************************************************/

/****************************************************************/
/*  * @func     vdgPsysctlInit( void )                          */
/*  * @scope    external                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgPsysctlInit( void )
{
    /* 初期化 */
    s8gPsysctlGearpos = s8g_PSYSCTL_INITGEAR;
    s8gPsysctlAcelpct = s8g_PSYSCTL_ACEL_NONE;
}

/****************************************************************/
/*  * @func     vdgPsysctl16ms( void )                          */
/*  * @scope    external                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgPsysctl16ms( void )
{

    int8_t  s8tGearpos; /* ギア情報 */
    uint8_t u8tAcelpct; /* アクセル開度 */
    uint8_t u8tSpdval;  /* 車速 */
    uint8_t u8tBrkpct;  /* ブレーキ開度 */
    uint8_t u8tClthpct; /* ブレーキ開度 */

    s8tGearpos = s8gPioifGear;
    u8tAcelpct = u8gPioifAcel;
    u8tSpdval  = u16gPioifSpd;
    u8tBrkpct  = u8gPioifBrk;
    u8tClthpct = u8gPioifClth;

    if ( u8gPioifIgsw == (uint8_t)ON ) /* イグニッション状態がONの場合 */
    {
        if ( s8gPioifGear == s8g_SHAREMACROIF_GEAR_REVERSE ) /* ギア情報がリバースの場合 */
        {
            if ( u8gPpermifShtre == (uint8_t)ON ) /* ギア遷移許可(リバース)がONの場合 */
            {
                s8tGearpos = s8gPioifGear; /* リバースギア情報をラッチ */
            }
        }
        else /* ギア情報がリバース以外の場合 */
        {
            if ( u8gPpermifShtre == (uint8_t)ON ) /* ギア遷移許可(通常)がONの場合 */
            {
                s8tGearpos = s8gPioifGear; /* ギア情報をラッチ */
            }
        }
 
        if ( u8gPpermifAcelLim == (uint8_t)ON ) /* アクセル制限フラグがONの場合 */
        {
            u8tAcelpct = u8gPpermifAcelMax; /* アクセルをアクセル上限値に設定 */
        }

        if ( u8gPpermifSpdLim == (uint8_t)ON ) /* 車速制限フラグがONの場合 */
        {
            if ( u16gPioifSpd > u8gPpermifSpdMax ) 
            {
                u8tSpdval = u8gPpermifSpdMax; /* 車速を車速上限値に設定 */
                u8tBrkpct = u8gPioifBrk + u8s_PSYSCTL_BRK_ADD  /* ブレーキに設定値加算 */

                if ( u8tBrkpct > u8s_PSYSCTL_BRK_MAX ) /* ブレーキが100%を超えた場合 */
                {
                    u8tBrkpct = u8s_PSYSCTL_BRK_MAX; /* ブレーキを100%に設定 */
                }
            }
        }
    }
    else /* イグニッション状態がOFFの場合 */
    {
        /* 各変数をシャットダウン状態に遷移 */
        u8tAcelpct   = (uint8_t)0;
        u8tBrkpct    = (uint8_t)0;
        u8tClthpct   = (uint8_t)0;
        s8tGearpos   = (uint8_t)0;
        u8tSpdval    = (uint8_t)0;
        u16gPioifRpm = (uint8_t)0;
        u16gPioifAcc = (uint8_t)0;
        u8gPioifStsStop  = (uint8_t)ON;
        u8gPioifStsRun   = (uint8_t)OFF;
        u8gPioifStsSpdsw = (uint8_t)OFF;
        u8gPioifStsEnst  = (uint8_t)OFF;
    }

    s8gPioifGear = s8tGearpos;
    u8gPioifAcel = u8tAcelpct;
    u16gPioifSpd = u8tSpdval;
    u8gPioifBrk  = u8tBrkpct;
    u8gPioifClth = u8tClthpct;

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
