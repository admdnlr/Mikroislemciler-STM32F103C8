#include "stm32f10x.h"

int main(){

//------------------------------------------ACIKLAMA----------------------------------------
	/*
		TIM1
		Timer’lar genel olarak mikrodenetleyicilerde, main fonksiyonu çalisirken belirli periyotlarda 
		timer alt programina inerek oradaki islemleri yapmasini saglar. Periyodik olarak ana program ve 
		timer alt programi sürekli olarak çalisir.
		
		Interrupt Ozellikleri
		>Update Event: Sayici tasma yada sifira gelme durumunda olusur.
	  >Trigger Event: Sayicinin baslamasi veya durmasi durumda olusur.
	
		TIM1 Registerlari
	  >Counter Register(TIMx_CNT): Sayma sirasinda o anki degeri tutar
	  >Prescaler Register(TIMx_PSC): Gelen frekansi böler
	  >Auto-Reload Register(TIMx_ARR): Saydirmak istedigimiz deger burada tutulur
	  >Status Register(TIMx_SR): Update Event oldugunda calisiyor
  	>DMA Interrupt Enable Register(TIMx_DIER): 0.biti enable yaptigimizda timer update oldugunda 
	   interrupt olusturur.
	  >Capture/Compare Mode Register 1(TIMx_CCMR1): PWM çikisinin hangi modda çalisacagi belirlenir
	*/
//------------------------------------------------------------------------------------------
	
	
//------------------------------------------BASLANGIC---------------------------------------

		RCC->APB2ENR |= (1<<11);    //Timer Enable
		TIM1->ARR = 7200;           //7200e kadar sayacak
		TIM1->PSC = 0;							//72MHz hizinda sayacak, 7200/72000000=100 mikro saniye
		TIM1->CR1 |= 1;  						//Timer Start
		
		while(!(TIM1->SR & 1)){  }  //Update olmadigi sürece döngü devam edecek
		TIM1->SR = 0;								//Update flag sifirlanir
		
		while(1){	}
//--------------------------------------------BITIS-----------------------------------------

		
//------------------------------------------BASLANGIC---------------------------------------
	
	//TIM1 kullanarak 1Hz'lik sinyal üretelim.
	RCC->APB2ENR |= ((1<<11)|(1<<4));   //Timer ve PortC Enable
	GPIOC->CRH |= ((1<<20)|(1<<21));    
	GPIOC->CRH &= ~((1<<22)|(1<<23));	

	TIM1->ARR = 7200;
	TIM1->PSC = 5000;										//7200/(72000000/5000)=500 milisaniye
	TIM1->CR1 |= 1;    									//Timer Start

	while(1){	
		while(!(TIM1->SR & 1)){}
		TIM1->SR &= ~1;
		GPIOC->ODR ^= (1<<13);
	}
//--------------------------------------------BITIS-----------------------------------------
	
	
//------------------------------------------BASLANGIC---------------------------------------
	
	//TIM1 kullanarak 1Hz'lik sinyal üretelim. Interrupt ile
	RCC->APB2ENR |= ((1<<11)|(1<<4));   
	GPIOC->CRH |= ((1<<20)|(1<<21));    
	GPIOC->CRH &= ~((1<<22)|(1<<23));	

	TIM1->ARR = 7200;
	TIM1->PSC = 5000;										
	TIM1->CR1 |= 1;    									
	TIM1->DIER |= 1;   					//Update oldugunda interrupt çalisacak
	NVIC->ISER[0] |= (1<<25);   //TIM1 için interrupt aktif hale getirdik
	
	while(1){	}
//--------------------------------------------BITIS-----------------------------------------
	
	
//------------------------------------------BASLANGIC---------------------------------------
	//Timer ile pwm sinyali olusturma
	RCC->APB2ENR |= (1<<11) | (1<<2) | 1;
	GPIOA->CRH &= ~(1<<2);
	GPIOA->CRH |= (1<<3)|3;
		
	TIM1->CCMR1 |= (6<<4);      //PortA 8.pin için mode1 ayarlandi
	TIM1->CCER |= 1;						//Kanal-1 çikis olarak ayarlandi
	TIM1->BDTR |= (1<<15);      //Main output enable
	TIM1->ARR = 3600; 					//20KHz
	TIM1->PSC = 0;
	TIM1->CCR1 = 360;						//Duty Cycle %10
	TIM1->CR1 |= 1;							//Timer Start
		
	while(1){	}
//--------------------------------------------BITIS-----------------------------------------
	

}


void TIM1_UP_IRQHandler(){   // TIM1 Update Interrupt'i, sayma islemi bittiginde devreye girer
	if(TIM1->SR &1){
		TIM1->SR &=~1;
		GPIOC->ODR ^=(1<<13);
	}
}

