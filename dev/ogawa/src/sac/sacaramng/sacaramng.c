/******************************************************************************
  * @file     sacaramngif.h                                                    
  * @brief    sacaramng                                                        
  * @domain   sensor-actuator                                                  
  * @date     2026/07/20                                                       
  * @(c)      2026 ocml                                                        
******************************************************************************/
/******************************************************************************
  * include
******************************************************************************/
#include "../../inc/common.h"   /* uint8_t等の型定義。以下のヘッダが型定義前提のため必須 */

#include "../acfmstsif.h"       /* vdgAcfmstsifInit()    */
#include "../agearcfmif.h"      /* vdgAgearcfmifInit()   */
                                /* vdgAgearcfmif64msout()*/
#include "../arpmcfmif.h"       /* vdgArpmcfmifInit()    */
                                /* vdgArpmcfmif16msout() */
#include "../avehstsif.h"       /* vdgAvehstsifInit()    */
                                /* vdgAvehstsif64msout() */
#include "../avelif.h"          /* vdgAvelifInit()       */
                                /* vdgAvelif16msout()    */
#include "../sacelcrtif.h"      /* vdgSacelcrtifInit()   */
                                /* vdgSacelcrtif4msin()  */
#include "../sbrkcrtif.h"       /* vdgSbrkcrtifInit()    */
                                /* vdgSbrkcrtif4msin()   */
#include "../sclthcrtif.h"      /* vdgSclthcrtifInit()   */
                                /* vdgSclthcrtif16msin() */
#include "../sgearcrtif.h"      /* vdgSgearcrtifInit()   */
                                /* vdgSgearcrtif64msin() */
#include "../sigswcrtif.h"      /* vdgSigswcrtifInit()   */
                                /* vdgSigswcrtif64msin() */



#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
#include "../../../debug/log/print_log.h"
#endif

#include "../sacaramngif.h"

/******************************************************************************
  * external public variables contains macros                                  
******************************************************************************/

/******************************************************************************
  * internal public variables contains macros                                  
******************************************************************************/

/******************************************************************************
  * external function                                                          
******************************************************************************/

/******************************************************************************
  * @func     vdgSacaramngifInit( void )                                       
  * @scope    external                                                         
  * @brief    -                                                                
  * @param    -                                                                
  * @return   -                                                                
******************************************************************************/
void
vdgSacaramngifInit( void )
{
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogPrint( "start vdgSacaramngifInit() " );
#endif
    vdgSacelcrtifInit();
    vdgSbrkcrtifInit();
    vdgSclthcrtifInit();
    vdgSigswcrtifInit();
    vdgSgearcrtifInit();
}

/******************************************************************************
  * @func     vdgSacaramngif4msin( void )                                      
  * @scope    external                                                         
  * @brief    -                                                                
  * @param    -                                                                
  * @return   -                                                                
******************************************************************************/
void
vdgSacaramngif4msin( void )
{
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogPrint( "start vdgSacaramngif4msin() " );
#endif
    vdgSacelcrtif4msin();
    vdgSbrkcrtif4msin();
}

/******************************************************************************
  * @func     vdgSacaramngif4msout( void )                                     
  * @scope    external                                                         
  * @brief    -                                                                
  * @param    -                                                                
  * @return   -                                                                
******************************************************************************/
void
vdgSacaramngif4msout( void )
{
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogPrint( "start vdgSacaramngif4msout() " );
#endif
}

/******************************************************************************
  * @func     vdgSacaramngif16msin( void )                                     
  * @scope    external                                                         
  * @brief    -                                                                
  * @param    -                                                                
  * @return   -                                                                
******************************************************************************/
void
vdgSacaramngif16msin( void )
{
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogPrint( "start vdgSacaramngif16msin() " );
#endif
    vdgSclthcrtif16msin();
}

/******************************************************************************
  * @func     vdgSacaramngif16msout( void )                                    
  * @scope    external                                                         
  * @brief    -                                                                
  * @param    -                                                                
  * @return   -                                                                
******************************************************************************/
void
vdgSacaramngif16msout( void )
{
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogPrint( "start vdgSacaramngif16msout() " );
#endif

}

/******************************************************************************
  * @func     vdgSacaramngif64msin( void )                                     
  * @scope    external                                                         
  * @brief    -                                                                
  * @param    -                                                                
  * @return   -                                                                
******************************************************************************/
void
vdgSacaramngif64msin( void )
{
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogPrint( "start vdgSacaramngif64msin() " );
#endif
    vdgSgearcrtif64msin();
    vdgSigswcrtif64msin();
}

/******************************************************************************
  * @func     vdgSacaramngif64msout( void )                                    
  * @scope    external                                                         
  * @brief    -                                                                
  * @param    -                                                                
  * @return   -                                                                
******************************************************************************/
void
vdgSacaramngif64msout( void )
{
#if ( PRINT_LOG_SETTING_CONF == PRINT_LOG_SETTING_VALID )
    vdgLogPrint( "start vdgSacaramngif64msout() " );
#endif
}

/******************************************************************************
  * internal function                                                          
******************************************************************************/

/******************************************************************************
  * @func     vdgSampleFunction( void )                                        
  * @scope    internal                                                         
  * @brief    sample function                                                  
  * @param    -                                                                
  * @return   -                                                                
******************************************************************************/

/******************************************************************************
  * end of file                                                                
******************************************************************************/
