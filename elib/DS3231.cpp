
#include "DS3231.h"
	
	

uint8_t DS3231::write_byte(uint8_t addr, uint8_t write_data)
{
		_start();
		_send_byte(DS3231_WriteAddress);
    if (_wait_ack() == 0)
        return 0;
		
		_send_byte(addr);
    if (_wait_ack() == 0)
        return 0;

   
		_send_byte(write_data);
    if (_wait_ack() == 0)
        return 0;
		_stop();

    delay_us(10);      
    return 1;
}
uint8_t DS3231::read_current(void)
{
    unsigned char read_data;
		_start();
		_send_byte(DS3231_ReadAddress);
		if (_wait_ack() == 0)
       return (0);

		read_data = _read_byte();
		_send_no_ack();
		_stop();
    return read_data;
}
uint8_t DS3231::read_random(uint8_t random_addr)
{
		_start();
		_send_byte(DS3231_WriteAddress);
		if (_wait_ack() == 0)
       return (0);
		
		_send_byte(random_addr);
		if (_wait_ack() == 0)
       return (0);
		

    return(read_current());
}

uint8_t DS3231::BcdToDec(uint8_t BCDCode)
{
	u8 temp,Dec;
	temp = (BCDCode >> 4) * 10;
	Dec = (BCDCode & 0x0f) + temp;
	return Dec;
}
uint8_t DS3231::DecToBcd(uint8_t Dec)
{
	u8 temp,temp2,Bcd;
	temp = Dec / 10;
	temp2 = Dec % 10;
	
	Bcd =  (temp << 4) + temp2;
	
	return Bcd;
}

void	DS3231::readTime(DateTime *t)
{
	buf[6]=read_random(DS3231_YEAR);			//年份低两位
	buf[5]=read_random(DS3231_MONTH);	   	//月份
	buf[4]=read_random(DS3231_DAY);		//日期
	buf[3]=read_random(DS3231_WEEK);
	buf[2]=read_random(DS3231_HOUR) & 0x3f;		//时
	buf[1]=read_random(DS3231_MINUTE);		//分
	buf[0]=read_random(DS3231_SECOND);	    	//秒

//	timer.w_year,timer.w_month,timer.w_date,timer.hour,timer.min,timer.sec
/******将读取的十六进制数据转换为十进制数据******/
	t->year 	=BcdToDec(buf[6]);
	t->month	=BcdToDec(buf[5]);
	t->date		=BcdToDec(buf[4]);
	t->week 	=BcdToDec(buf[3]);
	t->hour		=BcdToDec(buf[2]);
	t->min		=BcdToDec(buf[1]);
	t->sec	  =BcdToDec(buf[0]);	
}
void	DS3231::readTime(char* date,char* time)
{
	buf[0]=read_random(DS3231_DAY);		//日期
	buf[1]=read_random(DS3231_MONTH);	   	//月份
	buf[2]=read_random(DS3231_YEAR);			//年份低两位
	buf[3]=read_random(DS3231_HOUR) & 0x3f;		//时
	buf[4]=read_random(DS3231_MINUTE);		//分
	buf[5]=read_random(DS3231_SECOND);	    	//秒
	buf[6]=read_random(DS3231_WEEK);

	date[0] = (buf[0]>>4) 	+ 0x30;
	date[1] = (buf[0]&0x0f) + 0x30;
	date[2] = (buf[1]>>4) 	+ 0x30;
	date[3] = (buf[1]&0x0f) + 0x30;
	date[4] = (buf[2]>>4) 	+ 0x30;
	date[5] = (buf[2]&0x0f) + 0x30;
	

	time[0] = (buf[3]>>4) 	+ 0x30;
	time[1] = (buf[3]&0x0f) + 0x30;
	time[2] = (buf[4]>>4) 	+ 0x30;
	time[3] = (buf[4]&0x0f) + 0x30;
	time[4] = (buf[5]>>4) 	+ 0x30;
	time[5] = (buf[5]&0x0f) + 0x30;
}
void	DS3231::setTime(DateTime *t)
{
		DateTime tBCD;
		tBCD.week = DecToBcd(t->week);
		tBCD.year = DecToBcd(t->year);
		tBCD.month = DecToBcd(t->month);
		tBCD.date = DecToBcd(t->date);
		tBCD.hour = DecToBcd(t->hour);
		tBCD.min = DecToBcd(t->min);
		tBCD.sec = DecToBcd(t->sec);
   
    write_byte(DS3231_WEEK,tBCD.week);   //修改周
		write_byte(DS3231_YEAR,tBCD.year);   //修改年
    write_byte(DS3231_MONTH,tBCD.month);  //修改月
   
    write_byte(DS3231_DAY,tBCD.date);    //修改日 
    write_byte(DS3231_HOUR,tBCD.hour);   //修改时
   
    write_byte(DS3231_MINUTE,tBCD.min); //修改分
   
    write_byte(DS3231_SECOND,tBCD.sec ); //修改秒
}

void DS3231::setTime(char* ddmmyystr,char* hhmmssstr)
{

		DateTime tBCD;
//		tBCD.week = 0;
	   
		tBCD.date = uint8_t ((ddmmyystr[0]*16) + (ddmmyystr[1]))-0x30;
		tBCD.month = uint8_t ((ddmmyystr[2])*16 + (ddmmyystr[3]))-0x30;
		tBCD.year = uint8_t ((ddmmyystr[4])*16 + (ddmmyystr[5]))-0x30;
	
	
		tBCD.hour = uint8_t ((hhmmssstr[0])*16 + (hhmmssstr[1]))-0x30;
		tBCD.min = uint8_t ((hhmmssstr[2])*16 + (hhmmssstr[3]))-0x30;
		tBCD.sec = uint8_t ((hhmmssstr[4])*16 + (hhmmssstr[5]))-0x30;
//	  write_byte(DS3231_WEEK,tBCD.week);   //修改周
		write_byte(DS3231_YEAR,tBCD.year);   //修改年
    write_byte(DS3231_MONTH,tBCD.month);  //修改月
   
    write_byte(DS3231_DAY,tBCD.date);    //修改日 
    write_byte(DS3231_HOUR,tBCD.hour);   //修改时
   
    write_byte(DS3231_MINUTE,tBCD.min); //修改分
   
    write_byte(DS3231_SECOND,tBCD.sec ); //修改秒

}
	
