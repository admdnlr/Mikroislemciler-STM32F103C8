#include "stm32f10x.h"

int i,j;
int kontrol=0;
int main(){
	
	//------------------------------------------BASLANGIC----------------------------------------
	//Butona her basip çekildiginde ledi 5 kez yakip sondüren program
	
	RCC ->APB2ENR |= (1<<4);  //PortC yi aktif ediyoruz
	//LED
	GPIOC->CRH &= ~(0xf<<20); //13. pin için [20,23]4 biti sifirladik
	GPIOC->CRH |= (1<<21);    //21. biti 1 yaptik ve output yaptik
	//BUTTON
	GPIOC->CRH &= ~(0xf<<24); //14. pin için [24,27]4 biti sifirladik
	GPIOC->CRH |= (1<<27);    //25. biti 1 yaptik ve input(pullup/pulldown) yaptik
	GPIOC->ODR |= (1<<14);    //pullup
	GPIOC->ODR |= (1<<13);    //led söner

	
	while(1){
		while(GPIOC->IDR & (1<<14)){	}      //Input 1 iken bekleme
		while(!(GPIOC->IDR & (1<<14))){		}  //Input 0 iken bekleme
		for(i=0;i<5;i++){                    //Sonrasinda 5kez ledi yakip söndürme
			GPIOC->ODR&=~(1<<13);		 
			for(j=0;j<5000000;j++){		}
			GPIOC->ODR |= (1<<13);
			for(j=0;j<5000000;j++){		}
		}
	}
	//--------------------------------------------BITIS------------------------------------------
	
	//------------------------------------------BASLANGIC----------------------------------------
	//Butona her basip çekildiginde ledi 5 kez yakip sondüren program (interrupt ile)
	
	RCC ->APB2ENR |= (1<<4) | 1;         //PortC ve AFIO etkinlestirdik
	
	GPIOC->CRH &= ~(0xf<<20); 
	GPIOC->CRH |= (1<<21);
	
	GPIOC->CRH &= ~(0xf<<24); 
	GPIOC->CRH |= (1<<27);    
	GPIOC->ODR |= (1<<14);    
	GPIOC->ODR |= (1<<13);
	
	AFIO->EXTICR[3] |= (1<<9);  //PortC 14.pin interrupt girisi olarak ayarladik
	EXTI->IMR |= (1<<14);
	EXTI->RTSR |= (1<<14);      //Yükselen kenar tetikleyecek
	NVIC->ISER[1] |= (1<<8);    //Interrupt fonksiyonu devreye alinir
	
	SysTick->LOAD = 200*(72000000/8000);  //1 saniye
	
	
	while(1) {	}
	//--------------------------------------------BITIS------------------------------------------
}

void EXTI15_10_IRQHandler(){
	if(EXTI->PR & (1<<14)){
		EXTI->PR |=(1<<14);
		
		SysTick->CTRL = 3;
	}
}

void SysTick_Handler(){
	GPIOC->ODR ^=(1<<13);
	if(kontrol++>10){
		SysTick->CTRL=0;
		kontrol=0;
	}
}

