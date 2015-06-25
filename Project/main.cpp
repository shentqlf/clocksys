#include "ebox.h"
#include "boardcfg.h"
#include "uartx.h"
#include "lcd1602.h"
#include "protocol.h"
#include "ds3231.h"
#include "exti.h"
#include "gtimer.h"
#include "bd.h"
#include "clock.h"

#define OFFLINE		0
#define ONLINE 		1
#define READY			2
 
uint8_t starStatus;


DS3231 ds(DS3231_SDA_PIN,DS3231_SCL_PIN);
TIM tim2(TIM2);
TIM tim3(TIM3);
uint16_t T2millis;
uint16_t T3millis;
LCD1602 lcd(LCD_LED_PIN,LCD_EN_PIN,LCD_RW_PIN,LCD_RS_PIN,LCD_D0_PIN,LCD_D1_PIN,\
						LCD_D2_PIN,LCD_D3_PIN,LCD_D4_PIN,LCD_D5_PIN,LCD_D6_PIN,LCD_D7_PIN);
EXTIx exti7(7,EXTI_Trigger_Rising);

int rcvok = 0;
DateTime dt;
CLOCK clock;


char dateString[20];
char dateString2[20];
char newdateString[20];
char timeString[20];
char timeString2[20];
char newtimeString[20];

void uart1rxit()
{
	rcvok = protBD.deal( USART_ReceiveData(USART1));
}
void ppsit()
{
		T3millis = 0;
		tim2.clearCount();
		T2millis = 0;

	if(starStatus != READY)
		starStatus ++;
//	else
//	{
		if(protBD.used == 0)
		{
			uart3.printf("$DMYHMS,%s,%s,",dateString,timeString);						
			uart3.printf("%03d,>\r\n",T2millis);						
			lcd.dispDateString(1,dateString);
			lcd.dispTimeString(2,timeString);
			lcd.Dispnum(T2millis);
			protBD.used = 1;
			//�������
			clock.checkAlarm();
		}
//	}		

//				uart3.printf("\r\n===========start===========\r\n");
//	//			uart3.printf((const char *)protBD.msgRMC);
//			uart3.printf(protBD.GNTime);			
//			uart3.printf("\r\nms = %d",T2millis);
//			uart3.printf("\r\n date = ");			
//			uart3.printf(protBD.GNDate);
//			uart3.printf("\r\n BD  = %d",protBD.BDNum);
//			uart3.printf("\r\n GPS = %d",protBD.GPSNum);			

//			uart3.printf("\r\n==========end===========\r\n");
//	uart3.printf("\r\nms = %d",T2millis);

}
void tim2it()
{
	T2millis++;
}	
void tim3it()
{
	T3millis++;
	if(T3millis > 2000)
		starStatus = OFFLINE;
}	
void setup()
{
	eBoxInit();
	lcd.begin();
	uart3.begin(115200);
	uart1.begin(115200);
	
	uart1.interrupt(ENABLE);
	uart1.attachInterrupt(uart1rxit,1);
	
	exti7.attachInterrupt(ppsit);
	
	tim2.begin();
	tim2.Interrupt(ENABLE);
	tim2.attachInterrupt(tim2it);
	tim2.start();
	
	tim3.begin();
	tim3.Interrupt(ENABLE);
	tim3.attachInterrupt(tim3it);
	tim3.start();
	starStatus = OFFLINE;
	clock.alarmEnable = 0;

}
int main(void)
{

	setup();
	uart3.printf("setup is ok !\r\n");
	uint32_t ctime = millis(); 
	lcd.Clear();

	while(1)
	{	
		if(starStatus == OFFLINE)//��ʱ����ʱ�л���DS3231��ʱ��Դ
		{
			ds.readTime(&dt);
			ds.readTime(dateString,timeString);
			lcd.dispDateString(1,dateString);
			lcd.dispTimeString(2,timeString);
			lcd.Dispnum(555);

		}else if((starStatus == READY) || (starStatus == ONLINE))
		{
			if(protBD.isEnd())//�����ʱ��3û�г�ʱ
			{
				//�ύ�޸ĺ��ʱ����Ϣ�������´��жϵ���
				for(int i = 0; i < 20; i++)
				{
					dateString[i] = newdateString[i];
					timeString[i] = newtimeString[i];
				}
				protBD.used = 0;
				//��RMC֡���Ƶ��ܱ����Ļ�����
				protBD.cpymsgTomsgRMC();
				//������������
				protBD.updateStarNum();
				//��ȡʱ��
				protBD.cpyStrBeforeDot(protBD.msgRMC,newdateString,10);
				protBD.cpyStrBeforeDot(protBD.msgRMC,newtimeString,2);
				//����clock	
				clock.setClock(newdateString,newtimeString);
				//���1s
				clock.clockAddOneSec();
				//ת��Ϊ��8��ʱ��
				clock.GreenwichToTimeZone(8);
				//����ʱ���ַ������Ա��´��ж����
				clock.getDateStr(newdateString);
				clock.getTimeStr(newtimeString);
				//�����Զ�����ds3231
				if(clock.sec == 10)
					ds.setTime(dateString,timeString);

				//������Ϣ������ϣ��������
				protBD.clearAll();

			}
		}
//digitalWrite(7,!digitalRead(7));		
//		delay_ms(1);
	}
}




