/*
 *****************************************************************************************
 *	�� Ŀ �� ��:�๦�ܵ���ʱ��
 *  ʵ �� ƽ ̨��������� QX-MCS51������
 *	�� �� �� �ߣ�miki
 *  �� Ŀ ˵ �������ö�ʱ���ж�ʵ��׼ȷ��ʱ��ʹ�����������ʾʱ�䣬������ʵ�����ӹ���
 *               ����ʵ��Уʱ���л�������ܣ��Լ�ʵ���������ӹ��ܵ�
 *  github �� ַ��
 *	�� �� �� �ڣ�2017-11-18
 *****************************************************************************************
 */

/************************************* ����ͷ�ļ� ***************************************/
#include "config.h"
#include "digital_tube.h"
#include "delay.h"
#include "timer.h"

/************************************* ȫ�ֱ������� **************************************/
u8 GlobalShi1,GlobalShi0;
u8 GlobalFen1,GlobalFen0;
u8 GlobalMiao1,GlobalMiao0;
u16 GlobalTemp;

/********************************** ��չȫ�ֱ������� ************************************/
extern u8 GlobalInterruptAdd;

/*
 *****************************************************************************************
 * �������ƣ�main
 * �������ܣ��������������������
 * �����������
 * �����������
 * ����˵������
 ******************************************************************************************
 */
void main()
{	
	/* ��ʱ��0��ʼ���ӳ��� */
	timer0InterruptInit(); 
	while(1)
	{
		if(GlobalInterruptAdd == 20)
		  {
			GlobalInterruptAdd = 0;
			GlobalTemp ++;
			if(GlobalTemp == 86400)
		   {
				GlobalTemp=0;
		   }
			GlobalShi1=GlobalTemp/3600/10;
			GlobalShi0=GlobalTemp/3600-(GlobalShi1*10);
			GlobalFen1=GlobalTemp%3600/60/10;
			GlobalFen0=GlobalTemp%3600/60-(GlobalFen1*10);
			GlobalMiao1=GlobalTemp%3600%60/10;
			GlobalMiao0=GlobalTemp%3600%60-(GlobalMiao1*10);
		  }
		digitalTubeDisplayTime(GlobalShi1,GlobalShi0,GlobalFen1,
								GlobalMiao1,GlobalMiao1,GlobalMiao0);
	}
}

