#include "oled.h"
#include "oledfont.h"


uint8 OLED_GRAM[128][8];
	uint8 flag=0;

//���Ժ���
void OLED_ColorTurn(uint8 i)
{
	if(i==0)
		{
			OLED_WR_Byte(0xA6,OLED_CMD);//������ʾ
		}
	if(i==1)
		{
			OLED_WR_Byte(0xA7,OLED_CMD);//��ɫ��ʾ
		}
}

//��Ļ��ת180��
void OLED_DisplayTurn(uint8 i)
{
	if(i==0)
		{
			OLED_WR_Byte(0xC8,OLED_CMD);//������ʾ
			OLED_WR_Byte(0xA1,OLED_CMD);
		}
	if(i==1)
		{
			OLED_WR_Byte(0xC0,OLED_CMD);//��ת��ʾ
			OLED_WR_Byte(0xA0,OLED_CMD);
		}
}

//��ʼ�ź�
void I2C_Start(void)
{
	OLED_SDA_Set();
	OLED_SCL_Set();
	delay_us(2);
	OLED_SDA_Clr();
	delay_us(2);
	OLED_SCL_Clr();
	delay_us(2);
}

//�����ź�
void I2C_Stop(void)
{
	OLED_SDA_Clr();
	OLED_SCL_Set();
	delay_us(2);
	OLED_SDA_Set();
}

//�ȴ��ź���Ӧ
void I2C_WaitAck(void) //�������źŵĵ�ƽ
{
	OLED_SDA_Set();
	delay_us(2);
	OLED_SCL_Set();
	delay_us(2);
	OLED_SCL_Clr();
	delay_us(2);
}

//д��һ���ֽ�
void Send_Byte(uint8 dat)
{
	uint8 i;
	for(i=0;i<8;i++)
	{
		if(dat&0x80)OLED_SDA_Set();//��dat��8λ�����λ����д��
		else OLED_SDA_Clr();
		delay_us(2);
		OLED_SCL_Set();
		delay_us(2);
		OLED_SCL_Clr();//��ʱ���ź�����Ϊ�͵�ƽ
		dat<<=1;
  }
}

//����һ���ֽ�
//mode:����/�����־ 0,��ʾ����;1,��ʾ����;
void OLED_WR_Byte(uint8 dat,uint8 mode)
{
	I2C_Start();
	Send_Byte(0x78);
	I2C_WaitAck();
	if(mode)Send_Byte(0x40);
  else Send_Byte(0x00);
	I2C_WaitAck();
	Send_Byte(dat);
	I2C_WaitAck();
	I2C_Stop();
}

//����OLED��ʾ 
void OLED_DisPlay_On(void)
{
	OLED_WR_Byte(0x8D,OLED_CMD);//��ɱ�ʹ��
	OLED_WR_Byte(0x14,OLED_CMD);//������ɱ�
	OLED_WR_Byte(0xAF,OLED_CMD);//������Ļ
}

//�ر�OLED��ʾ 
void OLED_DisPlay_Off(void)
{
	OLED_WR_Byte(0x8D,OLED_CMD);//��ɱ�ʹ��
	OLED_WR_Byte(0x10,OLED_CMD);//�رյ�ɱ�
	OLED_WR_Byte(0xAE,OLED_CMD);//�ر���Ļ
}

//�����Դ浽OLED	
void OLED_Refresh(void)
{
	uint8 i,n;
	for(i=0;i<8;i++)
	{
		OLED_WR_Byte(0xb0+i,OLED_CMD); //��������ʼ��ַ
		OLED_WR_Byte(0x00,OLED_CMD);   //���õ�����ʼ��ַ
		OLED_WR_Byte(0x10,OLED_CMD);   //���ø�����ʼ��ַ
		I2C_Start();
		Send_Byte(0x78);
		I2C_WaitAck();
		Send_Byte(0x40);
		I2C_WaitAck();
		for(n=0;n<128;n++)
		{
			Send_Byte(OLED_GRAM[n][i]);
			I2C_WaitAck();
		}
		I2C_Stop();
  }
}
//��������
void OLED_Clear(uint8 CLEAR_COLOR)
{
	uint8 i,n;
	for(i=0;i<8;i++)
	{
	   for(n=0;n<128;n++)
			{
			 OLED_GRAM[n][i]=CLEAR_COLOR;//�����������
			}
  }
}
void OLED_Clear_Choose(uint8 x,uint8 y,uint8 width,uint8 height,uint8 CLEAR_COLOR)  
{ 
  unsigned char i,n; 
  for(i=0;i<width;i++)  
  {    
    for(n=0;n<height;n++)
    {
      OLED_GRAM[x+i][y]=CLEAR_COLOR;
    }
  } 
}

//���� 
//x:0~127
//y:0~63
//t:1 ��� 0,���	
void OLED_DrawPoint(uint8 x,uint8 y,uint8 t)
{
	uint8 i,m,n;
	i=y/8;
	m=y%8;
	n=1<<m;
	if(t){OLED_GRAM[x][i]|=n;}
	else
	{
		OLED_GRAM[x][i]=~OLED_GRAM[x][i];
		OLED_GRAM[x][i]|=n;
		OLED_GRAM[x][i]=~OLED_GRAM[x][i];
	}
}

//����
//x1,y1:�������
//x2,y2:��������
void OLED_DrawLine(uint8 x1,uint8 y1,uint8 x2,uint8 y2,uint8 mode)
{
	uint16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1;
	uRow=x1;//�����������
	uCol=y1;
	if(delta_x>0)incx=1; //���õ������� 
	else if (delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;}
	if(delta_y>0)incy=1;
	else if (delta_y==0)incy=0;//ˮƽ�� 
	else {incy=-1;delta_y=-delta_x;}
	if(delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y;
	for(t=0;t<distance+1;t++)
	{
		OLED_DrawPoint(uRow,uCol,mode);//����
		xerr+=delta_x;
		yerr+=delta_y;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}
}
//x,y:Բ������
//r:Բ�İ뾶
void OLED_DrawCircle(uint8 x,uint8 y,uint8 r)
{
	int a, b,num;
    a = 0;
    b = r;
    while(2 * b * b >= r * r)      
    {
        OLED_DrawPoint(x + a, y - b,1);
        OLED_DrawPoint(x - a, y - b,1);
        OLED_DrawPoint(x - a, y + b,1);
        OLED_DrawPoint(x + a, y + b,1);
 
        OLED_DrawPoint(x + b, y + a,1);
        OLED_DrawPoint(x + b, y - a,1);
        OLED_DrawPoint(x - b, y - a,1);
        OLED_DrawPoint(x - b, y + a,1);
        
        a++;
        num = (a * a + b * b) - r*r;//���㻭�ĵ���Բ�ĵľ���
        if(num > 0)
        {
            b--;
            a--;
        }
    }
}



//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//size1:ѡ������ 6x8/6x12/8x16/12x24
//mode:0,��ɫ��ʾ;1,������ʾ
void OLED_ShowChar(uint8 x,uint8 y,uint8 chr,uint8 size1,uint8 mode)
{
	uint8 i,m,temp,size2,chr1;
	uint8 x0=x,y0=y;

	if(size1==8)size2=6;
	else size2=(size1/8+((size1%8)?1:0))*(size1/2);  //�õ�����һ���ַ���Ӧ������ռ���ֽ���

	chr1=chr-' ';  //����ƫ�ƺ��ֵ
	for(i=0;i<size2;i++)
	{
		if(size1==8)
			  {temp=asc2_0806[chr1][i];} //����0806����
		else if(size1==12)
        {temp=asc2_1206[chr1][i];} //����1206����
		else if(size1==16)
        {temp=asc2_1608[chr1][i];} //����1608����
		else if(size1==24)
        {temp=asc2_2412[chr1][i];} //����2412����
		else return;
		for(m=0;m<8;m++)
		{
			if(temp&0x01)OLED_DrawPoint(x,y,mode);
			else OLED_DrawPoint(x,y,!mode);
			temp>>=1;
			y++;
		}
		x++;
		if((size1!=8)&&((x-x0)*2==size1))
		{x=x0;y0=y0+8;}
		y=y0;
  }
}


//��ʾ�ַ���
//x,y:�������  
//size1:�����С 
//*chr:�ַ�����ʼ��ַ 
//mode:0,��ɫ��ʾ;1,������ʾ
void OLED_ShowString(uint8 x,uint8 y,uint8 *chr,uint8 size1,uint8 mode)
{
	while((*chr>=' ')&&(*chr<='~'))//�ж��ǲ��ǷǷ��ַ�!
	{
		OLED_ShowChar(x,y,*chr,size1,mode);
		if(size1==8)x+=6;
		else x+=size1/2;
		chr++;
  }
}

//m^n
uint32 OLED_Pow(uint8 m,uint8 n)
{
	uint32 result=1;
	while(n--)
	{
	  result*=m;
	}
	return result;
}

//��ʾ����
//x,y :�������
//num :Ҫ��ʾ������
//len :���ֵ�λ��
//size:�����С
//mode:0,��ɫ��ʾ;1,������ʾ
void OLED_ShowNum(uint8 x,uint8 y,int32 num,uint8 len,uint8 size1,uint8 mode)
{
	uint8 t,temp,m=0;
	uint8 sign_num=0,num_len=0;

	if(num<0){num=-num;sign_num=1;}
	
	for(t=1;t<len+1;t++)
	{
		if(!(num/OLED_Pow(10,t)))
		{
			num_len=t;
			break;
		}
	}
	
	if(sign_num&&num_len==len)len+=1;
	
	if(size1==8)m=2;
	for(t=0;t<len;t++)
	{
		temp=(num/OLED_Pow(10,len-t-1))%10;
		if(t==(len-num_len-1)&&sign_num)OLED_ShowChar(x+(size1/2+m)*t,y,'-',size1,mode);
		else if(!temp)OLED_ShowChar(x+(size1/2+m)*t,y,'0',size1,mode);
		else if(temp) OLED_ShowChar(x+(size1/2+m)*t,y,temp+'0',size1,mode);
  }
}
void OLED_ShowDouble(uint8 x,uint8 y,double num,uint8 len,uint8 size1,uint8 mode)
{
	uint8 t,temp,m=0;
	uint8 sign_num=0,num_len=0,double_bit=0;
	uint32 double_num=0,uint32_num=0;
	
	if(num<0){num=-num;sign_num=1;}
	double_num=num;
	num*=OLED_Pow(10,len);
	uint32_num=num;
	
	for(t=1;t<11;t++)//num size
	{
		if(!(uint32_num/OLED_Pow(10,t)))
		{
			num_len=t;
			break;
		}
	}

	for(t=1;t<11;t++)//bit site
	{
		if(!(double_num/OLED_Pow(10,t)))
		{
			double_bit=t;
			break;
		}
	}
	
	if(size1==8)m=2;
	for(t=0;t<num_len;t++)
	{
		if(sign_num)
		{
			OLED_ShowChar(x+(size1/2+m)*t,y,'-',size1,mode);
			sign_num=0;
			num_len+=1;
			double_bit+=1;
		}else if(t==(double_bit)){
			OLED_ShowChar(x+(size1/2+m)*t,y,'.',size1,mode);
			num_len+=1;
		}else{
			temp=(uint32_num/OLED_Pow(10,num_len-t-1))%10;
			OLED_ShowChar(x+(size1/2+m)*t,y,temp+'0',size1,mode);
		}
  }
	
}
//��ʾ����
//x,y:�������
//num:���ֶ�Ӧ�����
//mode:0,��ɫ��ʾ;1,������ʾ
void OLED_ShowChinese(uint8 x,uint8 y,uint8 num,uint8 size1,uint8 mode)
{
	uint8 m,temp;
	uint8 x0=x,y0=y;
	uint16 i,size3=(size1/8+((size1%8)?1:0))*size1;  //�õ�����һ���ַ���Ӧ������ռ���ֽ���
	for(i=0;i<size3;i++)
	{
		if(size1==16)
				{temp=Hzk1[num][i];}//����16*16����
		else if(size1==24)
				{temp=Hzk2[num][i];}//����24*24����
		else if(size1==32)       
				{temp=Hzk3[num][i];}//����32*32����
		else if(size1==64)
				{temp=Hzk4[num][i];}//����64*64����
		else return;
		for(m=0;m<8;m++)
		{
			if(temp&0x01)OLED_DrawPoint(x,y,mode);
			else OLED_DrawPoint(x,y,!mode);
			temp>>=1;
			y++;
		}
		x++;
		if((x-x0)==size1)
		{x=x0;y0=y0+8;}
		y=y0;
	}
}

//num ��ʾ���ֵĸ���
//space ÿһ����ʾ�ļ��
//mode:0,��ɫ��ʾ;1,������ʾ
void OLED_ScrollDisplay(uint8 num,uint8 space,uint8 mode)
{
	uint8 i,n,t=0,m=0,r;
	while(1)
	{
		if(m==0)
		{
	    OLED_ShowChinese(128,24,t,16,mode); //д��һ�����ֱ�����OLED_GRAM[][]������
			t++;
		}
		if(t==num)
			{
				for(r=0;r<16*space;r++)      //��ʾ���
				 {
					for(i=1;i<144;i++)
						{
							for(n=0;n<8;n++)
							{
								OLED_GRAM[i-1][n]=OLED_GRAM[i][n];
							}
						}
           OLED_Refresh();
				 }
        t=0;
      }
		m++;
		if(m==16){m=0;}
		for(i=1;i<144;i++)   //ʵ������
		{
			for(n=0;n<8;n++)
			{
				OLED_GRAM[i-1][n]=OLED_GRAM[i][n];
			}
		}
		OLED_Refresh();
	}
}

//x,y���������
//sizex,sizey,ͼƬ����
//BMP[]��Ҫд���ͼƬ����
//mode:0,��ɫ��ʾ;1,������ʾ
void OLED_ShowPicture(uint8 x,uint8 y,uint8 sizex,uint8 sizey,uint8 BMP[],uint8 mode)
{
	uint16 j=0;
	uint8 i,n,temp,m;
	uint8 x0=x,y0=y;
	sizey=sizey/8+((sizey%8)?1:0);
	for(n=0;n<sizey;n++)
	{
		 for(i=0;i<sizex;i++)
		 {
				temp=BMP[j];
				j++;
				for(m=0;m<8;m++)
				{
					if(temp&0x01)OLED_DrawPoint(x,y,mode);
					else OLED_DrawPoint(x,y,!mode);
					temp>>=1;
					y++;
				}
				x++;
				if((x-x0)==sizex)
				{
					x=x0;
					y0=y0+8;
				}
				y=y0;
     }
	 }
}
//OLED�ĳ�ʼ��
void OLED_Init(void)
{
	OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
	OLED_WR_Byte(0xCF,OLED_CMD);// Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����
	OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00,OLED_CMD);//-not offset
	OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
	OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
	OLED_WR_Byte(0x30,OLED_CMD);//Set VCOM Deselect Level
	OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x02,OLED_CMD);//
	OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
	OLED_Clear(OLED_CLEAR_BLACK);
	OLED_WR_Byte(0xAF,OLED_CMD);
}

