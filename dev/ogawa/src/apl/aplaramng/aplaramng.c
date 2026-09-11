/****************************************************************/
/*  * @file     aplaramng.c                                     */
/*  * @brief    apl manager                                     */
/*  * @domain   -                                               */
/*  * @date     2026/08/04                                      */
/*  * @(c)      2026 ocml                                       */
/****************************************************************/


/****************************************************************/
/*  * include                                                   */
/****************************************************************/
#include "../../inc/common.h"
#include "../ppermif.h"
#include "../pprtctif.h"
#include "../psimbrdgif.h"
#include "../pvehstsjdgif.h"
#include "../pwarnif.h"
#include "../psysctlif.h"

#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
#include "../../../debug/log/print_log.h"
#endif

#include "../aplaramngif.h"
/****************************************************************/
/*  * external public variables contains macros                 */
/****************************************************************/

/****************************************************************/
/*  * internal public variables contains macros                 */
/****************************************************************/

/****************************************************************/
/*  * external function                                         */
/****************************************************************/

/****************************************************************/
/*  * @func     vdgAplaramngifInit( void )                      */
/*  * @scope    external                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgAplaramngifInit( void )
{
    vdgPprtctifInit();
    vdgPwarnifInit();
    vdgPpermifInit();
    vdgPsysctlInit();
    vdgPsimbrdgifInit();
    vdgPvehstsjdgifInit();
}

/****************************************************************/
/*  * @func     vdgAplaramngif4msin( void )                     */
/*  * @scope    external                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgAplaramngif4msin( void )
{
    vdgPsimbrdgif4msin();
}

/****************************************************************/
/*  * @func     vdgAplaramngif4msout( void )                    */
/*  * @scope    external                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgAplaramngif4msout( void )
{
    vdgPsimbrdgif4msout();
}


/****************************************************************/
/*  * @func     vdgAplaramngif16msin( void )                    */
/*  * @scope    external                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgAplaramngif16msin( void )
{
    vdgPprtctif16msin();
    vdgPpermif16msin();
    vdgPsysctl16msin();
}


/****************************************************************/
/*  * @func     vdgAplaramngif16msout( void )                   */
/*  * @scope    external                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgAplaramngif16msout( void )
{

}

/****************************************************************/
/*  * @func     vdgAplaramngif64msin( void )                    */
/*  * @scope    external                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgAplaramngif64msin( void )
{
    vdgPwarnif64msin();
    vdgPvehstsjdgif64msin();
}

/****************************************************************/
/*  * @func     vdgAplaramngif64msout( void )                   */
/*  * @scope    external                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgAplaramngif64msout( void )
{

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
