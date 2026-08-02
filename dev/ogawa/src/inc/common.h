/* (C) 2026 OCML */
/*============================================================================*/
/* FILE     | common.h                                                        */
/* DOMAIN   | -                                                               */
/* MODULE   | -                                                               */
/* DETAILS  | common header                                                   */
/* VER      | 26.06.27 make new                                               */
/*          |                                                                 */
/*          |                                                                 */
/*============================================================================*/
#ifndef COMMON_H
#define COMMON_H

/*----------------------------------------------------------------------------*/
/* INCLUDE                                                                    */
/*----------------------------------------------------------------------------*/
#include "../conf/conf.h" /* MACHINE_TYPE(with MACHINE LIST)                  */

/*----------------------------------------------------------------------------*/
/* TYPEDEF                                                                    */
/*----------------------------------------------------------------------------*/
#if ( MACHINE_TYPE == MACHINE_TYPE_IOS )

typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned long long  uint64_t;

typedef signed char      int8_t;
typedef signed short     int16_t;
typedef signed int       int32_t;
typedef signed long long int64_t;


#elif ( MACHINE_TYPE == MACHINE_TYPE_ANDROID )
/* TO BE DETERMINED */

#elif ( MACHINE_TYPE == MACHINE_TYPE_MACOS )
/* TO BE DETERMINED */

#elif ( MACHINE_TYPE == MACHINE_TYPE_RASP_PROTO )
/* TO BE DETERMINED */

#elif ( MACHINE_TYPE == MACHINE_TYPE_RASP_VER1_0 )
/* TO BE DETERMINED */

#elif ( MACHINE_TYPE == MACHINE_TYPE_RASP_VER2_0 )
/* TO BE DETERMINED */

#else
 #error "NOT DEFINED MACHINE_TYPE"
#endif

typedef struct
{
    uint8_t b0 : 1;
    uint8_t b1 : 1;
    uint8_t b2 : 1;
    uint8_t b3 : 1;
    uint8_t b4 : 1;
    uint8_t b5 : 1;
    uint8_t b6 : 1;
    uint8_t b7 : 1;
} stflag8;

typedef struct
{
    uint16_t b0  : 1;
    uint16_t b1  : 1;
    uint16_t b2  : 1;
    uint16_t b3  : 1;
    uint16_t b4  : 1;
    uint16_t b5  : 1;
    uint16_t b6  : 1;
    uint16_t b7  : 1;
    uint16_t b8  : 1;
    uint16_t b9  : 1;
    uint16_t b10 : 1;
    uint16_t b11 : 1;
    uint16_t b12 : 1;
    uint16_t b13 : 1;
    uint16_t b14 : 1;
    uint16_t b15 : 1;
} stflag16;

/*----------------------------------------------------------------------------*/
/* MACROS                                                                     */
/*----------------------------------------------------------------------------*/
#define ON  ((uint8_t)1)
#define OFF ((uint8_t)0)

#define HI  ((uint8_t)1)
#define LO  ((uint8_t)0)

#define TRUE  ((uint8_t)1)
#define FALSE ((uint8_t)0)

#define u8g_MAX ((uint8_t)0xff)
#define u16g_MAX ((uint16_t)0xffff)
#define u32g_MAX ((uint32_t)0xffffffff)
#define u8g_MIN ((uint8_t)0x00)
#define u16g_MIN ((uint16_t)0x0000)
#define u32g_MIN ((uint32_t)0x00000000)

#define s8g_MAX ((int8_t)0x7f)
#define s16g_MAX ((int16_t)0x7ffff)
#define s32g_MAX ((int32_t)0x7fffffff)
#define s8g_MIN ((int8_t)0x80)
#define s16g_MIN ((int16_t)0x8000)
#define s32g_MIN ((int32_t)0x80000000)


#endif
/*----------------------------------------------------------------------------*/
/* EOF                                                                        */
/*----------------------------------------------------------------------------*/
