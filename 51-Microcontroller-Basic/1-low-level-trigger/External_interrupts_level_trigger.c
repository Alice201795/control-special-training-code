/*
 *****************************************************************************************
 *	实 验 名 称:外部中断0的应用
 *  实 验 平 台：清翔电子 QX-MCS51开发板
 *	创 建 作 者：miki
 *  功 能 说 明：1.测试外部中断低电平触发方式的效果,主函数里数码管循环显示0-9，
 *				 当外部中断0低电平触发时（P3^2），进入中断服务函数让LED以500ms闪烁
 *				 2.测试外部中断下降沿触发方式的效果,主函数里数码管循环显示0-9，
 *				 当外部中断1下降沿触发时（P3^3），进入中断服务函数让蜂鸣器以500ms发声
 *  github 地 址：
 *	创 建 日 期：2017-11-14
 *****************************************************************************************
 */

/************************************* 包含头文件 ***************************************/
#include <reg52.h>

/**************************************** 宏定义 *****************************************/
#define uint unsigned int 
#define uchar unsigned char

//typedef unsigned int uint;
//typedef unsigned char uchar;

/*************************************** IO口定义 ****************************************/
sbit DULA_IO = P2^6;
sbit WELA_IO = P2^7;
sbit BEEP_IO = P2^3;	// 低电平驱动

/************************************* 全局变量定义 **************************************/
uchar code GlobalDisplayTable[] = 
	{0x3f,0x06,0x5b,0x4f,0x66,
	 0x6d,0x7d,0x07,0x7f,0x6f};	/* 段选，选择要显示的数字 */

/*************************************** 函数声明 ****************************************/
void delayMs(uint xms);
void externalInterrupt0Init(void);
void externalInterrupt1Init(void);
/*
 *****************************************************************************************
 * 函数名称：main
 * 函数功能：主函数，整个程序入口
 * 输入参数：无
 * 输出参数：无
 * 其他说明：无
 ******************************************************************************************
 */
void main(void)
{
	uchar num;
    externalInterrupt0Init();
	externalInterrupt1Init();

    while (1)
    {
        for (num=0;num<10;num++)
        {
	      	DULA_IO = 1;
			P0 = GlobalDisplayTable[num];
			DULA_IO = 0;
	
			P0 = 0xff;
			WELA_IO = 1;
	
			P0 = 0x00;
			WELA_IO = 0;

			P1 = 0xff;

			delayMs(1000);
        }
    }
}

/*
 *****************************************************************************************
 * 函数名称：externalInterrupt0Handler
 * 函数功能：外部中断0中断服务函数
 * 输入参数：无
 * 输出参数：无
 * 其他说明：无
 ******************************************************************************************
 */
void externalInterrupt0Handler(void) interrupt 0
{
    P1 = 0xff;
    delayMs(500);
    P1 = 0x00; 
}

/*
 *****************************************************************************************
 * 函数名称：externalInterrupt0Handler
 * 函数功能：外部中断1中断服务函数
 * 输入参数：无
 * 输出参数：无
 * 其他说明：无
 ******************************************************************************************
 */
void externalInterrupt1Handler(void) interrupt 2
{
    BEEP_IO = 0;
    delayMs(500);
    BEEP_IO = 1;
    delayMs(500); 
}

/*
 *****************************************************************************************
 * 函数名称：delayMs
 * 函数功能：实现毫秒级的延时
 * 输入参数：xms：需要延时时间
 * 输出参数：无
 * 其他说明：无
 ******************************************************************************************
 */
void delayMs(uint xms)
{
    uint x,y;
    for (x=xms;x>0;x--)
        for (y=114;y>0;y--);
}

/*
 *****************************************************************************************
 * 函数名称：externalInterrupt0Init
 * 函数功能：外部中断0中断初始化
 * 输入参数：无
 * 输出参数：无
 * 其他说明：无
 ******************************************************************************************
 */
void externalInterrupt0Init(void)
{
    EX0 = 1;   // 开启外部中断 0 ,P3.2选通
    IT0 = 0;   // 设置成电平触发（低电平）
    EA = 1;    // 开启总中断
}

/*
 *****************************************************************************************
 * 函数名称：externalInterrupt1Init
 * 函数功能：外部中断1中断初始化
 * 输入参数：无
 * 输出参数：无
 * 其他说明：无
 ******************************************************************************************
 */
void externalInterrupt1Init(void)
{
    EX1 = 1;   // 开启外部中断 0 ,P3.3选通
    IT1 = 1;   // 设置成边沿触发（下降沿）
    EA = 1;    // 开启总中断
}


