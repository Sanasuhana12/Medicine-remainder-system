#include "types.h"

void RTC_Init(void);

void RTCGETTime(u32 *,u32 *,u32*);
void DisplayRTCTime(u32,u32,u32);

void RTCGetDate(u32 *,u32 *,u32 *);
void DisplayRTCDate(u32,u32,u32);

void RTCDay(u32 *);
void DispalyRTCDay(u32);

void RTCsetTime(u32,u32,u32);
void RTCSetDate(u32,u32,u32);

void RTCSetDay(u32);



