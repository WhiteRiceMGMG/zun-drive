/******************************************************************************
  * @file     ppermif.h                                                        
  * @brief    -                                                                
  * @domain   -                                                                
  * @date     2026/07/26                                                       
  * @(c)      2026 ocml                                                        
******************************************************************************/
#ifndef PPERMIF_H
#define PPERMIF_H

/******************************************************************************
  * include                                                                    
******************************************************************************/

/******************************************************************************
  * external public variables contains macros                                  
******************************************************************************/
extern uint8_t u8gPpermifSht;
extern uint8_t u8gPpermifSim;
extern uint8_t u8gPpermifDisp;
extern uint8_t u8gPpermifSht;
extern uint8_t u8gPpermifShtre;
extern uint8_t u8gPpermifAcelLim;
extern uint8_t u8gPpermifSpdLim; 
extern uint8_t u8gPpermifShtdw;
extern uint8_t u8gPpermifPwrigoff;
extern uint8_t u8gPpermifAcelMax;
extern uint8_t u8gPpermifSpdMax;
extern uint8_t u8gPpermifPwrIgoff;

/******************************************************************************
  * external function prototype                                                
******************************************************************************/
void vdgPpermifInit( void );
void vdgPpermif16msin( void );

#endif
/******************************************************************************
  * end of file                                                                
******************************************************************************/
