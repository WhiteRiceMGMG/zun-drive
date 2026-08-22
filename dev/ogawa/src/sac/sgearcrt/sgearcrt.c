/******************************************************************************
  * @file     sgearcrt.c                                                       
  * @brief    gear correction                                                  
  * @domain   sensor-actuator                                                  
  * @date     2026/07/20                                                       
  * @(c)      2026 ocml                                                        
******************************************************************************/

/******************************************************************************
  * include                                                                    
******************************************************************************/

#include "../../inc/common.h"
#include "../../bsw/bios2bswif.h" /* s8gBios2bswifGear */

#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
#include "../../../debug/log/print_log.h"
#endif

#include "../sgearcrtif.h"

/******************************************************************************
  * external public variables contains macros                                  
******************************************************************************/
int8_t   s8gSgearcrtifPos;
uint8_t  u8gSgearcrtifCrtflg;

#define s8g_SGEARIF_REVERSE ((int8_t)-1)   /* gear: REVERSE */
#define s8g_SGEARIF_NEUTRAL ((int8_t)0)    /* gear: NEUTRAL */
#define s8g_SGEARIF_FIRST   ((int8_t)1)    /* gear: FIRST   */
#define s8g_SGEARIF_SECOND  ((int8_t)2)    /* gear: SECOND  */
#define s8g_SGEARIF_THIRD   ((int8_t)3)    /* gear: THIRD   */
#define s8g_SGEARIF_FOURTH  ((int8_t)4)    /* gear: FOURTH  */
#define s8g_SGEARIF_FIFTH   ((int8_t)5)    /* gear:FIFTH    */


/******************************************************************************
  * internal public variables contains macros                                  
******************************************************************************/
static int8_t s8sSgearcrtPosO;

/******************************************************************************
  * external function                                                          
******************************************************************************/

/******************************************************************************
  * @func     vdgSgearcrtifInit( void )                                        
  * @scope    external                                                         
  * @brief    gear correction init function                                    
  * @param    -                                                                
  * @return   -                                                                
******************************************************************************/
void
vdgSgearcrtifInit( void )
{
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogPrint( "start gSgearcrtifPwon()" );
#endif

    s8gSgearcrtifPos = (int8_t)0;
    u8gSgearcrtifCrtflg = (uint8_t)OFF;
    s8sSgearcrtPosO = (int8_t)0;

#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogArgPrint( "s8gSgearcrtifPos = %d", (int32_t)s8gSgearcrtifPos );
    vdgLogArgPrint( "u8gSgearcrtifCrtflg = %d", (int32_t)u8gSgearcrtifCrtflg );
    vdgLogArgPrint( "s8sSgearcrtPosO = %d", (int32_t)s8sSgearcrtPosO );
#endif
}

/******************************************************************************
  * @func     vdgSgearcrtif64msin( void )                                      
  * @scope    external                                                         
  * @brief    gear correction 64ms function                                    
  * @param    -                                                                
  * @return   -                                                                
******************************************************************************/
void 
vdgSgearcrtif64msin( void )
{
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogPrint( "start vdgSgearcrtif64msin()" );
    vdgLogArgPrint( "input : s8gSgearcrtifPos = %d", (int32_t)s8gSgearcrtifPos );
    vdgLogArgPrint( "input : u8gSgearcrtifCrtflg = %d", (int32_t)u8gSgearcrtifCrtflg );
    vdgLogArgPrint( "input : s8sSgearcrtPosO = %d", (int32_t)s8sSgearcrtPosO );
#endif

    int8_t  s8tGearpos;
    uint8_t u8tCrtflg;
    int8_t  s8tGearposO;

    s8tGearpos = s8gBios2bswifGear;
    u8tCrtflg = u8gSgearcrtifCrtflg;
    s8tGearposO = s8sSgearcrtPosO;

    u8tCrtflg = (uint8_t)ON;
    if ( s8tGearpos == s8tGearposO )
    {
        s8tGearpos = s8tGearposO;
        u8tCrtflg = (uint8_t)OFF;
    }
    s8gSgearcrtifPos = s8tGearpos;
    s8sSgearcrtPosO = s8tGearpos;
    u8gSgearcrtifCrtflg = u8tCrtflg;

#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogPrint( "DONE! vdgSgearcrtif64msin()" );
    vdgLogArgPrint( "output : s8gSgearcrtifPos = %d", (int32_t)s8gSgearcrtifPos );
    vdgLogArgPrint( "output : u8gSgearcrtifCrtflg = %d", (int32_t)u8gSgearcrtifCrtflg );
    vdgLogArgPrint( "output : s8sSgearcrtPosO = %d", (int32_t)s8sSgearcrtPosO );
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
