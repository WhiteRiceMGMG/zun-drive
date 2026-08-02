/******************************************************************************
  * @file     bcyclemng.c                                                      
  * @brief    cycle manager                                                    
  * @domain   bsw                                                              
  * @date     2026/07/20                                                       
  * @(c)      2026 ocml                                                        
******************************************************************************/

/******************************************************************************
  * include                                                                    
******************************************************************************/

#include "../../sac/sacaramngif.h"  /* vdgSacaramngifInit()    */
                                    /* vdgSacaramngif4msin()   */
                                    /* vdgSacaramngif4msout()  */
                                    /* vdgSacaramngif16msin()  */
                                    /* vdgSacaramngif16msout() */
                                    /* vdgSacaramngif64msin()  */
                                    /* vdgSacaramngif64msout() */

#include "../../apl/aplaramngif.h"  /* vdgAplaramngifInit()    */
                                    /* vdgAplaramngif4msin()   */
                                    /* vdgAplaramngif4msout()  */
                                    /* vdgAplaramngif16msin()  */
                                    /* vdgAplaramngif16msout() */
                                    /* vdgAplaramngif64msin()  */
                                    /* vdgAplaramngif64msout() */

#include "../../sim/simaramngif.h"  /* vdgSimaramngifInit()    */
                                    /* vdgSimaramngif4msin()   */
                                    /* vdgSimaramngif4msout()  */
                                    /* vdgSimrramngif16msin()  */
                                    /* vdgSimaramngif16msout() */
                                    /* vdgSimaramngif64msin()  */
                                    /* vdgSimaramngif64msout() */

#if ( PRINT_LOGSETTING_CONF == PRINT_LOGSETTING_VALID )
#include "../../../debug/log/print_log.h"
#endif

#include "../bcyclemngif.h"         /* self header */

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
  * @func     vdgBcyclemngifInit( void )                                       
  * @scope    external                                                         
  * @brief    pwon cycle manager                                               
  * @param    -                                                                
  * @return   -                                                                
******************************************************************************/
void
vdgBcyclemngifInit( void )
{
#if ( PRINT_LOGSETTING_CONF == PRINT_LOGSETTING_VALID )
    vdgLogPrint( "---EXECUTE vdgBcyclemngifInit()---" );
#endif
    /* ▼▼▼ INSERT BSW PWON FUNCTION ▼▼▼ */

    /* ▲▲▲ INSERT BSW PWON FUNCTION ▲▲▲ */

    vdgSacaramngifInit(); /* sac layer manager pwon function */
    vdgAplaramngifInit(); /* apl layer manager pwon function */
    vdgSimaramngifInit(); /* sim layer manager pwon function */
}

/******************************************************************************
  * @func     vdgBcyclemngif4msin( void )                                      
  * @scope    external                                                         
  * @brief    4msin cycle manager                                              
  * @param    -                                                                
  * @return   -                                                                
******************************************************************************/
void
vdgBcyclemngif4msin( void )
{
#if ( PRINT_LOGSETTING_CONF == PRINT_LOGSETTING_VALID )
    vdgLogPrint( "---EXECUTE vdgBcyclemngif4msin()---" );
#endif


    vdgSacaramngif4msin(); /* sac layer manager 4msin function */
    vdgAplaramngif4msin(); /* apl layer manager 4msin function */
    vdgSimaramngif4msin(); /* sim layer manager 4msin function */
}

/******************************************************************************
  * @func     vdgBcyclemngif4msout( void )                                     
  * @scope    external                                                         
  * @brief    4msout cycle manager                                             
  * @param    -                                                                
  * @return   -                                                                
******************************************************************************/
void
vdgBcyclemngif4msout( void )
{
#if ( PRINT_LOGSETTING_CONF == PRINT_LOGSETTING_VALID )
    vdgLogPrint( "---execute vdgBcyclemngif4msout()---" );
#endif
    vdgSacaramngif4msout(); /* sac layer manager 4msout function */
    vdgAplaramngif4msout(); /* apl layer manager 4msout function */
    vdgSimaramngif4msout(); /* sim layer manager 4msout function */
}

/******************************************************************************
  * @func     vdgBcyclemngif16msin( void )                                     
  * @scope    external                                                         
  * @brief    16msin cycle manager                                             
  * @param    -                                                                
  * @return   -                                                                
******************************************************************************/
void
vdgBcyclemngif16msin( void )
{
#if ( PRINT_LOGSETTING_CONF == PRINT_LOGSETTING_VALID )
    vdgLogPrint( "---EXECUTE vdgBcyclemngif16msin()---" );
#endif
    vdgSacaramngif16msin(); /* sac layer manager 16msin function */
    vdgAplaramngif16msin(); /* apl layer manager 16msin function */
    vdgSimaramngif16msin(); /* sim layer manager 16msin function */
}

/******************************************************************************
  * @func     vdgBcyclemngif16msout( void )                                    
  * @scope    external                                                         
  * @brief    16msout cycle manager                                            
  * @param    -                                                                
  * @return   -                                                                
******************************************************************************/
void
vdgBcyclemngif16msout( void )
{
#if ( PRINT_LOGSETTING_CONF == PRINT_LOGSETTING_VALID )
    vdgLogPrint( "---EXECUTE vdgBcyclemngif16msout()---" );
#endif
    vdgSacaramngif16msout(); /* sac layer manager 16msout function */
    vdgAplaramngif16msout(); /* apl layer manager 16msout function */
    vdgSimaramngif16msout(); /* sim layer manager 16msout function */
}

/******************************************************************************
  * @func     vdgBcyclemngif64msin( void )                                     
  * @scope    external                                                         
  * @brief    64msin cycle manager                                             
  * @param    -                                                                
  * @return   -                                                                
******************************************************************************/
void
vdgBcyclemngif64msin( void )
{
#if ( PRINT_LOGSETTING_CONF == PRINT_LOGSETTING_VALID )
    vdgLogPrint( "---EXECUTE vdgBcyclemngif64msin()---" );
#endif
    vdgSacaramngif64msin(); /* sac layer manager 64msin function */
    vdgAplaramngif64msin(); /* apl layer manager 64msin function */
    vdgSimaramngif64msin(); /* sim layer manager 64msin function */
}

/******************************************************************************
  * @func     vdgBcyclemngif64msout( void )                                    
  * @scope    external                                                         
  * @brief    64msout cycle manager                                            
  * @param    -                                                                
  * @return   -                                                                
******************************************************************************/
void
vdgBcyclemngif64msout( void )
{
#if ( PRINT_LOGSETTING_CONF == PRINT_LOGSETTING_VALID )
    vdgLogPrint( "---EXECUTE vdgBcyclemngif64msout()---" );
#endif
    vdgSacaramngif64msout(); /* sac layer manager 64msout function */
    vdgAplaramngif64msout(); /* apl layer manager 64msout function */
    vdgSimaramngif64msout(); /* sim layer manager 64msout function */
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
