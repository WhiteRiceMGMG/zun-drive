/******************************************************************************
  * @file     mgearbox.c
  * @brief    gearbox ratio model
  * @domain   sim
  * @date     2026/09/09
  * @(c)      2026 ocml
******************************************************************************/

/******************************************************************************
  * include
******************************************************************************/
#include "../../inc/common.h"
#include "../../apl/psimbrdgif.h" /* s8gPsimbrdgifGearpos */
#include "../../sac/sgearcrtif.h" /* s8g_SGEARIF_NEUTRAL, s8g_SGEARIF_REVERSE */
#include "../mvirtmachif.h"       /* u16gMvirtmachifVelspd */

#include "../mgearboxif.h"

/******************************************************************************
  * external public variables contains macros
******************************************************************************/
uint16_t u16gMgearboxifWheelrpm;
uint16_t u16gMgearboxifDrvaccel;

/******************************************************************************
  * internal public variables contains macros
******************************************************************************/
/* PLACEHOLDER TUNING VALUES - made up for prototype validation only;       */
/* Ogawa (or the eventual UE5 port) will retune/replace these with real     */
/* gear ratios / vehicle data. Both tables are simple linear-in-gear-number */
/* approximations, not derived from any real gearbox.                      */
#define u16s_MGEARBOX_RATIO_BASE140 ((uint16_t)140) /* 1st gear: rpm per km/h            */
#define u16s_MGEARBOX_RATIO_STEP20  ((uint16_t)20)  /* ratio drops by this per gear up   */
#define u16s_MGEARBOX_DRVACC_BASE19 ((uint16_t)19)  /* 1st gear: drive constant          */
#define u16s_MGEARBOX_DRVACC_STEP3  ((uint16_t)3)   /* drive constant drops per gear up  */

/******************************************************************************
  * external function
******************************************************************************/

/******************************************************************************
  * @func     vdgMgearboxifInit( void )
  * @scope    external
  * @brief    gearbox model init function
  * @param    -
  * @return   -
******************************************************************************/
void
vdgMgearboxifInit( void )
{
    u16gMgearboxifWheelrpm = (uint16_t)0;
    u16gMgearboxifDrvaccel = (uint16_t)0;
}

/******************************************************************************
  * @func     vdgMgearboxif4msin( void )
  * @scope    external
  * @brief    gearbox model 4ms function
  * @param    -
  * @return   -
******************************************************************************/
void
vdgMgearboxif4msin( void )
{
    int8_t   s8tFwdgear;
    uint16_t u16tRatio;
    uint16_t u16tDrvaccel;

    if ( s8gPsimbrdgifGearpos == s8g_SGEARIF_NEUTRAL )
    {
        u16tRatio    = (uint16_t)0;
        u16tDrvaccel = (uint16_t)0;
    }
    else
    {
        /* reverse reuses 1st gear's magnitude - direction is handled purely */
        /* via s8gPsimbrdgifGearpos elsewhere, not modeled as negative speed */
        s8tFwdgear = ( s8gPsimbrdgifGearpos == s8g_SGEARIF_REVERSE ) ? (int8_t)1 : s8gPsimbrdgifGearpos;

        u16tRatio    = (uint16_t)( u16s_MGEARBOX_RATIO_BASE140  - (uint16_t)( ( s8tFwdgear - 1 ) * u16s_MGEARBOX_RATIO_STEP20  ) );
        u16tDrvaccel = (uint16_t)( u16s_MGEARBOX_DRVACC_BASE19  - (uint16_t)( ( s8tFwdgear - 1 ) * u16s_MGEARBOX_DRVACC_STEP3  ) );
    }

    u16gMgearboxifWheelrpm = (uint16_t)( (uint32_t)u16gMvirtmachifVelspd * u16tRatio );
    u16gMgearboxifDrvaccel = u16tDrvaccel;
}

/******************************************************************************
  * internal function
******************************************************************************/

/******************************************************************************
  * end of file
******************************************************************************/
