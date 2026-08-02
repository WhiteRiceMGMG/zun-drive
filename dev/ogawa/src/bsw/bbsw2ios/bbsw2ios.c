/******************************************************************************
  * @file     bbsw2ios.c                                                       
  * @brief    bsw to swift                                                     
  * @domain   rename                                                           
  * @date     2026/07/20                                                       
  * @(c)      2026 ocml                                                        
******************************************************************************/

/******************************************************************************
  * include                                                                    
******************************************************************************/
/* #include "../../inc/common.h" */
#include "../bbsw2iosif.h"

#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
#include "../../../debug/log/print_log.h"
#endif

/******************************************************************************
  * external public variables contains macros                                  
******************************************************************************/
stflag16 stgBbsw2iosif_sts;
#if 0
uint16_t u16gBbsw2iosifVel;        /* VELOCITY 0-300[km]               */
uint16_t u16gBbsw2iosifRpm;        /* RPM 0-12000[km]                  */
int8_t   s8gBbsw2iosifGear;       /* GEAR INFORMATION 1,2,3,4,5,6,N[-] */
uint8_t  u8gBbsw2iosifIgswsts;    /* IGSW STS ON,OFF[-]               */
uint8_t  u8gBbsw2iosifAclthlpct;  /* ACCEL THROTTLE 0-100[%]           */
uint8_t  u8gBbsw2iosifBrkpdlpct;  /* BRAKE PEDAL 0-100[%]              */
uint8_t  u8gBbsw2iosifClthpdlpct; /* CLUTCH PEDAL 0-100[%]             */
uint8_t  u8gBbsw2iosifEng;        /* ENGINE PERMISSION ON,OFF[-]       */
uint8_t  u8gBbsw2iosifSht;        /* SHIFT CHANGE PERMISSION ON,OFF[-] */
uint8_t  u8gBbsw2iosifOvrvsts;    /* OVER REV JUDGE STATUS ON,OFF[-]   */
uint8_t  u8gBbsw2iosifClthszsts;  /* CLUTCH SEIZURE STATUS ON,OFF[-]   */
uint8_t  u8gBbsw2iosifBrkszsts;   /* BRAKE SEIZURE STATUS ON,OFF[-]    */
uint8_t  u8gBbsw2iosifEnststs;    /* ENGINE STALL STATUS ON,IFF[-]     */
uint8_t  u8gBbsw2iosifOvrhet;     /* OVER HEAT STATUS ON,OFF[-]        */
uint8_t  u8gBbsw2iosifSnserr;     /* SENSOR ERROR STATUS ON,OFF[-]     */
uint8_t  u8gBbsw2iosifStopZsts;    /* ZUN STATUS:STOP ON,OFF[-]        */
uint8_t  u8gBbsw2iosifRunZsts;     /* ZUN STATUS:RUN ON,OFF[-]         */
uint8_t  u8gBbsw2iosifSpdupZsts;   /* ZUN STATUS:SPEED UP ON,OFF[-]    */
uint8_t  u8gBbsw2iosifSpddwZsts;   /* ZUN STATUS:SPEED DOWN ON,OFF[-]  */
uint8_t  u8gBbsw2iosifEnstZsts;    /* ZUN STATUS:ENST ON,OFF[-]        */
uint8_t  u8gBbsw2iosifTBD1;       /* T.B.D                             */
uint8_t  u8gBbsw2iosifTBD2;       /* T.B.D                             */
uint8_t  u8gBbsw2iosifTBD3;       /* T.B.D                             */
#endif
/******************************************************************************
  * internal public variables contains macros                                  
******************************************************************************/

/******************************************************************************
  * external function                                                          
******************************************************************************/

/******************************************************************************
  * @func     u8g_sample_func( void )                                          
  * @scope    external                                                         
  * @brief    brk correction init function                                     
  * @param    -                                                                
  * @return   -                                                                
******************************************************************************/

/******************************************************************************
  * internal function                                                          
******************************************************************************/

/******************************************************************************
  * @func     vdgSampleFunction( void )                                        
  * @scope    internal                                                         
  * @brief    sample function                                                  
  * @param    -                                                                
  * @return   -                                                                
******************************************************************************/

/******************************************************************************
  * end of file                                                                
******************************************************************************/
