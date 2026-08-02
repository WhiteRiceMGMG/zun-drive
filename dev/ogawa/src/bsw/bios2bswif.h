/******************************************************************************
  * @file     bios2bswif.h                                                     
  * @brief    swift to bsw bridge                                              
  * @domain   bsw                                                              
  * @date     2026/07/20                                                       
  * @(c)      2026 ocml                                                        
******************************************************************************/
#ifndef BIOS2BSWIF_H
#define BIOS2BSWIF_H

/******************************************************************************
  * include                                                                    
******************************************************************************/
/* #include "../../swiftbridge.h" */ /* swift bridge header */

/******************************************************************************
  * external public variables contains macros                                  
******************************************************************************/
extern uint8_t u8gBios2bswifAcelthl; /* ACCLE THROTTLE  1-100[%]         */
extern uint8_t u8gBios2bswifBrkpdl;  /* BRAKE PEDAL     1-100[%]         */
extern uint8_t u8gBios2bswifClthpdl; /* CLUTCH PEDAL    1-100[%]         */
extern int8_t  s8gBios2bswifGear;    /* GEAR POSITION   1,2,3,4,5,6,N[-] */
extern uint8_t u8gBios2bswifIgsw;    /* IGNITION SWITCH ON,OFF[-]        */

#define u8gSwiftifAcelthl  u8gBios2bswifAcelthl /* ACCLE THROTTLE   */
#define u8gSwiftifBrkpdl   u8gBios2bswifBrkpdl  /* BRAKE PEDAL      */
#define u8gSwiftifClthpdl  u8gBios2bswifClthpdl /* CLUTCH PEDAL     */
#define s8gSwiftifGear     s8gBios2bswifGear    /* GEAR POSITION    */
#define u8gSwiftifIgsw     u8gBios2bswifIgsw    /* IGNITION SWITCH  */

/******************************************************************************
  * external function prototype                                                
******************************************************************************/

#endif
/******************************************************************************
  * end of file                                                                
******************************************************************************/
