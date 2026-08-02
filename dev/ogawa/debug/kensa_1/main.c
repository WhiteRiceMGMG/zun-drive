/******************************************************************************
  * @file     main.c                                                           
  * @brief    -                                                                
  * @domain   -                                                                
  * @date     2026/07/20                                                       
  * @(c)      2026 ocml                                                        
******************************************************************************/

/******************************************************************************
  * include                                                                    
******************************************************************************/
#include "./main.h"

/******************************************************************************
  * external public variables contains macros                                  
******************************************************************************/
uint32_t main( void );

enum DummyNum
{
    eng_DUMMY1,
    eng_DUMMY2,
    eng_DUMMY3,
    eng_DUMMY4,
    eng_DUMMY5,
    eng_DUMMY6,
    eng_DUMMY7,
    eng_DUMMY8,
    eng_DUMMY9,
    eng_DUMMY10,
    eng_DUMMY11,
    eng_DUMMY12,
    eng_DUMMY13,
    eng_DUMMY14,
    eng_DUMMY15,
    eng_DUMMY16,
    eng_DUMMY17,
    eng_DUMMY18,
    eng_DUMMY19,
    eng_DUMMY20,
    eng_DUMMY21,
    eng_DUMMY22,
    eng_DUMMY23,
    eng_DUMMY24,
    eng_DUMMY25,
    eng_DUMMY26,
    eng_DUMMY27,
    eng_DUMMY28,
    eng_DUMMY29,
    eng_DUMMY30,
    eng_DUMMY31,
    eng_DUMMY32,
    eng_DUMMY33,
    eng_DUMMY34,
    eng_DUMMY35,
    eng_DUMMY36,
    eng_DUMMY37,
    eng_DUMMY38,
    eng_DUMMY39,
    eng_DUMMY40,
    eng_DUMMY41,
    eng_DUMMY42,
    eng_DUMMY43
};

/******************************************************************************
  * internal public variables contains macros                                  
******************************************************************************/

/******************************************************************************
  * external function                                                          
******************************************************************************/

/******************************************************************************
  * @func     dummy function                                                   
  * @scope    -                                                                
  * @brief    -                                                                
  * @param    -                                                                
  * @return   -                                                                
******************************************************************************/
uint32_t
main( void )
{
    printf("hello");
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogPrint("E X E C U T E  S I M U L A T O R");
#endif
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogArgPrint( "u8gBscheduleifRstflg = %d", (uint32_t)u8gBscheduleifRstflg );
#endif

    vdgVirtualenvInit();
    vdgVirtualenvExecute();
    return 0;

}


/******************************************************************************
  * internal function                                                          
******************************************************************************/

/*****************************************************************************
 u * @func     vdsDdummyFunc( void )                                            
  * @scope    internal                                                         
  * @brief    sample function                                                  
  * @param    -                                                                
  * @return   -                                                                
******************************************************************************/
void
vdsDdummyFunc( void )
{/*
    u8gBios2bswifAcelthl   = eng_DUMMY1;
    u8gBios2bswifBrkpdl    = eng_DUMMY2;
    u8gBios2bswifClthpdl   = eng_DUMMY3;
    s8gBios2bswifGear      = eng_DUMMY4;
    u8gBios2bswifIgsw      = eng_DUMMY5;
    u16gBbsw2iosifVel       = eng_DUMMY6;
    u16gBbsw2iosifRpm       = eng_DUMMY7;
    s8gBbsw2iosifGear      = eng_DUMMY8;
    u8gBbsw2iosifAclthlpct = eng_DUMMY9;
    u8gBbsw2iosifBrkpdlpct = eng_DUMMY10;
    u8gBbsw2iosifClthpdlpct= eng_DUMMY12;
    u8gBbsw2iosifEng       = eng_DUMMY13;
    u8gBbsw2iosifSht       = eng_DUMMY14;
    u8gBbsw2iosifOvrvsts   = eng_DUMMY15;
    u8gBbsw2iosifClthszsts = eng_DUMMY16;
    u8gBbsw2iosifBrkszsts  = eng_DUMMY17;
    u8gBbsw2iosifEnststs   = eng_DUMMY18;
    u8gBbsw2iosifOvrhet    = eng_DUMMY19;
    u8gBbsw2iosifSnserr    = eng_DUMMY20;
    u8gBbsw2iosifStopZsts   = eng_DUMMY21;
    u8gBbsw2iosifRunZsts    = eng_DUMMY22;
    u8gBbsw2iosifSpdupZsts  = eng_DUMMY23;
    u8gBbsw2iosifSpddwZsts  = eng_DUMMY24;
    u8gBbsw2iosifEnstZsts   = eng_DUMMY25;
*/
/*    u1g_bscheduleif_cnt      = eng_DUMMY26;*/
    u8gBscheduleifRstflg   = eng_DUMMY27;
/*
    u8gBbsw2iosifEng       = eng_DUMMY28;
    u8gBbsw2iosifSht       = eng_DUMMY29;
    u8gBbsw2iosifOvrvsts   = eng_DUMMY30;
    u8gBbsw2iosifClthszsts = eng_DUMMY31;
    u8gBbsw2iosifBrkszsts  = eng_DUMMY32;
    u8gBbsw2iosifEnststs   = eng_DUMMY33;
    u8gBbsw2iosifOvrhet    = eng_DUMMY34;
    u8gBbsw2iosifSnserr    = eng_DUMMY35;
    u8gBbsw2iosifStopZsts   = eng_DUMMY36;
    u8gBbsw2iosifRunZsts    = eng_DUMMY37;
    u8gBbsw2iosifSpdupZsts  = eng_DUMMY38;
    u8gBbsw2iosifSpddwZsts  = eng_DUMMY39;
    u8gBbsw2iosifEnstZsts   = eng_DUMMY40;
    u8gBbsw2iosifTBD1      = eng_DUMMY41;
    u8gBbsw2iosifTBD2      = eng_DUMMY42;
    u8gBbsw2iosifTBD3      = eng_DUMMY43;
*/
}

/******************************************************************************
  * end of file                                                                
******************************************************************************/
