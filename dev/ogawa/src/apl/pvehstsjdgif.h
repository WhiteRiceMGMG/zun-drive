/****************************************************************/
/*  * @file     pvehstsjdgif.h                                  */
/*  * @brief    -                                               */
/*  * @domain   -                                               */
/*  * @date     2026/07/26                                      */
/*  * @(c)      2026 ocml                                       */
/****************************************************************/
#ifndef PVEHSTSJDGIF_H
#define PVEHSTSJDGIF_H

/****************************************************************/
/*  * include                                                   */
/****************************************************************/
#include "../inc/common.h" /* uint8_t等の型定義。他ファイルからのinclude順序に依存しないための自己完結化 */

/****************************************************************/
/*  * external public variables contains macros                 */
/****************************************************************/
extern uint8_t u8gPvehstsjdgifStop;
extern uint8_t u8gPvehstsjdgifRun;
extern uint8_t u8gPvehstsjdgifSpdup;
extern uint8_t u8gPvehstsjdgifSpddw;
extern uint8_t u8gPvehstsjdgifEnst;

/****************************************************************/
/*  * external function prototyp                                */
/****************************************************************/
void vdgPvehstsjdgifInit( void );
void vdgPvehstsjdgif64msin( void );

#endif
/****************************************************************/
/*  * end of file                                               */
/****************************************************************/

