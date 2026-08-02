/******************************************************************************
  * @file     swift_env.c                                                      
  * @brief    -                                                                
  * @domain   -                                                                
  * @date     2026/07/20                                                       
  * @(c)      2026 ocml                                                        
******************************************************************************/

/******************************************************************************
  * include                                                                    
******************************************************************************/
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
#include <windows.h>
#endif

#ifdef TRUE
#undef TRUE
#endif
#ifdef FALSE
#undef FALSE
#endif
#include "../../src/inc/common.h"

#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
#include "../../debug/log/print_log.h"
#endif

#include "../../src/bsw/bcyclemngif.h"

#include "../swift_envif.h"
/******************************************************************************
  * external public variables contains macros                                  
******************************************************************************/
uint32_t u32gVirtualenvRealtime;
uint16_t u16gVirtualenvVirtualtime;
uint16_t u16gVirtualenvCm4;
uint16_t u16gVirtualenvCm16;
uint16_t u16gVirtualenvCm64;


/******************************************************************************
  * internal public variables contains macros                                  
******************************************************************************/
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
void vdsVirtualtimeUpdate( void );
#else
void vdsVirtualtimeUpdateDm( void );
#endif

static DWORD DWsPrevTick;

#define u16g_VIRTUALENV_4MS_CM   ((uint16_t)4U)
#define u16g_VIRTUALENV_16MS_CM  ((uint16_t)16U)
#define u16g_VIRTUALENV_64MS_CM  ((uint16_t)64U)

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
void
vdgVirtualenvInit( void )
{
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    DWsPrevTick = GetTickCount();
#else
    DWsPrevTick = (u1)0;
#endif

    u32gVirtualenvRealtime    = (uint32_t)0U;
    u16gVirtualenvVirtualtime = (uint32_t)0U;
}

/******************************************************************************
  * @func     dummy function                                                   
  * @scope    -                                                                
  * @brief    -                                                                
  * @param    -                                                                
  * @return   -                                                                
******************************************************************************/
void
vdgVirtualenvExecute( void )
{
    uint16_t u16tTimer4ms = (uint16_t)0U;
    uint16_t u16tTimer16ms = (uint16_t)0U;
    uint16_t u16tTimer64ms = (uint16_t)0U;

    uint16_t u16tPrevVirtualtime = (uint16_t)0U;
    uint16_t u16tDeltaTime  = (uint16_t)0U;


    while(1)
    {
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
        vdsVirtualtimeUpdate();
#else
        vdsVirtualtimeUpdateDm();
#endif
        u16tDeltaTime = (uint16_t)(u16gVirtualenvVirtualtime - u16tPrevVirtualtime);
        u16tPrevVirtualtime = u16gVirtualenvVirtualtime;

        u16tTimer4ms  += u16tDeltaTime;
        u16tTimer16ms += u16tDeltaTime;
        u16tTimer64ms += u16tDeltaTime;

        while ( u16tTimer4ms >= u16g_VIRTUALENV_4MS_CM )
        {
            vdgBcyclemngif4msin();
            vdgBcyclemngif4msout();
            u16tTimer4ms -= u16g_VIRTUALENV_4MS_CM;
        }

        while ( u16tTimer16ms >= u16g_VIRTUALENV_16MS_CM )
        {
            vdgBcyclemngif16msin();
            vdgBcyclemngif16msout();
            u16tTimer16ms -= u16g_VIRTUALENV_16MS_CM;
        }

        while ( u16tTimer64ms >= u16g_VIRTUALENV_64MS_CM )
        {
            vdgBcyclemngif64msin();
            vdgBcyclemngif64msout();
            u16tTimer64ms -= u16g_VIRTUALENV_64MS_CM;
        }

        Sleep(1);
    }
}

/******************************************************************************
  * internal function                                                          
******************************************************************************/
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
/******************************************************************************
  * @func     vdsDdummyFunc( void )                                            
  * @scope    internal                                                         
  * @brief    sample function                                                  
  * @param    -                                                                
  * @return   -                                                                
******************************************************************************/
void
vdsVirtualtimeUpdate( void )
{
    DWORD DWtVirtualenvNowtime;
    DWORD DWtVirtualenvElaspedtime;

    DWtVirtualenvNowtime = GetTickCount();
    DWtVirtualenvElaspedtime = DWtVirtualenvNowtime - DWsPrevTick;


    DWsPrevTick = DWtVirtualenvNowtime;

    u32gVirtualenvRealtime += (uint32_t)DWtVirtualenvElaspedtime;

    u16gVirtualenvVirtualtime = (uint16_t)( (uint16_t)u32gVirtualenvRealtime / (uint16_t)u16g_VIRTUAL_REAL_TIME_SCALE );
}
#else
/******************************************************************************
  * @func     vdsVirtualtimeUpdateDm( void )                                   
  * @scope    internal                                                         
  * @brief    sample function                                                  
  * @param    -                                                                
  * @return   -                                                                
******************************************************************************/
void
vdsVirtualtimeUpdateDm( void )
{
    /* T.B.D */
    ;
}

/******************************************************************************
  * @func     vdsVirtualtimeDmCounter( void )                                  
  * @scope    internal                                                         
  * @brief    sample function                                                  
  * @param    -                                                                
  * @return   -                                                                
******************************************************************************/
void
vdsVirtualtimeDmCounter( void 9
{
    /* T.B.D */
    ;
}

#endif
/******************************************************************************
  * end of file                                                                
******************************************************************************/
