/******************************************************************************
  * @file     meng.c
  * @brief    engine RPM model
  * @domain   sim
  * @date     2026/09/09
  * @(c)      2026 ocml
******************************************************************************/

/******************************************************************************
  * include
******************************************************************************/
#include "../../inc/common.h"
#include "../../apl/psimbrdgif.h" /* u8gPsimbrdgifAclthlpc, u8gPsimbrdigIgswsts */
#include "../mgearboxif.h"        /* u16gMgearboxifWheelrpm */
#include "../mclthif.h"           /* u8gMclthifCplpct */

#include "../mengif.h"

/******************************************************************************
  * external public variables contains macros
******************************************************************************/
uint16_t u16gMengifRpm;

/******************************************************************************
  * internal public variables contains macros
******************************************************************************/
/* PLACEHOLDER TUNING VALUES - made up for prototype validation only.       */
#define u16s_MENG_IDLE_RPM800     ((uint16_t)800)  /* idle speed, IG on, no throttle       */
#define u16s_MENG_FREEMAX_RPM6000 ((uint16_t)6000) /* rpm at 100% throttle, fully uncoupled */
#define u16s_MENG_REDLINE_RPM6500 ((uint16_t)6500) /* hard clamp ceiling                    */
#define u16s_MENG_RPM_SLEW4MS15   ((uint16_t)15)   /* max rpm change per 4ms tick(~3750rpm/s)*/

/******************************************************************************
  * external function
******************************************************************************/

/******************************************************************************
  * @func     vdgMengifInit( void )
  * @scope    external
  * @brief    engine model init function
  * @param    -
  * @return   -
******************************************************************************/
void
vdgMengifInit( void )
{
    u16gMengifRpm = (uint16_t)0;
}

/******************************************************************************
  * @func     vdgMengif4msin( void )
  * @scope    external
  * @brief    engine model 4ms function
  * @param    -
  * @return   -
******************************************************************************/
void
vdgMengif4msin( void )
{
    uint32_t u32tFreerpm;
    uint32_t u32tWheelrpm;
    uint32_t u32tTargetrpm;
    int32_t  s32tRpm;
    int32_t  s32tDelta;

    /* "free-revving" target: what the engine would spin to under the       */
    /* current throttle with NO load at all (clutch pressed / neutral) -    */
    /* simple linear map from throttle 0-100% onto idle..freemax rpm.       */
    u32tFreerpm = (uint32_t)u16s_MENG_IDLE_RPM800
                + ( (uint32_t)u8gPsimbrdgifAclthlpc
                  * (uint32_t)( u16s_MENG_FREEMAX_RPM6000 - u16s_MENG_IDLE_RPM800 ) / (uint32_t)100 );

    /* "slaved" target: what the wheels force the engine to via the current */
    /* gear ratio, as if the clutch were 100% locked.                      */
    u32tWheelrpm = (uint32_t)u16gMgearboxifWheelrpm;

    /* actual target is a blend of the two by clutch coupling%: fully       */
    /* engaged -> slaved to road speed; fully disengaged -> free-revs off   */
    /* throttle alone, independent of road speed.                          */
    u32tTargetrpm = ( ( u32tWheelrpm * (uint32_t)u8gMclthifCplpct )
                     + ( u32tFreerpm * (uint32_t)( 100U - u8gMclthifCplpct ) ) ) / (uint32_t)100;

    if ( u8gPsimbrdigIgswsts != (uint8_t)ON )
    {
        u32tTargetrpm = (uint32_t)0; /* ignition off: no restart modeled */
    }

    if ( u32tTargetrpm > (uint32_t)u16s_MENG_REDLINE_RPM6500 )
    {
        u32tTargetrpm = (uint32_t)u16s_MENG_REDLINE_RPM6500;
    }

    /* move actual rpm toward target, bounded per tick (models flywheel/    */
    /* engine inertia so rpm ramps rather than jumping instantly - this is  */
    /* also what makes a stall fall out naturally: at a stop, in gear,      */
    /* clutch fully released, throttle 0% -> wheelrpm=0 & freerpm-weight=0% */
    /* -> target=0, and the engine winds down to 0 over ~1 second)          */
    s32tRpm   = (int32_t)u16gMengifRpm;
    s32tDelta = (int32_t)u32tTargetrpm - s32tRpm;

    if ( s32tDelta > (int32_t)u16s_MENG_RPM_SLEW4MS15 )
    {
        s32tDelta = (int32_t)u16s_MENG_RPM_SLEW4MS15;
    }
    if ( s32tDelta < -(int32_t)u16s_MENG_RPM_SLEW4MS15 )
    {
        s32tDelta = -(int32_t)u16s_MENG_RPM_SLEW4MS15;
    }

    s32tRpm += s32tDelta;
    if ( s32tRpm < 0 )
    {
        s32tRpm = 0;
    }

    u16gMengifRpm = (uint16_t)s32tRpm;
}

/******************************************************************************
  * internal function
******************************************************************************/

/******************************************************************************
  * end of file
******************************************************************************/
