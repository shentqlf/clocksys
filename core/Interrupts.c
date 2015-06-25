#include "interrupts.h"
#include "mcuconfig.h"
callbackFun gTimxcbTable[TIM_NUM +1];
callbackFun ExticbTable[EXTI_LINE_NUM + 1];
callbackFun UARTcbTable[USART_NUM * 2];//֧�ִ��ڵ�rx��tx�ж�



void TIM2_IRQHandler(void)
{

 if(TIM_GetITStatus(TIM2 , TIM_IT_Update) == SET)
 {
  TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);
		gTimxcbTable[2]();
 }
}
void TIM3_IRQHandler(void)
{
 if(TIM_GetITStatus(TIM3 , TIM_IT_Update) == SET)
 {
  TIM_ClearITPendingBit(TIM3 , TIM_FLAG_Update);
		gTimxcbTable[3]();
 }
}
void TIM4_IRQHandler(void)
{
 if(TIM_GetITStatus(TIM4 , TIM_IT_Update) == SET)
 {
  TIM_ClearITPendingBit(TIM4 , TIM_FLAG_Update);
		gTimxcbTable[4]();
 }
}
void EXTI0_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line0) != RESET) //ȷ���Ƿ������EXTI Line�ж�
  {
		ExticbTable[0]();
    EXTI_ClearITPendingBit(EXTI_Line0);     //����жϱ�־λ
  }  	
}
void EXTI1_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line1) != RESET) //ȷ���Ƿ������EXTI Line�ж�
  {
		ExticbTable[1]();

    EXTI_ClearITPendingBit(EXTI_Line1);     //����жϱ�־λ
  }  	
}
void EXTI2_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line2) != RESET) //ȷ���Ƿ������EXTI Line�ж�
  {

		ExticbTable[2]();

    EXTI_ClearITPendingBit(EXTI_Line2);     //����жϱ�־λ
  }  	
}
void EXTI3_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line3) != RESET) //ȷ���Ƿ������EXTI Line�ж�
  {
		ExticbTable[3]();
    EXTI_ClearITPendingBit(EXTI_Line3);     //����жϱ�־λ
  }  	
}
void EXTI4_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line4) != RESET) //ȷ���Ƿ������EXTI Line�ж�
  {
		ExticbTable[4]();
    EXTI_ClearITPendingBit(EXTI_Line4);     //����жϱ�־λ
  }  	
}

void EXTI9_5_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line5) != RESET) //ȷ���Ƿ������EXTI Line�ж�
  {
		ExticbTable[5]();
    EXTI_ClearITPendingBit(EXTI_Line5);     //����жϱ�־λ
  }   
	if(EXTI_GetITStatus(EXTI_Line6) != RESET) //ȷ���Ƿ������EXTI Line�ж�
  {
		ExticbTable[6]();
    EXTI_ClearITPendingBit(EXTI_Line6);     //����жϱ�־λ
  }  
  if(EXTI_GetITStatus(EXTI_Line7) != RESET) //ȷ���Ƿ������EXTI Line�ж�
  {
		ExticbTable[7]();
    EXTI_ClearITPendingBit(EXTI_Line7);     //����жϱ�־λ
  }   
	if(EXTI_GetITStatus(EXTI_Line8) != RESET) //ȷ���Ƿ������EXTI Line�ж�
  {
		ExticbTable[8]();
    EXTI_ClearITPendingBit(EXTI_Line8);     //����жϱ�־λ
  }	
  if(EXTI_GetITStatus(EXTI_Line9) != RESET) //ȷ���Ƿ������EXTI Line�ж�
  {
		ExticbTable[9]();
    EXTI_ClearITPendingBit(EXTI_Line9);     //����жϱ�־λ
  }   

}

void EXTI15_10_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line10) != RESET) //ȷ���Ƿ������EXTI Line�ж�
  {
		ExticbTable[10]();
    EXTI_ClearITPendingBit(EXTI_Line10);     //����жϱ�־λ
  }   
	if(EXTI_GetITStatus(EXTI_Line11) != RESET) //ȷ���Ƿ������EXTI Line�ж�
  {
		ExticbTable[11]();
    EXTI_ClearITPendingBit(EXTI_Line11);     //����жϱ�־λ
  }  
  if(EXTI_GetITStatus(EXTI_Line12) != RESET) //ȷ���Ƿ������EXTI Line�ж�
  {
		ExticbTable[12]();
    EXTI_ClearITPendingBit(EXTI_Line12);     //����жϱ�־λ
  }   
	if(EXTI_GetITStatus(EXTI_Line13) != RESET) //ȷ���Ƿ������EXTI Line�ж�
  {
		ExticbTable[13]();
    EXTI_ClearITPendingBit(EXTI_Line13);     //����жϱ�־λ
  }	
  if(EXTI_GetITStatus(EXTI_Line14) != RESET) //ȷ���Ƿ������EXTI Line�ж�
  {
		ExticbTable[14]();
    EXTI_ClearITPendingBit(EXTI_Line14);     //����жϱ�־λ
  }   
  if(EXTI_GetITStatus(EXTI_Line15) != RESET) //ȷ���Ƿ������EXTI Line�ж�
  {
		ExticbTable[15]();
    EXTI_ClearITPendingBit(EXTI_Line15);     //����жϱ�־λ
  }   

}
void USART1_IRQHandler(void)
{
	
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
	{
		UARTcbTable[0]();
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		return;
	}
	if(USART_GetITStatus(USART1,USART_IT_TXE)==SET)
	{
		UARTcbTable[1]();
		USART_ClearITPendingBit(USART1,USART_IT_TXE);
	}
}
void USART2_IRQHandler(void)
{
	
	if(USART_GetITStatus(USART2,USART_IT_RXNE)==SET)
	{
		UARTcbTable[2]();
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
		return;
	}	
	if(USART_GetITStatus(USART2,USART_IT_TXE)==SET)
	{
		UARTcbTable[3]();
		USART_ClearITPendingBit(USART2,USART_IT_TXE);
	}
}
void USART3_IRQHandler(void)
{
	
	if(USART_GetITStatus(USART3,USART_IT_RXNE)==SET)
	{
		UARTcbTable[4]();
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);
		return;
	}
	if(USART_GetITStatus(USART3,USART_IT_TXE)==SET)
	{
		UARTcbTable[5]();
		USART_ClearITPendingBit(USART3,USART_IT_TXE);
	}
}
