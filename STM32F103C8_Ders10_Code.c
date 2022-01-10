#include "stm32f10x.h"

static int say1,say2 =0;
volatile int i,j=0;

int main(){
	
	RCC->APB2ENR |= (1<<2);
	GPIOA->CRL &= ~(1<<2);
	GPIOA->CRL |= (1<<1); //A0 led1 trafik kirmizi
	GPIOA->CRL &= ~(1<<6);
	GPIOA->CRL |= (1<<5);  //A1 led2 trafik sari
	GPIOA->CRL &= ~(1<<10);
	GPIOA->CRL |= (1<<9);  //A2 led3 trafik yesil
	GPIOA->CRL &= ~(1<<14);
	GPIOA->CRL |= (1<<13);  //A3 led4 yaya yesil
	GPIOA->CRL &= ~(1<<18);
	GPIOA->CRL |= (1<<17);  //A4 led5 yaya kirmizi
	GPIOA->CRL &= ~(1<<22);
	GPIOA->CRL |= (1<<23);  //A5 buton
	
	GPIOA->ODR |= (1<<2); //trafik yesil
	GPIOA->ODR |= (1<<4); //yaya kirmizi
	while(1){
		if(GPIOA->IDR & (1<<5)){
			SysTick ->LOAD = 9000000; //1 saniye
	    SysTick ->CTRL = 3; //systick aktif
		}
		if(say1 == 10 & say2 == 10){
			GPIOA->ODR &= ~(1<<2); //trafik yesil sondur
			GPIOA->ODR |= (1<<1); //trafik sari yak
			for(i=0;i<5000000;i++) {	} //sari isikta biraz bekle
			GPIOA->ODR &= ~(1<<1); //trafik sari sondur
			GPIOA->ODR |= 1; //trafik kirmizi yak
			GPIOA->ODR &= ~(1<<4); //yaya kirmizi sondur
			GPIOA->ODR |= (1<<3); //yaya yesil yak
			say1 =0;
		}
		if(say2 == 30){
			GPIOA->ODR &= ~1; //trafik kirmizi sondur
			GPIOA->ODR |= (1<<1); //trafik sari yak
			for(j=0;j<5000000;j++) {	}
			GPIOA->ODR &= ~(1<<1); //trafik sari sondur
			GPIOA->ODR |= (1<<2); //trafik yesil yak
			GPIOA->ODR &= ~(1<<3); //yaya yesil sondur
			GPIOA->ODR |= (1<<4); //yaya kirmizi yak 
			say1=0;
			say2=0;
			SysTick ->CTRL = 0; //systick kapali
		}
	}
}

void SysTick_Handler(){
	say1++;
	say2++;
}