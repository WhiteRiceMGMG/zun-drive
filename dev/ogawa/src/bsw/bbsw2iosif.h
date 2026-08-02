/******************************************************************************
  * @file     bbsw2iosif.h                                                     
  * @brief    bbsw2ios                                                         
  * @domain   bsw                                                              
  * @date     2026/07/20                                                       
  * @(c)      2026 ocml                                                        
******************************************************************************/
#ifndef BBSW2IOSIF_H
#define BBSW2IOSIF_H

/******************************************************************************
  * include                                                                    
******************************************************************************/
/* #include "../../swiftbridge.h" */ /* swift bridge header */
#include "../inc/common.h"
#include "../sac/acfmstsif.h"
#include "../sac/avehstsif.h"

/******************************************************************************
  * external public variables contains macros                                  
******************************************************************************/
#if 0
extern uint16_t u16gBbsw2iosifVel;       /* VELOCITY 0-300[km]                */
extern uint16_t u16gBbsw2iosifRpm;       /* RPM 0-12000[km]                   */
extern int8_t   s8gBbsw2iosifGear;       /* GEAR INFORMATION 1,2,3,4,5,6,N[-] */
extern uint8_t  u8gBbsw2iosifAclthlpct;  /* ACCEL THROTTLE 0-100[%]           */
extern uint8_t  u8gBbsw2iosifBrkpdlpct;  /* BRAKE PEDAL 0-100[%]              */
extern uint8_t  u8gBbsw2iosifClthpdlpct; /* CLUTCH PEDAL 0-100[%]             */
extern uint8_t  u8gBbsw2iosifEng;        /* ENGINE PERMISSION ON,OFF[-]       */
extern uint8_t  u8gBbsw2iosifSht;        /* SHIFT CHANGE PERMISSION ON,OFF[-] */
extern uint8_t  u8gBbsw2iosifOvrvsts;    /* OVER REV JUDGE STATUS ON,OFF[-]   */
extern uint8_t  u8gBbsw2iosifClthszsts;  /* CLUTCH SEIZURE STATUS ON,OFF[-]   */
extern uint8_t  u8gBbsw2iosifBrkszsts;   /* BRAKE SEIZURE STATUS ON,OFF[-]    */
extern uint8_t  u8gBbsw2iosifEnststs;    /* ENGINE STALL STATUS ON,IFF[-]     */
extern uint8_t  u8gBbsw2iosifOvrhet;     /* OVER HEAT STATUS ON,OFF[-]        */
extern uint8_t  u8gBbsw2iosifSnserr;     /* SENSOR ERROR STATUS ON,OFF[-]     */
extern uint8_t  u8gBbsw2iosifStopZsts;   /* ZUN STATUS:STOP ON,OFF[-]         */
extern uint8_t  u8gBbsw2iosifRunZsts;    /* ZUN STATUS:RUN ON,OFF[-]          */
extern uint8_t  u8gBbsw2iosifSpdupZsts;  /* ZUN STATUS:SPEED UP ON,OFF[-]     */
extern uint8_t  u8gBbsw2iosifSpddwZsts;  /* ZUN STATUS:SPEED DOWN ON,OFF[-]   */
extern uint8_t  u8gBbsw2iosifEnstZsts;   /* ZUN STATUS:ENST ON,OFF[-]         */
extern uint8_t  u8gBbsw2iosifTBD1;       /* T.B.D                             */
extern uint8_t  u8gBbsw2iosifTBD2;       /* T.B.D                             */
extern uint8_t  u8gBbsw2iosifTBD3;       /* T.B.D                             */
#endif

extern stflag16 stgBbsw2iosifSts;
#define b8gBbsw2iosifEng       (stgBbsw2iosifSts.b0)  /* ENGINE PERMISSION ON,OFF[-]       */
#define b8gBbsw2iosifSht       (stgBbsw2iosifSts.b1)  /* SHIFT CHANGE PERMISSION ON,OFF[-] */
#define b8gBbsw2iosifOvrvsts   (stgBbsw2iosifSts.b2)  /* OVER REV JUDGE STATUS ON,OFF[-]   */
#define b8gBbsw2iosifClthszsts (stgBbsw2iosifSts.b3)  /* CLUTCH SEIZURE STATUS ON,OFF[-]   */
#define b8gBbsw2iosifBrkszsts  (stgBbsw2iosifSts.b4)  /* BRAKE SEIZURE STATUS ON,OFF[-]    */
#define b8gBbsw2iosifEnststs   (stgBbsw2iosifSts.b5)  /* ENGINE STALL STATUS ON,IFF[-]     */
#define b8gBbsw2iosifOvrhet    (stgBbsw2iosifSts.b6)  /* OVER HEAT STATUS ON,OFF[-]        */
#define b8gBbsw2iosifSnserr    (stgBbsw2iosifSts.b7)  /* SENSOR ERROR STATUS ON,OFF[-]     */
#define b8gBbsw2iosifStopZsts  (stgBbsw2iosifSts.b8)  /* ZUN STATUS:STOP ON,OFF[-]         */
#define b8gBbsw2iosifRunZsts   (stgBbsw2iosifSts.b9)  /* ZUN STATUS:RUN ON,OFF[-]          */
#define b8gBbsw2iosifSpdupZsts (stgBbsw2iosifSts.b10) /* ZUN STATUS:SPEED UP ON,OFF[-]     */
#define b8gBbsw2iosifSpddwZsts (stgBbsw2iosifSts.b11) /* ZUN STATUS:SPEED DOWN ON,OFF[-]   */
#define b8gBbsw2iosifEnstZsts  (stgBbsw2iosifSts.b12) /* ZUN STATUS:ENST ON,OFF[-]         */
#define b8gBbsw2iosifTBD1      (stgBbsw2iosifSts.b13) /* T.B.D                             */
#define b8gBbsw2iosifTBD2      (stgBbsw2iosifSts.b14) /* T.B.D                             */
#define b8gBbsw2iosifTBD3      (stgBbsw2iosifSts.b15) /* T.B.D                             */



#define u8gBbsw2iosifAclthlpct   u8gAcfmstsifAclthlpct
#define u8gBbsw2iosifBrkpdlpct   u8gAcfmstsifBrkpdlpct
#define u8gBbsw2iosifClthpdlpct  u8gAcfmstsifClthpdlpct
#define u8gBbsw2iosifEng         u8gAcfmstsifEng
#define u8gBbsw2iosifSht         u8gAcfmstsifSht
#define u8gBbsw2iosifOvrvsts     u8gAcfmstsifOvrvsts
#define u8gBbsw2iosifClthszsts   u8gAcfmstsifClthszsts
#define u8gBbsw2iosifBrkszsts    u8gAcfmstsifBrkszsts
#define u8gBbsw2iosifEnststs     u8gAcfmstsifEnststs
#define u8gBbsw2iosifOvrhet      u8gAcfmstsifOvrhet
#define u8gBbsw2iosifSnserr      u8gAcfmstsifSnserr
#define u8gBbsw2iosifIgswsts     u8gAcfmstsifIgswsts
#define s8gBbsw2iosifGear        s8gAcfmstsifGearpos
#define u16gBbsw2iosifVel        u16gAcfmstsifVelspd
#define u16gBbsw2iosifRpm        u16gAcfmstsifRpmval
#define u8gBbsw2iosifStopZsts    u8gAvehstsifStop
#define u8gBbsw2iosifRunZsts     u8gAvehstsifRun
#define u8gBbsw2iosifSpdupZsts   u8gAvehstsifSpdup
#define u8gBbsw2iosifSpddwZsts   u8gAvehstsifSpddw
#define u8gBbsw2iosifEnstZsts    u8gAvehstsifEnst

#define u8gSwiftifVel        u16gBbsw2iosifVel
#define u8gSwiftifRpm        u16gBbsw2iosifRpm
#define u8gSwiftifCfmGear    s8gBbsw2iosifGear
#define u8gSwiftifCfmAclpct  u8gBbsw2iosifAclthlpct
#define u8gSwiftifCfmBrkpct  u8gBbsw2iosifBrkpdlpct
#define u8gSwiftifCfmClthpct u8gBbsw2iosifClthpdlpct
#define u8gSwiftifEngsts     u8gBbsw2iosifEng
#define u8gSwiftifShtsts     u8gBbsw2iosifSht
#define u8gSwiftifOvrvsts    u8gBbsw2iosifOvrvsts
#define u8gSwiftifClthszsts  u8gBbsw2iosifClthszsts
#define u8gSwiftifBrkszsts   u8gBbsw2iosifBrkszsts
#define u8gSwiftifEnststs    u8gBbsw2iosifEnststs
#define u8gSwiftifOvrhet     u8gBbsw2iosifOvrhet
#define u8gSwiftifSnserr     u8gBbsw2iosifSnserr
#define u8gSwiftifStopZsts   u8gBbsw2iosifStopZsts
#define u8gSwiftifRunZsts    u8gBbsw2iosifRunZsts
#define u8gSwiftifSpdupZsts  u8gBbsw2iosifSpdupZsts
#define u8gSwiftifSpddwZsts  u8gBbsw2iosifSpddwZsts
#define u8gSwiftifEnstZsts   u8gBbsw2iosifEnstZsts
#define u8gSwiftifTBD1       u8gBbsw2iosifTBD1
#define u8gSwiftifTBD2       u8gBbsw2iosifTBD2
#define u8gSwiftifTBD3       u8gBbsw2iosifTBD3
/*
#define u8gSwiftifEngsts     b1gBbsw2iosifEng
#define u8gSwiftifShtsts     b1gBbsw2iosifSht
#define u8gSwiftifOvrvsts    b1gBbsw2iosifOvrvsts
#define u8gSwiftifClthszsts  b1gBbsw2iosifClthszsts
#define u8gSwiftifBrkszsts   b1gBbsw2iosifBrkszsts
#define u8gSwiftifEnststs    b1gBbsw2iosifEnststs
#define u8gSwiftifOvrhet     b1gBbsw2iosifOvrhet
#define u8gSwiftifSnserr     b1gBbsw2iosifSnserr
#define u8gSwiftifStopsts    b1gBbsw2iosifStopsts
#define u8gSwiftifRunsts     b1gBbsw2iosifRunsts
#define u8gSwiftifSpdupsts   b1gBbsw2iosifSpdupsts
#define u8gSwiftifSpddwsts   b1gBbsw2iosifSpddwsts
#define u8gSwiftifEnststs    b1gBbsw2iosifEnststs
#define u8gSwiftifTBD1       b1gBbsw2iosifTBD1
#define u8gSwiftifTBD2       b1gBbsw2iosifTBD2
#define u8gSwiftifTBD3       b1gBbsw2iosifTBD3
*/
/******************************************************************************
  * external function prototype                                                
******************************************************************************/

#endif
/******************************************************************************
  * end of file                                                                
******************************************************************************/
