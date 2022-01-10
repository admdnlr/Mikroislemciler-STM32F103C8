#include "stm32f10x.h"


int main(){

	//------------------------------------------BASLANGIC----------------------------------------
	
	RCC->APB2ENR |= (1<<4) | (1<<3);  //PortB ve PortC Enable durumuna getirildi
	
	GPIOB->CRH &=~(0xf<<16);    			//[16,19] bitleri 0 oldu
	GPIOB->CRH |=(1<<19);      			  //19.biti 1 yaparak 12 numarali pin giris oldu
	GPIOB->ODR &=~(1<<12);            //PortB 12 numarali pin pulldown oldu
	GPIOC->CRH &=~(0xf<<20); 					//[20,23] bitleri 0 oldu
	GPIOC->CRH |=(1<<21);             //21.biti 1 yaparak 13 numarali pin çikis oldu
	
	while(1){
		//IDR(Input Data Register): Ilgili pinden gelen veriyi okur
		if(GPIOB->IDR & (1<<12))        //PortB 12 numarali pin 1 ise kod çalisacaktir.
		{
			GPIOC->ODR &=~(1<<13);        //led yanar
		}
		else 														//PortB 12 numarali pin 0 ise kod çalisacaktir.
		{
			GPIOC->ODR |=(1<<13);         //led soner
		}
	}
	
	//--------------------------------------------BITIS------------------------------------------
	
  //------------------------------------------BASLANGIC----------------------------------------
	
	// Yukaridaki kodda input degeri sürekli kontrol edilerek led yakilir veya söndürülür.
	// Sürekli kontrol etmek yerine 12 numarali pin 1 oldugunda INTERRUPT olusturarak ledi yakalim.
	
	// Interrupt biriminin devreye girmesi için AFIO mutlaka Enable olmalidir.
	// ->AFIO(Alternate-Function I/Os)
	// ->ETICR[x](External Interrupt Configuration Register);
	//   Hangi portun hangi pinini ayarlamak icin kullanilir. (x, 0'dan 3'e kadar deger alabilir.)
	//   Her x degeri, 4 pin için ayarlama yapabiliyor.
	// ->NVIC(Nested Vectored Interrupt Controller)
	// ->ISER(Interrupt Set Enable Register)
	// ->IMR(Interrupt Mask Register)
	// ->PR(Pending Register)
	
	RCC->APB2ENR |= (1<<4) | (1<<3) | 1;  //PortB, PortC ve AFIO Enable durumuna getirildi
	GPIOB->CRH &=~(0xf<<16);    			    //[16,19] bitleri 0 oldu    
	GPIOB->CRH |=(1<<19);      			      //19.biti 1 yaparak 12 numarali pin giris oldu       
	GPIOB->ODR &=~(1<<12);                //PortB 12 numarali pin pulldown oldu      
	GPIOC->CRH &=~(0xf<<20); 					    //[20,23] bitleri 0 oldu 
	GPIOC->CRH |=(1<<21);                 //21.biti 1 yaparak 13 numarali pin çikis oldu       
	GPIOC->ODR |=(1<<13);                 //led soner
	
	AFIO->EXTICR[3] |= 1;                 //PortB 12 numarali pini interrupt girisi olarak ayarladik.
	EXTI->FTSR |= (1<<12);                //Butondan elimizi çektigimizde interrupt olusacak.
	EXTI->IMR |= (1<<12);  								//12 numarali pin ile çalistigimiz için 12. biti 1 yaptik
	NVIC->ISER[1] |= (1<<8);              //8.biti yani EXTI15_10 interrupt'ini 1 yaptik
	
	while(1){
	
	}
	
	//--------------------------------------------BITIS------------------------------------------
	
}

void EXTI15_10_IRQHandler(){   //[10,15] pinlerinden interrupt geldiginde bu fonksiyon cagrilir.
	if(EXTI->PR & (1<<12)){      //Interrupt'in 12 numarali pinden geldigini kontrol ediyoruz
		GPIOC->ODR &=~(1<<13);     //led yanar
		EXTI->PR |= (1<<12);       // interrupt'i tekrar kullanabilmek için tekrar 1 degerini atadik.
	}
	
	
}

