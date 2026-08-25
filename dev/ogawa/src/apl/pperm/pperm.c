/****************************************************************/
/*  * @file     ppermif.c                                       */
/*  * @brief    -                                               */
/*  * @domain   -                                               */
/*  * @date     2026/08/04                                      */
/*  * @(c)      2026 ocml                                       */
/****************************************************************/

/****************************************************************/
/*  * include                                                   */
/****************************************************************/
#include "../../inc/common.h"

#include "../../sac/sacelcrtif.h" /* u8gSacelcrtifthlpct */
#include "../../sac/sclthcrtif.h" /* u8gSclthcrtifPdlpct */
#include "../../sac/sigswcrtif.h" /* u8gSigswifSts       */

#include "../pprtctif.h" /* u8gPprtctifOvrvsts   */
                         /* u8gPprtctifClthszsts */
                         /* u8gPprtctifBrkszsts  */
                         /* u8gPprtctifEnststs   */

#include "../psimbrdif.h" /* u16gPsimbrdgifVelspd  */

#include "../ppermif.h"

/****************************************************************/
/*  * external public variables contains macros                 */
/****************************************************************/
uint8_t u8gPpermifSht;      /* shift change flag  */
uint8_t u8gPpermifSim;      /* simulation flag    */
uint8_t u8gPpermifDisp;     /* display flag       */
uint8_t u8gPpermifShtrev;   /* shift reverce flag */
uint8_t u8gPpermifAcelLim;  /* acel limit         */
uint8_t u8gPpermifSpdLim;   /* speed limit        */
uint8_t u8gPpermifShtdw;    /* shift down flag    */
uint8_t u8gPpermifPwrigoff; /* power ig-off flag  */
uint8_t u8gPpermifAcelMax;  /* acel limit value   */
uint8_t u8gPpermifSpdMax;   /* speed limit value  */

/****************************************************************/
/*  * internal public variables contains macros                 */
/****************************************************************/

/****************************************************************/
/*  * external function                                         */
/****************************************************************/

/****************************************************************/
/*  * @func     vdgPpermifInit( void )                          */
/*  * @scope    external                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgPpermifInit( void )
{
    u8gPpermifSht      = (uint8_t)OFF;
    u8gPpermifSim      = (uint8_t)OFF;
    u8gPpermifDisp     = (uint8_t)OFF;
    u8gPpermifShtrev   = (uint8_t)OFF;
    u8gPpermifAcelLim  = (uint8_t)OFF;
    u8gPpermifSpdLim;  = (uint8_t)OFF;
    u8gPpermifShtdw;   = (uint8_t)OFF;
    u8gPpermifPwrigoff = (uint8_t)OFF;
    u8gPpermifAcelMax  = (uint8_t)OFF;
    u8gPpermifSpdMax   = (uint8_t)OFF;
}

/****************************************************************/
/*  * @func     vdgPpermif16ms( void )                          */
/*  * @scope    external                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgPpermif16ms( void )
{
    
    if ( u8gSigswifSts == (uint8_t)ON ) /* igsw == on */
    {
        if ( u8gSclthcrtifPdlpct > u8s_PPERM_SHT_CLTHPCT30 ) /* acel > 30% */
        {
            if ( u16gPsimbrdgifVelspd > u16s_PPERM_SHT_SPD5 ) /* spd > 5 */
            {
                u8gPpermifSht == (uint8_t)ON; /* shift(N) == on   */
            }
            if ( u16gPsimbrdgifVelspd <= u16s_PPERM_SHTREV_SPD5 ) /* acel <= 5 */
            {
                u8gPpermifShtrev == (uint8_t)ON; /* shift(R) == on */
            }
        }

        if ( u8gPprtctifBrkszsts == (uint8_t)ON ) /* brake szs */
        {
            u8gPpermifAcelMax = u8s_PPERM_ACEL_LIM70; /* acel limit = 70 */
            u8gPpermifSpdMax  = u8s_PPERM_SPD_LIM50; /* spd limit = 50 */
        }

        if ( u8gPprtctifOvrvst == (uint8_t)ON )
        {
            u8gPpermifAcelMax = u8s_PPERM_ACEL_LIM50; /* acel limit 50% */
            u8gPpermifShtdw   = (uint8_t)OFF; /* dont perm shift down */
        }

        if ( u8gPprtctifEnststs == (uint8_t)ON ) /* enst == on */
        {
            u8gPprtctifEnststs = (uint8_t)OFF; /* enst == off */
            u8gPpermifPwrIgoff = (uint8_t)ON; /* poewr igsw == on */
        }
    }
    else
    {
        u8gPpermifAcelMax == (uint8_t)0;
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
