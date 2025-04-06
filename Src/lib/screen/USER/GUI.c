//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//����Ӳ������Ƭ��STM32F103RCT6,����ԭ��MiniSTM32������,��Ƶ72MHZ������12MHZ
//QDtech-TFTҺ������ for STM32 IOģ��
//xiao��@ShenZhen QDtech co.,LTD
//��˾��վ:www.qdtft.com
//�Ա���վ��http://qdtech.taobao.com
//wiki������վ��http://www.lcdwiki.com
//��˾�ṩ����֧�֣��κμ������⻶ӭ��ʱ����ѧϰ
//�̻�(����) :+86 0755-23594567
//�ֻ�:15989313508���빤��
//����:lcdwiki01@gmail.com    support@lcdwiki.com    goodtft@163.com
//����֧��QQ:3002773612  3002778157
//��������QQȺ:324828016
//��������:2018/08/09
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������ȫ�����Ӽ������޹�˾ 2018-2028
//All rights reserved
/****************************************************************************************************
//=========================================��Դ����================================================//
//     LCDģ��                STM32��Ƭ��
//      VCC          ��        DC5V/3.3V      //��Դ
//      GND          ��          GND          //��Դ��
//=======================================Һ���������߽���==========================================//
//��ģ��Ĭ��������������ΪSPI����
//     LCDģ��                STM32��Ƭ��
//    SDI(MOSI)      ��          PB15         //Һ����SPI��������д�ź�
//    SDO(MISO)      ��          PB14         //Һ����SPI�������ݶ��źţ��������Ҫ�������Բ�����
//=======================================Һ���������߽���==========================================//
//     LCDģ�� 					      STM32��Ƭ��
//       LED         ��          PB9          //Һ������������źţ��������Ҫ���ƣ���5V��3.3V
//       SCK         ��          PB13         //Һ����SPI����ʱ���ź�
//      DC/RS        ��          PB10         //Һ��������/��������ź�
//       RST         ��          PB12         //Һ������λ�����ź�
//       CS          ��          PB11         //Һ����Ƭѡ�����ź�
//=========================================������������=========================================//
//���ģ�鲻���������ܻ��ߴ��д������ܣ����ǲ���Ҫ�������ܣ�����Ҫ���д���������
//	   LCDģ��                STM32��Ƭ��
//      T_IRQ        ��          PC10         //�����������ж��ź�
//      T_DO         ��          PC2          //������SPI���߶��ź�
//      T_DIN        ��          PC3          //������SPI����д�ź�
//      T_CS         ��          PC13         //������Ƭѡ�����ź�
//      T_CLK        ��          PC0          //������SPI����ʱ���ź�
**************************************************************************************************/
 /* @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
**************************************************************************************************/
#include "GUI.h"
#include "lcd.h"
#include "main.h"

LCD_COUNTER lcd_coubnter;

Keypad keypad ={
		.name = {LCD_W*0.05, 0.95*LCD_W, 0.5*LCD_H, 0.5*LCD_H + 20, RED},

		.b1 = {LCD_W*0.05, LCD_W*0.33, LCD_H*0.5 + 25, LCD_H*0.5 + 50, LIGHTBLUE},
		.b2 = {LCD_W*0.33 + 5, LCD_W*0.64, LCD_H*0.5 + 25, LCD_H*0.5 + 50, LIGHTBLUE},
		.b3 = {LCD_W*0.64 + 5, LCD_W*0.95, LCD_H*0.5 + 25, LCD_H*0.5 + 50, LIGHTBLUE},

		.b4 = {LCD_W*0.05, LCD_W*0.33, LCD_H*0.5 + 55, LCD_H*0.5 + 80, LIGHTBLUE},
		.b5 = {LCD_W*0.33 + 5, LCD_W*0.64, LCD_H*0.5 + 55, LCD_H*0.5 + 80, LIGHTBLUE},
		.b6 = {LCD_W*0.64 + 5, LCD_W*0.95, LCD_H*0.5 + 55, LCD_H*0.5 + 80, LIGHTBLUE},

		.b7 = {LCD_W*0.05, LCD_W*0.33, LCD_H*0.5 + 85, LCD_H*0.5 + 110, LIGHTBLUE},
		.b8 = {LCD_W*0.33 + 5, LCD_W*0.64, LCD_H*0.5 + 85, LCD_H*0.5 + 110, LIGHTBLUE},
		.b9 = {LCD_W*0.64 + 5, LCD_W*0.95, LCD_H*0.5 + 85, LCD_H*0.5 + 110, LIGHTBLUE},

		.clr = {LCD_W*0.05, LCD_W*0.33, LCD_H*0.5 + 115, LCD_H*0.5 + 140, RED},
		.b0 = {LCD_W*0.33 + 5, LCD_W*0.64, LCD_H*0.5 + 115, LCD_H*0.5 + 140, LIGHTBLUE},
		.set = {LCD_W*0.64 + 5, LCD_W*0.95, LCD_H*0.5 + 115, LCD_H*0.5 + 140, GREEN},

		.color = BLUE
};

//DS18B20 ds18b20_hot;
//DS18B20 ds18b20_cold;
//DS18B20 ds18b20_terminal;
/*******************************************************************
 * @name       :void GUI_DrawPoint(u16 x,u16 y,u16 color)
 * @date       :2018-08-09
 * @function   :draw a point in LCD screen
 * @parameters :x:the x coordinate of the point
                y:the y coordinate of the point
								color:the color value of the point
 * @retvalue   :None
********************************************************************/
void GUI_DrawPoint(u16 x,u16 y,u16 color)
{
	LCD_SetCursor(x,y);//���ù��λ��
	Lcd_WriteData_16Bit(color);
}

/*******************************************************************
 * @name       :void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
 * @date       :2018-08-09
 * @function   :fill the specified area
 * @parameters :sx:the bebinning x coordinate of the specified area
                sy:the bebinning y coordinate of the specified area
								ex:the ending x coordinate of the specified area
								ey:the ending y coordinate of the specified area
								color:the filled color value
 * @retvalue   :None
********************************************************************/
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
{
	u16 i,j;
	u16 width=ex-sx+1; 		//�õ����Ŀ���
	u16 height=ey-sy+1;		//�߶�
	LCD_SetWindows(sx,sy,ex,ey);//������ʾ����
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		Lcd_WriteData_16Bit(color);	//д������
	}
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//�ָ���������Ϊȫ��
}

/*******************************************************************
 * @name       :void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
 * @date       :2018-08-09
 * @function   :Draw a line between two points
 * @parameters :x1:the bebinning x coordinate of the line
                y1:the bebinning y coordinate of the line
								x2:the ending x coordinate of the line
								y2:the ending y coordinate of the line
 * @retvalue   :None
********************************************************************/
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u16 t;
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;

	delta_x=x2-x1; //������������
	delta_y=y2-y1;
	uRow=x1;
	uCol=y1;
	if(delta_x>0)incx=1; //���õ�������
	else if(delta_x==0)incx=0;//��ֱ��
	else {incx=-1;delta_x=-delta_x;}
	if(delta_y>0)incy=1;
	else if(delta_y==0)incy=0;//ˮƽ��
	else{incy=-1;delta_y=-delta_y;}
	if( delta_x>delta_y)distance=delta_x; //ѡȡ��������������
	else distance=delta_y;
	for(t=0;t<=distance+1;t++ )//�������
	{
		LCD_DrawPoint(uRow,uCol);//����
		xerr+=delta_x ;
		yerr+=delta_y ;
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

/*****************************************************************************
 * @name       :void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
 * @date       :2018-08-09
 * @function   :Draw a rectangle
 * @parameters :x1:the bebinning x coordinate of the rectangle
                y1:the bebinning y coordinate of the rectangle
								x2:the ending x coordinate of the rectangle
								y2:the ending y coordinate of the rectangle
 * @retvalue   :None
******************************************************************************/
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}

/*****************************************************************************
 * @name       :void LCD_DrawFillRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
 * @date       :2018-08-09
 * @function   :Filled a rectangle
 * @parameters :x1:the bebinning x coordinate of the filled rectangle
                y1:the bebinning y coordinate of the filled rectangle
								x2:the ending x coordinate of the filled rectangle
								y2:the ending y coordinate of the filled rectangle
 * @retvalue   :None
******************************************************************************/
void LCD_DrawFillRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_Fill(x1,y1,x2,y2,POINT_COLOR);
}

/*****************************************************************************
 * @name       :void _draw_circle_8(int xc, int yc, int x, int y, u16 c)
 * @date       :2018-08-09
 * @function   :8 symmetry circle drawing algorithm (internal call)
 * @parameters :xc:the x coordinate of the Circular center
                yc:the y coordinate of the Circular center
								x:the x coordinate relative to the Circular center
								y:the y coordinate relative to the Circular center
								c:the color value of the circle
 * @retvalue   :None
******************************************************************************/
void _draw_circle_8(int xc, int yc, int x, int y, u16 c)
{
	GUI_DrawPoint(xc + x, yc + y, c);

	GUI_DrawPoint(xc - x, yc + y, c);

	GUI_DrawPoint(xc + x, yc - y, c);

	GUI_DrawPoint(xc - x, yc - y, c);

	GUI_DrawPoint(xc + y, yc + x, c);

	GUI_DrawPoint(xc - y, yc + x, c);

	GUI_DrawPoint(xc + y, yc - x, c);

	GUI_DrawPoint(xc - y, yc - x, c);
}

/*****************************************************************************
 * @name       :void gui_circle(int xc, int yc,u16 c,int r, int fill)
 * @date       :2018-08-09
 * @function   :Draw a circle of specified size at a specified location
 * @parameters :xc:the x coordinate of the Circular center
                yc:the y coordinate of the Circular center
								r:Circular radius
								fill:1-filling,0-no filling
 * @retvalue   :None
******************************************************************************/
void gui_circle(int xc, int yc,u16 c,int r, int fill)
{
	int x = 0, y = r, yi, d;

	d = 3 - 2 * r;


	if (fill)
	{
		// �����䣨��ʵ��Բ��
		while (x <= y) {
			for (yi = x; yi <= y; yi++)
				_draw_circle_8(xc, yc, x, yi, c);

			if (d < 0) {
				d = d + 4 * x + 6;
			} else {
				d = d + 4 * (x - y) + 10;
				y--;
			}
			x++;
		}
	} else
	{
		// �������䣨������Բ��
		while (x <= y) {
			_draw_circle_8(xc, yc, x, y, c);
			if (d < 0) {
				d = d + 4 * x + 6;
			} else {
				d = d + 4 * (x - y) + 10;
				y--;
			}
			x++;
		}
	}
}

/*****************************************************************************
 * @name       :void Draw_Triangel(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2)
 * @date       :2018-08-09
 * @function   :Draw a triangle at a specified position
 * @parameters :x0:the bebinning x coordinate of the triangular edge
                y0:the bebinning y coordinate of the triangular edge
								x1:the vertex x coordinate of the triangular
								y1:the vertex y coordinate of the triangular
								x2:the ending x coordinate of the triangular edge
								y2:the ending y coordinate of the triangular edge
 * @retvalue   :None
******************************************************************************/
void Draw_Triangel(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2)
{
	LCD_DrawLine(x0,y0,x1,y1);
	LCD_DrawLine(x1,y1,x2,y2);
	LCD_DrawLine(x2,y2,x0,y0);
}

static void _swap(u16 *a, u16 *b)
{
	u16 tmp;
  tmp = *a;
	*a = *b;
	*b = tmp;
}

/*****************************************************************************
 * @name       :void Fill_Triangel(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2)
 * @date       :2018-08-09
 * @function   :filling a triangle at a specified position
 * @parameters :x0:the bebinning x coordinate of the triangular edge
                y0:the bebinning y coordinate of the triangular edge
								x1:the vertex x coordinate of the triangular
								y1:the vertex y coordinate of the triangular
								x2:the ending x coordinate of the triangular edge
								y2:the ending y coordinate of the triangular edge
 * @retvalue   :None
******************************************************************************/
void Fill_Triangel(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2)
{
	u16 a, b, y, last;
	int dx01, dy01, dx02, dy02, dx12, dy12;
	long sa = 0;
	long sb = 0;
 	if (y0 > y1)
	{
    _swap(&y0,&y1);
		_swap(&x0,&x1);
 	}
 	if (y1 > y2)
	{
    _swap(&y2,&y1);
		_swap(&x2,&x1);
 	}
  if (y0 > y1)
	{
    _swap(&y0,&y1);
		_swap(&x0,&x1);
  }
	if(y0 == y2)
	{
		a = b = x0;
		if(x1 < a)
    {
			a = x1;
    }
    else if(x1 > b)
    {
			b = x1;
    }
    if(x2 < a)
    {
			a = x2;
    }
		else if(x2 > b)
    {
			b = x2;
    }
		LCD_Fill(a,y0,b,y0,POINT_COLOR);
    return;
	}
	dx01 = x1 - x0;
	dy01 = y1 - y0;
	dx02 = x2 - x0;
	dy02 = y2 - y0;
	dx12 = x2 - x1;
	dy12 = y2 - y1;

	if(y1 == y2)
	{
		last = y1;
	}
  else
	{
		last = y1-1;
	}
	for(y=y0; y<=last; y++)
	{
		a = x0 + sa / dy01;
		b = x0 + sb / dy02;
		sa += dx01;
    sb += dx02;
    if(a > b)
    {
			_swap(&a,&b);
		}
		LCD_Fill(a,y,b,y,POINT_COLOR);
	}
	sa = dx12 * (y - y1);
	sb = dx02 * (y - y0);
	for(; y<=y2; y++)
	{
		a = x1 + sa / dy12;
		b = x0 + sb / dy02;
		sa += dx12;
		sb += dx02;
		if(a > b)
		{
			_swap(&a,&b);
		}
		LCD_Fill(a,y,b,y,POINT_COLOR);
	}
}

/*****************************************************************************
 * @name       :void LCD_ShowChar(u16 x,u16 y,u16 fc, u16 bc, u8 num,u8 size,u8 mode)
 * @date       :2018-08-09
 * @function   :Display a single English character
 * @parameters :x:the bebinning x coordinate of the Character display position
                y:the bebinning y coordinate of the Character display position
								fc:the color value of display character
								bc:the background color of display character
								num:the ascii code of display character(0~94)
								size:the size of display character
								mode:0-no overlying,1-overlying
 * @retvalue   :None
******************************************************************************/
void LCD_ShowChar(u16 x,u16 y,u16 fc, u16 bc, u8 num,u8 size,u8 mode)
{
    u8 temp;
    u8 pos,t;
	u16 colortemp=POINT_COLOR;

	num=num-' ';//�õ�ƫ�ƺ��ֵ
	LCD_SetWindows(x,y,x+size/2-1,y+size-1);//���õ���������ʾ����
	if(!mode) //�ǵ��ӷ�ʽ
	{
		for(pos=0;pos<size;pos++)
		{
			if(size==12)temp=asc2_1206[num][pos];//����1206����
			else temp=asc2_1608[num][pos];		 //����1608����
			for(t=0;t<size/2;t++)
		    {
		        if(temp&0x01)Lcd_WriteData_16Bit(fc);
				else Lcd_WriteData_16Bit(bc);
				temp>>=1;

		    }

		}
	}else//���ӷ�ʽ
	{
		for(pos=0;pos<size;pos++)
		{
			if(size==12)temp=asc2_1206[num][pos];//����1206����
			else temp=asc2_1608[num][pos];		 //����1608����
			for(t=0;t<size/2;t++)
		    {
				POINT_COLOR=fc;
		        if(temp&0x01)LCD_DrawPoint(x+t,y+pos);//��һ����
		        temp>>=1;
		    }
		}
	}
	POINT_COLOR=colortemp;
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//�ָ�����Ϊȫ��
}

/*****************************************************************************
 * @name       :void LCD_ShowString(u16 x,u16 y,u8 size,u8 *p,u8 mode)
 * @date       :2018-08-09
 * @function   :Display English string
 * @parameters :x:the bebinning x coordinate of the English string
                y:the bebinning y coordinate of the English string
								p:the start address of the English string
								size:the size of display character
								mode:0-no overlying,1-overlying
 * @retvalue   :None
******************************************************************************/
	void LCD_ShowString(u16 x,u16 y,u8 size,u8 *p,u8 mode)
	{
		while((*p<='~')&&(*p>=' '))//�ж��ǲ��ǷǷ��ַ�!
		{
			if(x>(lcddev.width-1)||y>(lcddev.height-1))
			return;
			LCD_ShowChar(x,y,POINT_COLOR,BACK_COLOR,*p,size,mode);
			x+=size/2;
			p++;
		}
	}

/*****************************************************************************
 * @name       :u32 mypow(u8 m,u8 n)
 * @date       :2018-08-09
 * @function   :get the nth power of m (internal call)
 * @parameters :m:the multiplier
                n:the power
 * @retvalue   :the nth power of m
******************************************************************************/
u32 mypow(u8 m,u8 n)
{
	u32 result=1;
	while(n--)result*=m;
	return result;
}

/*****************************************************************************
 * @name       :void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
 * @date       :2018-08-09
 * @function   :Display number
 * @parameters :x:the bebinning x coordinate of the number
                y:the bebinning y coordinate of the number
								num:the number(0~4294967295)
								len:the length of the display number
								size:the size of display number
 * @retvalue   :None
******************************************************************************/
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
{
	u8 t,temp;
	u8 enshow=0;
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,POINT_COLOR,BACK_COLOR,' ',size,0);
				continue;
			}else enshow=1;

		}
	 	LCD_ShowChar(x+(size/2)*t,y,POINT_COLOR,BACK_COLOR,temp+'0',size,0);
	}
}

/*****************************************************************************
 * @name       :void GUI_DrawFont16(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode)
 * @date       :2018-08-09
 * @function   :Display a single 16x16 Chinese character
 * @parameters :x:the bebinning x coordinate of the Chinese character
                y:the bebinning y coordinate of the Chinese character
								fc:the color value of Chinese character
								bc:the background color of Chinese character
								s:the start address of the Chinese character
								mode:0-no overlying,1-overlying
 * @retvalue   :None
******************************************************************************/
/*
void GUI_DrawFont16(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode)
{
	u8 i,j;
	u16 k;
	u16 HZnum;
	u16 x0=x;
	HZnum=sizeof(tfont16)/sizeof(typFNT_GB16);	//�Զ�ͳ�ƺ�����Ŀ


	for (k=0;k<HZnum;k++)
	{
	  if ((tfont16[k].Index[0]==*(s))&&(tfont16[k].Index[1]==*(s+1)))
	  { 	LCD_SetWindows(x,y,x+16-1,y+16-1);
		    for(i=0;i<16*2;i++)
		    {
				for(j=0;j<8;j++)
		    	{
					if(!mode) //�ǵ��ӷ�ʽ
					{
						if(tfont16[k].Msk[i]&(0x80>>j))	Lcd_WriteData_16Bit(fc);
						else Lcd_WriteData_16Bit(bc);
					}
					else
					{
						POINT_COLOR=fc;
						if(tfont16[k].Msk[i]&(0x80>>j))	LCD_DrawPoint(x,y);//��һ����
						x++;
						if((x-x0)==16)
						{
							x=x0;
							y++;
							break;
						}
					}

				}

			}


		}
		continue;  //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
	}

	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//�ָ�����Ϊȫ��
}
*/
/*****************************************************************************
 * @name       :void GUI_DrawFont24(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode)
 * @date       :2018-08-09
 * @function   :Display a single 24x24 Chinese character
 * @parameters :x:the bebinning x coordinate of the Chinese character
                y:the bebinning y coordinate of the Chinese character
								fc:the color value of Chinese character
								bc:the background color of Chinese character
								s:the start address of the Chinese character
								mode:0-no overlying,1-overlying
 * @retvalue   :None
******************************************************************************/
/*
void GUI_DrawFont24(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode)
{
	u8 i,j;
	u16 k;
	u16 HZnum;
	u16 x0=x;
	HZnum=sizeof(tfont24)/sizeof(typFNT_GB24);	//�Զ�ͳ�ƺ�����Ŀ

			for (k=0;k<HZnum;k++)
			{
			  if ((tfont24[k].Index[0]==*(s))&&(tfont24[k].Index[1]==*(s+1)))
			  { 	LCD_SetWindows(x,y,x+24-1,y+24-1);
				    for(i=0;i<24*3;i++)
				    {
							for(j=0;j<8;j++)
							{
								if(!mode) //�ǵ��ӷ�ʽ
								{
									if(tfont24[k].Msk[i]&(0x80>>j))	Lcd_WriteData_16Bit(fc);
									else Lcd_WriteData_16Bit(bc);
								}
							else
							{
								POINT_COLOR=fc;
								if(tfont24[k].Msk[i]&(0x80>>j))	LCD_DrawPoint(x,y);//��һ����
								x++;
								if((x-x0)==24)
								{
									x=x0;
									y++;
									break;
								}
							}
						}
					}


				}
				continue;  //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
			}

	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//�ָ�����Ϊȫ��
}
*/
/*****************************************************************************
 * @name       :void GUI_DrawFont32(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode)
 * @date       :2018-08-09
 * @function   :Display a single 32x32 Chinese character
 * @parameters :x:the bebinning x coordinate of the Chinese character
                y:the bebinning y coordinate of the Chinese character
								fc:the color value of Chinese character
								bc:the background color of Chinese character
								s:the start address of the Chinese character
								mode:0-no overlying,1-overlying
 * @retvalue   :None
******************************************************************************/
/*
void GUI_DrawFont32(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode)
{
	u8 i,j;
	u16 k;
	u16 HZnum;
	u16 x0=x;
	HZnum=sizeof(tfont32)/sizeof(typFNT_GB32);	//�Զ�ͳ�ƺ�����Ŀ
	for (k=0;k<HZnum;k++)
			{
			  if ((tfont32[k].Index[0]==*(s))&&(tfont32[k].Index[1]==*(s+1)))
			  { 	LCD_SetWindows(x,y,x+32-1,y+32-1);
				    for(i=0;i<32*4;i++)
				    {
						for(j=0;j<8;j++)
				    	{
							if(!mode) //�ǵ��ӷ�ʽ
							{
								if(tfont32[k].Msk[i]&(0x80>>j))	Lcd_WriteData_16Bit(fc);
								else Lcd_WriteData_16Bit(bc);
							}
							else
							{
								POINT_COLOR=fc;
								if(tfont32[k].Msk[i]&(0x80>>j))	LCD_DrawPoint(x,y);//��һ����
								x++;
								if((x-x0)==32)
								{
									x=x0;
									y++;
									break;
								}
							}
						}
					}


				}
				continue;  //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
			}

	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//�ָ�����Ϊȫ��
}
*/
/*****************************************************************************
 * @name       :void Show_Str(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size,u8 mode)
 * @date       :2018-08-09
 * @function   :Display Chinese and English strings
 * @parameters :x:the bebinning x coordinate of the Chinese and English strings
                y:the bebinning y coordinate of the Chinese and English strings
								fc:the color value of Chinese and English strings
								bc:the background color of Chinese and English strings
								str:the start address of the Chinese and English strings
								size:the size of Chinese and English strings
								mode:0-no overlying,1-overlying
 * @retvalue   :None
******************************************************************************/
void Show_Str(u16 x, u16 y, u16 fc, u16 bc, char *str,u8 size,u8 mode)
{
	u16 x0=x;
  	u8 bHz=0;     //�ַ���������
    while(*str!=0)//����δ����
    {
        if(!bHz)
        {
			if(x>(lcddev.width-size/2)||y>(lcddev.height-size))
			return;
	        if(*str>0x80)bHz=1;//����
	        else              //�ַ�
	        {
		        if(*str==0x0D)//���з���
		        {
		            y+=size;
					x=x0;
		            str++;
		        }
		        else
				{
					if(size>16)//�ֿ���û�м���12X24 16X32��Ӣ������,��8X16����
					{
					LCD_ShowChar(x,y,fc,bc,*str,16,mode);
					x+=8; //�ַ�,Ϊȫ�ֵ�һ��
					}
					else
					{
					LCD_ShowChar(x,y,fc,bc,*str,size,mode);
					x+=size/2; //�ַ�,Ϊȫ�ֵ�һ��
					}
				}
				str++;

	        }
        }else//����
        {
			if(x>(lcddev.width-size)||y>(lcddev.height-size))
			return;
            bHz=0;//�к��ֿ�


	        str+=2;
	        x+=size;//��һ������ƫ��
        }
    }
}


/*****************************************************************************
 * @name       :void Gui_StrCenter(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size,u8 mode)
 * @date       :2018-08-09
 * @function   :Centered display of English and Chinese strings
 * @parameters :x:the bebinning x coordinate of the Chinese and English strings
                y:the bebinning y coordinate of the Chinese and English strings
								fc:the color value of Chinese and English strings
								bc:the background color of Chinese and English strings
								str:the start address of the Chinese and English strings
								size:the size of Chinese and English strings
								mode:0-no overlying,1-overlying
 * @retvalue   :None
******************************************************************************/
void Gui_StrCenter(u16 x, u16 y, u16 fc, u16 bc, char *str,u8 size,u8 mode)
{
	u16 len=strlen((const char *)str);
	u16 x1=(lcddev.width-len*8)/2;
	Show_Str(x1,y,fc,bc,str,size,mode);
}

/*****************************************************************************
 * @name       :void Gui_Drawbmp16(u16 x,u16 y,const unsigned char *p)
 * @date       :2018-08-09
 * @function   :Display a 16-bit BMP image
 * @parameters :x:the bebinning x coordinate of the BMP image
                y:the bebinning y coordinate of the BMP image
								p:the start address of image array
 * @retvalue   :None
******************************************************************************/
void Gui_Drawbmp16(u16 x,u16 y,const unsigned char *p) //��ʾ40*40 QQͼƬ
{
  	int i;
	unsigned char picH,picL;
	LCD_SetWindows(x,y,x+40-1,y+40-1);//��������
    for(i=0;i<40*40;i++)
	{
	 	picL=*(p+i*2);	//���ݵ�λ��ǰ
		picH=*(p+i*2+1);
		Lcd_WriteData_16Bit(picH<<8|picL);
	}
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//�ָ���ʾ����Ϊȫ��
}


void LCD_DrawPage1(void){
	char *top = "StartTech Incorporation";
	char *b1 = "Temp. Set: ";
	char *b2 = "Hot Water: ";
	char *b3 = "Term. Water: ";
	char *b4 = "Valve Opening: ";
	char *b6 = "New Temp: ";

	Show_Str(40, 10, BLACK, WHITE, top, 16, 1);
	Show_Str(5, 50, BLACK, WHITE, b1, 12, 1);
	Show_Str(5, 70, BLACK, WHITE, b2, 12, 1);
	Show_Str(5, 90, BLACK, WHITE, b3, 12, 1);
	Show_Str(5, 110, BLACK, WHITE, b4, 12, 1);
	Show_Str(110, 130, BLACK, WHITE, b6, 12, 1);
	LCD_DrawKeyPad();
}

void LCD_DrawKeyPad(void){
	char *name = "Temperature Control";
	char *b1 = "1", *b2 = "2", *b3 = "3", *b4 = "4", *b5 = "5", *b6 = "6", *b7 = "7", *b8 = "8", *b9 = "9", *b0 = "0", *clr = "CLR", *set = "SET";
	//char *start = "START", *stop = "STOP";
	LCD_Fill(keypad.name[0], keypad.name[2], keypad.name[1], keypad.name[3], keypad.name[4]);
	Show_Str((keypad.name[0] + ((keypad.name[1] - keypad.name[0]) - strlen(name)*5)/4), (keypad.name[2]+ 3), BLACK, WHITE, name, 16, 1);

	LCD_Fill(keypad.b1[0], keypad.b1[2], keypad.b1[1], keypad.b1[3], keypad.b1[4]);
	Show_Str((keypad.b1[0] + ((keypad.b1[1] - keypad.b1[0]) - strlen(b1)*5)/2), (keypad.b1[2]+ 5), BLACK, WHITE, b1, 16, 1);

	LCD_Fill(keypad.b2[0], keypad.b2[2], keypad.b2[1], keypad.b2[3], keypad.b2[4]);
	Show_Str((keypad.b2[0] + ((keypad.b2[1] - keypad.b2[0]) - strlen(b2)*5)/2), (keypad.b2[2]+ 5), BLACK, WHITE, b2, 16, 1);

	LCD_Fill(keypad.b3[0], keypad.b3[2], keypad.b3[1], keypad.b3[3], keypad.b3[4]);
	Show_Str((keypad.b3[0] + ((keypad.b3[1] - keypad.b3[0]) - strlen(b3)*5)/2), (keypad.b3[2]+ 5), BLACK, WHITE, b3, 16, 1);

	LCD_Fill(keypad.b4[0], keypad.b4[2], keypad.b4[1], keypad.b4[3], keypad.b4[4]);
	Show_Str((keypad.b4[0] + ((keypad.b4[1] - keypad.b4[0]) - strlen(b4)*5)/2), (keypad.b4[2]+ 5), BLACK, WHITE, b4, 16, 1);

	LCD_Fill(keypad.b5[0], keypad.b5[2], keypad.b5[1], keypad.b5[3], keypad.b5[4]);
	Show_Str((keypad.b5[0] + ((keypad.b5[1] - keypad.b5[0]) - strlen(b5)*5)/2), (keypad.b5[2]+ 5), BLACK, WHITE, b5, 16, 1);

	LCD_Fill(keypad.b6[0], keypad.b6[2], keypad.b6[1], keypad.b6[3], keypad.b6[4]);
	Show_Str((keypad.b6[0] + ((keypad.b6[1] - keypad.b6[0]) - strlen(b6)*5)/2), (keypad.b6[2]+ 5), BLACK, WHITE, b6, 16, 1);

	LCD_Fill(keypad.b7[0], keypad.b7[2], keypad.b7[1], keypad.b7[3], keypad.b7[4]);
	Show_Str((keypad.b7[0] + ((keypad.b7[1] - keypad.b7[0]) - strlen(b7)*5)/2), (keypad.b7[2]+ 5), BLACK, WHITE, b7, 16, 1);

	LCD_Fill(keypad.b8[0], keypad.b8[2], keypad.b8[1], keypad.b8[3], keypad.b8[4]);
	Show_Str((keypad.b8[0] + ((keypad.b8[1] - keypad.b8[0]) - strlen(b8)*5)/2), (keypad.b8[2]+ 5), BLACK, WHITE, b8, 16, 1);

	LCD_Fill(keypad.b9[0], keypad.b9[2], keypad.b9[1], keypad.b9[3], keypad.b9[4]);
	Show_Str((keypad.b9[0] + ((keypad.b9[1] - keypad.b9[0]) - strlen(b9)*5)/2), (keypad.b9[2]+ 5), BLACK, WHITE, b9, 16, 1);

	LCD_Fill(keypad.clr[0], keypad.clr[2], keypad.clr[1], keypad.clr[3], keypad.clr[4]);
	Show_Str((keypad.clr[0] + ((keypad.clr[1] - keypad.clr[0]) - strlen(clr)*5)/3), (keypad.clr[2]+ 5), BLACK, WHITE, clr, 16, 1);

	LCD_Fill(keypad.b0[0], keypad.b0[2], keypad.b0[1], keypad.b0[3], keypad.b0[4]);
	Show_Str((keypad.b0[0] + ((keypad.b0[1] - keypad.b0[0]) - strlen(b0)*5)/2), (keypad.b0[2]+ 5), BLACK, WHITE, b0, 16, 1);

	LCD_Fill(keypad.set[0], keypad.set[2], keypad.set[1], keypad.set[3], keypad.set[4]);
	Show_Str((keypad.set[0] + ((keypad.set[1] - keypad.set[0]) - strlen(set)*5)/3), (keypad.set[2]+ 5), BLACK, WHITE, set, 16, 1);

}



void LCD_UpdateTemperature(DS18B20 *sensor, float temperature){
	if(temperature != sensor->temperature){
		sensor->temperature = temperature;
		switch (sensor->pos){
			case 5:
				//LCD_UpdateColdWater(temperature);
				break;
			case 6:
				LCD_UpdateHotWater(temperature);
				break;
			case 7:
				LCD_UpdateTerminalWater(temperature);
				break;
		}
	}
	return;
}

void LCD_UpdateTempSet(float temp){
	char num[30];
	int integer = (int)temp;
	int decimal = (int)((temp - integer)*10000);
	sprintf(num, "%d.%d *C", integer, decimal);
	LCD_Fill(90, 50, 12*12+90, 69, WHITE);
	Show_Str(90, 50, BLACK, WHITE, num, 12, 1);
}

void LCD_UpdateHotWater(float temp){
	char num[30];
	int integer = (int)temp;
	int decimal = (int)((temp - integer)*10000);
	LCD_Fill(90, 70, 12*12+90, 89, WHITE);
	sprintf(num, "%d.%d *C", integer, decimal);
	Show_Str(90, 70, BLACK, WHITE, num, 12, 1);
}

void LCD_UpdateTerminalWater(float temp){
	char num[30];
	int integer = (int)temp;
	int decimal = (int)((temp - integer)*10000);
	LCD_Fill(90, 90, 12*12+90, 109, WHITE);
	sprintf(num, "%d.%d *C", integer, decimal);
	Show_Str(90, 90, BLACK, WHITE, num, 12, 1);
}

void LCD_UpdateOpening(int steps){
	char num[30];
	LCD_Fill(5, 110, 130, 129, WHITE);
	sprintf(num, "%d", steps);
	Show_Str(5, 110, BLACK, WHITE, num, 12, 1);
}

void LCD_UpdateTypedTemp(char *c){
	LCD_Fill(190, 130, 240, 145, WHITE);
	Show_Str(190, 130, BLACK, WHITE, c, 12, 1);
}
























