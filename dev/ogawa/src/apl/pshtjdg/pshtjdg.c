/****************************************************************/
/*  * @file     pshtjdg.c                                       */
/*  * @brief    シフト遷移調停                                  */
/*  * @domain   APL                                             */
/*  * @date     2026.09.18 新規作成                             */
/*              2026.09.26 機能レベルアップ                     */
/*              2026.10.01 回転数スケーリング違い検討不足       */
/*              2026.10.02 回転数スケーリング検討済             */
/*              次回，レブマッチング機能実装予定                */
/*  * @(c)      2026 ocml                                       */
/****************************************************************/

/****************************************************************/
/*  * include                                                   */
/****************************************************************/
#include "../../inc/common.h" /* 共通ライブラリ */
                              /* u16g_MAX       */


#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
#include "../../../debug/log/print_log.h"
#endif

#include "../../sac/sacelcrtif.h" /* u8gSacelcrtifthlpct, lsb=100/256 */
#include "../../sac/sclthcrtif.h" /* u8gSclthcrtifPdlpct, lsb=100/256 */
#include "../../sac/sbrkcrtif.h"  /* u8gSbrkcrtifPdlpct,  lsb=100/256 */
#include "../../sac/sgearcrtif.h" /* s8gSgearcrtifPos, lsb=1          */

#include "../../sim/mspdif.h"     /* u8gMspdifspd, lsb=300/256           */
#include "../../sim/mrpmif.h"     /* u16gMrpmifengrpm, lsb=15000/256/256 */

#include "../../sim/simconfif.h" /* u8g_SIMCONFIF_GEARRATE_R, lsb=5/256 */
                                 /* u8g_SIMCONFIF_GEARRATE_N, lsb=5/256 */
                                 /* u8g_SIMCONFIF_GEARRATE_1, lsb=5/256 */
                                 /* u8g_SIMCONFIF_GEARRATE_2, lsb=5/256 */
                                 /* u8g_SIMCONFIF_GEARRATE_3, lsb=5/256 */
                                 /* u8g_SIMCONFIF_GEARRATE_4, lsb=5/256 */
                                 /* u8g_SIMCONFIF_GEARRATE_5, lsb=5/256 */
                                 /* u8s_PSHTJDG_GEARRATE_NUM, lsb=1     */
                                 /* s8g_SIMCONFIF_GEARPOS_R, lsb=1      */
                                 /* s8g_SIMCONFIF_GEARPOS_N, lsb=1      */
                                 /* s8g_SIMCONFIF_GEARPOS_1, lsb=1      */
                                 /* u16g_SIMCONFIF_RPMMAX, lsb=15000/256/256 */

/****************************************************************/
/*  * external public variables contains macros                 */
/****************************************************************/
uint8 u8gPshtjdgifChgeq;   /* APLシフト遷移要求, lsb=1   */
sint8 s8gPshtjdgifCfrmSht; /* APL確定シフト遷移先, lsb=1 */


/****************************************************************/
/*  * internal public variables contains macros                 */
/****************************************************************/
static uint8 u8sPshtjdgReq( void );  /* シフト遷移要求判定関数 */
static void  vdsPshtjdgChg( uint8 ); /* シフト遷移判定関数     */

static sint8 s8sPshtjdgSht_o; /* シフト前回値, lsb=1 */
#define u8s_PSHTJDG_REQ_NONE    ((uint8)0) /* 要求なし, lsb=1 */
#define u8s_PSHTJDG_REQ_NEUTRAL ((uint8)1) /* シフトニュートラル要求, lsb=1 */
#define u8s_PSHTJDG_REQ_REVERSE ((uint8)2) /* シフトリバース要求 ,lsb=1     */
#define u8s_PSHTJDG_REQ_SHTUP   ((uint8)3) /* シフトアップ要求, lsb=1       */
#define u8s_PSHTJDG_REQ_SHTDW   ((uint8)4) /* シフトダウン要求, lsb=1       */

/* リバース判定用車速閾値, lsb=300/256 */
#define u8s_PSHTJDG_REV_SPD  ((uint8)((5.)/((300.)/(256.))+0.5))
/* リバース判定用クラッチ開度閾値, lsb=100/256 */  
#define u8s_PSHTJDG_REV_CLTH ((uint8)((90.)/((100.)/(256.))+0.5))
/* リバース判定用アクセル開度閾値, lsb=100/256 */ 
#define u8s_PSHTJDG_REV_ACEL ((uint8)((5.)/((100.)/(256.))+0.5))  

/* シフトアップ判定用クラッチ開度閾値, lsb=100/256 */
#define u8s_PSHTJDG_SHTUP_CLTH ((uint8)((80.)/((100.)/(256.))+0.5))
/* シフトアップ判定用回転数閾値, lsb=15000/256/256 */
#define u16s_PSHTJDG_SHTUP_RPM ((uint16)((1500.)/((15000.)/(256.)/(256.))+0.5))
/* シフトアップ判定用アクセル開度閾値, lsb=100/256 */
#define u8s_PSHTJDG_SHTUP_ACEL ((uint8)((10.)/((100.)/(256.))+0.5))

/* シフトダウン判定用クラッチ開度閾値, lsb=100/256 */
#define u8s_PSHTJDG_SHTDW_CLTH ((uint8)((80.)/((100.)/(256.))+0.5))

/* ▼▼▼以下ダミー値のため設定すること▼▼▼ */
/* 目標回転数演算用ファイナル比 */
#define u8s_PSHTJDG_FINAL_RATE ((uint8)((3.)/((5.)/(256.))+0.5))
/* 目標回転数演算用変換値 */
#define phs_PSHTJDG_KMH_RPM    (8.8)
#define u8s_PSHTJDG_KMH_RPM    ((uint8)((phs_PSHTJDG_KMH_RPM)/((10.)/(256.))+0.5))

/* LSB補正用マクロ */
#if ( FPU_CALC == FPU_DISENABLE ) /* 浮動小数使用不可の場合 */
#define u16s_PSHTJDG_LSB_DIV  ((uint16)( ((15000.)/(256.)/(256.))/(((300.)/(256.))*((5.)/(256.))*((5.)/(256.))*((10.)/(256.)))))
#else /* 浮動小数使用可能の場合 */
#define f32s_PSHTJDG_LSB_CONV  ((float32)(((300.)/(256.))*((5.)/(256.))*((5.)/(256.))*((10.)/(256.))/((15000.)/(256.)/(256.))))
#endif
/* ▲▲▲以上ダミー値のため設定すること▲▲▲ */

/* #define _u8s_PSHTJDG_GEARRATE_NUM ((uint8)7)*/ /* ギア種類数設定 */
volatile const uint8 u8sPshtjdgTrgrate[ u8s_PSHTJDG_GEARRATE_NUM ] = 
    { u8g_SIMCONFIF_GEARRATE_R,  /* ギア比(R) */
      u8g_SIMCONFIF_GEARRATE_N,  /* ギア比(N) */
      u8g_SIMCONFIF_GEARRATE_1,  /* ギア比(1) */
      u8g_SIMCONFIF_GEARRATE_2,  /* ギア比(2) */
      u8g_SIMCONFIF_GEARRATE_3,  /* ギア比(3) */
      u8g_SIMCONFIF_GEARRATE_4,  /* ギア比(4) */
      u8g_SIMCONFIF_GEARRATE_5   /* ギア比(5) */
    };

/****************************************************************/
/*  * external function                                         */
/****************************************************************/

/****************************************************************/
/*  * @func     vdgPshtjdgidInit( void )                        */
/*  * @scope    external                                        */
/*  * @brief    シフト遷移調停init関数                          */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgPshtjdgidInit( void )
{
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogPrint( "start vdgPshtjdgidInit()" );
    vdgLogArgPrint( "in : u8gPshtjdgifChgeq = %d", (uint32_t)u8gPshtjdgifChgeq );
    vdgLogArgPrint( "in : s8gPshtjdgifCfrmSht = %d", (uint32_t)s8gPshtjdgifCfrmSht );
    vdgLogArgPrint( "in : s8sPshtjdgSht_o = %d", (uint32_t)s8sPshtjdgSht_o );
#endif

    u8gPshtjdgifChgeq   = u8s_PSHTJDG_REQ_NEUTRAL;
    s8gPshtjdgifCfrmSht = s8g_SIMCONFIF_GEARPOS_N;
    s8sPshtjdgSht_o     = s8g_SIMCONFIF_GEARPOS_N;

#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogArgPrint( "out : u8gPshtjdgifChgeq = %d", (uint32_t)u8gPshtjdgifChgeq );
    vdgLogArgPrint( "out : s8gPshtjdgifCfrmSht = %d", (uint32_t)s8gPshtjdgifCfrmSht );
    vdgLogArgPrint( "out : s8sPshtjdgSht_o = %d", (uint32_t)s8sPshtjdgSht_o );
    vdgLogPrint( "end vdgPshtjdgidInit()" );
    
#endif
}

/****************************************************************/
/*  * @func     vdgPshtjdgif16ms( void )                        */
/*  * @scope    external                                        */
/*  * @brief    シフト遷移調停16ms関数                          */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgPshtjdgif16ms( void )
{
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogPrint( "start vdgPshtjdgif16ms()" );
#endif

    uint8 u8tShtreq; /* 遷移要求 */

    u8tShtreq = u8sPshtjdgReq(); /* 遷移要求判定の返り値で更新 */
    vdsPshtjdgChg( u8tShtreq );  /* 遷移判定をコール */

#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogPrint( "end vdgPshtjdgif16ms()" );
#endif

}

/****************************************************************/
/*  * internal function                                         */
/****************************************************************/

/****************************************************************/
/*  * @func     u8sPshtjdgReq( void )                           */
/*  * @scope    internal                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   シフト遷移要求                                  */
/****************************************************************/
uint8
u8sPshtjdgReq( void )
{
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogPrint( "start u8sPshtjdgReq()" );
    vdgLogArgPrint( "in : s8gSgearcrtifPos = %d", (uint32_t)s8gSgearcrtifPos );
    vdgLogArgPrint( "in : s8sPshtjdgSht_o = %d", (uint32_t)s8sPshtjdgSht_o );
    vdgLogArgPrint( "in : u8gPshtjdgifChgeq = %d", (uint32_t)u8gPshtjdgifChgeq );
#endif

    sint8 s8tGear;   /* ギア           */
    sint8 s8tGear_o; /* ギア前回値     */
    uint8 u8tShtreq; /* シフト遷移要求 */

    s8tGear = s8gSgearcrtifPos;  /* 最新のギア値を保持する */
    s8tGear_o = s8sPshtjdgSht_o; /* ギア前回値を保持する */

    u8tShtreq = u8s_PSHTJDG_REQ_NONE; /* 要求なしを初期値に設定 */
    /* ギア最新値がニュートラルの場合 */
    if ( s8tGear == s8g_SIMCONFIF_GEARPOS_N )
    {
        u8tShtreq = u8s_PSHTJDG_REQ_NEUTRAL; /* N遷移要求設定 */
    }
    /* ギア最新値がリバースの場合 */
    else if ( s8tGear == s8g_SIMCONFIF_GEARPOS_R )
    {
        u8tShtreq = u8s_PSHTJDG_REQ_REVERSE; /* R遷移要求設定 */
    }
    /* ギア最新値が前回値より大きい場合 */
    else if ( s8tGear > s8tGear_o )
    {
        u8tShtreq = u8s_PSHTJDG_REQ_SHTUP; /* シフトアップ要求設定 */
    }
    /* ギア最新値が前回値より小さい場合 */
    else if ( s8tGear < s8tGear_o )
    {
        u8tShtreq = u8s_PSHTJDG_REQ_SHTDW; /* シフトダウン要求設定 */
    }

    u8gPshtjdgifChgeq = u8tShtreq; /* APLシフト遷移要求を更新 */

    return u8tShtreq; /* シフト遷移要求を返す */

#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogArgPrint( "out : s8gSgearcrtifPos = %d", (uint32_t)s8gSgearcrtifPos );
    vdgLogArgPrint( "out : s8sPshtjdgSht_o = %d", (uint32_t)s8sPshtjdgSht_o );
    vdgLogArgPrint( "out : u8gPshtjdgifChgeq = %d", (uint32_t)u8gPshtjdgifChgeq );
    vdgLogPrint( "end u8sPshtjdgReq()" );
#endif
}

/****************************************************************/
/*  * @func     vdsPshtjdgChg( void )                           */
/*  * @scope    internal                                        */
/*  * @brief    -                                               */
/*  * @param    シフト遷移要求                                  */
/*  * @return   -                                               */
/****************************************************************/
void
vdsPshtjdgChg( uint8 u8tShtreq )
{
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogPrint( "start vdsPshtjdgChg()" );
    vdgLogArgPrint( "in : s8gSgearcrtifPos = %d", (uint32_t)s8gSgearcrtifPos );
    vdgLogArgPrint( "in : u8gMspdifspd = %d", (uint32_t)u8gMspdifspd );
    vdgLogArgPrint( "in : u8gSclthcrtifPdlpct = %d", (uint32_t)u8gSclthcrtifPdlpct );
    vdgLogArgPrint( "in : u8gSacelcrtifthlpct = %d", (uint32_t)u8gSacelcrtifthlpct );
    vdgLogArgPrint( "in : s8gPshtjdgifCfrmSht = %d", (uint32_t)s8gPshtjdgifCfrmSht );
    vdgLogArgPrint( "in : s8sPshtjdgSht_o = %d", (uint32_t)s8sPshtjdgSht_o );
#endif

    uint8 u8tShtperm;     /* 遷移許可 */
    sint8 s8tGearpos;     /* 最新(生値)ギア値 */
    uint8 u8tGearpos_idx; /* 配列使用用最新ギア値変換値 */
    uint16 u16tTrgrpm;    /* 目標回転数 lsb=15000/256/256*/
    uint32 u32tTrgrpm_tmp;    /* 一時利用用目標回転数 lsb=15000/256/256*/
    sint8 s8tGearpos_o;   /* 前回値(確定値) */
#if ( FPU_CALC == FPU_ENABLE ) /* 浮動小数使用可能の場合 */
    float32 f32tTrgrpm_tmp; /* 浮動小数演算用 */
#endif

    u8tShtperm = (uint8)OFF;
    s8tGearpos = s8gSgearcrtifPos; /* 最新(生値)ギア値で更新 */
    s8tGearpos_o = s8sPshtjdgSht_o; /* 前回値(確定値)で更新  */

    switch ( u8tShtreq )
    {
        case u8s_PSHTJDG_REQ_NEUTRAL: /* ニュートラル遷移要求 */
            u8tShtperm = (uint8)ON;
            break;
        case u8s_PSHTJDG_REQ_REVERSE: /* リバース遷移要求 */
            if ( ( u8gMspdifspd < u8s_PSHTJDG_REV_SPD ) /* 車速 < 5km/h*/
              && ( u8gSclthcrtifPdlpct > u8s_PSHTJDG_REV_CLTH ) /* クラッチ開度 > 90% */
              && ( u8gSacelcrtifthlpct < u8s_PSHTJDG_REV_ACEL ) ) /* アクセル開度 < 5% */
            {
                u8tShtperm = (uint8)ON;
            }
            break;
        case u8s_PSHTJDG_REQ_SHTUP: /* シフトアップ要求 */
            /* ニュートラルからシフトアップする場合は常時許可 */
            if ( s8tGearpos_o == s8g_SIMCONFIF_GEARPOS_N )
            {
                u8tShtperm = (uint8)ON; /* 常時許可 */
            }
            else /* ニュートラル以外のシフトアップの場合 */
            {
                /* クラッチ開度 > 80% かつ 回転数 > 1500rpm かつ アクセル開度 < 10% */
                if ( ( u8gSclthcrtifPdlpct > u8s_PSHTJDG_SHTUP_CLTH )
                  && ( u16gMrpmifengrpm > u16s_PSHTJDG_SHTUP_RPM )
                  && ( u8gSacelcrtifthlpct < u8s_PSHTJDG_SHTUP_ACEL ) )
                {
                    u8tShtperm = (uint8)ON; /* シフトアップ許可 */
                }
            }
            break;
        case u8s_PSHTJDG_REQ_SHTDW: /* シフトダウン許可 */
            /* ギア確定値が2以上の場合のみシフトダウン調停を行う */
            if ( s8tGearpos_o > s8g_SIMCONFIF_GEARPOS_1 )
            {
                /* シフトダウン時使用．最新ギア値から配列要素指定番号へ変換する */
                u8tGearpos_idx = (uint8)(s8tGearpos + 1);
                
                /* 配列領域外への意図しないアクセスを防ぐためガード処理を実施する                     */
                /* キャストにて0以上を保証しており，仮にラップアラウンドした場合もガード処理に入る．  */
                /* そのため処理負荷も考慮し，0以下ガードは実装しない                                  */
                if ( u8tGearpos_idx >= u8s_PSHTJDG_GEARRATE_NUM )
                {
                    u8tShtperm = (uint8)OFF; /* シフトダウン拒否 */
                }
                else /* 配列使用用最新ギア値変換値が0から6のとき */
                {
                    /* 遷移先回転数演算                                                              */
                    /* ターゲット回転数 = 車速 x ギア比率 x ファイナル比 x 単位変換係数(km/h → rpm) */
                    /* 遷移先回転数配列に最新(目標)ギア値を入れ，回転数演算実施                      */
                    
                    /* ▼▼▼演算時は一時的に32bitへ拡張する▼▼▼ */
                    u32tTrgrpm_tmp = (uint32)u8gMspdifspd
                                   * (uint32)u8sPshtjdgTrgrate[u8tGearpos_idx]
                                   * (uint32)u8s_PSHTJDG_FINAL_RATE
                                   * (uint32)u8s_PSHTJDG_KMH_RPM;
                    /* ▲▲▲演算時は一時的に32bitへ拡張する▲▲▲ */

                    /* 左右でLSBを合わせる補正演算 */
#if ( FPU_CALC == FPU_DISENABLE ) /* 浮動小数使用不可の場合 */
                        u32tTrgrpm_tmp = u32tTrgrpm_tmp / (uint32)u16s_PSHTJDG_LSB_DIV;
                         /* 上限ガード処理 */
                        if ( u32tTrgrpm_tmp > u16g_MAX )
                        {
                            u32tTrgrpm_tmp = u16g_MAX;
                        }
                        u16tTrgrpm = (uint16)u32tTrgrpm_tmp;
#else                             /* 浮動小数使用可能の場合 */
                        f32tTrgrpm_tmp = (float32)u32tTrgrpm_tmp * f32s_PSHTJDG_LSB_CONV;
                        if ( f32tTrgrpm_tmp > (float32)u16g_MAX )
                        {
                            f32tTrgrpm_tmp = (float32)u16g_MAX;
                        }
                        u16tTrgrpm = (uint16)f32tTrgrpm_tmp;
#endif

                    /* クラッチ開度 > 80% かつターゲット回転数 < 上限回転数の場合 */
                    if ( ( u8gSclthcrtifPdlpct > u8s_PSHTJDG_SHTDW_CLTH )
                      && ( u16tTrgrpm < u16g_SIMCONFIF_RPMMAX ) )
                    {
                        u8tShtperm = (uint8)ON; /* シフトダウン許可 */
                    }
                }
            }
            break;
        default:
            ; /* 処理なし */
            break;
    }
    /* 遷移許可がONの場合 */
    if ( u8tShtperm == (uint8)ON )
    {
        s8sPshtjdgSht_o = s8tGearpos;     /* ギア前回値(確定値)をギア最新値で更新       */
    }
    s8gPshtjdgifCfrmSht = s8sPshtjdgSht_o;     /* 確定シフト遷移先をギア最新値で更新 */

#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogArgPrint( "out : s8gSgearcrtifPos = %d", (uint32_t)s8gSgearcrtifPos );
    vdgLogArgPrint( "out : u8gMspdifspd = %d", (uint32_t)u8gMspdifspd );
    vdgLogArgPrint( "out : u8gSclthcrtifPdlpct = %d", (uint32_t)u8gSclthcrtifPdlpct );
    vdgLogArgPrint( "out : u8gSacelcrtifthlpct = %d", (uint32_t)u8gSacelcrtifthlpct );
    vdgLogArgPrint( "out : s8gPshtjdgifCfrmSht = %d", (uint32_t)s8gPshtjdgifCfrmSht );
    vdgLogArgPrint( "out : s8sPshtjdgSht_o = %d", (uint32_t)s8sPshtjdgSht_o );
    vdgLogPrint( "end vdsPshtjdgChg()" );
#endif
}

/****************************************************************/
/*  * end of file                                               */
/****************************************************************/
