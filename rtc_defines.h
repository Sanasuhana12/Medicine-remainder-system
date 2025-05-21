#ifndef _RTC_DEFINEs_H
#define _RTC_DEFINES_H

#define FOSC 12000000
#define CCLK (5*FOSC)
#define PCLK (CCLK/4)

#define PREINT_val (int)((PCLK/32768)-1)
#define PREFRAC_val PCLK-((PREINT_val+1)*32768)

#define RTC_CCR_EN (1<<0)
#define RTC_CTC_RESET (1<<1)
#define RTC_CLKSRC (1<<4)
#endif

