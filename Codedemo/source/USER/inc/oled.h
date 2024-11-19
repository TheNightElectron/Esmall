#include <stc32g.h>
#ifndef __OLED_H
#define __OLED_H		

#include "headfile.h"
 
#define OLED_CMD  0	//???
#define OLED_DATA 1	//???


#define OLED_CLEAR_BLACK 0
#define OLED_CLEAR_WHITE 0xff

#define OLED_SLACE 0x78
 
 
#define OLED_SCL  P15
#define OLED_SDA  P14
 
 
#define OLED_SCL_Clr() OLED_SCL=0
#define OLED_SCL_Set() OLED_SCL=1
 
#define OLED_SDA_Clr() OLED_SDA=0
#define OLED_SDA_Set() OLED_SDA=1					   
 
//OLED?????			   		    
void OLED_ClearPoint(uint8 x,uint8 y);
void OLED_ColorTurn(uint8 i);
void OLED_DisplayTurn(uint8 i);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_WaitAck(void);
void Send_Byte(uint8 dat);
void OLED_WR_Byte(uint8 dat,uint8 mode);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);
void OLED_Clear(uint8 CLEAR_COLOR);
void OLED_DrawPoint(uint8 x,uint8 y,uint8 t);
void OLED_DrawLine(uint8 x1,uint8 y1,uint8 x2,uint8 y2,uint8 mode);
void OLED_DrawCircle(uint8 x,uint8 y,uint8 r);
void OLED_ShowChar(uint8 x,uint8 y,uint8 chr,uint8 size1,uint8 mode);
void OLED_ShowChar6x8(uint8 x,uint8 y,uint8 chr,uint8 mode);
void OLED_ShowString(uint8 x,uint8 y,uint8 *chr,uint8 size1,uint8 mode);
void OLED_ShowNum(uint8 x,uint8 y,int32 num,uint8 len,uint8 size1,uint8 mode);
void OLED_ShowDouble(uint8 x,uint8 y,double num,uint8 len,uint8 size1,uint8 mode);
void OLED_ShowChinese(uint8 x,uint8 y,uint8 num,uint8 size1,uint8 mode);
void OLED_ScrollDisplay(uint8 num,uint8 space,uint8 mode);
void OLED_ShowPicture(uint8 x,uint8 y,uint8 sizex,uint8 sizey,uint8 BMP[],uint8 mode);
void OLED_Init(void);
void OLED_Clear_Choose(uint8 x,uint8 y,uint8 width,uint8 height,uint8 CLEAR_COLOR);
#endif  
	 
 
 
 