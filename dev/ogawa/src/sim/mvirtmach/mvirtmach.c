/******************************************************************************
  * @file     mvirtmach.c
  * @brief    vehicle virtual machine (orchestrator + body physics)
  * @domain   sim
  * @date     2026/09/09
  * @(c)      2026 ocml
******************************************************************************/

/******************************************************************************
  * include
******************************************************************************/
#include "../../inc/common.h"
#include "../../apl/psimbrdgif.h" /* u8gPsimbrdgifAclthlpc, u8gPsimbrdigIgswsts */
#include "../mclthif.h"           /* vdgMclthif4msin(), u8gMclthifCplpct */
#include "../mgearboxif.h"        /* vdgMgearboxif4msin(), u16gMgearboxifDrvaccel */
#include "../mengif.h"            /* vdgMengif4msin(), u16gMengifRpm */
#include "../mbrakeif.h"          /* vdgMbrakeif4msin(), u16gMbrakeifDeclspd */

#include "../mvirtmachif.h"

/******************************************************************************
  * external public variables contains macros
******************************************************************************/
uint16_t u16gMvirtmachifVelspd;
uint8_t  u8gMvirtmachifEngrunsts;

/******************************************************************************
  * internal public variables contains macros
******************************************************************************/
/* PLACEHOLDER TUNING VALUES - made up for prototype validation only.       */
#define u16s_MVIRTMACH_ENGRUN_RPM400 ((uint16_t)400) /* rpm floor to call the engine "running" */
#define u8s_MVIRTMACH_ROLLRESIST1    ((uint8_t)1)    /* flat rolling resistance[0.01km/h/tick] */
#define u16s_MVIRTMACH_DRAG_DIV4000  ((uint16_t)4000)/* aero-ish drag: speed/4000 per tick     */

static uint16_t u16sMvirtmachSpdaccO; /* speed accumulator, 0.01km/h units (finer than the      */
                                       /* uint16_t whole-km/h published interface allows)        */

/******************************************************************************
  * external function
******************************************************************************/

/******************************************************************************
  * @func     vdgMvirtmachifInit( void )
  * @scope    external
  * @brief    vehicle virtual machine init function
  * @param    -
  * @return   -
******************************************************************************/
void
vdgMvirtmachifInit( void )
{
    vdgMclthifInit();
    vdgMgearboxifInit();
    vdgMengifInit();
    vdgMbrakeifInit();

    u16sMvirtmachSpdaccO    = (uint16_t)0;
    u16gMvirtmachifVelspd   = (uint16_t)0;
    u8gMvirtmachifEngrunsts = (uint8_t)OFF;
}

/******************************************************************************
  * @func     vdgMvirtmachif4msin( void )
  * @scope    external
  * @brief    vehicle virtual machine 4ms function - runs the whole sim chain
  * @param    -
  * @return   -
******************************************************************************/
void
vdgMvirtmachif4msin( void )
{
    int32_t s32tSpdacc;
    int32_t s32tDelta;

    /* gearbox reads THIS tick's start-of-tick velocity (still last tick's  */
    /* published value at this point), everything else follows from it     */
    vdgMclthif4msin();
    vdgMgearboxif4msin();
    vdgMengif4msin();
    vdgMbrakeif4msin();

    s32tSpdacc = (int32_t)u16sMvirtmachSpdaccO;

    /* drive force: throttle x clutch coupling x this gear's drive constant */
    s32tDelta  = (int32_t)u8gPsimbrdgifAclthlpc * (int32_t)u8gMclthifCplpct
               * (int32_t)u16gMgearboxifDrvaccel / (int32_t)10000;
    s32tDelta -= (int32_t)u16gMbrakeifDeclspd;

    if ( s32tSpdacc > 0 )
    {
        /* rolling resistance + speed-proportional drag only apply while moving */
        s32tDelta -= (int32_t)u8s_MVIRTMACH_ROLLRESIST1;
        s32tDelta -= s32tSpdacc / (int32_t)u16s_MVIRTMACH_DRAG_DIV4000;
    }

    s32tSpdacc += s32tDelta;
    if ( s32tSpdacc < 0 )
    {
        s32tSpdacc = 0;
    }

    u16sMvirtmachSpdaccO  = (uint16_t)s32tSpdacc;
    u16gMvirtmachifVelspd = (uint16_t)( (uint16_t)s32tSpdacc / (uint16_t)100 );

    u8gMvirtmachifEngrunsts = (uint8_t)OFF;
    if ( ( u8gPsimbrdigIgswsts == (uint8_t)ON ) && ( u16gMengifRpm >= u16s_MVIRTMACH_ENGRUN_RPM400 ) )
    {
        u8gMvirtmachifEngrunsts = (uint8_t)ON;
    }
}

/******************************************************************************
  * internal function
******************************************************************************/

/******************************************************************************
  * end of file
******************************************************************************/
