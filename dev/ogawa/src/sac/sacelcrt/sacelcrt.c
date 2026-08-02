/******************************************************************************
  * @file     sacelcrt.c                                                       
  * @brief    acel correction                                                  
  * @domain   sensor-actuator                                                  
  * @date     2026/07/20                                                       
  * @(c)      2026 ocml                                                        
******************************************************************************/

/******************************************************************************
  * include                                                                    
******************************************************************************/
#include "../../inc/common.h"
#include "../../bsw/bios2bswif.h"  /* u8gBios2bswifAcelthl  */

#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
#include "../../../debug/log/print_log.h"
#endif

#include "../sacelcrtif.h"



/******************************************************************************
  * external public variables contains macros                                  
******************************************************************************/
uint8_t u8gSacelcrtifThlpct;
uint8_t u8gSacelcrtifCrtflg;

/******************************************************************************
  * internal public variables contains macros                                  
******************************************************************************/
#define u8s_ACELCRT_DEADBAND  ((uint8_t)((4.) / ((100.) / (256.) + 0.5)))
static uint8_t u8sSacelcrtThlpctO;

/******************************************************************************
  * external function                                                          
******************************************************************************/

/******************************************************************************
  * @func     vdgSacelcrtifInit( void )                                        
  * @scope    external                                                         
  * @brief    acel correction init function                                    
  * @param    -                                                                
  * @return   -                                                                
******************************************************************************/
void
vdgSacelcrtifInit( void )
{
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogPrint( "start vdgSacelcrtifInit()" );
#endif
    u8sSacelcrtThlpctO  = (uint8_t)0;
    u8gSacelcrtifThlpct = (uint8_t)0;
    u8gSacelcrtifCrtflg = (uint8_t)OFF;

#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogArgPrint( "u8sSacelcrtThlpctO = %d", (uint32_t)u8sSacelcrtThlpctO );
    vdgLogArgPrint( "u8gSacelcrtifThlpct = %d", (uint32_t)u8gSacelcrtifThlpct );
    vdgLogArgPrint( "u8gSacelcrtifCrtflg = %d", (uint32_t)u8gSacelcrtifCrtflg );
#endif

}

/******************************************************************************
  * @func     vdgSacelcrtif4msin( void )                                       
  * @scope    external                                                         
  * @brief    acel correction 4ms function                                     
  * @param    -                                                                
  * @return   -                                                                
******************************************************************************/
void
vdgSacelcrtif4msin( void )
{
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogPrint( "start vdgSacelcrtif4msin()" );
    vdgLogArgPrint( "input : u8sSacelcrtThlpctO = %d", (uint32_t)u8sSacelcrtThlpctO );
    vdgLogArgPrint( "input : u8gSacelcrtifThlpct = %d", (uint32_t)u8gSacelcrtifThlpct );
    vdgLogArgPrint( "input : u8gSacelcrtifCrtflg = %d", (uint32_t)u8gSacelcrtifCrtflg );
#endif

    uint8_t u8tAcelpct;
    uint8_t u8tAcelpctO;
    uint8_t u8tPctdelta;
    uint8_t u8tCrtflg;

    u8tAcelpct = u8gBios2bswifAcelthl;
    u8tAcelpctO = u8sSacelcrtThlpctO;

    if ( u8tAcelpct > u8g_MAX )
    {
        u8tAcelpct = u8g_MAX;
    }

    if ( u8tAcelpct >= u8tAcelpctO )
    {
        u8tPctdelta = u8tAcelpct - u8tAcelpctO;
    }
    else
    {
        u8tPctdelta = u8tAcelpctO - u8tAcelpct;
    }


    u8tCrtflg = (uint8_t)OFF;
    if ( u8tPctdelta <= u8s_ACELCRT_DEADBAND )
    {
        u8tCrtflg = (uint8_t)ON;
        u8tAcelpct = u8tAcelpctO;
    }

    u8sSacelcrtThlpctO = u8tAcelpct;
    u8gSacelcrtifThlpct = u8tAcelpct;
    u8gSacelcrtifCrtflg = u8tCrtflg;

#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogArgPrint( "output : u8sSacelcrtThlpctO = %d", (uint32_t)u8sSacelcrtThlpctO );
    vdgLogArgPrint( "output : u8gSacelcrtifThlpct = %d", (uint32_t)u8gSacelcrtifThlpct );
    vdgLogArgPrint( "output : u8gSacelcrtifCrtflg = %d", (uint32_t)u8gSacelcrtifCrtflg );
#endif
}

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
