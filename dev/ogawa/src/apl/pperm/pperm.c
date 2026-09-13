/****************************************************************/
/*  * @file     ppermif.c                                       */
/*  * @brief    許可・設定値調停                                */
/*  * @domain   -                                               */
/*  * @date     2026/08/04 新規作成                             */
/*  *           2026/09/10 pioI/Fの参照へ変更                   */
/*  *                      閾値自動反映修正                     */
/*  * @(c)      2026 ocml                                       */
/****************************************************************/

/****************************************************************/
/*  * include                                                   */
/****************************************************************/
#include "../../inc/common.h"

/* ▼▼▼ 以下，SAC各部品からのインクルードは集約予定 ▼▼▼ */
#include "../pioif.h" /* u8gPioifClth */
                      /* u8gPioifIgsw */
                      /* u16gPioifSpd */
/* ▲▲▲ -----------------ここまで------------------ ▲▲▲ */

/* ▼▼▼ 以下，SAC各部品からのインクルードは集約予定 ▼▼▼ */
/* #include "../../sac/sacelcrtif.h" */ /* u8gSacelcrtifthlpct */
/* #include "../../sac/sclthcrtif.h" */ /* u8gSclthcrtifPdlpct */
/* #include "../../sac/sigswcrtif.h" */ /* u8gSigswifSts       */
/* #include "../pprtctif.h"*/ /* u8gPprtctifOvrvsts   */
                              /* u8gPprtctifClthszsts */
                              /* u8gPprtctifBrkszsts  */
                              /* u8gPprtctifEnststs   */
/* #include "../psimbrdif.h" */ /* u16gPsimbrdgifVelspd  */
/* ▲▲▲ -----------------ここまで------------------ ▲▲▲ */


#include "./pperm_conf.h" /* 自設定ヘッダ */
#include "../ppermif.h"   /* 自ヘッダ */


/****************************************************************/
/*  * external public variables contains macros                 */
/****************************************************************/
uint8_t  u8gPpermifSht;      /* シフト遷移(N)許可      */
uint8_t  u8gPpermifSim;      /* シミュレーション許可   */
uint8_t  u8gPpermifDisp;     /* 表示許可               */
uint8_t  u8gPpermifShtrev;   /* シフト遷移(R)許可      */
uint8_t  u8gPpermifAcelLim;  /* アクセル制限フラグ     */
uint8_t  u8gPpermifSpdLim;   /* スピード制限フラグ     */
uint8_t  u8gPpermifShtdw;    /* シフトダウン許可フラグ */
uint8_t  u8gPpermifPwrigoff; /* イグニッション強制OFFフラグ */
uint8_t  u8gPpermifAcelMax;  /* アクセル上限値         */
uint16_t u16gPpermifSpdMax;  /* スピード上限値         */

/****************************************************************/
/*  * internal public variables contains macros                 */
/****************************************************************/
/* シフト遷移許可判定用クラッチ開度マクロ     */
#define u8s_PPERM_SHT_CLTH        ((uint8_t)((phs_PPERM_SHT_CLTH)/(100.)/(256.)+0.5))
/* シフト遷移許可判定用スピードマクロ         */
#define u16s_PPERM_SHT_SPD        ((uint16_t)((phs_PPERM_SHT_SPD)/(300.)/(256.)/(256.)+0.5))
/* ブレーキ焼き付き時アクセル制限設定用マクロ */
#define u8s_PPERM_ACEL_BRKSZ_LIM  ((uint8_t)((phs_PPERM_ACEL_BRKSZ_LIM)/(100.)/(256.)+0.5))
/* オーバーレブ時アクセル制限設定用マクロ     */
#define u8s_PPERM_ACEL_OVRV_LIM   ((uint8_t)((phs_PPERM_ACEL_OVRV_LIM)/(100.)/(256.)+0.5))
/* ブレーキ焼き付き時スピード制限設定用マクロ */
#define u16s_PPERM_SPD_BRKSZ_LIM  ((uint16_t)((phs_PPERM_SPD_BRKSZ_LIM)/(300.)/(256.)/(256.)+0.5))

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
    u8gPpermifSpdLim;  = (uint8_t)OFF;
    u8gPpermifShtdw;   = (uint8_t)OFF;
    u8gPpermifPwrigoff = (uint8_t)OFF;
    u8gPpermifAcelMax  = (uint8_t)OFF;
    u8gPpermifSpdMax   = (uint8_t)OFF;
}

/****************************************************************/
/*  * @func     vdgPpermif16ms( void )                          */
/*  * @scope    external                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgPpermif16ms( void )
{
    
    if ( u8gPioifIgsw == (uint8_t)ON ) /* イグニッションがONの場合*/
    {
        if ( u8gPioifClth > u8s_PPERM_SHT_CLTHPCT30 ) /* クラッチが30%より大きい */
        {
            if ( u16gPioifSpd >= u16s_PPERM_SHT_SPD5 ) /* スピードが5km/h以上 */
            {
                u8gPpermifSht == (uint8_t)ON; /* シフト遷移許可(ノーマル)をON  */
            }
            if ( u16gPioifSpd < u16s_PPERM_SHTREV_SPD5 ) /* スピードが5km/hより小さい */
            {
                u8gPpermifShtrev == (uint8_t)ON; /* シフト遷移許可(リバース)をON */
            }
        }

        if ( u8gPprtctifBrkszsts == (uint8_t)ON ) /* ブレーキ焼き付きがONの場合 */
        {
            u8gPpermifAcelMax = u8s_PPERM_ACEL_LIM70;   /* アクセル上限を70% */
            u16gPpermifSpdMax = u16s_PPERM_SPD_LIM50;   /* スピードを50km/h  */
        }

        if ( u8gPprtctifOvrvst == (uint8_t)ON ) /* オーバーレブがONの場合 */
        {
            u8gPpermifAcelMax = u8s_PPERM_ACEL_LIM50; /* アクセル上限を50%     */
            u8gPpermifShtdw   = (uint8_t)OFF;         /* シフトダウン許可をOFF */
        }

        if ( u8gPprtctifEnststs == (uint8_t)ON ) /* エンストがONの場合*/
        {
            u8gPprtctifEnststs = (uint8_t)OFF; /* エンストをOFF         */
            u8gPpermifPwrIgoff = (uint8_t)ON;  /* イグニッション強制OFF */
        }
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
