#include "stm32f10x.h"
static int veri = 0;
int main(){
	/* Yapilan örnek: PortA_3 den gelen analog sinyali okuyarak degiskene aktar. */
	
	RCC->APB2ENR |= (1<<2) | (1<<9); //PortA ve ADC1 aktif
	GPIOA->CRL &= ~(0xf<<12); 			 //PortA 3. pini input ve analog moda aldik
	RCC->CFGR |= (1<<15);             
	RCC->CFGR &= ~(1<<14);					 //ADC'yi 12Mhz clock speed'e ayarladik
	
	ADC1->SMPR2 &= ~(0x7);           //örnekleme hizini 1.5 cycle olarak ayarladik
	ADC1->SQR1 &= ~(0xf<<20);        //ADC'nin sadece 1 pinini kullanacagimizi ayarladik
	ADC1->SQR3 |= 3;								 //PortA 3 numarali pini kullanacagimiz için 3 degerini atadik
	ADC1->CR2 |= 1;  								 //ADC'yi açtik
	ADC1->CR2 |= (1<<20); 					 //Harici tetiklemeyi aktif ettik
	ADC1->CR2 |= (0x7<<17);          //Yazilimsal olarak calistirmak için ayarladik
	ADC1->CR2 |= (1<<2);             //ADC deki kararsizlik durumunu kaldirmak icin kalibre ettik
	
	while(ADC1->CR2 & (1<<2)){  }    //Kalibrasyon isleminin bitmesini bekledik
	while(1){
		ADC1->CR2 |= (1<<22);          //ADC'ye Software Start verdik
		while(!(ADC1->SR & (1<<1))){ } //islemin bitmesini bekledik
		veri = ADC1->DR & 0xfff;   		 //ADC'nin data registerindaki degeri maskeleyerek degiskene atadik
	}
}
