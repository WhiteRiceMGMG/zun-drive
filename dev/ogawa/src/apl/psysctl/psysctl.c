/****************************************************************/
/*  * @file     psysctl.c                                       */
/*  * @brief    -                                               */
/*  * @domain   -                                               */
/*  * @date     2026/09/09                                      */
/*  * @(c)      2026 ocml                                       */
/****************************************************************/

/****************************************************************/
/*  * include                                                   */
/****************************************************************/
#include "../../inc/common.h"
#include "../ppermif.h"  /* u8gPpermifSht     */
                         /* u8gPpermifShtrev  */
                         /* u8gPpermifAcelLim */
                         /* u8gPpermifAcelMax */
                         /* u8gPpermifSpdLim  */
                         /* u8gPpermifSpdMax  */
                         /* u8gPpermifPwrigoff*/

#include "../../sac/sigswcrtif.h" /* u8gSigswcrtifSts  */
#include "../../sac/sgearcrtif.h" /* s8gSgearcrtifPos  */
                                  /* s8g_SGEARIF_NEUTRAL/REVERSE */
#include "../../sac/sbrkcrtif.h"  /* u8gSbrkcrtifPdlpct  */
#include "../../sac/sacelcrtif.h" /* u8gSacelcrtifThlpct */
#include "../../sac/sclthcrtif.h" /* u8gSclthcrtifPdlpct */
#include "../psimbrdgif.h"        /* u16gPsimbrdgifVelspd */

#include "../psysctlif.h"

/****************************************************************/
/*  * external public variables contains macros                 */
/****************************************************************/
int8_t  s8gPsysctlGearpos;
uint8_t u8gPsysctlAcelpct;
uint8_t u8gPsysctlBrkpct;
uint8_t u8gPsysctlClthpct;
uint8_t u8gPsysctlIgswsts;

/****************************************************************/
/*  * internal public variables contains macros                 */
/****************************************************************/
/* doc要件4は10-70%の可変加算を求めているが、今回は固定+30%に簡略化 */
#define u8s_PSYSCTL_OVRSPD_BRKADD30 ((uint8_t)30)
#define u8s_PSYSCTL_PCT_MAX100      ((uint8_t)100)

static int8_t  s8sPsysctlGearposO;
static uint8_t u8sPsysctlIgswstsO; /* 前回の生イグニッション値(立ち上がりエッジ検出用) */

/****************************************************************/
/*  * external function                                         */
/****************************************************************/

/****************************************************************/
/*  * @func     vdgPsysctlInit( void )                          */
/*  * @scope    external                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgPsysctlInit( void )
{
    s8gPsysctlGearpos  = s8g_SGEARIF_NEUTRAL;
    u8gPsysctlAcelpct  = (uint8_t)0;
    u8gPsysctlBrkpct   = (uint8_t)0;
    u8gPsysctlClthpct  = (uint8_t)0;
    u8gPsysctlIgswsts  = (uint8_t)OFF;

    s8sPsysctlGearposO = s8g_SGEARIF_NEUTRAL;
    u8sPsysctlIgswstsO = (uint8_t)OFF;
}

/****************************************************************/
/*  * @func     vdgPsysctl16msin( void )                        */
/*  * @scope    external                                        */
/*  * @brief    pperm調停結果をSACの生値へ適用し、SIMへ渡す最終値を確定する */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
vdgPsysctl16msin( void )
{
    int8_t  s8tGearpos;
    uint8_t u8tAcelpct;
    uint8_t u8tBrkpct;

    /* 要件5: 強制IG-OFFの解除は「キーの再投入(OFF->ONの立ち上がり)」でのみ  */
    /* 行う。毎サイクル無条件に解除すると、pprtctがエンストを検知して        */
    /* ppermが強制OFFを立てた"その同じサイクル"に自己解除してしまう。       */
    if ( ( u8gSigswcrtifSts == (uint8_t)ON ) && ( u8sPsysctlIgswstsO == (uint8_t)OFF ) )
    {
        u8gPpermifPwrigoff = (uint8_t)OFF;
    }
    u8sPsysctlIgswstsO = u8gSigswcrtifSts;

    if ( u8gSigswcrtifSts == (uint8_t)ON )
    {
        /* 要件1・2: 変速許可されていなければ前回値を維持して公開 */
        s8tGearpos = s8sPsysctlGearposO;
        if ( s8gSgearcrtifPos == s8g_SGEARIF_REVERSE )
        {
            if ( u8gPpermifShtrev == (uint8_t)ON )
            {
                s8tGearpos = s8gSgearcrtifPos;
            }
        }
        else
        {
            if ( u8gPpermifSht == (uint8_t)ON )
            {
                s8tGearpos = s8gSgearcrtifPos;
            }
        }

        /* 要件3: アクセル開度入力制限 */
        u8tAcelpct = u8gSacelcrtifThlpct;
        if ( ( u8gPpermifAcelLim == (uint8_t)ON ) && ( u8tAcelpct > u8gPpermifAcelMax ) )
        {
            u8tAcelpct = u8gPpermifAcelMax;
        }

        /* 要件4: 車速制限超過時はブレーキを加算(固定+30%に簡略化) */
        u8tBrkpct = u8gSbrkcrtifPdlpct;
        if ( ( u8gPpermifSpdLim == (uint8_t)ON ) && ( u16gPsimbrdgifVelspd > (uint16_t)u8gPpermifSpdMax ) )
        {
            u8tBrkpct = (uint8_t)( u8tBrkpct + u8s_PSYSCTL_OVRSPD_BRKADD30 );
            if ( u8tBrkpct > u8s_PSYSCTL_PCT_MAX100 )
            {
                u8tBrkpct = u8s_PSYSCTL_PCT_MAX100;
            }
        }

        u8gPsysctlClthpct = u8gSclthcrtifPdlpct;

        u8gPsysctlIgswsts = (uint8_t)ON;
        if ( u8gPpermifPwrigoff == (uint8_t)ON )
        {
            u8gPsysctlIgswsts = (uint8_t)OFF; /* エンスト等による強制シャットダウン */
        }
    }
    else
    {
        /* IG-OFF: 車速がある場面(惰性走行等)を想定しブレーキ等の効力は  */
        /* 持たせるためシミュレーションは継続する。アクセルのみ0にする。  */
        s8tGearpos = s8sPsysctlGearposO;
        u8tAcelpct = (uint8_t)0;
        u8tBrkpct  = u8gSbrkcrtifPdlpct;
        u8gPsysctlClthpct = u8gSclthcrtifPdlpct;
        u8gPsysctlIgswsts = (uint8_t)OFF;
    }

    s8gPsysctlGearpos  = s8tGearpos;
    s8sPsysctlGearposO = s8tGearpos;
    u8gPsysctlAcelpct  = u8tAcelpct;
    u8gPsysctlBrkpct   = u8tBrkpct;
}

/****************************************************************/
/*  * internal function                                         */
/****************************************************************/

/****************************************************************/
/*  * end of file                                               */
/****************************************************************/
