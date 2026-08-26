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
#include "../ppermif.h"  /* u8gPpermifSht   */
                         /* u8gPpermifShtre */
                         /* u8gPpermifAcelLim */
                         /* u8gPpermifAcelMax */
                         /* u8gPpermifSpdLim  */

#include "../../sac/sigswcrtif.h" /* u8gSigswcrtifSts  */
#include "../../sac/sgearcrtif.h" /* s8gSgearcrtifPos  */
                                  /* s8g_SGEARIF_REVERSE */
#include "../../sac/sbrkcrtif.h"  /* u8gSbrkcrtifPdlpct  */
#include "../../sac/sacelcrtif.h" /* u8gSclthcrtifPdlpct */
#include "../../sac/sclthcrtif.h" /* u8gSacelcrtifThlpct */

#include "../psysctlif.h"

/****************************************************************/
/*  * external public variables contains macros                 */
/****************************************************************/
int8_t s8gPsysctlGearpos;   /* SACから受け取った値をSIMに渡す */
uint8_t u8gPsysctlAcelpct;  /* SACから受け取った値をSIMに渡す */
uint8_t u8gPsysctlBrkpct;   /* SACから受け取った値をSIMに渡す */
uint8_t u8gPsysctlClthpct;  /* SACから受け取った値をSIMに渡す */



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
}

    if ( u8gSigswcrtifSts == (uint8_t)ON )
    {
        if ( s8gSgearcrtifPos == s8g_SGEARIF_REVERSE )
        {
            if ( u8gPpermifShtre == (uint8_t)ON )
            {
                s8tGearpos = s8gSgearcrtifPos;
            }
        }
        else
        {
            if ( u8gPpermifShtre == (uint8_t)ON )
            {
                s8tGearpos = s8gSgearcrtifPos;
            }
        }
        
        if ( u8gPpermifAcelLim == (uint8_t)ON )
        {
            u8tAcelpct = u8gPpermifAcelMax;
        }
        
        if ( u8gPpermifSpdLim == (uint8_t)ON )
        {
            if ( スピード > u8gPpermifSpdMax )
            {
                u8tSpdval = u8gPpermifSpdMax;
                ブレーキ = u8gSbrkcrtifPdlpct + 50%
                if ( ブレーキ > 100% )
                {
                    ブレーキ = 100%;
                }
            }
        }
    }
    else
    {


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
