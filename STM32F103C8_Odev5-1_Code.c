#include "stm32f10x.h"
static volatile int i=0;

int main(){
	//PA7 potansiyometre, PA10 led 
	RCC->APB2ENR |= (1<<2) | (1<<9) | (1<<11);
	
	GPIOA->CRL &= ~(1<<30); //ADC7
	
	GPIOA->CRH |= (0xf<<8);
	GPIOA->CRH &= ~(1<<10);//LED
	
	TIM1->CCMR2 |= (6<<4);
	TIM1->CCER |= (1<<8);
	TIM1->BDTR |= (1<<15);
	TIM1->ARR = 4095;
	TIM1->PSC = 0;
	TIM1->CCR3 = 0;
	TIM1->CR1 |= 1;
	
	RCC->CFGR |= (1<<15);
	ADC1->SMPR2 |= (0x7);
	ADC1->SQR1 &= ~(0xf<<20);
	ADC1->SQR3 |= 7;
	ADC1->CR2 |= 1;
	ADC1->CR2 |= (1<<20); 
	ADC1->CR2 |= (0x7<<17);
	ADC1->CR2 |= (1<<2);
	while(ADC1->CR2 & (1<<2)){ }
	
	while(1){
		ADC1->CR2 |= (1<<22);
		while(!(ADC1->SR & (1<<1))){ }
		TIM1->CCR3 = ADC1->DR & 0xfff;
		for(i=0;i<300000;i++) {}
	}
}

