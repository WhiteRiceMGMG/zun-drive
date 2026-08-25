/****************************************************************/
/*  * @file     sigswcrt.c                                      */
/*  * @brief    igsw correction                                 */
/*  * @domain   sensor-actuator                                 */
/*  * @date     2026/07/20                                      */
/*  * @(c)      2026 ocml                                       */
/****************************************************************/

/****************************************************************/
/*  * include                                                   */
/****************************************************************/
#include "../../inc/common.h"
#include "../../bsw/bios2bswif.h" /* u8gBios2bswifIgsw */

#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
#include "../../../debug/log/print_log.h"
#endif

#include "../sigswcrtif.h"

/****************************************************************/
/*  * external public variables contains macros                 */
/****************************************************************/
uint8_t u8gSigswcrtifSts;
uint8_t u8gSigswcrtifCrtflg;

/****************************************************************/
/*  * internal public variables contains macros                 */
/****************************************************************/
static uint8_t u8sSigswcrtStsO;

/****************************************************************/
/*  * external function                                         */
/****************************************************************/

/****************************************************************/
/*  * @func     vdgSigswcrtifInit( void )                       */
/*  * @scope    external                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgSigswcrtifInit( void )
{
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogPrint( "start vdgSigswcrtifInit()" );
#endif

    u8gSigswcrtifSts = (uint8_t)OFF;
    u8gSigswcrtifCrtflg = (uint8_t)OFF;
    u8sSigswcrtStsO = (uint8_t)OFF;

#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogArgPrint( "u8gSigswcrtifSts = %d", (uint32_t)u8gSigswcrtifSts );
    vdgLogArgPrint( "u8gSigswcrtifCrtflg = %d", (uint32_t)u8gSigswcrtifCrtflg );
    vdgLogArgPrint( "u8sSigswcrtStsO = %d", (uint32_t)u8sSigswcrtStsO );
#endif
}

/****************************************************************/
/*  * @func     vdgSigswcrtif64msin( void )                     */
/*  * @scope    external                                        */
/*  * @brief    igsw correction 64ms function                   */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgSigswcrtif64msin( void )
{
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogPrint( "start vdgSigswcrtif64msin()" );
    vdgLogArgPrint( "input : u8gSigswcrtifSts = %d", (uint32_t)u8gSigswcrtifSts );
    vdgLogArgPrint( "input : u8gSigswcrtifCrtflg = %d", (uint32_t)u8gSigswcrtifCrtflg );
    vdgLogArgPrint( "input : u8sSigswcrtStsO = %d", (uint32_t)u8sSigswcrtStsO );
#endif

    uint8_t u8tIgswsts;
    uint8_t u8tIgswstsO;
    uint8_t u8tCrtflg;

    u8tIgswsts = u8gBios2bswifIgsw;
    u8tIgswstsO = u8sSigswcrtStsO;
    u8tCrtflg = u8gSigswcrtifCrtflg;

    u8tCrtflg = (uint8_t)ON;
    if ( u8tIgswsts == u8tIgswstsO )
    {
        u8tIgswsts = u8tIgswstsO;
        u8tCrtflg = (uint8_t)OFF;
    }

    u8gSigswcrtifCrtflg = u8tCrtflg;
    u8gSigswcrtifSts = u8tIgswsts;
    u8sSigswcrtStsO = u8tIgswsts;

#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogPrint( "DONE! vdgSigswcrtif64msin()" );
    vdgLogArgPrint( "output : u8gSigswcrtifSts = %d", (uint32_t)u8gSigswcrtifSts );
    vdgLogArgPrint( "output : u8gSigswcrtifCrtflg = %d", (uint32_t)u8gSigswcrtifCrtflg );
    vdgLogArgPrint( "output : u8sSigswcrtStsO = %d", (uint32_t)u8sSigswcrtStsO );
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

