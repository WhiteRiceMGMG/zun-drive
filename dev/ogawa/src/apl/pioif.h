/****************************************************************/
/*  * @file     pioif.h                                         */
/*  * @brief    -                                               */
/*  * @domain   -                                               */
/*  * @date     2026/08/26                                      */
/*  * @(c)      2026 ocml                                       */
/****************************************************************/
#ifndef PIOIF_H
#define PIOIF_H

/****************************************************************/
/*  * include                                                   */
/****************************************************************/


#include "../../sim/mioif.h"   /* u16gMioifRPM     */
                               /* u16gMioifSpd     */
                               /* u16gMioifAcc     */



/****************************************************************/
/*  * external public variables contains macros                 */
/****************************************************************/
extern uint8_t u8gPioifIgsw; /* APL層専用イグニッション状態 ON,OFF[-] */
extern uint8_t u8gPioifAcel; /* APL層専用アクセル開度 0 - 100[%]      */
extern uint8_t u8gPioifBrk;  /* APL層専用ブレーキ開度 0 - 100[%]      */
extern uint8_t u8gPioifClth; /* APL層専用クラッチ開度 0 - 100[%]      */
extern int8_t  s8gPioifGear; /* APL層専用ギア情報 R,N,1,2,3,4,5[-]    */

/* ▼▼▼ 以下，データ型は暫定のため要確認 ▼▼▼ */
extern uint16_t u16gPioifSpd; /* APL層専用車速 0 - 300[km/h]    */
extern uint16_t u16gPioifRpm; /* APL層専用回転数 0 - 20000[rpm] */
extern uint16_t u16gPioifAcc; /* APL層専用加速度 0 - 2[m/ss]  */
/* ▲▲▲ -----------ここまで------------- ▲▲▲ */

extern uint8_t u8gPioifStsStop;  /* ずんだもん状態：ストップ ON,OFF[-] */
extern uint8_t u8gPioifStsRun;   /* ずんだもん状態：走行 ON,OFF[-]     */
extern uint8_t u8gPioifStsSpdup; /* ずんだもん状態：加速 ON,OFF[-]     */
extern uint8_t u8gPioifStsSpdsw; /* ずんだもん状態：減速 ON,OFF[-]     */
extern uint8_t u8gPioifStsEnst;  /* ずんだもん状態：エンスト ON,OFF[-] */


/* ▼▼▼ 以下，ずん状態はAPLでRAM確保予定のため削除 ▼▼▼ */
/* #define u8gPioifStsStop   u8gMioifStsStop   */
/* #define u8gPioifStsRun    u8gMioifStsRun    */
/* #define u8gPioifStsSpdup  u8gMioifStsSpdup  */
/* #define u8gPioifStsSpdsw  u8gMioifStsSpdsw  */
/* #define u8gPioifStsEnst   u8gMioifStsEnst   */
/* ▲▲▲ ----------------ここまで------------------ ▲▲▲ */

/****************************************************************/
/*  * external function prototyp                                */
/****************************************************************/
void vdgPioifInit( void );
void vdgPioif4ms( void );
void vdgPioif16ms( void );
void vdgPioif64ms( void );

#endif
/****************************************************************/
/*  * end of file                                               */
/****************************************************************/

