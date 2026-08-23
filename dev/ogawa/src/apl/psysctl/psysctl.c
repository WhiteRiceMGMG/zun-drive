/****************************************************************/
/*  * @file     psysctl.c                                       */
/*  * @brief    -                                               */
/*  * @domain   -                                               */
/*  * @date     2026/08/11                                      */
/*  * @(c)      2026 ocml                                       */
/****************************************************************/

/****************************************************************/
/*  * include                                                   */
/****************************************************************/
#include "../../inc/common.h"
#include "../ppermif.h"
#include "../psysctlif.h"


/****************************************************************/
/*  * external public variables contains macros                 */
/****************************************************************/
int8_t s8gPsysctlGearpos;
int8_t s8gPsysctlAcelpct;

/****************************************************************/
/*  * internal public variables contains macros                 */
/****************************************************************/

/****************************************************************/
/*  * external function                                         */
/****************************************************************/

/****************************************************************/
/*  * @func     vdgPsysctlInit( void )                          */
/*  * @scope    external                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgPsysctlInit( void )
{
    s8gPsysctlGearpos = (uint8_t)s8g_PSYSCTL_INITGEAR;
    s8gPsysctlAcelpct = (uint8_t)0;
}

/****************************************************************/
/*  * @func     vdgPsysctlInit( void )                          */
/*  * @scope    external                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgPsysctl16ms( void )
{
    int8_t s8tGearpos;
    uint8_t u8tGearrev;
    uint8_t u8tAcelpct;

    u8tAcelpct = u8gSacelcrtifThlpct;
    s8tGearpos = s8gSgearcrtifPos;
    u8tGearrev = 

    if ( u8gPpermifSht == (uint8_t)ON )
    {
        s8sGearposO = s8tGearpos;
        s8gPsysctlGearpos = s8tGearpos;
    }

    if ( u8gPpermifShtrev == (uint8_t)ON )
    {
        
        
    
    if ( u8gPpermifAcelLim == (uint8_t)ON )
    {
        u8tAcelpct = u8gPpermifAcelMax;
    }
    
    
    

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
