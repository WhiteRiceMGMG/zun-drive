/* SACからの入力は定義済．SIM層からの車速と加速度，回転数は */
/* 未作成のためpio未対応． */

/****************************************************************/
/*  * @file     pioif.c                                         */
/*  * @brief    apl input output interface                      */
/*  * @domain   apllication                                     */
/*  * @date     2026/08/27                                      */
/*  * @(c)      2026 ocml                                       */
/****************************************************************/

/****************************************************************/
/*  * include                                                   */
/****************************************************************/
#include "../../inc/common.h"

#include "../../sac/sacelcrtif.h" /* u8gSacelcrtifthlpct */
#include "../../sac/sclthcrtif.h" /* u8gSclthcrtifPdlpct */
#include "../../sac/sbrkcrtif.h"  /* u8gSbrkcrtifPdlpct  */
#include "../../sac/sigswcrtif.h" /* u8gSigswifSts       */
#include "../../sac/sgearcrtif.h" /* s8gSgearcrtifPos    */

/* 以下，今後SIMからの車速のインクルードを追加する． */


#include "../pprtctif.h" /* u8gPprtctifOvrvsts   */
                         /* u8gPprtctifClthszsts */
                         /* u8gPprtctifBrkszsts  */
                         /* u8gPprtctifEnststs   */

#include "../psimbrdif.h" /* u16gPsimbrdgifVelspd  */

#include "../ppermif.h"

/****************************************************************/
/*  * external public variables contains macros                 */
/****************************************************************/
uint8_t u8gPioifIgsw;
uint8_t u8gPioifAcel;
uint8_t u8gPioifBrk;
uint8_t u8gPioifClth;
int8_t  s8gPioifGear;
uint8_t u8gPioifSpd;
uint8_T u8gPioifRpm;

/****************************************************************/
/*  * internal public variables contains macros                 */
/****************************************************************/

/****************************************************************/
/*  * external function                                         */
/****************************************************************/

/****************************************************************/
/*  * @func     vdgPpermifInit( void )                          */
/*  * @scope    external                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgPioifInit( void )
{

	u8gPioifIgsw = (uint8_t)OFF;
	u8gPioifAcel = (uint8_t)0;
	u8gPioifBrk  = (uint8_t)0;
	u8gPioifClth = (uint8_t)0;
	s8gPioifGear = (int8_t)0;;
	u8gPioifSpd  = (uint8_t)0;
	u8gPioifRpm  = (uint8_t)0;
}

/****************************************************************/
/*  * @func     vdgPpermif4ms( void )                           */
/*  * @scope    external                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgPioif4ms( void )
{
    u8gPioifAcel = u8gSacelcrtifthlpct;
    u8gPioifBrk = u8gSbrkcrtifPdlpct;


}

/****************************************************************/
/*  * @func     vdgPpermif16ms( void )                          */
/*  * @scope    external                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgPioif16ms( void )
{
    u8gPioifClth = vdgSclthcrtif16msin;


}

/****************************************************************/
/*  * @func     vdgPpermif64ms( void )                          */
/*  * @scope    external                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgPioif64ms( void )
{
    u8gPioifIgsw = u8gSigswifSts;
    s8gPioifGear = s8gSgearcrtifPos;
}


/****************************************************************/
/*  * internal function                                         */
/****************************************************************/

/****************************************************************/
/*  * @func     vdsSampleFunc( void )                           */
/*  * @scope    internal                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/

/****************************************************************/
/*  * end of file                                               */
/****************************************************************/
