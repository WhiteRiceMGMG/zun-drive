/******************************************************************************
  * @file     bscheduleif.h                                                    
  * @brief    scheduler                                                        
  * @domain   bsw                                                              
  * @date     2026/07/20                                                       
  * @(c)      2026 ocml                                                        
******************************************************************************/

/******************************************************************************
  * include                                                                    
******************************************************************************/
#include "../../inc/common.h"
#include "../bcyclemngif.h"    /* vdgBcyclemngifIwon()                      */
                               /* vdgBcyclemngif4msin()                     */
                               /* vdgBcyclemngif4msout()                    */
                               /* vdgBcyclemngif16msin()                    */
                               /* vdgBcyclemngif16msout()                   */
                               /* vdgBcyclemngif64msin()                    */
                               /* vdgBcyclemngif64msout()                   */

#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
#include "../../../debug/log/print_log.h"
#endif

#include "../bscheduleif.h"

/******************************************************************************
  * external public variables contains macros                                  
******************************************************************************/
uint8_t u8gBscheduleifRstflg;

/******************************************************************************
  * internal public variables contains macros                                  
******************************************************************************/
static uint8_t u8sBscheduleIncntO;
static uint8_t u8sBscheduleOutcntO;

#define u8s_BSCHEDULE_CNT_64MS  ((uint8_t)4) 

/******************************************************************************
  * external function                                                          
******************************************************************************/

/******************************************************************************
  * @func     vdgBscheduleifInitcall( void )                                   
  * @scope    external                                                         
  * @brief    function manager                                                 
  * @param    -                                                                
  * @return   -                                                                
******************************************************************************/
void
vdgBscheduleifInitcall( void )
{
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogPrint( "execute vdgBscheduleifInitcall()" );
#endif

    u8sBscheduleIncntO = (uint8_t)0;
    u8sBscheduleOutcntO = (uint8_t)0;
    u8gBscheduleifRstflg = (uint8_t)OFF;

    vdgBcyclemngifInit();
}

/******************************************************************************
  * @func     vdgBscheduleifIncall( void )                                     
  * @scope    external                                                         
  * @brief    function manager                                                 
  * @param    -                                                                
  * @return   -                                                                
******************************************************************************/
void
vdgBscheduleifIncall( void )
{
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogPrint( "execute vdgBscheduleifIncall()" );
#endif
    uint8_t u8tIncnt;
    uint8_t u8tRstflg;

    u8tIncnt  = u8sBscheduleIncntO;
    u8tRstflg = u8gBscheduleifRstflg;

    if ( u8tIncnt < u8g_MAX)
    {
        u8tIncnt++;
    }

    vdgBcyclemngif4msin();
    vdgBcyclemngif4msin();
    vdgBcyclemngif4msin();
    vdgBcyclemngif4msin();

    vdgBcyclemngif16msin();

    u8tRstflg = (uint8_t)OFF;
    if ( u8tIncnt == u8s_BSCHEDULE_CNT_64MS )
    {
        vdgBcyclemngif64msin();
        u8tIncnt = (uint8_t)0;
        u8tRstflg = (uint8_t)ON;
    }

    u8sBscheduleIncntO = u8tIncnt;
    u8gBscheduleifRstflg = u8tRstflg;
}

/******************************************************************************
  * @func     vdgBscheduleifOutcall( void )                                    
  * @scope    external                                                         
  * @brief    function manager                                                 
  * @param    -                                                                
  * @return   -                                                                
******************************************************************************/
void
vdgBscheduleifOutcall( void )
{
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogPrint( "execute vdgBscheduleifOutcall()" );
#endif

    uint8_t u8tOutcnt;
    uint8_t u8tRstflg;

    u8tOutcnt = u8sBscheduleOutcntO;
    u8tRstflg = u8gBscheduleifRstflg;

    if ( u8tOutcnt < u8g_MAX)
    {
        u8tOutcnt++;
    }

    vdgBcyclemngif4msout();
    vdgBcyclemngif4msout();
    vdgBcyclemngif4msout();
    vdgBcyclemngif4msout();

    vdgBcyclemngif16msout();

    u8tRstflg = (uint8_t)OFF;
    if ( u8tOutcnt == u8s_BSCHEDULE_CNT_64MS )
    {
        vdgBcyclemngif64msout();
        u8tOutcnt = (uint8_t)0;
        u8tRstflg = (uint8_t)ON;
    }

    u8sBscheduleOutcntO = u8tOutcnt;
    u8gBscheduleifRstflg = u8tRstflg;
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
