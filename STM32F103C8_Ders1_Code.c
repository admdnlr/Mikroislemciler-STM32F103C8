#include "stm32f10x.h"

volatile static int i; 

int main(){
	
	RCC->APB2ENR |=  (1<<4);  
	// RCC ( Reset & Clock Control ) 
	// APB2ENR Register'i RCC'nin kontrol�ndedir. Baslangi� degeri 0'dir yani b�t�n bitleri 0 dir.
	// PortC 'yi aktif etmek i�in register'in 4.bitini 1 yapiyoruz.
	
	GPIOC->CRH |=(1<<21); 
	/*
	
	 GPIOC giris �ikis birimlerinden C portunu se�iyoruz
	 CRL ve CRH ( Configuration Register (LOW-HIGH) )
	 CRL de olan portlar [0,7], CRH de olan portlar [8,15]
	 13.Portu kontrol edecegimiz i�in CRH kullaniyoruz, kontrol i�in 4 bit'lik veriye ihtiyacimiz var 
	 bu bitler CNF1 (register'in 23.biti), CNF0 (register'in 22.biti), 
	 MODE1 (register'in 21.biti), MODE0 (register'in 20.biti) 
	(Tablodan bitlerin ne anlama geldigine bakiniz)
	 bu bitlerin varsayilan degeri 0100'dir. Yapmak istedigimiz 0010.
	
	 12.satirdaki kodda yapilan islem;
   "|" isareti or anlamina gelmektedir.  
	 (1<<21) anlami:    0x0000 0000 0000 0000 0000 0000 0000 0001 degerini 21 kez sola shift etmek
	 olusan yeni deger: 0x0000 0000 0010 0000 0000 0000 0000 0000 
	 bu degeri CRH register'i ile or'luyoruz.
	 
	                                              "____" bu bitleri 0010 olacak sekilde d�zenleyecegiz.
	 CRH'nin Varsayilan degeri:        0x0100 0100 0100 0100 0100 0100 0100 0100
	                                          OR
	 (1<<21) ile olusturdugumuz deger: 0x0000 0000 0010 0000 0000 0000 0000 0000
	                                   -----------------------------------------
	 CRH'nin Yeni degeri:              0x0100 0100 0110 0100 0100 0100 0100 0100
	 Hala istedigimiz 0010 bitlerini elde edemedik bu y�zden bir islem daha yapacagiz.
	 
	*/
	GPIOC->CRH &=~(1<<22);
	/*
	 39.satirdaki kodda yapilan islem;
	 "&" isareti and anlamina gelmektedir.
	 "~" isareti degili anlamina gelmektedir.
	 CRH'nin suanki degeri:              0x0100 0100 0110 0100 0100 0100 0100 0100
	                                          AND
	 ~(1<<22) ile olusturdugumuz deger:  0x1111 1111 1011 1111 1111 1111 1111 1111
	                                     -----------------------------------------
	 CRH'nin Yeni degeri:                0x0100 0100 0010 0100 0100 0100 0100 0100
	 istedigimiz 0010 degerine ulastik              "----" 
	 artik PortC 13'u output olarak kullanabilecegiz ve led yanacak.
	 
	*/
	
	while(1){
GPIOC->ODR|=(1<<13);		// led s�ner
		  /* 55.satirda
		  ODR ( Output Data Register ) Varsayilan degeri 0'dir. 0 iken aktiftirler.
		  13.bit, 13.pine denk gelmektedir bu yuzden bu biti 1 yapacagiz ve led s�necektir.
		  */
		for( i=0;i<500000;i++) {}  // bekleme s�resi yaratacak
GPIOC->ODR&=~(1<<13); // led yanar
			/* 61.satirda
			ledi yakmak i�in 13. biti 0 yapiyoruz.
			*/
		for( i=0;i<500000;i++) {}
			
	}
	
}

