#include "stm32f10x.h"

volatile static int i;

int main(){
	
  RCC->APB2ENR |=  (1<<4);
	GPIOC->CRH |=(1<<21);
	GPIOC->CRH &=~(1<<22);
	int say =0;
	
	while(say<5){
		GPIOC->ODR |= (1 << 13); for( i=0;i<500000;i++) {}
		GPIOC->ODR &= ~(1 << 13); for( i=0;i<500000;i++) {}
		say++;
	}
	GPIOC->ODR|=(1<<13);

}