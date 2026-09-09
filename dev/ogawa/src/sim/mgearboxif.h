/******************************************************************************
  * @file     mgearboxif.h
  * @brief    gearbox ratio model
  * @domain   sim
  * @date     2026/09/09
  * @(c)      2026 ocml
******************************************************************************/
#ifndef MGEARBOXIF_H
#define MGEARBOXIF_H

/******************************************************************************
  * include
******************************************************************************/

/******************************************************************************
  * external public variables contains macros
******************************************************************************/
extern uint16_t u16gMgearboxifWheelrpm; /* engine rpm implied by current speed through this gear[rpm] */
extern uint16_t u16gMgearboxifDrvaccel; /* drive constant for this gear at 100% throttle & coupling[-] */

/******************************************************************************
  * external function prototype
******************************************************************************/
void vdgMgearboxifInit( void );
void vdgMgearboxif4msin( void );

#endif
/******************************************************************************
  * end of file
******************************************************************************/
