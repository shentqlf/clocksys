
#include "arduino.h"

void setup()
{
	systemtickcfg(9000);//1ms����һ���ж�
	pinMode(7,OUTPUT);
}

int main(void)
{
	setup();

	while(1)
	{
		digitalWrite(7,1);
		delay_ms(1);
		digitalWrite(7,0);
		delay_ms(1);	
	}
}




