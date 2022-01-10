#include "stm32f10x.h"

static int duty_deger = 0;
static int kontrol = 1;

int main(){
RCC ->APB2ENR |= (1<<2);					// PortA Enable
	GPIOA ->CRH &= ~(1<<6); 				// Porta nin 9. pini çikis
	GPIOA ->CRH |= (1<<7) | (3<<4);
	
	RCC ->APB2ENR |= (1<<11); 			// TIM1 Enable
	TIM1 ->CCMR1 |= (6<<12); 			// Chanel-2
	TIM1 ->ARR = 36000; 						// 2KHz
	TIM1->PSC = 0;
	TIM1 ->CCR2 = duty_deger;
	TIM1 ->CCER |= (1<<4); 				// Chanel-2 Enable
	TIM1 ->BDTR |= (1<<15);
	
	SysTick -> LOAD = 720000/8;		//10ms
	SysTick ->CTRL = 3; 						//SysTick ve Tickint Enable
	TIM1 ->CR1 |= 1; 							//TIM1 basla
	
	while(1){	}
	
}

void SysTick_Handler(){ 	
	
	if(kontrol){
	duty_deger += 360;
	if(duty_deger >= 36000) { kontrol = 0; }
	}
	
	else{
	duty_deger -= 360;
	if(duty_deger <=0 ) { kontrol = 1; }
	}
	
	TIM1 ->CCR2 = duty_deger;
}
