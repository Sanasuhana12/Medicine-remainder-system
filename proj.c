#include <LPC21xx.H>
#include "proj.h"
#include "types.h"
#include "rtc.h"
#include "lcd.h"
#include "keypad.h"
#include "delay.h"
#include "rtc_defines.h"
#include "lcd_defines.h"

#define BUZZER 26
#define sw2 24

u32 hr,min,sec,day,date,month,year;
s32 hour1=-1,min1=-1,sec1;
void Init_Buzzer(void)
{
	IODIR1|=1<<BUZZER;
}

void Buzzer_NO(void)
{
	IOSET1=1<<BUZZER;
}

void Buzzer_OFF(void)
{
	IOCLR1=1<<BUZZER;
}



void clk()
{
        RTCGETTime(&hr,&min,&sec);
        DisplayRTCTime(hr,min,sec);
				RTCGetDate(&date,&month,&year);
        DisplayRTCDate(date,month,year);
        RTCDay(&day);
        DispalyRTCDay(day);
}

void hour(u32 *hr)
{
	s32 num,res=0;
	int position=0;
	CmdLCD(0x01);
	while(1)
	{
		//CmdLCD(0x01);
		SetCursor(1,0);
		StrLCD("EDIT HOUR:");
		num=KeyDetect();
		if(num!=14 && num!=15 )
		{
		res=(res*10)+num;
			U32LCD(res);
			position++;
		}
		SetCursor(2,8);
		StrLCD("=:SAVE");
		if(num==14 && res>0)
			{ 
				res=res/10;
				if(position>0)
				{
					SetCursor(1,10+ position);
					CmdLCD(SHIFT_CUR_LEFT);
					CharLCD(' ');
					SetCursor(1,10+ position);
					CmdLCD(SHIFT_CUR_LEFT);
					position--;
					//delay_ms(500);
				}
			}
		else if(num==14)
			{ 
				return;
			}
			else if(num==15 && res<=23)
			{
				HOUR=res;
				return;
			}
			else if (res==24 && num==15)
			{
				HOUR=0;
				return;
			}
		else if(res>24 && num==15)
		{
			CmdLCD(0X01);
			SetCursor(2,5);
			StrLCD("ERROR");
			SetCursor(3,8);
			StrLCD("OUT OF RANGE");
			delay_s(1);
			CmdLCD(0X01);
			res=0;
		}
		
	}

}


void minute(u32 *min)
{
	s32 num,res=0;
	int position=0;
	CmdLCD(0x01);
	while(1)
	{
		//CmdLCD(0x01);
		SetCursor(1,0);
		StrLCD("EDIT MIN:");
		num=KeyDetect();
		if(num!=14 && num!=15 )
		{
		res=(res*10)+num;
			U32LCD(res);
			position++;
		}
		SetCursor(2,8);
		StrLCD("=:SAVE");
		if(num==14 && res>0)
			{ 
				res=res/10;
				if(position>0)
				{
					SetCursor(1,9+ position);
					CmdLCD(SHIFT_CUR_LEFT);
					CharLCD(' ');
					SetCursor(1,9+ position);
					CmdLCD(SHIFT_CUR_LEFT);
					position--;
				}
			}
		else if(num==14)
			{ 
				
				return;
			}
			else if(num==15 && res<=59)
			{
				MIN=res;
				return;
			}
			else if(res==59 && num==15)
			{
				MIN=0;
				return;
			}
		else if(res>60 && num==15)
		{
				CmdLCD(0X01);
				SetCursor(2,8);
				StrLCD("ERROR");
				SetCursor(3,8);
				StrLCD("OUT OF RANGE");
				delay_s(1);
				CmdLCD(0X01);
				res=0;
		}
		
	}

}


void second(u32 *sec)
{
	s32 num,res=0;
	int position=0;
	CmdLCD(0x01);
	while(1)
	{
		//CmdLCD(0x01);
		SetCursor(1,0);
		StrLCD("EDIT sec:");
		num=KeyDetect();
		if(num!=14 && num!=15 )
		{
		res=(res*10)+num;
			U32LCD(res);
			position++;
		}
		SetCursor(2,8);
				StrLCD("=:SAVE");
		if(num==14 && res>0)
			{ 
				res=res/10;
				if(position>0)
				{
					SetCursor(1,10+ position);
					CmdLCD(SHIFT_CUR_LEFT);
					CharLCD(' ');
					SetCursor(1,10+ position);
					CmdLCD(SHIFT_CUR_LEFT);
					position--;
				}
			}
		else if(num==14)
			{ 
				
				return;
			}
			else if(num==15 && res<=59)
			{
				SEC=res;
				return;
			}
			else if(res==59 && num==15)
			{
				SEC=0;
				return;
			}
		else if(res>60 && num==15)
		{
				CmdLCD(0X01);
				SetCursor(2,8);
				StrLCD("ERROR");
				SetCursor(3,8);
				StrLCD("OUT OF RANGE");
				delay_s(1);
				CmdLCD(0X01);
				res=0;
		}
		
	}

}


void days(u32 *day)
{
	s32 num,res=0;
	int position=0;
	CmdLCD(0x01);
	while(1)
	{
		//CmdLCD(0x01);
		SetCursor(1,0);
		StrLCD("EDIT DAY:");
		num=KeyDetect();
		if(num!=14 && num!=15 )
		{
		res=(res*10)+num;
			U32LCD(res);
			position++;
		}
		SetCursor(2,8);
				StrLCD("=:SAVE");
		if(num==14 && res>0)
			{ 
				res=res/10;
				if(position>0)
				{
					SetCursor(1,9+ position);
					CmdLCD(SHIFT_CUR_LEFT);
					CharLCD(' ');
					SetCursor(1,9+ position);
					CmdLCD(SHIFT_CUR_LEFT);
					position--;
				}
			}
		else if(num==14)
			{ 
				
				return;
			}
			else if(num==15 && res<=6)
			{
				DOW=res;
				return;
			}
			else if(res==7 && res==15)
			{
				DOW=0;
				return;
			}
		else if(res>7 && num==15)
		{
				CmdLCD(0X01);
				SetCursor(2,8);
				StrLCD("ERROR");
				SetCursor(3,8);
				StrLCD("OUT OF RANGE");
				delay_s(1);
				CmdLCD(0X01);
				res=0;
		}
		
	}

}

void Date(u32 *date)
{
	s32 num,res=0;
	int position=0;
	CmdLCD(0x01);
	while(1)
	{
		//CmdLCD(0x01);
		SetCursor(1,0);
		StrLCD("EDIT DATE:");
		num=KeyDetect();
		if(num!=14 && num!=15 )
		{
		res=(res*10)+num;
			U32LCD(res);
			position++;
		}
		SetCursor(2,8);
		StrLCD("=:SAVE");
		if(num==14 && res>0)
			{ 
				res=res/10;
				if(position>0)
				{
					SetCursor(1,10+ position);
					CmdLCD(SHIFT_CUR_LEFT);
					CharLCD(' ');
					SetCursor(1,10+ position);
					CmdLCD(SHIFT_CUR_LEFT);
					position--;
				}
			}
		else if(num==14)
			{ 
				
				return;
			}
			else if(num==15 && res<=31)
			{
				DOM=res;
				return;
			}
		else if(res>32 && num==15)
		{
				CmdLCD(0X01);
				SetCursor(2,8);
				StrLCD("ERROR");
				SetCursor(3,8);
				StrLCD("OUT OF RANGE");
				delay_s(1);
				CmdLCD(0X01);
				res=0;
		}
		
	}

}
void Month(u32 *month)
{
	s32 num,res=0;
	int position=0;
	CmdLCD(0x01);
	while(1)
	{
		//CmdLCD(0x01);
		SetCursor(1,0);
		StrLCD("EDIT MONTH:");
		num=KeyDetect();
		if(num!=14 && num!=15 )
		{
		res=(res*10)+num;
			U32LCD(res);
			position++;
		}
		SetCursor(2,8);
		StrLCD("=:SAVE");
		if(num==14 && res>0)
			{ 
				res=res/10;
				if(position>0)
				{
					SetCursor(1,11+ position);
					CmdLCD(SHIFT_CUR_LEFT);
					CharLCD(' ');
					SetCursor(1,11+ position);
					CmdLCD(SHIFT_CUR_LEFT);
					position--;
				}
			}
		else if(num==14)
			{ 
				return;
			}
			else if(num==15 && res<=12)
			{
				MONTH=res;
				return;
			}
		else if(res>13 && num==15)
		{
				CmdLCD(0X01);
				SetCursor(2,8);
				StrLCD("ERROR");
				SetCursor(3,8);
				StrLCD("OUT OF RANGE");
				delay_s(1);
				CmdLCD(0X01);
				res=0;
		}
		
	}
}

void Year(u32 *year)
{
	s32 num,res=0;
	int position=0;
	CmdLCD(0x01);
	while(1)
	{
		//CmdLCD(0x01);
		SetCursor(1,0);
		StrLCD("EDIT YEAR:");
		num=KeyDetect();
		if(num!=14 && num!=15 )
		{
			res=(res*10)+num;
			U32LCD(res);
			position++;
		}
		SetCursor(2,8);
		StrLCD("=:SAVE");
		if(num==14 && res>0)
			{ 
				res=res/10;
				if(position>0)
				{
					SetCursor(1,10+ position);
					CmdLCD(SHIFT_CUR_LEFT);
					CharLCD(' ');
					SetCursor(1,10+ position);
					CmdLCD(SHIFT_CUR_LEFT);
					position--;
				}
			}
			else if(num==14)
			{
				return;
			}
			else if(num==15 && res)
			{
				YEAR=res;
				return;
			}
			else if(res>2025)
			{
				CmdLCD(0x01);
				SetCursor(1,0);
				StrLCD("THIS SYSTEM");
				SetCursor(2,0);
				StrLCD("SUPPORTS TILL 2025");
				delay_s(1);
				CmdLCD(0x01);
				res=0;
			}
	}
}


void RTC_submenu(void) 
{
	u32 Key;
	CmdLCD(0x01);
	while(1)
	{
		CmdLCD(0x80);
		StrLCD("1.hr");
		CmdLCD(0xC0);
		StrLCD("2.min");
		CmdLCD(0x94);
		StrLCD("3.sec");
		CmdLCD(0xD4);
		StrLCD("4.day");
		CmdLCD(0x87);
		StrLCD("5.date");
		CmdLCD(0xC7);
		StrLCD("6.month");
		//CmdLCD(0x90);
		SetCursor(3,11);
		StrLCD("7.year");
		//CmdLCD(0xD10);
		SetCursor(4,11);
		StrLCD("8.Exit");
		
		Key=KeyDetect();
		//CmdLCD(0x01);
		switch(Key)
		{
			case 1:hour(&hr);
						break;
			case 2:minute(&min);
						break;
			case 3:second(&sec);
						break;
			case 4:days(&day);
						break;
			case 5:Date(&date);
						break;
			case 6:Month(&month);
						break;
			case 7:Year(&year);
						break;
			case 8:break;
			default:StrLCD("invalid Key");
							break;
		}	
		CmdLCD(0x01);
		
		break;
	}
}
void displaymedtime(u32 hour1,u32 min)
{
        SetCursor(1,0);
        CharLCD((hour1/10)+48);
        CharLCD((hour1%10)+48);
				CharLCD(':');
        CharLCD((min1/10)+48);
        CharLCD((min1%10)+48);
        CharLCD(':');
				CharLCD((sec1/10)+48);
        CharLCD((sec1%10)+48);
	
}
void med_hour(s32 *hour1)
{
	u32 num,res=0;
	int position=0;
	CmdLCD(0x01);
	while(1)
	{
		//CmdLCD(0x01);
		SetCursor(1,0);
		StrLCD("EDIT HOUR:");
		num=KeyDetect();
		if(num!=14 && num!=15 )
		{
		res=(res*10)+num;
			U32LCD(res);
			position++;
		}
		SetCursor(2,8);
				StrLCD("=:SAVE");
		if(num==14 && res>0)
			{ 
				res=res/10;
				if(position>0)
				{
					SetCursor(1,10+ position);
					CmdLCD(SHIFT_CUR_LEFT);
					CharLCD(' ');
					SetCursor(1,10+ position);
					CmdLCD(SHIFT_CUR_LEFT);
					position--;
				}
			}
		else if(num==14)
			{ 
				return;
			}
			else if(num==15 && res<=23)
			{
				*hour1=res;
				return;
			}
			else if (res==24 && num==15)
			{
				*hour1=0;
				return;
			}
		else if(res>24 && num==15)
		{
			CmdLCD(0X01);
			SetCursor(2,5);
			StrLCD("ERROR");
			SetCursor(3,8);
			StrLCD("OUT OF RANGE");
			delay_s(1);
			CmdLCD(0X01);
			res=0;
		}
		
	}
}

void med_min(s32 *min1)
{
	u32 num,res=0;
	int position=0;
	CmdLCD(0x01);
	while(1)
	{
		SetCursor(1,0);
		StrLCD("EDIT MIN:");
		num=KeyDetect();
		if(num!=14 && num!=15 )
		{
		res=(res*10)+num;
			U32LCD(res);
			position++;
		}
		SetCursor(2,8);
				StrLCD("=:SAVE");
		if(num==14 && res>0)
			{ 
				res=res/10;
				if(position>0)
				{
					SetCursor(1,9+ position);
					CmdLCD(SHIFT_CUR_LEFT);
					CharLCD(' ');
					SetCursor(1,9+ position);
					CmdLCD(SHIFT_CUR_LEFT);
					position--;
				}
			}
		else if(num==14)
			{ 
				
				return;
			}
			else if(num==15 && res<=59)
			{
				*min1=res;
				return;
			}
			else if(res==59 && num==15)
			{
				*min1=0;
				return;
			}
		else if(res>60 && num==15)
		{
				CmdLCD(0X01);
				SetCursor(2,8);
				StrLCD("ERROR");
				SetCursor(3,8);
				StrLCD("OUT OF RANGE");
				delay_s(1);
				CmdLCD(0X01);
				res=0;
		}
		
	}
}

void Med_Time_submenu()
{
		s32 num,key;
		CmdLCD(0x01);
		while(1)
			{
				CmdLCD(0x80);
				StrLCD("ENTER M.T: ");
				CmdLCD(0xc0);
				StrLCD("HH:MM:SS");
				num=KeyDetect();
				switch(num)
				{
					case 1:med_hour(&hour1);
					case 2:med_min(&min1);
					break;
				}
				CmdLCD(0x01);
				SetCursor(2,0);
				StrLCD("Time:");
				displaymedtime(hour1,min1);
				CmdLCD(0xc0);
				StrLCD("want to update?");
				//CmdLCD(0x90);
				SetCursor(3,4);
				StrLCD("1.YES 2.NO");
				key=KeyDetect();
				switch(key)
				{
					case 1:CmdLCD(0x01);
								CmdLCD(0xc4);
								StrLCD("UPDATED");
								//CmdLCD(0x92);
								SetCursor(3,6);
								StrLCD("SUCCESSFULLY");
								delay_s(1);
								CmdLCD(0x01);
								CmdLCD(0x80);
								StrLCD("MEDICINE TIME ON");
								delay_s(1);
								break;
					case 2:CmdLCD(0x01);
								continue;
				}
				CmdLCD(0x01);
				break;
		}
}

void alarm(void)
{
	if((HOUR == hour1) && (MIN == min1)) 
	{
		CmdLCD(0x01);
		StrLCD("MEDICINE TIME");
		while(((IOPIN0>>sw2)&1)==1)
		{
			IOSET1=1<<BUZZER;
		}
		
		IOCLR1=1<<BUZZER;
		hour1=-1;
		min1=-1;
		CmdLCD(0x01);
	}
}
