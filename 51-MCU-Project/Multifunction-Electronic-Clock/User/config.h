#ifndef CONFIG_H__
#define CONFIG_H__

/************************************* ����ͷ�ļ� ***************************************/
/******************** C���Ա�׼�� **********************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <intrins.h>
#include <reg52.h>

/********************** ���Ͷ��� ************************/

#ifndef u8
typedef unsigned char u8;
#endif

#ifndef s8
typedef signed char   s8;
#endif

#ifndef u16
typedef unsigned int u16;
#endif

#ifndef s16
typedef signed int   s16;
#endif

#ifndef u32
typedef unsigned long   u32;
#endif

#ifndef s32
typedef signed long     s32;
#endif


#ifndef f32
typedef float f32;
#endif

#ifndef f64
typedef double f64;
#endif

#ifndef bool
typedef enum
{
	false = 0,
	true = !false
}bool;
#endif

#ifndef null
#define null 0
#endif

#endif
