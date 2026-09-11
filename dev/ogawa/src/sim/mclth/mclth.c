/******************************************************************************
  * @file     mclth.c
  * @brief    clutch coupling model
  * @domain   sim
  * @date     2026/09/09
  * @(c)      2026 ocml
******************************************************************************/

/******************************************************************************
  * include
******************************************************************************/
#include "../../inc/common.h"
#include "../../apl/psimbrdgif.h" /* s8gPsimbrdgifGearpos, u8gPsimbrdgifClthpdlpct */
#include "../../sac/sgearcrtif.h" /* s8g_SGEARIF_NEUTRAL */

#include "../mclthif.h"

/******************************************************************************
  * external public variables contains macros
******************************************************************************/
uint8_t u8gMclthifCplpct;

/******************************************************************************
  * internal public variables contains macros
******************************************************************************/

/******************************************************************************
  * external function
******************************************************************************/

/******************************************************************************
  * @func     vdgMclthifInit( void )
  * @scope    external
  * @brief    clutch model init function
  * @param    -
  * @return   -
******************************************************************************/
void
vdgMclthifInit( void )
{
    u8gMclthifCplpct = (uint8_t)0;
}

/******************************************************************************
  * @func     vdgMclthif4msin( void )
  * @scope    external
  * @brief    clutch model 4ms function
  * @param    -
  * @return   -
******************************************************************************/
void
vdgMclthif4msin( void )
{
    uint8_t u8tCplpct;

    if ( s8gPsimbrdgifGearpos == s8g_SGEARIF_NEUTRAL )
    {
        /* neutral: never mechanically coupled, regardless of pedal position */
        u8tCplpct = (uint8_t)0;
    }
    else
    {
        /* pedal 0%(released)=fully engaged, pedal 100%(floored)=fully disengaged */
        u8tCplpct = (uint8_t)( (uint8_t)100 - u8gPsimbrdgifClthpdlpct );
    }

    u8gMclthifCplpct = u8tCplpct;
}

/******************************************************************************
  * internal function
******************************************************************************/

/******************************************************************************
  * end of file
******************************************************************************/
