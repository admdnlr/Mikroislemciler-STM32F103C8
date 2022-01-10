#include "stm32f10x.h"

 int duty_val = 0;
 int cont = 1;

int main(){
	RCC ->APB2ENR |= (1<<2);
	GPIOA ->CRH &= ~(1<<6); 
	GPIOA ->CRH |= (1<<7) | (3<<4);
	RCC ->APB2ENR |= (1<<11);
	TIM1 ->CCMR1 |= (6<<12); 
	TIM1 ->ARR = 36000; 						// 2KHz
	TIM1->PSC = 0;
	TIM1 ->CCR2 = duty_val;
	TIM1 ->CCER |= (1<<4);
	TIM1 ->BDTR |= (1<<15);
	SysTick -> LOAD = 720000/8;		  //10ms
	SysTick ->CTRL = 3;
	TIM1 ->CR1 |= 1;
	
	while(1){	}
}

void SysTick_Handler(){
	if(cont){
		duty_val += 360;
		if(duty_val >= 36000) { cont = 0; }
	}else{
		duty_val -= 360;
		if(duty_val <=0 ) { cont = 1; }
	}
	TIM1 ->CCR2 = duty_val;
}
