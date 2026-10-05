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
#define PRINT_LOG_SETTING_CONF  (PRINT_LOG_SETTING_VALID)
/*▲▲▲ SET PRINT LOG VALID ▲▲▲ */

/**************************************/
/* KENSA VIRTUAL TIME SCALE SETTING!  */
/**************************************/
/* -------- SCALE LIST -------- */
#define u16g_TIME_SCALE_4MS_TO_400MS     ( 400U / 4U )
#define u16g_TIME_SCALE_4MS_TO_200MS     ( 200U / 4U )
#define u16g_TIME_SCALE_4MS_TO_100MS     ( 100U / 4U )
/* -------- SCALE LIST -------- */

/*▼▼▼ SET TIME SCALE ▼▼▼ */
#define u16g_VIRTUAL_REAL_TIME_SCALE  (u16g_TIME_SCALE_4MS_TO_200MS)
/*▲▲▲ SET TIME SCALE ▲▲▲ */

#endif

/*----------------------------------------------------------------------------*/
/* EOF                                                                        */
/*----------------------------------------------------------------------------*/
