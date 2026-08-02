/******************************************************************************
  * @file     sclthcrt.c                                                       
  * @brief    clth correction                                                  
  * @domain   sensor-actuator                                                  
  * @date     2026/07/20                                                       
  * @(c)      2026 ocml                                                        
******************************************************************************/

/******************************************************************************
  * include                                                                    
******************************************************************************/
#include "../../inc/common.h"
#include "../../bsw/bios2bswif.h"  /* u8gBios2bswifClthpdl  */

#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
#include "../../../debug/log/print_log.h"
#endif

#include "../sclthcrtif.h"

/******************************************************************************
  * external public variables contains macros                                  
******************************************************************************/
uint8_t u8gSclthcrtifPdlpct;
uint8_t u8gSclthcrtifCrtflg;

/******************************************************************************
  * internal public variables contains macros                                  
******************************************************************************/
#define u8s_ClTHCRT_DEADBAND  ((uint8_t)((4.) / ((100.) / (256.) + 0.5)))
static uint8_t u8sSclthcrtPdlpctO;

/******************************************************************************
  * external function                                                          
******************************************************************************/

/******************************************************************************
  * @func     vdgSclthcrtifInit( void )                                        
  * @scope    external                                                         
  * @brief    clth correction init function                                    
  * @param    -                                                                
  * @return   -                                                                
******************************************************************************/
void
vdgSclthcrtifInit( void )
{
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogPrint( "start vdgSclthcrtifPwon()" );
#endif
    u8gSclthcrtifPdlpct= (uint8_t)0;
    u8gSclthcrtifCrtflg = (uint8_t)OFF;
    u8sSclthcrtPdlpctO = (uint8_t)0;

#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogArgPrint( "u8gSclthcrtifPdlpct = %d", (uint32_t)u8gSclthcrtifPdlpct );
    vdgLogArgPrint( "u8gSclthcrtifCrtflg = %d", (uint32_t)u8gSclthcrtifCrtflg );
    vdgLogArgPrint( "u8sSclthcrtPdlpctO = %d", (uint32_t)u8sSclthcrtPdlpctO );
#endif
}

/******************************************************************************
  * @func     vdgSclthcrtif16msin( void )                                      
  * @scope    external                                                         
  * @brief    clth correction 16ms function                                    
  * @param    -                                                                
  * @return   -                                                                
******************************************************************************/
void
vdgSclthcrtif16msin( void )
{
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogPrint( "start vdgSclthcrtif16msin()" );
    vdgLogArgPrint( "input : u8gSclthcrtifPdlpct = %d", (uint8_t)u8gSclthcrtifPdlpct );
    vdgLogArgPrint( "input : u8gSclthcrtifCrtflg = %d", (uint8_t)u8gSclthcrtifCrtflg );
    vdgLogArgPrint( "input : u8sSclthcrtPdlpctO = %d", (uint8_t)u8sSclthcrtPdlpctO );
#endif

    uint8_t u8tClthpct;
    uint8_t u8tClthpctO;
    uint8_t u8tPctdelta;
    uint8_t u8tCrtflg;

    u8tClthpct = u8gBios2bswifClthpdl;
    u8tClthpctO = u8sSclthcrtPdlpctO;

    if ( u8tClthpct > u8g_MAX )
    {
        u8tClthpct = u8g_MAX;
    }

    if ( u8tClthpct >= u8tClthpctO )
    {
        u8tPctdelta = u8tClthpct - u8tClthpctO;
    }
    else
    {
        u8tPctdelta = u8tClthpctO - u8tClthpct;
    }


    u8tCrtflg = (uint8_t)OFF;
    if ( u8tPctdelta <= u8s_ClTHCRT_DEADBAND )
    {
        u8tCrtflg = (uint8_t)ON;
        u8tClthpct = u8tClthpctO;
    }

    u8sSclthcrtPdlpctO = u8tClthpct;
    u8gSclthcrtifPdlpct = u8tClthpct;
    u8gSclthcrtifCrtflg = u8tCrtflg;

#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogPrint( "DONE! vdgSclthcrtif16msin()" );
    vdgLogArgPrint( "output : u8gSclthcrtifPdlpct = %d", (uint32_t)u8gSclthcrtifPdlpct );
    vdgLogArgPrint( "output : u8gSclthcrtifCrtflg = %d", (uint32_t)u8gSclthcrtifCrtflg );
    vdgLogArgPrint( "output : u8sSclthcrtPdlpctO = %d", (uint32_t)u8sSclthcrtPdlpctO );
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
