/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897(已满)  三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		main
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ790875685)
 * @version    		查看doc内version文件 版本说明
 * @Software 		MDK FOR C251 V5.60
 * @Target core		STC32G12K1287
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-12-18
 ********************************************************************************************************************/
#include "headfile.h"

/*
 * 系统频率，可查看board.h中的 FOSC 宏定义修改。
 * board.h文件中FOSC的值设置为0,则程序自动设置系统频率为33.1776MHZ
 * 在board_init中,已经将P54引脚设置为复位
 * 如果需要使用P54引脚,可以在board.c文件中的board_init()函数中删除SET_P54_RESRT即可
 */
 
//uint8 push_flag=0,key_num=0,key_num2=0;
//extern uint8 key_value,key_push_flag;
//extern uint32 key_push_time,key_rotate;

void main()
{
	board_init();			// 初始化寄存器,勿删除此句代码。
	// 此处编写用户代码(例如：外设初始化代码等)
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
