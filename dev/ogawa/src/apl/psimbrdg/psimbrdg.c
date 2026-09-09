/****************************************************************/
/*  * @file     psimbrdgif.c                                    */
/*  * @brief    -                                               */
/*  * @domain   -                                               */
/*  * @date     2026/07/26                                      */
/*  * @(c)      2026 ocml                                       */
/****************************************************************/

/****************************************************************/
/*  * include                                                   */
/****************************************************************/
#include "../../inc/common.h"
#include "../psysctlif.h"      /* s8gPsysctlGearpos,u8gPsysctlAcelpct,   */
                               /* u8gPsysctlBrkpct,u8gPsysctlClthpct,   */
                               /* u8gPsysctlIgswsts                     */
#include "../../sim/mvirtmachif.h" /* u16gMvirtmachifVelspd             */
#include "../../sim/mengif.h"      /* u16gMengifRpm                     */

#include "../psimbrdgif.h"

/****************************************************************/
/*  * external public variables contains macros                 */
/****************************************************************/
uint8_t  u8gPsimbrdgifAclthlpc;
uint8_t  u8gPsimbrdgifBrkpdlpct;
uint8_t  u8gPsimbrdgifClthpdlpct;
int8_t   s8gPsimbrdgifGearpos;
uint16_t u16gPsimbrdgifVelspd;
uint16_t u16gPsimbrdgifRpmval;
uint8_t  u8gPsimbrdigIgswsts;

/****************************************************************/
/*  * internal public variables contains macros                 */
/****************************************************************/

/****************************************************************/
/*  * external function                                         */
/****************************************************************/

/****************************************************************/
/*  * @func     vdgPsimbrdgifInit( void )                       */
/*  * @scope    external                                        */
/*  * @brief    apl<->sim bridge init function                  */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgPsimbrdgifInit( void )
{
    u8gPsimbrdgifAclthlpc   = (uint8_t)0;
    u8gPsimbrdgifBrkpdlpct  = (uint8_t)0;
    u8gPsimbrdgifClthpdlpct = (uint8_t)0;
    s8gPsimbrdgifGearpos    = (int8_t)0;
    u16gPsimbrdgifVelspd    = (uint16_t)0;
    u16gPsimbrdgifRpmval    = (uint16_t)0;
    u8gPsimbrdigIgswsts     = (uint8_t)OFF;
}

/****************************************************************/
/*  * @func     vdgPsimbrdgif4msin( void )                      */
/*  * @scope    external                                        */
/*  * @brief    apl->sim direction: publish psysctl's finalized  */
/*  *           output as sim's input, before sim runs this tick*/
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgPsimbrdgif4msin( void )
{
    u8gPsimbrdgifAclthlpc   = u8gPsysctlAcelpct;
    u8gPsimbrdgifBrkpdlpct  = u8gPsysctlBrkpct;
    u8gPsimbrdgifClthpdlpct = u8gPsysctlClthpct;
    s8gPsimbrdgifGearpos    = s8gPsysctlGearpos;
    u8gPsimbrdigIgswsts     = u8gPsysctlIgswsts;
}

/****************************************************************/
/*  * @func     vdgPsimbrdgif4msout( void )                     */
/*  * @scope    external                                        */
/*  * @brief    sim->apl direction: publish sim's freshly-       */
/*  *           computed speed/rpm, after sim ran this same tick*/
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgPsimbrdgif4msout( void )
{
    u16gPsimbrdgifVelspd = u16gMvirtmachifVelspd;
    u16gPsimbrdgifRpmval = u16gMengifRpm;
}

/****************************************************************/
/*  * internal function                                         */
/****************************************************************/

/****************************************************************/
/*  * end of file                                               */
/****************************************************************/
