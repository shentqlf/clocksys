#ifndef __CLOCK_H
#define __CLOCK_H
#include "ebox.h"

class CLOCK
{
	public:
		uint8_t year;
		uint8_t mon;
		uint8_t date;
		uint8_t hour;
		uint8_t min;
		uint8_t sec;
	
		uint8_t ayear;
		uint8_t amon;
		uint8_t adate;
		uint8_t ahour;
		uint8_t amin;
		uint8_t asec;
		uint8_t alarmEnable;
	
		void setAlarmClock(uint8_t p1,uint8_t p2,uint8_t p3,uint8_t p4,uint8_t p5,uint8_t p6,uint8_t p7)
		{
			 ayear = p1;
			 amon 	= p2;
			 adate = p3;
			 ahour = p4;
			 amin 	= p5;
			 asec 	= p6;
			// millis = p7;
		};
		uint8_t checkAlarm()
		{
			uint8_t alarm = 0;
			if(alarmEnable == 1)
			{
				if((ayear == year) | (amon == mon) | (adate == date) | (ahour == hour) | (amin == min) | (asec == sec))
					alarm = 1;
				else
					alarm = 0;
			}
			return alarm;
		}
		void setClock(uint8_t p1,uint8_t p2,uint8_t p3,uint8_t p4,uint8_t p5,uint8_t p6,uint8_t p7)
		{
			 year = p1;
			 mon 	= p2;
			 date = p3;
			 hour = p4;
			 min 	= p5;
			 sec 	= p6;
			// millis = p7;
		};
		void setClock(char _date[],char _time[])
		{
			year	= uint8_t ((_date[5]-0x30) + (_date[4]-0x30)*10);
			mon		= uint8_t ((_date[3]-0x30) + (_date[2]-0x30)*10);
			date	= uint8_t ((_date[1]-0x30) + (_date[0]-0x30)*10);
			
			hour	= uint8_t ((_time[0]-0x30)*10 + (_time[1]-0x30));
			min		= uint8_t ((_time[2]-0x30)*10 + (_time[3]-0x30));
			sec		= uint8_t ((_time[4]-0x30)*10 + (_time[5]-0x30));
		};
		void clockAddOneSec()
		{
			if(sec == 59)
			{
				sec = 0;
				if(min == 59)
				{
					min = 0;
					if(hour == 23)
					{
						hour = 0;
					}
					else
					{
						hour ++;
					}		
				}
				else
				{
					min ++;
				}			
			}
			else
			{
				sec ++;
			}
		}
		void getDateStr(char* str)
		{
			str[0] = date/10 + 0x30;
			str[1] = date%10 + 0x30;
			str[2] = mon/10 + 0x30;
			str[3] = mon%10 + 0x30;
			str[4] = year/10 + 0x30;
			str[5] = year%10 + 0x30;
		}
		void getTimeStr(char* str)
		{
			str[0] = hour/10 + 0x30;
			str[1] = hour%10 + 0x30;
			str[2] = min/10 + 0x30;
			str[3] = min%10 + 0x30;
			str[4] = sec/10 + 0x30;
			str[5] = sec%10 + 0x30;
			
			str[10] = '\0';
		}
		void GreenwichToTimeZone(uint8_t TimeZone)
		{
			hour += TimeZone;
			if(hour >= 24)
				hour -= 24;
		}

};

#endif

