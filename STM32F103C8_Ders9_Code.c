#include "stm32f10x.h"

unsigned int buffer[4]={3500,200,400,800};

int main(){
	RCC->APB2ENR|=(1<<2)|1;
	
	GPIOA->CRH&=~(1<<2);
	GPIOA->CRH|=(1<<3)|3;
	GPIOA->CRH&=~(1<<6);
	GPIOA->CRH|=(1<<7)|(3<<4);
	GPIOA->CRH&=~(1<<10);
	GPIOA->CRH|=(1<<11)|(3<<8);
	GPIOA->CRH&=~(1<<14);
	GPIOA->CRH|=(1<<15)|(3<<12);
	
	RCC->APB2ENR|=(1<<11);//tim1 aktif
	RCC->AHBENR|=1;//dma1 aktif
	TIM1->CCMR1|=(6<<4);//kanal1 aktif
	TIM1->CCMR1|=(6<<12);//kanal2 aktif
	TIM1->CCMR2|=(6<<4);//kanal3 aktif
	TIM1->CCMR2|=(6<<12);//kanal4 aktif
	TIM1->ARR=3600;//1Hz(20000 bölme ile)
	TIM1->PSC=20000;//bölme
	TIM1->CCER |= 1|(1<<4)|(1<<8)|(1<<12); //enable TIM1  Output(kanal 1 2 3 4)
	TIM1->BDTR |= (1<<15); //Main output enable

	DMA1_Channel5->CPAR=0x40012C00+0x4C;//tim1 DMAR register adresi
	DMA1_Channel5->CMAR=(u32)&buffer;//degisken adresi 
	DMA1_Channel5->CCR|=(1<<11) | (1<<9)  | (1<<4) ;
	//Bellek boyutu 32bit, çevrebirimi 32bit, bellek arttirma modu, öncelik çok yüksek
	//Veri transferi bellekten
	DMA1_Channel5->CNDTR = 4;//bellekten okunacak veri sayisi
	TIM1->DCR|=(4<<8)|0x34/4; //CCR1’in offset adresidir bellekten okunan 4 veri bu adresten baslanarak aktarilacaktir. 
	//Bellekten okunan 4 veri CCR1 den baslayip CCR2,CCR3 ve CCR4 e sirasi ile aktarilacaktir.
	TIM1->DIER|=(1<<8);//DMA için update tetikleme
	TIM1->EGR |= 6;//DMA tetikleme 
	DMA1_Channel5->CCR|=1;//DMA aktif
	TIM1->CR1|=1;//Tim aktif
	
	while(1){ }
}//0x34/4 : registerlar 32bit uzunluga sahiptir CCR1 in TIM1 içerisindeki sirasini bulmak için 4 e bölüyoruz.