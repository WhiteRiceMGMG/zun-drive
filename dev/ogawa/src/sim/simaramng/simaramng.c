/******************************************************************************
  * @file     simaramng.c
  * @brief    sim layer cycle aggregator
  * @domain   sim
  * @date     2026/09/09
  * @(c)      2026 ocml
******************************************************************************/

/******************************************************************************
  * include
******************************************************************************/
#include "../../inc/common.h"
#include "../mvirtmachif.h" /* vdgMvirtmachifInit(), vdgMvirtmachif4msin() */

#include "../simaramngif.h"

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
  * @func     vdgSimaramngifInit( void )
  * @scope    external
  * @brief    sim layer manager init function
  * @param    -
  * @return   -
******************************************************************************/
void
vdgSimaramngifInit( void )
{
    vdgMvirtmachifInit(); /* mvirtmach.Init() also inits meng/mgearbox/mclth/mbrake */
}

/******************************************************************************
  * @func     vdgSimaramngif4msin( void )
  * @scope    external
  * @brief    sim layer manager 4msin function
  * @param    -
  * @return   -
******************************************************************************/
void
vdgSimaramngif4msin( void )
{
    vdgMvirtmachif4msin(); /* mvirtmach internally sequences clth/gearbox/meng/brake */
}

/******************************************************************************
  * @func     vdgSimaramngif4msout( void )
  * @scope    external
  * @brief    sim layer manager 4msout function
  * @param    -
  * @return   -
******************************************************************************/
void
vdgSimaramngif4msout( void )
{
}

/******************************************************************************
  * @func     vdgSimaramngif16msin( void )
  * @scope    external
  * @brief    sim layer manager 16msin function
  * @param    -
  * @return   -
******************************************************************************/
void
vdgSimaramngif16msin( void )
{
}

/******************************************************************************
  * @func     vdgSimaramngif16msout( void )
  * @scope    external
  * @brief    sim layer manager 16msout function
  * @param    -
  * @return   -
******************************************************************************/
void
vdgSimaramngif16msout( void )
{
}

/******************************************************************************
  * @func     vdgSimaramngif64msin( void )
  * @scope    external
  * @brief    sim layer manager 64msin function
  * @param    -
  * @return   -
******************************************************************************/
void
vdgSimaramngif64msin( void )
{
}

/******************************************************************************
  * @func     vdgSimaramngif64msout( void )
  * @scope    external
  * @brief    sim layer manager 64msout function
  * @param    -
  * @return   -
******************************************************************************/
void
vdgSimaramngif64msout( void )
{
}

/******************************************************************************
  * internal function
******************************************************************************/

/******************************************************************************
  * end of file
******************************************************************************/
