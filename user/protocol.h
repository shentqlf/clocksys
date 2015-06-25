#ifndef __PROTOCOL_H
#define __PROTOCOL_H
#include "uartx.h"
#define NEED_$ 0
#define NEED_G 1
#define NEED_N 2
#define NEED_R 3
#define NEED_M 4
#define NEED_C 5
#define MSG_GNRMC 7

#define MSG_OK		0XF0
#define MSG_NUM 20



#include "ebox.h"


 
class PROTBD
{
	private:
		uint8_t _count;
		uint8_t _msgcount;
		uint8_t _status;
	



		
	public:
		
		uint32_t lastchartime;
		uint8_t BDNum;
		uint8_t GPSNum;
		uint8_t starNum;
		uint8_t used;
	

		char msg[MSG_NUM][256];
		char msgRMC[256];




	public:
		PROTBD()
		{
			clearAll();
		}		
		uint8_t deal(char c);
	
		uint8_t updateStarNum(void);
		
		uint8_t cpymsgTomsgRMC(void)
		{
			for(int i = 0; i < 256; i++)
				msgRMC[i] = msg[0][i];
			return 0;
		}
		uint8_t cpyStrBeforeDot(char * sStr,char * tStr,uint8_t endDotNum);
		
		
		uint8_t getBDstarNum(void);
		
		uint8_t getGPSstarNum(void);
		
		uint8_t getstarNum(void);
		
		uint8_t isEnd(void);
		
		void clearAll()
		{
			_count = 0;
			_msgcount = 0;
			_status = NEED_$;
			for(int i = 0; i < MSG_NUM; i ++)
				for(int j = 0; j < 256; j++)
					msg[i][j] = '\0';
		}

};
extern class PROTBD protBD;
#endif
