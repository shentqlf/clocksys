#include "protocol.h"

uint8_t PROTBD::deal(char c)
{
	lastchartime = millis();
	switch(_status)
	{
		case NEED_$:
					if(c == '$')
					{
						msg[_msgcount][_count] = c;
						_status = NEED_G;
						_count ++;
					}
					else
					{
						_status = NEED_$;
						_count = 0;		
						_msgcount = 0;
					}
					break;
		case NEED_G:
					if(c == 'G')
					{
						msg[_msgcount][_count] = c;
						_status = NEED_N;
						_count ++;
					}
					else
					{
						_status = NEED_$;
						_count = 0;	
						_msgcount = 0;						
					}
					break;			
		case NEED_N:
					if(c == 'N')
					{
						msg[_msgcount][_count] = c;
						_status = NEED_R;
						_count ++;
					}
					else
					{
						_status = NEED_$;
						_count = 0;	
						_msgcount = 0;												
					}
					break;			
		case NEED_R:
					if(c == 'R')
					{
						msg[_msgcount][_count] = c;
						_status = NEED_M;
						_count ++;
					}
					else
					{
						_status = NEED_$;
						_count = 0;	
						_msgcount = 0;												
					}
					break;			
		case NEED_M:
					if(c == 'M')
					{
						msg[_msgcount][_count] = c;
						_status = NEED_C;
						_count ++;
						
					}
					else
					{
						_status = NEED_$;
						_count = 0;	
						_msgcount = 0;						
						
					}
					break;			
		case NEED_C:
					if(c == 'C')
					{
						msg[_msgcount][_count] = c;
						_status = MSG_GNRMC;
						_count ++;
					}
					else
					{
						_status = NEED_$;
						_count = 0;	
						_msgcount = 0;												
					}
					break;			
	
		case MSG_GNRMC:
				msg[_msgcount][_count++] = c;
				if(msg[_msgcount][_count - 1] == '\n')
				{
					_msgcount++;
					_count = 0;
					if(_msgcount == MSG_NUM)_msgcount  = 0;
				}
				break;
	}

	return _status;
};

uint8_t PROTBD::updateStarNum(void)
{											

		char GPSStr[20];
		char BDStr[20];	
	uint8_t dateln;
	for(int i = 0;i < _msgcount; i ++)
	{
		if((msg[i][1] == 'B') &&(msg[i][2] == 'D') &&(msg[i][3] == 'G') &&(msg[i][4] == 'S') &&(msg[i][5] == 'V'))
		{
			dateln = cpyStrBeforeDot(msg[i],BDStr,4);
			if(dateln == 1)
				BDNum = BDStr[0] - 0X30;
			else
				BDNum = (BDStr[0]-0X30) *10 + (BDStr[1] - 0X30);
			break;
		}
	}	
	
	for(int i = 0;i < _msgcount; i ++)
	{
		if((msg[i][1] == 'G') &&(msg[i][2] == 'P') &&(msg[i][3] == 'G') &&(msg[i][4] == 'S') &&(msg[i][5] == 'V'))
		{
			dateln = cpyStrBeforeDot(msg[i],GPSStr,4);
			if(dateln == 1)
			 GPSNum= GPSStr[0] - 0X30;
			else
			 GPSNum= (GPSStr[0]-0X30) *10 + (GPSStr[1] - 0X30);
			break;
		}
	}

	starNum = GPSNum + BDNum;
	return 0;
}

uint8_t PROTBD::cpyStrBeforeDot(char * sStr,char* tStr,uint8_t endDotNum)
{
	uint8_t t = 0;
	char msgok = 0;
	uint8_t dotNum = 0;

	if(*sStr++ == '$') 
		msgok = 1;
	else
		return 0;
	if(msgok)
	{
		while(*sStr != '\0')
		{
			tStr[t++] = *sStr++;
			if(*sStr == ',')
			{
				tStr[t++] = *sStr++;
				tStr[--t]='\0';
				dotNum++;
				if(dotNum == endDotNum)
				{
					return t;
				}
				t=0;
			}
		}
	}
	*tStr++ = 0;
	return 0;
}



uint8_t PROTBD::isEnd(void)
{
	uint8_t end = 0;
		if((millis() - lastchartime > 1) && (_status == MSG_GNRMC))//如果1ms内没有新的数据认为结束
		{
			end = 1;
		}
		return end;
}

class PROTBD protBD;
