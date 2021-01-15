/**
 * @file    x/std.h
 * @brief   표준 라이브러리 헤더
 * @details
 * 
 * @version 0.0.1
 */

#ifndef   __NOVEMBERIZING_X__STD__H__
#define   __NOVEMBERIZING_X__STD__H__

typedef __INT8_TYPE__   xint8;          /**!< 8 bit integer type */
typedef __INT16_TYPE__  xint16;         /**!< 16 bit integer type */
typedef __INT32_TYPE__  xint32;         /**!< 32 bit integer type */
typedef __INT64_TYPE__  xint64;         /**!< 64 bit integer type */
typedef __UINT8_TYPE__  xuint8;         /**!< 8 bit unsigned integer type */
typedef __UINT16_TYPE__ xuint16;        /**!< 16 bit unsigned integer type */
typedef __UINT32_TYPE__ xuint32;        /**!< 32 bit unsigned integer type */
typedef __UINT64_TYPE__ xuint64;        /**!< 64 bit unsigned integer type */
typedef unsigned char   xbyte;          /**!< byte type */
typedef char            xchar;          /**!< character type */

/** MACROS */

#define xsuccess        (0)             /**!< sucess */
#define xfail           (-1)            /**!< fail */
#define xinvalid        (-1)            /**!< invalid */
#define xtrue           (1)             /**!< true */
#define xfalse          (0)             /**!< false */
#define xnil            ((void *)(0))   /**!< null */

/** FUCTION POINTER */

typedef void * (*xdestructor)(void *);

/** PRIMITIVE TYPE */

union xval;

typedef union xval xval;                /**!< primitive type */

union xval
{
    xbyte   u;                          /**!< byte value */
    xchar   c;                          /**!< character value */
    xint32  i32;                        /**!< 32 bit integer value */
    xint64  i64;                        /**!< 64 bit integer value */
    xuint32 u32;                        /**!< 32 bit unsigned integer value */
    xuint64 u64;                        /**!< 64 bit unsigned integer value */
    void *  ptr;                        /**!< pointer address */
};

/**
 * @def     xvalinit(v)
 * @brief   프리미티브 변수 초기화 함수
 * 
 * @param   v | in | 변수 |
 * 
 * @return  | xval | 생성된 변수 |
 */
#define xvalinit(v) (xval){ .u64 = v }

/**
 * @def     xobj_mask_allocated
 * @brief   객체의 동적할당 여부 비트 마스크
 */
#define xobj_mask_allocated     0x80000000U

/**
 * @def     xobj_mask_types
 * @brief   객체의 타입 마스크
 */
#define xobj_mask_types         0x0000FFFFU

/***/


#endif // __NOVEMBERIZING_X__STD__H__
