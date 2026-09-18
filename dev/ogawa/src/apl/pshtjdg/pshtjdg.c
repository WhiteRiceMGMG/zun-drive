/****************************************************************/
/*  * @file     pshtjdg.c                                       */
/*  * @brief    sht jdg                                         */
/*  * @domain   apl                                             */
/*  * @date     2026/09/18                                      */
/*  * @(c)      2026 ocml                                       */
/****************************************************************/

/****************************************************************/
/*  * include                                                   */
/****************************************************************/
#include "../../inc/common.h" /* 共通ライブラリ */

#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
#include "../../../debug/log/print_log.h"
#endif

/****************************************************************/
/*  * external public variables contains macros                 */
/****************************************************************/

/****************************************************************/
/*  * internal public variables contains macros                 */
/****************************************************************/
static s_u8PshtjdgSht_o; /* シフト前回値 */


/****************************************************************/
/*  * external function                                         */
/****************************************************************/


/****************************************************************/
/*  * @func     g_VdPshtjdgifInit( void )                       */
/*  * @scope    external                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
g_VdPshtjdgifInit( void )
{
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogPrint( "xxxx" );
#endif


    初期化


#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogArgPrint( "xxxx = %d", (uint32_t)xxxx );
#endif

}

/****************************************************************/
/*  * @func     g_VdPshtjdgif16ms( void )                       */
/*  * @scope    external                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
g_VdPshtjdgif16ms( void )
{
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogPrint( "xxxx" );
#endif


    内部関数(要求調停)を呼ぶ
    内部関数(遷移調停)を呼ぶ


#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogArgPrint( "xxxx = %d", (uint32_t)xxxx );
#endif

}


/****************************************************************/
/*  * internal function                                         */
/****************************************************************/

/****************************************************************/
/*  * @func     s_VdPshtjdgReq( void )                          */
/*  * @scope    internal                                        */
/*  * @brief    -                                               */
/*  * @param    -                                               */
/*  * @return   -                                               */
/****************************************************************/
void
s_VdPshtjdgReq( void )
{
    uint8 t_u8ShtjdgReq; /* シフト遷移要求フラグ */
    sint8 t_s8Gear; /* ギア */
    sint8 t_s8Gear_o; /* ギア前回値 */


    t_u8ShtjdgReq = g_u8ShtjdgifChgreq; /* シフト遷移要求フラグをラッチ */
    t_s8Gear = g_s8PioifGear; /* 最新ギア(生値)を取得する． */
    t_s8Gear_o = s_s8ShtjdgGear_o /* ギア前回値を取得する */
    
    t_u8ShtjdgReq  = なし
    if ( t_s8Gear > t_s8Gear_o )
    {
        t_u8ShtjdgReq = シフトアップ要求フラグ
    }
    if (シフト < 前回値)
    {
        t_u8ShtjdgReq = シフトダウン要求フラグ
    }
    if ( シフト = リバース ) 
    {
        t_u8ShtjdgReq = シフトリバース要求フラグ
    }
    
    s_s8ShtjdgGear_o = t_s8Gear;
    g_u8ShtjdgifChgreq = t_u8ShtjdgReq; /* シフト遷移要求フラグ更新 */
}

/****************************************************************/
/*  * end of file                                               */
/****************************************************************/
