/* SACからの入力は定義済．SIM層からの車速と加速度，回転数は */
/* データ型・更新周期が確定していないため，暫定で作成．     */

/****************************************************************/
/*  * @file     pioif.c                                         */
/*  * @brief    apl input output interface                      */
/*  * @domain   apllication                                     */
/*  * @date     2026/08/29                                      */
/*  * @(c)      2026 ocml                                       */
/****************************************************************/

/****************************************************************/
/*  * include                                                   */
/****************************************************************/
#include "../../inc/common.h" /* 共通ライブラリ */

#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
#include "../../../debug/log/print_log.h"
#endif


/* ▼▼▼ 以下，SAC各部品からのインクルードは集約予定 ▼▼▼ */
#include "../../sac/sacelcrtif.h" /* u8gSacelcrtifthlpct */
#include "../../sac/sclthcrtif.h" /* u8gSclthcrtifPdlpct */
#include "../../sac/sbrkcrtif.h"  /* u8gSbrkcrtifPdlpct  */
#include "../../sac/sigswcrtif.h" /* u8gSigswifSts       */
#include "../../sac/sgearcrtif.h" /* s8gSgearcrtifPos    */
/* #include "../../sac/sioif.h"(未作成)                  */
/* ▲▲▲ -----------------ここまで------------------ ▲▲▲ */

/* ▼▼▼ 以下，SIMからのinclude差し込み予定 ▼▼▼ */
/* pioif.hでインクルード済のためコメントアウト */
/* #include "../../sim/mioif.h" *//* u16gMioifRPM     */
                                  /* u16gMioifSpd     */
                                  /* u16gMioifAcc     */
/* ▲▲▲ -------------ここまで------------- ▲▲▲ */

#include "../pioif.h" /* 自ヘッダ */

/****************************************************************/
/*  * external public variables contains macros                 */
/****************************************************************/
uint8_t u8gPioifIgsw; /* APL層専用イグニッション状態 ON,OFF[-] */
uint8_t u8gPioifAcel; /* APL層専用アクセル開度 0 - 100[%]      */
uint8_t u8gPioifBrk;  /* APL層専用ブレーキ開度 0 - 100[%]      */
uint8_t u8gPioifClth; /* APL層専用クラッチ開度 0 - 100[%]      */
int8_t  s8gPioifGear; /* APL層専用ギア情報 R,N,1,2,3,4,5[-]    */

/* ▼▼▼ 以下，データ型は暫定のため要確認 ▼▼▼ */
uint16_t u16gPioifSpd; /* APL層専用車速 0 - 300[km/h]    */
uint16_t u16gPioifRpm; /* APL層専用回転数 0 - 20000[rpm] */
uint16_t u16gPioifAcc; /* APL層専用加速度 0 - 2[m/ss]  */
/* ▲▲▲ -----------ここまで------------- ▲▲▲ */

uint8_t u8gPioifStsStop;  /* ずんだもん状態：ストップ ON,OFF[-] */
uint8_t u8gPioifStsRun;   /* ずんだもん状態：走行 ON,OFF[-]     */
uint8_t u8gPioifStsSpdup; /* ずんだもん状態：加速 ON,OFF[-]     */
uint8_t u8gPioifStsSpdsw; /* ずんだもん状態：減速 ON,OFF[-]     */
uint8_t u8gPioifStsEnst;  /* ずんだもん状態：エンスト ON,OFF[-] */

/****************************************************************/
/*  * internal public variables contains macros                 */
/****************************************************************/

#define u8s_PIOIF_IGSW_OFF  ((uint8_t)OFF) /* APL層専用イグニッション状態 OFF[-] */
#define u8s_PIOIF_ACEL_NONE ((uint8_t)0)   /* APL層専用アクセル開度 0[%] */
#define u8s_PIOIF_BRK_NONE  ((uint8_t)0)   /* APL層専用ブレーキ開度 0[%] */
#define u8s_PIOIF_CLTH_NONE ((uint8_t)0)   /* APL層専用クラッチ開度 0[%] */
#define u8s_PIOIF_GEAR_NTL  ((uint8_t)0)   /* APL層専用ギア情報 N[-]      */

#define u8s_PIOIF_SPD_NONE  ((uint8_t)0)  /* APL層専用車速   0[km/h] */
#define u8s_PIOIF_RPM_NONE  ((uint8_t)0)  /* APL層専用回転数 0[rpm]  */
#define u8s_PIOIF_ACC_NONE  ((uint8_t)0)  /* APL層専用加速度 0[m/ss] */

/****************************************************************/
/*  * external function                                         */
/****************************************************************/

/****************************************************************/
/*  * @func     vdgPioifInit( void )                            */
/*  * @scope    external                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgPioifInit( void )
{
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogPrint( "start vdgPioifInit()" );
#endif

    /* 初期化 */
    u8gPioifIgsw = u8s_PIOIF_IGSW_OFF;
    u8gPioifAcel = u8s_PIOIF_ACEL_NONE;
    u8gPioifBrk  = u8s_PIOIF_BRK_NONE;
    u8gPioifClth = u8s_PIOIF_CLTH_NONE;
    
    s8gPioifGear = u8s_PIOIF_GEAR_NTL;
    u8gPioifSpd  = u8s_PIOIF_SPD_NONE;
    u8gPioifRpm  = u8s_PIOIF_RPM_NONE;
    u8gPioifAcc  = u8s_PIOIF_ACC_NINE;
    
    u8gPioifStsStop  = ((uint8_t)ON);
    u8gPioifStsRun   = ((uint8_t)OFF);
    u8gPioifStsSpdup = ((uint8_t)OFF);
    u8gPioifStsSpdsw = ((uint8_t)OFF);
    u8gPioifStsEnst  = ((uint8_t)OFF);
    
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogArgPrint( "u8gPioifIgsw = %d", (uint32_t)u8gPioifIgsw );
    vdgLogArgPrint( "u8gPioifAcel = %d", (uint32_t)u8gPioifAcel );
    vdgLogArgPrint( "u8gPioifBrk = %d", (uint32_t)u8gPioifBrk );
    vdgLogArgPrint( "u8gPioifClth = %d", (uint32_t)u8gPioifClth );
    vdgLogArgPrint( "s8gPioifGear = %d", (uint32_t)s8gPioifGear );
    vdgLogArgPrint( "u8gPioifSpd = %d", (uint32_t)u8gPioifSpd );
    vdgLogArgPrint( "u8gPioifRpm = %d", (uint32_t)u8gPioifRpm );
    vdgLogArgPrint( "u8gPioifAcc = %d", (uint32_t)u8gPioifAcc );
    vdgLogArgPrint( "u8gPioifStsStop = %d", (uint32_t)u8gPioifStsStop );
    vdgLogArgPrint( "u8gPioifStsRun = %d", (uint32_t)u8gPioifStsRun );
    vdgLogArgPrint( "u8gPioifStsSpdup = %d", (uint32_t)u8gPioifStsSpdup );
    vdgLogArgPrint( "u8gPioifStsSpdsw = %d", (uint32_t)u8gPioifStsSpdsw );
    vdgLogArgPrint( "u8gPioifStsEnst = %d", (uint32_t)u8gPioifStsEnst );
#endif
}

/****************************************************************/
/*  * @func     vdgPioif4ms( void )                             */
/*  * @scope    external                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgPioif4ms( void )
{
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogPrint( "start vdgPioif4ms()" );
#endif

    u8gPioifAcel = u8gSacelcrtifthlpct;
    u8gPioifBrk = u8gSbrkcrtifPdlpct;

/* ▼▼▼ 以下，更新周期は暫定のため要確認 ▼▼▼ */
    u16gPioifSpd = u16gMioifSpd;
    u16gPioifAcc = u16gMioifAcc;
/* ▲▲▲ -----------ここまで------------- ▲▲▲ */

#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogArgPrint( "u8gPioifAcel = %d", (uint32_t)u8gPioifAcel );
    vdgLogArgPrint( "u8gPioifBrk = %d", (uint32_t)u8gPioifBrk );
    vdgLogArgPrint( "u16gPioifSpd = %d", (uint32_t)u16gPioifSpd );
    vdgLogArgPrint( "u16gPioifAcc = %d", (uint32_t)u16gPioifAcc );
#endif

}

/****************************************************************/
/*  * @func     vdgPioif16ms( void )                            */
/*  * @scope    external                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgPioif16ms( void )
{
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogPrint( "start vdgPioif16ms()" );
#endif

    u8gPioifClth = vdgSclthcrtif16msin;

#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogArgPrint( "u8gPioifClth = %d", (uint32_t)u8gPioifClth );
#endif
}

/****************************************************************/
/*  * @func     vdgPioif64ms( void )                            */
/*  * @scope    external                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgPioif64ms( void )
{
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogPrint( "start vdgPioif64ms()" );
#endif

    u8gPioifIgsw = u8gSigswifSts;
    s8gPioifGear = s8gSgearcrtifPos;
    
    /* zundamon status */
    u8gPioifStsStop  = u8gMioifStsStop;
    u8gPioifStsRun   = u8gMioifStsRun;
    u8gPioifStsSpdup = u8gMioifStsSpdup;
    u8gPioifStsSpdsw = u8gMioifStsSpdsw;
    u8gPioifStsEnst  = u8gMioifStsEnst;
    
    /* ▼▼▼ 以下，更新周期は暫定のため要確認 ▼▼▼ */
    u16gPioifRpm = u16gMioifRPM;
    /* ▲▲▲ -----------ここまで------------- ▲▲▲ */

#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogArgPrint( "u8gPioifIgsw = %d", (uint32_t)u8gPioifIgsw );
    vdgLogArgPrint( "s8gPioifGear = %d", (uint32_t)s8gPioifGear );
    vdgLogArgPrint( "u8gPioifStsStop = %d", (uint32_t)u8gPioifStsStop );
    vdgLogArgPrint( "u8gPioifStsRun = %d", (uint32_t)u8gPioifStsRun );
    vdgLogArgPrint( "u8gPioifStsSpdup = %d", (uint32_t)u8gPioifStsSpdup );
    vdgLogArgPrint( "u8gPioifStsSpdsw = %d", (uint32_t)u8gPioifStsSpdsw );
    vdgLogArgPrint( "u8gPioifStsEnst = %d", (uint32_t)u8gPioifStsEnst );
#endif

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
