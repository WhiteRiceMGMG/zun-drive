/****************************************************************/
/*  * @file     sbrkcrt.c                                       */
/*  * @brief    brk correction                                  */
/*  * @domain   sensor-actuator                                 */
/*  * @date     2026/08/11                                      */
/*  * @(c)      2026 ocml                                       */
/****************************************************************/

/****************************************************************/
/*  * include                                                   */
/****************************************************************/
#include "../../inc/common.h"
#include "../../bsw/bios2bswif.h"  /* u8gBios2bswifBrkpdl  */

#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
#include "../../../debug/log/print_log.h"
#endif

#include "../sbrkcrtif.h"

/****************************************************************/
/*  * external public variables contains macros                 */
/****************************************************************/
uint8_t u8gSbrkcrtifPdlpct;
uint8_t u8gSbrkcrtifCrtflg;

/****************************************************************/
/*  * internal public variables contains macros                 */
/****************************************************************/
#define u8s_BRKCRT_DEADBAND  ((uint8_t)((4.) / ((100.) / (256.) + 0.5)))
static uint8_t u8sSbrkcrtPdlpctO;

/****************************************************************/
/*  * external function                                         */
/****************************************************************/

/****************************************************************/
/*  * @func     vdgSbrkcrtifInit( void )                        */
/*  * @scope    external                                        */
/*  * @brief    brk correction init function                    */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgSbrkcrtifInit( void )
{
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogPrint( "start vdgSbrkcrtifInit()" );
#endif

    u8sSbrkcrtPdlpctO  = (uint8_t)0;
    u8gSbrkcrtifPdlpct = (uint8_t)0;
    u8gSbrkcrtifCrtflg = (uint8_t)OFF;

#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogArgPrint( "u8sSbrkcrtPdlpctO = %d", (uint32_t)u8sSbrkcrtPdlpctO );
    vdgLogArgPrint( "u8gSbrkcrtifPdlpct = %d", (uint32_t)u8gSbrkcrtifPdlpct );
    vdgLogArgPrint( "u8gSbrkcrtifCrtflg = %d", (uint32_t)u8gSbrkcrtifCrtflg );
#endif
}

/****************************************************************/
/*  * @func     vdgSbrkcrtif4msin( void )                       */
/*  * @scope    external                                        */
/*  * @brief    brk correction 64ms function                    */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgSbrkcrtif4msin( void )
{
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogPrint( "start vdgSbrkcrtif4msin()" );
    vdgLogArgPrint( "input : u8sSbrkcrtPdlpctO = %d", (uint32_t)u8sSbrkcrtPdlpctO );
    vdgLogArgPrint( "input : u8gSbrkcrtifPdlpct = %d", (uint32_t)u8gSbrkcrtifPdlpct );
    vdgLogArgPrint( "input : u8gSbrkcrtifCrtflg = %d", (uint32_t)u8gSbrkcrtifCrtflg );
#endif

    uint8_t u8tBrkpct;
    uint8_t u8tBrkpctO;
    uint8_t u8tPctdelta;
    uint8_t u8tCrtflg;

    u8tBrkpct = u8gBios2bswifBrkpdl;
    u8tBrkpctO = u8sSbrkcrtPdlpctO;

    if ( u8tBrkpct > u8g_MAX )
    {
        u8tBrkpct = u8g_MAX;
    }

    if ( u8tBrkpct >= u8tBrkpctO )
    {
        u8tPctdelta = u8tBrkpct - u8tBrkpctO;
    }
    else
    {
        u8tPctdelta = u8tBrkpctO - u8tBrkpct;
    }


    u8tCrtflg = (uint8_t)OFF;
    if ( u8tPctdelta <= u8s_BRKCRT_DEADBAND )
    {
        u8tCrtflg = (uint8_t)ON;
        u8tBrkpct = u8tBrkpctO;
    }

    u8sSbrkcrtPdlpctO = u8tBrkpct;
    u8gSbrkcrtifPdlpct = u8tBrkpct;
    u8gSbrkcrtifCrtflg = u8tCrtflg;

#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogPrint( "DONE! vdgSbrkcrtif4msin()" );
    vdgLogArgPrint( "output : u8sSbrkcrtPdlpctO = %d", (uint32_t)u8sSbrkcrtPdlpctO );
    vdgLogArgPrint( "output : u8gSbrkcrtifPdlpct = %d", (uint32_t)u8gSbrkcrtifPdlpct );
    vdgLogArgPrint( "output : u8gSbrkcrtifCrtflg = %d", (uint32_t)u8gSbrkcrtifCrtflg );
#endif
}


/****************************************************************/
/*  * internal function                                         */
/****************************************************************/

/****************************************************************/
/*  * @func     vdsSampleFunc( void )                           */
/*  * @scope    internal                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/

/****************************************************************/
/*  * end of file                                               */
/****************************************************************/
