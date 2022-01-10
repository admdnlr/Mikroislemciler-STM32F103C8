#include "stm32f10x.h"

volatile int sayac,bitis_sure;

int main(){
	RCC->APB2ENR |= (1<<2) | (1<<3) | 1;
	GPIOA->CRL &=~(0xf<<8);
	GPIOA->CRL |= (1<<11);
	GPIOB->CRH &=~(0xf<<4);
	GPIOB->CRH |= (1<<9);
	
	AFIO->EXTICR[1] &=~(0xf<<8);
	AFIO->EXTICR[3] |= (1<<4);
	EXTI->RTSR |= (1<<2) | (1<<9);
	EXTI->IMR |= (1<<2) | (1<<9);
	NVIC->ISER[0] |= (1<<23);
	NVIC->ISER[1] |= (1<<8);
	
	SysTick->LOAD = 9000;
	SysTick->CTRL = 0;
	
	while(1){
	}
	
}
void EXTI2_IRQHandler(){
	if(EXTI->PR & (1<<2)){
		EXTI->PR |= (1<<2);
		SysTick->CTRL = 3;
	}
}
void EXTI9_5_IRQHandler(){
	if(EXTI->PR & (1<<9)){
		EXTI->PR |= (1<<9);
		bitis_sure = sayac / 1000;
		SysTick->CTRL = 0;
		sayac = 0;
	}
}
void SysTick_Handler(){
	sayac++;
}
