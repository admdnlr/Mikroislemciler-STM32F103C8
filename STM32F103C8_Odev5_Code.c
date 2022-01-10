/*
  Islemcinin PortA_10 nolu pinine led PortA_0 ve PortA_1 pinlerine buton baglanmistir.
	Butonlardan birine basildiginda led'in parlakligini %10 arttiran, digerine basildiginda 
	%10 azaltan ve her iki butona basildiginda ledin parlakligini %50 yapan programi Timer1 
	kullanarak yaziniz.
	> RCC registeri ile gerekli port ve fonksiyonlari aktiflestir.
	> GPIOx ile kullanilacak giris ve çikis portlarini ayarla.
	> EXTI ve NVIC ile porttan gelen interrupt'i ayarla
	> TIM1 ayarla
	> Port interrupt'inin fonksiyonunda TIM1'in duty degerini degistir.
*/

#include "stm32f10x.h"
static uint16_t duty_cyc = 0;
static int portA_0 = 0;
static int portA_1 = 0;
int main(){
	
	RCC->APB2ENR |= (1<<11) | (1<<2) | 1; 
	
	//LED'in port atamaleri
	GPIOA->CRH |= (0xF<<8);
	GPIOA->CRH &= ~(1<<10);
	
	//1.Butonun port atamalari (PortA_0)
	GPIOA->CRL &= ~(1<<2);
	GPIOA->CRL |= (1<<3);
	GPIOA->ODR &= ~1;
	
	//2.Butonun port atamalari (PortA_1)
	GPIOA->CRL &= ~(1<<6);
	GPIOA->CRL |= (1<<7);
	GPIOA->ODR &= ~2;
	//1.Buton için interrupt atamalari
	EXTI->RTSR |= 1;
	EXTI->IMR |= 1;
	NVIC->ISER[0] |= (1<<6);
	
	//2.Buton için interrupt atamalari
	EXTI->RTSR |= 2;
	EXTI->IMR |= 2;
	NVIC->ISER[0] |= (1<<7);
	
	//TIM1 ayarlari
  TIM1->CCMR2 |= (6<<4);
  TIM1->CCER |= (1<<8); 
  TIM1->BDTR |= (1<<15);
  TIM1->ARR = 3600; 
  TIM1->PSC = 0;
  TIM1->CCR3 = duty_cyc;   //Duty Cycle 
  TIM1->CR1 |= 1;
	
	while(1){ }
}

//PortA_0 interrupt olustugunda calisacak fonksiyon
void EXTI0_IRQHandler(){
	portA_0 = 1;
	
	if(duty_cyc >= 3600){	}
	else{
		duty_cyc += 360;
		TIM1->CCR3 = duty_cyc;
	}
	
	EXTI->PR |= 1;
	portA_0 =0;
}

//PortA_1 interrupt olustugunda calisacak fonksiyon
void EXTI1_IRQHandler(){
	portA_1 = 1;
	
	if(portA_0 & portA_1){
		TIM1->CCR3 = 1800;
	}
	
	if(duty_cyc == 0){	}
	else{
		duty_cyc -= 360;
		TIM1->CCR3 = duty_cyc;
	}
	
	EXTI->PR |= 2;
	portA_1 = 0;
}
