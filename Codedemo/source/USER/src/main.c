/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		main
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ790875685)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		MDK FOR C251 V5.60
 * @Target core		STC32G12K1287
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-12-18
 ********************************************************************************************************************/
#include "headfile.h"

/*
 * ϵͳƵ�ʣ��ɲ鿴board.h�е� FOSC �궨���޸ġ�
 * board.h�ļ���FOSC��ֵ����Ϊ0,������Զ�����ϵͳƵ��Ϊ33.1776MHZ
 * ��board_init��,�Ѿ���P54��������Ϊ��λ
 * �����Ҫʹ��P54����,������board.c�ļ��е�board_init()������ɾ��SET_P54_RESRT����
 */
 
//uint8 push_flag=0,key_num=0,key_num2=0;
//extern uint8 key_value,key_push_flag;
//extern uint32 key_push_time,key_rotate;

void main()
{
	board_init();			// ��ʼ���Ĵ���,��ɾ���˾���롣
	// �˴���д�û�����(���磺�����ʼ�������)
	pit_timer_ms(TIM_4,5);
	OLED_Init();
	OLED_ColorTurn(0);
	OLED_DisplayTurn(0);
	adc_init(ADC_P00,ADC_SYSclk_DIV_32);//adc1
	adc_init(ADC_P01,ADC_SYSclk_DIV_32);//adc2
	pwm_init(PWMA_CH3P_P24, 0, 0);//pwm1
	pwm_init(PWMB_CH2_P21,  0, 0);//pwm2
	pwm_init(PWMB_CH1_P20,  0, 0);//pwm3
	pwm_init(PWMA_CH4P_P34, 0, 0);//pwm4
//	OLED_ShowChar(52,20,97+' ',24,1);
//	OLED_ShowChar(52,44,98+' ',24,1);
//	OLED_ShowChar(64,20,97+' ',24,1);
//	OLED_ShowChar(64,44,98+' ',24,1);
	windows_start();


	
	while(1)
	{	
//		windows_adc();
		key_work();
//		if(P23==0)
//		{
//			push_flag=1;
//			num++;
//			OLED_Clear(OLED_CLEAR_BLACK);
//		}
//		OLED_ShowNum(0,0,key_value,2,16,1);
//		OLED_Refresh();
//		if(push_flag)
//		{
//			OLED_ShowNum(0,0,num,2,16,1);
//			OLED_ShowChar(26,24,95+' ',16,1);
//			OLED_ShowChar(38,20,95+' ',24,1);
//			OLED_ShowChar(58,20,95+' ',24,1);
//			OLED_ShowChar(78,20,95+' ',24,1);
//			OLED_ShowChar(94,24,95+' ',16,1);
//			OLED_Refresh();
//			delay_ms(500);
//			OLED_ShowChar(26,24,95+' ',16,1);
//			OLED_ShowChar(38,20,95+' ',24,1);
//			OLED_ShowChar(58,20,96+' ',24,1);
//			OLED_ShowChar(78,20,95+' ',24,1);
//			OLED_ShowChar(94,24,95+' ',16,1);
//			OLED_Refresh();
//			delay_ms(500);
//			OLED_ShowChar(26,24,95+' ',16,1);
//			OLED_ShowChar(38,20,96+' ',24,1);
//			OLED_ShowChar(58,20,96+' ',24,1);
//			OLED_ShowChar(78,20,96+' ',24,1);
//			OLED_ShowChar(94,24,95+' ',16,1);
//			OLED_Refresh();		
//			delay_ms(500);
//			OLED_ShowChar(26,24,96+' ',16,1);
//			OLED_ShowChar(38,20,96+' ',24,1);
//			OLED_ShowChar(58,20,96+' ',24,1);
//			OLED_ShowChar(78,20,96+' ',24,1);
//			OLED_ShowChar(94,24,96+' ',16,1);
//			OLED_Refresh();			
//			delay_ms(500);			
//		}
		
	}
}
