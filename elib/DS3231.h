#ifndef __DS3231_H__
#define __DS3231_H__

#include "ebox.h"
#include "softi2c.h"
		
#define DS3231_WriteAddress 0xD0    //����д��ַ 
#define DS3231_ReadAddress  0xD1    //��������ַ
#define DS3231_SECOND       0x00    //��
#define DS3231_MINUTE       0x01    //��
#define DS3231_HOUR         0x02    //ʱ
#define DS3231_WEEK         0x03    //����
#define DS3231_DAY          0x04    //��
#define DS3231_MONTH        0x05    //��
#define DS3231_YEAR         0x06    //��
//����1            
#define DS3231_SALARM1ECOND 0x07    //��
#define DS3231_ALARM1MINUTE 0x08    //��
#define DS3231_ALARM1HOUR   0x09    //ʱ
#define DS3231_ALARM1WEEK   0x0A    //����/��
//����2
#define DS3231_ALARM2MINUTE 0x0b    //��
#define DS3231_ALARM2HOUR   0x0c    //ʱ
#define DS3231_ALARM2WEEK   0x0d    //����/��
#define DS3231_CONTROL      0x0e    //���ƼĴ���
#define DS3231_STATUS       0x0f    //״̬�Ĵ���
#define BSY                 2       //æ
#define OSF                 7       //����ֹͣ��־
#define DS3231_XTAL         0x10    //�����ϻ��Ĵ���
#define DS3231_TEMPERATUREH 0x11    //�¶ȼĴ������ֽ�(8λ)
#define DS3231_TEMPERATUREL 0x12    //�¶ȼĴ������ֽ�(��2λ)  
//timer.w_year,timer.w_month,timer.w_date,timer.hour,timer.min,timer.sec
 typedef struct
 {
	 u8 w;
	 u8 year;
	 u8 month;
	 u8 date;
	 u8 hour;
	 u8 min;
	 u8 sec;
	 u8 week;
 }DateTime;

 class DS3231:public Softi2c
 {
	 private:
		uint8_t buf[8];
		uint8_t write_byte(uint8_t addr, uint8_t write_data);
		uint8_t read_current(void);
		uint8_t read_random(uint8_t random_addr);
		uint8_t BcdToDec(uint8_t BCDCode);
		uint8_t DecToBcd(uint8_t Dec);
	 public:
		 DateTime t;
		 DS3231(uint8_t SDApin,uint8_t SCLpin):Softi2c(SDApin,SCLpin){
		 // do nothing;
		 };										
		void readTime(DateTime *t);
		void readTime(char* date,char* time);
		void setTime(DateTime *t);
		void setTime(char* datestr,char* timestr);
 
 };


#endif
