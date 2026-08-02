/******************************************************************************
  * @file     acfmsts.c                                                        
  * @brief    -                                                                
  * @domain   -                                             
                   
  * @date     2026/07/26                                                       
  * @(c)      2026 ocml                                                        
******************************************************************************/
#ifndef ACFMSTS_H
#define ACFMSTS_H

/******************************************************************************
  * include                                                                    
******************************************************************************/
#include "../apl/ppermif.h"    /* u8gPpermifEng        */
                               /* u8gPpermifSht        */
#include "../apl/pprtctif.h"   /* u8gPprtctifOvrvsts   */
                               /* u8gPprtctifClthszsts */
                               /* u8gPprtctifBrkszsts  */
                               /* u8gPprtctifEnststs   */
#include "../apl/pwarnif.h"    /* u8gPwarnifOvrhet     */
                               /* u8gPwarnifSnserr     */
#include "../apl/psimbrdgif.h" /* u8gPsimbrdgifAclthlpc   */
                               /* u8gPsimbrdgifBrkpdlpct  */
                               /* u8gPsimbrdgifClthpdlpct */
                               /* s8gPsimbrdgifGearpos    */
                               /* u16gPsimbrdgifVelspd    */
                               /* u16gPsimbrdgifRpmval    */
                               /* u8gPsimbrdigIgswsts     */

/******************************************************************************
  * external public variables contains macros                                  
******************************************************************************/
#if 0
extern uint8_t u8gAcfmstsifAclthlpct;
extern uint8_t u8gAcfmstsifBrkpdlpct;
extern uint8_t u8gAcfmstsifClthpdlpct;
extern uint8_t u8gAcfmstsifEng;
extern uint8_t u8gAcfmstsifSht;
extern uint8_t u8gAcfmstsifOvrvsts;
extern uint8_t u8gAcfmstsifClthszsts;
extern uint8_t u8gAcfmstsifBrkszsts;
extern uint8_t u8gAcfmstsifEnststs;
extern uint8_t u8gAcfmstsifOvrhet;
extern uint8_t u8gAcfmstsifSnserr;
extern uint8_t u8gAcfmstsifIgswsts;
extern uint8_t s8gAcfmstsifGearpos;
extern uint8_t u16gAcfmstsifVelspd;
extern uint8_t u16gAcfmstsifRpmval;
#endif

#define u8gAcfmstsifAclthlpct  u8gPsimbrdgifAclthlpc
#define u8gAcfmstsifBrkpdlpct  u8gPsimbrdgifBrkpdlpct
#define u8gAcfmstsifClthpdlpct u8gPsimbrdgifClthpdlpct
#define u8gAcfmstsifEng        u8gPpermifEng
#define u8gAcfmstsifSht        u8gPpermifSht
#define u8gAcfmstsifOvrvsts    u8gPprtctifOvrvsts
#define u8gAcfmstsifClthszsts  u8gPprtctifClthszsts
#define u8gAcfmstsifBrkszsts   u8gPprtctifBrkszsts
#define u8gAcfmstsifEnststs    u8gPprtctifEnststs
#define u8gAcfmstsifOvrhet     u8gPwarnifOvrhet
#define u8gAcfmstsifSnserr     u8gPwarnifSnserr
#define u8gAcfmstsifIgswsts    u8gPsimbrdigIgswsts
#define s8gAcfmstsifGearpos    s8gPsimbrdgifGearpos
#define u16gAcfmstsifVelspd    u16gPsimbrdgifVelspd
#define u16gAcfmstsifRpmval    u16gPsimbrdgifRpmval

/******************************************************************************
  * external function prototype                                                
******************************************************************************/

#endif
/******************************************************************************
  * end of file                                                                
******************************************************************************/
