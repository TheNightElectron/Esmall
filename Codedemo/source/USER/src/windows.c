#include "windows.h"

uint8 windows=0,pwm_choose=0;
extern uint8 windows_num,pwm_set_flag;
extern int32 key_push;
extern uint16 duty[4],hz[4];
extern double adc1,adc2;


void windows_start(void)
{
	OLED_Clear(OLED_CLEAR_BLACK);
	OLED_ShowString(5,20,"ROMANCE",24,1);
	OLED_ShowString(40,40,"never dies",16,1);
	OLED_Refresh();
	delay_ms(500);
}
void windows_menu(void)
{
	OLED_Clear(OLED_CLEAR_BLACK);
	OLED_ShowString(45,5,"PWM",24,1);
	OLED_ShowString(45,32,"ADC",24,1);
	if(key_push%2==0){OLED_ShowChar(30,9,96+' ',16,1);windows=11;}
	else {OLED_ShowChar(30,36,96+' ',16,1);windows=12;}
	OLED_Refresh();
}
void windows_pwm(void)
{
	windows=2;
	OLED_Clear(OLED_CLEAR_BLACK);
	OLED_ShowString(16,5,"PWM1",24,1);
	OLED_ShowString(80,5,"PWM2",24,1);
	OLED_ShowString(16,32,"PWM3",24,1);
	OLED_ShowString(80,32,"PWM4",24,1);
	if(key_push%4==0){OLED_ShowChar(4,9,96+' ',16,1);  pwm_choose=1;}
	if(key_push%4==1||key_push%4==-1){OLED_ShowChar(68,9,96+' ',16,1); pwm_choose=2;}
	if(key_push%4==2||key_push%4==-2){OLED_ShowChar(4,36,96+' ',16,1); pwm_choose=3;}
	if(key_push%4==3||key_push%4==-3){OLED_ShowChar(68,36,96+' ',16,1);pwm_choose=4;}
	OLED_Refresh();
}
void windows_adc(void)
{
	OLED_Clear(OLED_CLEAR_BLACK);
	adc_detection();
	OLED_ShowString(16,5,"ADC1:",24,1);
	OLED_ShowDouble(76,9,adc1,2,16,1);
	OLED_ShowChar(110,5,'V',24,1);
	OLED_ShowString(16,32,"ADC2:",24,1);
	OLED_ShowDouble(76,36,adc2,2,16,1);
	OLED_ShowChar(110,32,'V',24,1);
	OLED_Refresh();
}
void windows_pwm_data(void)
{
	OLED_Clear(OLED_CLEAR_BLACK);
	OLED_ShowString(16,5,"HZ:",24,1);
	OLED_ShowNum(52,9,hz[pwm_choose-1],5,16,1);
	OLED_ShowString(98,5,"hz",24,1);
	OLED_ShowString(16,32,"DUTY:",24,1);
	OLED_ShowNum(76,36,duty[pwm_choose-1],3,16,1);
	OLED_ShowChar(110,32,'%',24,1);
	if(!pwm_set_flag)
	{
		if(key_push%2==0){OLED_ShowChar(4,9 ,96+' ',16,1);windows=21;}
		else{OLED_ShowChar(4,36,96+' ',16,1);windows=22;}
	}
	pwm_start();
	OLED_Refresh();
}
void windows_show(void)
{
	switch(windows_num)
	{
		case 0:windows_menu();break;
		case 1:windows_pwm();break;
		case 2:windows_adc();break;
		case 3:windows_pwm_data();break;
		default:break;
	}
}