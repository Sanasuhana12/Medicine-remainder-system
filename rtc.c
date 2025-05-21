#include <LPC21xx.H>
#include "delay.h"
#include "rtc_defines.h"
#include "rtc.h"
#include "types.h"
#include "lcd.h"
#include "keypad.h"



s8 week[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};

void RTC_Init(void)
{
        CCR = RTC_CTC_RESET;
        PREINT = PREINT_val;
        PREFRAC = PREFRAC_val;
        CCR = RTC_CCR_EN | RTC_CLKSRC;
}

void RTCGETTime(u32 *hr,u32 *min,u32 *sec)
{
        *hr = HOUR;
        *min = MIN;
        *sec = SEC; 
}

void DisplayRTCTime(u32 hr,u32 min,u32 sec)
{
        SetCursor(1,0);
        CharLCD((hr/10)+48);
        CharLCD((hr%10)+48);
				CharLCD(':');
        CharLCD((min/10)+48);
        CharLCD((min%10)+48);
        CharLCD(':');
        CharLCD((sec/10)+48);
        CharLCD((sec%10)+48);
}

void RTCGetDate(u32 *date,u32 *month,u32 *year)
{
        *date = DOM;
        *month = MONTH;
        *year = YEAR;
}

void DisplayRTCDate(u32 date,u32 month,u32 year)
{
        SetCursor(2,0);
        CharLCD((date/10)+48);
        CharLCD((date%10)+48);
        CharLCD('/');
        CharLCD((month/10)+48);
        CharLCD((month%10)+48);
        CharLCD('/');
        U32LCD(year); 
}

void RTCDay(u32 *day)
{
        *day = DOW;
}
void DispalyRTCDay(u32 day)
{
        SetCursor(1,10);
        StrLCD(week[day]);      
}

void RTCsetTime(u32 hr,u32 min,u32 sec)
{
        HOUR = hr;
        MIN = min;
        SEC = sec;
}
void RTCSetDate(u32 date,u32 month,u32 year)
{
        DOM = date;
        MONTH = month;
        YEAR = year;
}
void RTCSetDay(u32 day)
{
        DOW = day;
}
