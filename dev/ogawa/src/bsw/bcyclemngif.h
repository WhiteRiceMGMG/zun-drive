/******************************************************************************
  * @file     bcyclemngif.h                                                    
  * @brief    cycle manager                                                    
  * @domain   bsw                                                              
  * @date     2026/07/20                                                       
  * @(c)      2026 ocml                                                        
******************************************************************************/
#ifndef BCYCLEMNGIF_H
#define BCYCLEMNGIF_H

/******************************************************************************
  * include                                                                    
******************************************************************************/
#include "../inc/common.h"

/******************************************************************************
  * external public variables contains macros                                  
******************************************************************************/

/******************************************************************************
  * external function prototype                                                
******************************************************************************/
void vdgBcyclemngifInit( void );     /* init cycle manager        */
void vdgBcyclemngif4msin( void );    /* 4ms input cycle manager   */
void vdgBcyclemngif4msout( void );   /* 4ms output cycle manager  */
void vdgBcyclemngif16msin( void );   /* 16ms input cycle manager  */
void vdgBcyclemngif16msout( void );  /* 16ms output cycle manager */
void vdgBcyclemngif64msin( void );   /* 64ms input cycle manager  */
void vdgBcyclemngif64msout( void );  /* 64ms output cycle manager */

#endif
/******************************************************************************
  * end of file                                                                
******************************************************************************/
