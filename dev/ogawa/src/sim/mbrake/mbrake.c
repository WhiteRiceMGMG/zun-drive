/******************************************************************************
  * @file     mbrake.c
  * @brief    braking deceleration model
  * @domain   sim
  * @date     2026/09/09
  * @(c)      2026 ocml
******************************************************************************/

/******************************************************************************
  * include
******************************************************************************/
#include "../../inc/common.h"
#include "../../apl/psimbrdgif.h" /* u8gPsimbrdgifBrkpdlpct */

#include "../mbrakeif.h"

/******************************************************************************
  * external public variables contains macros
******************************************************************************/
uint16_t u16gMbrakeifDeclspd;

/******************************************************************************
  * internal public variables contains macros
******************************************************************************/
/* PLACEHOLDER TUNING VALUE - made up for prototype validation only. At 100% */
/* pedal this is ~7.5km/h of deceleration per real second (0.01km/h per 4ms  */
/* virtual tick, scaled by conf.h's virtual/real time ratio).                */
#define u16s_MBRAKE_MAXDECEL_SCALED12 ((uint16_t)12)

/******************************************************************************
  * external function
******************************************************************************/

/******************************************************************************
  * @func     vdgMbrakeifInit( void )
  * @scope    external
  * @brief    brake model init function
  * @param    -
  * @return   -
******************************************************************************/
void
vdgMbrakeifInit( void )
{
    u16gMbrakeifDeclspd = (uint16_t)0;
}

/******************************************************************************
  * @func     vdgMbrakeif4msin( void )
  * @scope    external
  * @brief    brake model 4ms function
  * @param    -
  * @return   -
******************************************************************************/
void
vdgMbrakeif4msin( void )
{
    u16gMbrakeifDeclspd = (uint16_t)( (uint32_t)u8gPsimbrdgifBrkpdlpct * u16s_MBRAKE_MAXDECEL_SCALED12 / (uint32_t)100 );
}

/******************************************************************************
  * internal function
******************************************************************************/

/******************************************************************************
  * end of file
******************************************************************************/
