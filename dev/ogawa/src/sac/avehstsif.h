/******************************************************************************
  * @file     avehstsif.h                                                      
  * @brief    -                                                                
  * @domain   -                                                                
  * @date     2026/07/26                                                       
  * @(c)      2026 ocml                                                        
******************************************************************************/
#ifndef AVEHSTSIF_H
#define AVEHSTSIF_H

/******************************************************************************
  * include                                                                    
******************************************************************************/
#include "../apl/pvehstsjdgif.h"

/******************************************************************************
  * external public variables contains macros                                  
******************************************************************************/
#if 0
extern uint8_t u8gAvehstsifStop;
extern uint8_t u8gAvehstsifRun;
extern uint8_t u8gAvehstsifSpdup;
extern uint8_t u8gAvehstsifSpddw;
extern uint8_t u8gAvehstsifEnst;
#endif

#define u8gAvehstsifStop  u8gPvehstsjdgifStop
#define u8gAvehstsifRun   u8gPvehstsjdgifRun
#define u8gAvehstsifSpdup u8gPvehstsjdgifSpdup
#define u8gAvehstsifSpddw u8gPvehstsjdgifSpddw
#define u8gAvehstsifEnst  u8gPvehstsjdgifEnst

/******************************************************************************
  * external function prototype                                                
******************************************************************************/

#endif
/******************************************************************************
  * end of file                                                                
******************************************************************************/
