/******************************************************************************
  * @file     mvirtmachif.h
  * @brief    vehicle virtual machine (orchestrator + body physics)
  * @domain   sim
  * @date     2026/09/09
  * @(c)      2026 ocml
******************************************************************************/
#ifndef MVIRTMACHIF_H
#define MVIRTMACHIF_H

/******************************************************************************
  * include
******************************************************************************/

/******************************************************************************
  * external public variables contains macros
******************************************************************************/
extern uint16_t u16gMvirtmachifVelspd;   /* vehicle speed[km/h] */
extern uint8_t  u8gMvirtmachifEngrunsts; /* engine actually running: IG-ON && rpm>=threshold OFF,ON[-] */

/******************************************************************************
  * external function prototype
******************************************************************************/
void vdgMvirtmachifInit( void );
void vdgMvirtmachif4msin( void );

#endif
/******************************************************************************
  * end of file
******************************************************************************/
