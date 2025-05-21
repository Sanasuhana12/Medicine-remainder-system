#include "types.h"
#include <LPC21xx.h>
#include "lcd_defines.h"
#include "defines.h"
#include "delay.h"
void WriteLCD(u8 byte)
{

	SCLRBIT(IOCLR0,LCD_RW);
	WRITEBYTE(IOPIN0,LCD_DATA,byte);
	SSETBIT(IOSET0,LCD_EN);
	delay_us(1);
	SCLRBIT(IOCLR0,LCD_EN);
	delay_ms(2);
}

void CmdLCD(u8 cmd)
{ 
	SCLRBIT(IOCLR0,LCD_RS);	
	WriteLCD(cmd);
}

void InitLCD(void)
{
  WRITEBYTE(IODIR0,LCD_DATA,0XFF);
  SETBIT(IODIR0,LCD_RS);
  SETBIT(IODIR0,LCD_RW);
  SETBIT(IODIR0,LCD_EN);
	delay_ms(15);
	CmdLCD(0x30);
	delay_ms(1);
	CmdLCD(0x30);
	delay_us(100);
	CmdLCD(0x30);
	CmdLCD(MODE_8BIT_2LINE);
	CmdLCD(DSP_ON_CUR_BLINK);	
	CmdLCD(CLEAR_LCD);	
	CmdLCD(SHIFT_CUR_RIGHT);
}

void CharLCD(u8 asciiVal)
{
	SSETBIT(IOSET0,LCD_RS);	
	WriteLCD(asciiVal);
}	

void SetCursor(u8 lineNo,u8 pos)
{
	if(lineNo==1)
		CmdLCD(GOTO_LINE1_POS0+pos);
	else if(lineNo==2)
		CmdLCD(GOTO_LINE2_POS0+pos);
	else if(lineNo==3)
		CmdLCD(GOTO_LINE3_POS0+pos);
	else if(lineNo==4)
		CmdLCD(GOTO_LINE4_POS0+pos);
}	

void StrLCD(s8 *str)
{
	while(*str)
		CharLCD(*str++);
}
void U32LCD(u32 num)
{
	u8 a[10];
	s32 i=0;
	if(num==0)
	{
		CharLCD('0');
	}
	else
	{
		while(num)
		{
			a[i++] = (num%10)+48;
			num = num/10;
		}
		for(--i;i>=0;i--)
			CharLCD(a[i]);	
	}
}

void S32LCD(s32 num)
{
	if(num<0)
	{
		
		CharLCD('-');		
		num=-num;		
	}
	U32LCD(num);	
}

void F32LCD(f32 fNum,u32 nDP)
{
	s32 iNum;
	if(fNum<0.0)
	{
		CharLCD('-');		
		fNum = -fNum;	
	}	
	iNum = fNum;	
	U32LCD(iNum);
	CharLCD('.');
	while(nDP)
	{
		fNum = (fNum-iNum)*10;
		iNum = fNum;
		CharLCD(iNum+0x30);
		nDP--;
	}
}
void BuildCGRAM(u8 *p,u8 num)
{
	u32 i;
	CmdLCD(0x40);	
	for(i=0;i<num;i++)
	{
		CharLCD(p[i]);		
	}
	CmdLCD(0x80);
}

