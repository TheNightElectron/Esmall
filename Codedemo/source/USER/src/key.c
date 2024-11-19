#include "key.h"
	
typedef enum {
	key_normal,
	key_press,
	key_reless
}KEY_STATE;

KEY_STATE key_state=key_normal;

uint8 key_push_flag=0,key_value=0,key_push_a_time_flag=0,key_push_b_time_flag=0,key_push_c_time_flag=0,
			windows_num=0,
		  pwm_set_flag=0;
int32 key_push=0;
uint32 key_push_time_a=0,key_push_time_b=0,key_push_time_c=0;

extern uint8 windows,pwm_set_data;

void key_scan(void)
{
	switch(key_state)
	{
		case key_normal:{
			if(!key_a||!key_b||!key_c)key_state=key_press;
		}break;
		case key_press:{
			if(!key_c){key_state=key_reless;key_value=3;}
			if(!key_b){key_state=key_reless;key_value=2;}
			if(!key_a){key_state=key_reless;key_value=1;}
		}break;
		case key_reless:{
			if(!key_a){key_push_time_a+=10;if(key_push_time_a>=500){key_push_a_time_flag=1;key_push_time_a=0;}}
			else if(!key_b){key_push_time_b+=10;if(key_push_time_b>=500){key_push_b_time_flag=1;key_push_time_b=0;}}
			else if(!key_c){key_push_time_c+=10;if(key_push_time_c>=500){key_push_c_time_flag=1;key_push_time_c=0;}}
			else{key_state=key_normal;key_push_flag=1;key_push_time_a=0;key_push_time_b=0;key_push_time_c=0;}
		}break;
		default:break;
	}
}

void key_work(void)
{
	if(key_push_flag)
	{
		switch(key_value)
		{
			case 1:{key_push-=1;}break;
			case 2:{
				if(!key_push_b_time_flag)
				{
					if(pwm_set_flag){pwm_set_flag=0;windows=0;}
					switch(windows)
					{
						case 11: windows_num=1;break;
						case 12: windows_num=2;break;
						case  2: windows_num=3;break;
						case 21:pwm_set_flag=1;break;
						case 22:pwm_set_flag=2;break;
						default:break;
					}
					key_push=0;
				}
				else{
					switch(windows)
					{
						case 12:windows_num=0;break;
						case  2:windows_num=0;break;
						case 21:windows_num=1;break;
						case 22:windows_num=1;break;
						default:break;
					}
				}
			}break;
			case 3:{key_push+=1;}break;
			default:break;
		}
		key_value=0;
		key_push_flag=0;
		key_push_b_time_flag=0;
	}
	windows_show();
}
