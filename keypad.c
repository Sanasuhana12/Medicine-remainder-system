#include <LPC21xx.H>

#include "types.h"
#include "keypad_defines.h"
#include "lcd_defines.h"
#include "defines.h"
#include "lcd.h"

/*
unsigned char keypad_lut[4][4] = {'7','8','9','/',
																	'4','5','6','*',
																	'1','2','3','-',
																	'C','0','=','+'};																	
*/
unsigned int keypad_lut[4][4] = {7,8,9,11,
																	4,5,6,12,
																	1,2,3,13,
																	14,0,15,16};
																	
void Keypad_Init(void)																	
{
	
	 IODIR1 |= (0xF << ROWS);   // Configure pins for rows as output (P1.16 - P1.19)
   IOCLR1 |= (0xF<< ROWS);
	//configuring the rows port pins as output port pins	
	//WRITENIBBLE(IODIR1,ROW0,15);
	//WRITENIBBLE(IOCLR1,COL0,15);
	//WRITENIBBLE(IOSET1,ROW0,15);
	
}


u32 ColScan(void)
{
	return (READNIBBLE(IOPIN1,COL0)<15)?0:1;	
}

u32 RowCheck(void)
{
	u32 rNo;
	//row0 identification
	for(rNo=0;rNo<=3;rNo++)
	{
		//WRITENIBBLE(IOPIN1,ROW0,rowno[rNo]);
		WRITENIBBLE(IOPIN1,ROW0,((1<<rNo)^15));
		if(ColScan() == 0)
			break;		
	}
	return rNo;
}

u32 ColCheck(void)
{
	u32 cNo;
	//columns identification process
	for(cNo=0;cNo<=3;cNo++)
	{
		if(READBIT(IOPIN1,(COL0+cNo)) == 0)
			break;
	}	
	return cNo;
}

u32 KeyDetect(void)
{
	u32 rowval,colval;
	
	IOCLR1 = ((1<<ROW0)|(1<<ROW1)|(1<<ROW2)|(1<<ROW3));
	
	while(ColScan()); //waiting for switch press
	
	rowval = RowCheck(); //row identification process
	
	colval = ColCheck(); //columns identification process
	
	while(!ColScan());  //waiting for switch release
	
	return keypad_lut[rowval][colval];	
}

/*
s32 ReadNum(void)
{
	s32 KeyC;
	u32 num=0;
	
		//CmdLCD(CLEAR_LCD);
			KeyC = KeyDetect();
		
			if((KeyC >= 0) && (KeyC<=9))
			{
				num = (num*10) + (KeyC);
			}
			
			else if(KeyC == 14)//for backspace
			{
				if(num>0)
				{
					num = num/10;
					CmdLCD(SHIFT_CUR_LEFT);
					CharLCD(' ');
					CmdLCD(SHIFT_CUR_LEFT);
				}
			}	
			
				
			if(KeyC == 15)
				{
					return num;
				}
	return -1;	
}
*/





