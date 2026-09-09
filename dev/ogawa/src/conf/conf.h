/* (C) 2026 OCML */
/*============================================================================*/
/* FILE     | conf.h                                                          */
/* DOMAIN   | -                                                               */
/* MODULE   | -                                                               */
/* DETAILS  | common config header                                            */
/* VER      | 26.06.27 make new                                               */
/*          |                                                                 */
/*          |                                                                 */
/*============================================================================*/
/******************************************************************************
  * @file     conf.h                                                           
  * @brief    common config header                                             
  * @domain   -                                                                
  * @date     XXXX/XX/XX                                                       
  * @(c)      2026 ocml                                                        
******************************************************************************/
#ifndef CONFIG_H
#define CONFIG_H

/******************************************************************************
  * config                                                                     
******************************************************************************/
/**************************************/
/* MACHINE TYPE SETTING!              */
/**************************************/
/* -------- ADD MACHINE LIST -------- */
#define MACHINE_TYPE_IOS         (0)
#define MACHINE_TYPE_ANDROID     (1)
#define MACHINE_TYPE_MACOS       (2)
#define MACHINE_TYPE_RASP_PROTO  (3)
#define MACHINE_TYPE_RASP_VER1_0 (4)
#define MACHINE_TYPE_RASP_VER2_0 (5)
/* -------- ADD MACHINE LIST -------- */

/*▼▼▼ SET MACHINE TYPE ▼▼▼ */
#define MACHINE_TYPE  (MACHINE_TYPE_IOS)
/*▲▲▲ SET MACHINE TYPE ▲▲▲ */

/**************************************/
/* PRINT LOG VALID SETTING!           */
/**************************************/
/* -------- ADD PRINT LOG LIST -------- */
#define PRINT_LOG_SETTING_UNVALID    (0)
#define PRINT_LOG_SETTING_VALID      (1)
/* -------- ADDPRINT  LOG LIST -------- */

/*▼▼▼ SET PRINT LOG VALID ▼▼▼ */
/* 2026-09-10: 手動操作(kensa_manual)時に詳細トレースが画面を埋め尽くして   */
/* 遊べなくなるためUNVALIDに変更。kensa_manual自身のステータス表示はこの   */
/* 設定と独立に常時出るので、操作結果は引き続き確認できる。内部モジュールの */
/* 挙動を詳しく追いたいときだけVALIDに戻すこと(swift_env.cの時刻計測は     */
/* この設定に関わらず常に動作する)。                                       */
#define PRINT_LOG_SETTING_CONF  (PRINT_LOG_SETTING_UNVALID)
/*▲▲▲ SET PRINT LOG VALID ▲▲▲ */

/**************************************/
/* KENSA VIRTUAL TIME SCALE SETTING!  */
/**************************************/
/* -------- SCALE LIST -------- */
#define u16g_TIME_SCALE_4MS_TO_400MS     ( 400U / 4U )
#define u16g_TIME_SCALE_4MS_TO_200MS     ( 200U / 4U )
#define u16g_TIME_SCALE_4MS_TO_100MS     ( 100U / 4U )
#define u16g_TIME_SCALE_4MS_TO_4MS       (   4U / 4U )  /* 等倍(実時間=仮想時間)。手動操作(kensa_manual)向け */
/* -------- SCALE LIST -------- */

/*▼▼▼ SET TIME SCALE ▼▼▼ */
/* 2026-09-10: 台本自動再生(kensa_seq)の可読性より手動キー操作(kensa_manual)の */
/* 応答性を優先し、等倍設定に変更。kensa_seqを見るために戻す場合は元の         */
/* u16g_TIME_SCALE_4MS_TO_200MS に戻すこと(その場合、体感速度が約50倍遅くなる)。*/
#define u16g_VIRTUAL_REAL_TIME_SCALE  (u16g_TIME_SCALE_4MS_TO_4MS)
/*▲▲▲ SET TIME SCALE ▲▲▲ */

#endif

/*----------------------------------------------------------------------------*/
/* EOF                                                                        */
/*----------------------------------------------------------------------------*/
