/******************************************************************************
  * @file     ppermif.c                                                        
  * @brief    -                                                                
  * @domain   -                                                                
  * @date     2026/07/26                                                       
  * @(c)      2026 ocml                                                        
******************************************************************************/

/******************************************************************************
  * include                                                                    
******************************************************************************/
#include "../../inc/common.h"

#include "../../sac/sacelcrtif.h" /* u8gSacelcrtifthlpct */
#include "../../sac/sclthcrtif.h" /* u8gSclthcrtifPdlpct */
#include "../../sac/sigswcrtif.h" /* u8gSigswifSts       */

#include "../pprtctif.h" /* u8gPprtctifOvrvsts   */
                         /* u8gPprtctifClthszsts */
                         /* u8gPprtctifBrkszsts  */
                         /* u8gPprtctifEnststs   */

#include "../psimbrdif.h" /* u16gPsimbrdgifVelspd  */

#include "../ppermif.h"

/******************************************************************************
  * external public variables contains macros                                  
******************************************************************************/
uint8_t u8gPpermifSht;
uint8_t u8gPpermifSim;
uint8_t u8gPpermifDisp;
uint8_t u8gPpermifSht;
uint8_t u8gPpermifShtre;
uint8_t u8gPpermifAcelLim;
uint8_t u8gPpermifSpdLim; 
uint8_t u8gPpermifShtdw;
uint8_t u8gPpermifPwrigoff;
uint8_t u8gPpermifAcelMax;
uint8_t u8gPpermifSpdMax;
uint8_t u8gPpermifPwrIgoff;
uint8_t u8gPpermifShtR;

/******************************************************************************
  * internal public variables contains macros                                  
******************************************************************************/

/******************************************************************************
  * external function                                                          
******************************************************************************/

/******************************************************************************
  * @func     vdgPpermifInit( void )                                           
  * @scope    external                                                         
  * @brief    -                                                                
  * @param    -                                                                
  * @return   -                                                                
******************************************************************************/
void
vdgPpermifInit( void )
{
    u8gPpermifSim      = (uint8_t)ON;
    u8gPpermifDisp     = (uint8_t)ON;
    u8gPpermifSht      = (uint8_t)OFF;
    u8gPpermifShtre    = (uint8_t)OFF;
    u8gPpermifAcelLim  = (uint8_t)OFF;
    u8gPpermifSpdLim   = (uint8_t)OFF;
    u8gPpermifShtdw    = (uint8_t)OFF;
    u8gPpermifPwrigoff = (uint8_t)OFF;
    u8gPpermifAcelMax  = (uint8_t)OFF;
    u8gPpermifSpdMax   = (uint8_t)OFF;
    u8gPpermifPwrIgoff = (uint8_t)OFF;
}

/******************************************************************************
  * @func     vdgSampleFunc( void )                                            
  * @scope    external                                                         
  * @brief    -                                                                
  * @param    -                                                                
  * @return   -                                                                
******************************************************************************/
void
vdgPpermif16msin( void )
{
    if ( u8gSigswifSts == (uint8_t)ON ) /* イグニッションがON */
    {
        if ( u8gSclthcrtifPdlpct > u8s_PPERM_SHT_CLTHPCT30 ) /* アクセル開度が30%以上 */
        {
            if ( u16gPsimbrdgifVelspd > u16s_PPERM_SHT_SPD5 ) /* 車速が5km以上 */
            {
                u8gPpermifSht == (uint8_t)ON; /* シフト遷移(R以外)ON */
            }
            if ( u16gPsimbrdgifVelspd <= u16s_PPERM_SHTREV_SPD5 ) /* 車速が5km以下 */
            {
                u8gPpermifShtR == (uint8_t)ON; /* シフト遷移(R)がON */
            }
        }

        if ( u8gPprtctifBrkszsts == (uint8_t)ON ) /* ブレーキが焼き付き */
        {
            u8gPpermifAcelMax = u8s_PPERM_ACEL_LIM70; /* アクセル開度70%制限 */
            u8gPpermifSpdMax  = u8s_PPERM_SPD_LIM50; /* 車速50km制限 */
        }

        if ( u8gPprtctifOvrvst == (uint8_t)ON )
        {
            u8gPpermifAcelMax = u8s_PPERM_ACEL_LIM50; /* アクセル開度50%制限 */
            u8gPpermifShtdw   = (uint8_t)OFF; /* シフトダウン許可しない */
        }

        if ( u8gPprtctifEnststs == (uint8_t)ON )
        {
            u8gPprtctifEnststs = (uint8_t)OFF;
            u8gPpermifPwrIgoff = (uint8_t)ON;
        }
    }
    else
    {
        u8gPpermifAcelMax == (uint8_t)0;
    }


}


/******************************************************************************
  * internal function                                                          
******************************************************************************/

/******************************************************************************
  * @func     vdsSampleFunc( void )                                            
  * @scope    internal                                                         
  * @brief    -                                                                
  * @param    -                                                                
  * @return   -                                                                
******************************************************************************/

/******************************************************************************
  * end of file                                                                
******************************************************************************/
