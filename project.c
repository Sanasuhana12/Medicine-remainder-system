#include <LPC21xx.H>
#include "rtc.h"
#include "rtc_defines.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "keypad.h"
#include "keypad_defines.h"
#include "delay.h"
#include "defines.h"
#include "proj.h"
#define sw1 23


s32 keyc;

int main()
{
        InitLCD();
        RTC_Init();
				Keypad_Init();
				Init_Buzzer();
	
				CmdLCD(DSP_ON_CUR_OFF);
				CmdLCD(0x01);
				StrLCD("MEDICINE REMIND");
				CmdLCD(0xC4);
				StrLCD("SYSTEM");
				delay_ms(500);
				CmdLCD(0x01);
	
			RTCsetTime(04,30,00);
			RTCSetDate(10,02,2025);
			RTCSetDay(1);
	
				while(1)
				{
					CmdLCD(0x80);
					clk();
					if((READBIT(IOPIN0,sw1))==0)
					{
						CmdLCD(0x01);	
						while(1)
						{
							CmdLCD(0x80);
							StrLCD("1.RTC EDIT");
							CmdLCD(0xc0);
							StrLCD("2.M.T UPDATE");
							CmdLCD(0x94);
							StrLCD("3.BACK");
							//delay_ms(500);
							keyc=KeyDetect();
							switch(keyc)
							{						
									case 1:RTC_submenu();
												CmdLCD(0x01);
												break;
									case 2:Med_Time_submenu();
													break;
									case 3:break;
							}
							CmdLCD(0x01);	
						  break;
						}
				}
				alarm();
			}
				
}
