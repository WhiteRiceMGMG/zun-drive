/****************************************************************/
/*  * @file     sgearcrt.h                                      */
/*  * @brief    gear correction                                 */
/*  * @domain   -                                               */
/*  * @date     2026/07/20                                      */
/*  * @(c)      2026 ocml                                       */
/****************************************************************/
#ifndef SGEARCRT_H
#define SGEARCRT_H

/****************************************************************/
/*  * include                                                   */
/****************************************************************/

/****************************************************************/
/*  * external public variables contains macros                 */
/****************************************************************/
extern int8_t  s8gSgearcrtifPos;
extern uint8_t u8gSgearcrtifCrtflg;

/* promoted here from sgearcrt.c so other modules (psysctl, sim layer) can */
/* reference gear positions by name instead of raw integers               */
#define s8g_SGEARIF_REVERSE ((int8_t)-1)   /* gear: REVERSE */
#define s8g_SGEARIF_NEUTRAL ((int8_t)0)    /* gear: NEUTRAL */
#define s8g_SGEARIF_FIRST   ((int8_t)1)    /* gear: FIRST   */
#define s8g_SGEARIF_SECOND  ((int8_t)2)    /* gear: SECOND  */
#define s8g_SGEARIF_THIRD   ((int8_t)3)    /* gear: THIRD   */
#define s8g_SGEARIF_FOURTH  ((int8_t)4)    /* gear: FOURTH  */
#define s8g_SGEARIF_FIFTH   ((int8_t)5)    /* gear: FIFTH   */

/****************************************************************/
/*  * external function prototyp                                */
/****************************************************************/
void vdgSgearcrtifInit( void );
void vdgSgearcrtif64msin( void );

#endif
/****************************************************************/
/*  * end of file                                               */
/****************************************************************/
