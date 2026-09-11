/******************************************************************************
  * @file     psimbrdgif.h                                                     
  * @brief    -                                                                
  * @domain   -                                                                
  * @date     2026/07/26                                                       
  * @(c)      2026 ocml                                                        
******************************************************************************/
#ifndef PSIMBRDGIF_H
#define PSIMBRDGIF_H

/******************************************************************************
  * include
******************************************************************************/
#include "../inc/common.h" /* uint8_t等の型定義。他ファイルからのinclude順序に依存しないための自己完結化 */

/******************************************************************************
  * external public variables contains macros
******************************************************************************/
extern uint8_t  u8gPsimbrdgifAclthlpc;
extern uint8_t  u8gPsimbrdgifBrkpdlpct;
extern uint8_t  u8gPsimbrdgifClthpdlpct;
extern int8_t   s8gPsimbrdgifGearpos;
extern uint16_t u16gPsimbrdgifVelspd;
extern uint16_t u16gPsimbrdgifRpmval;
extern uint8_t  u8gPsimbrdigIgswsts;

/******************************************************************************
  * external function prototype
******************************************************************************/
void vdgPsimbrdgifInit( void );
void vdgPsimbrdgif4msin( void );
void vdgPsimbrdgif4msout( void );

#endif
/******************************************************************************
  * end of file                                                                
******************************************************************************/
