	AREA ders4, CODE
	EXPORT __main
		
__main PROC

;------------------------------------------ACIKLAMA----------------------------------------
	; Karsilastirma islemi
	;CMP R3,#0 ; Hedef: R3, Kaynak: #0
	
	;Bazi Branch Komutlari
	;B <etiket adi>   : Kosulsuz olarak etiket adinin bulundugu kod satirina gider.
	;BEQ <etiket adi> : Karsilastirma sonucu esit ise etikete gider.
	;BNE <etiket adi> : Karsilastirma sonucu esit degil ise etikete gider.
	;BGT <etiket adi> : Karsilastirma sonucu buyuk ise etikete gider.
	;BLT <etiket adi> : Karsilastirma sonucu kucuk ise etikete gider.
	;BLE <etiket adi> : Karsilastirma sonucu kucuk veya esit ise etikete gider.
	;BGE <etiket adi> : Karsilastirma sonucu buyuk veya esit ise etikete gider.
 
;-------------------------------------------------------------------------------------------

;------------------------------------------BASLANGIC----------------------------------------
	
	;if(i == j) { f = g + h;} else{ f = g - h;}
	MOV R0,#5    ;i degiskeni
	MOV R1,#6    ;j 
	MOV R2,#20   ;g
	MOV R3,#3    ;h
	MOV R4,#0    ;f
	CMP R0,R1
	BEQ dogru0   ;R0,R1'e esit ise "dogru0" etiketinin oldugu kod satirina git.
	SUB R4,R2,R3 ;BEQ komutu calismazsa yani esit degilse bu kod satirindan devam.
	B son0       ;Buradan sonra, "dogru0" etiketinin calismamasi icin "son0" etiketinin oldugu
				 ;kod satirina kosulsuz olarak git.
	
dogru0
	ADD R4,R2,R3
son0
;--------------------------------------------BITIS------------------------------------------
	
;------------------------------------------BASLANGIC----------------------------------------

	; if(x>20 && x<25) { a = 1;}
	MOV R0,#5    ;x degiskeni
	CMP R0, #20 
	BLE son1     ;x 20den kucuk veya esitse "son1" etiketine git.
	CMP R0,#25  
	BGE son1     ;x 25den buyuk veya esitse "son1" etiketine git.
	MOV R1,#1    ;a degiskeni, BLE ve BGE saglanmazsa bu komut calisir.

son1             ;BLE veya BGE saglanirsa bu komut satiri calisir.
;--------------------------------------------BITIS------------------------------------------

;------------------------------------------BASLANGIC----------------------------------------

	;if(x<=20 || x>=25) { a = 1}
	MOV R0,#5   ;x
	CMP R0,#20
	BLE dogru1   ;x 20den kucuk veya esit ise "dogru1" etiketine git.
	CMP R0,#25
	BLT son2     ;x 25den kucuk ise "son2" etiketine git.
	
dogru1
	MOV R1,#1    ;a

son2
;--------------------------------------------BITIS------------------------------------------

;------------------------------------------BASLANGIC----------------------------------------

	;do{g--; i=i+j;}while(i!=h)
	MOV R0,#9    ;g
	MOV R1,#0    ;i
	MOV R2,#1    ;j
	MOV R3,#6    ;h
loop1
	SUB R0,#1
	ADD R1,R1,R2
	CMP R1,R3
	BNE loop1   ;i, h'ye esit degil ise loop1 etiketine git.
;--------------------------------------------BITIS------------------------------------------

;------------------------------------------BASLANGIC----------------------------------------

	;sum =0;
	;for(i=0; i<10;i++){sum=sum+i}
	MOV R0,#0   ;i
	MOV R1,#0   ;sum
dongu
	CMP R0,#10
	BGE son3    ;i, 10dan buyuk veya esit ise "son3" etiketine git.
	ADD R1,R1,R0
	ADD R0,#1
	B dongu     ;Kosulsuz olarak "dongu" etiketine git.
son3 
;--------------------------------------------BITIS------------------------------------------

;------------------------------------------BASLANGIC----------------------------------------
	
	BL delay    ;Alt programi cagirmak icin bu komut kullanilir.
				;BL <etiket adi> seklinde yazilir. 
;--------------------------------------------BITIS------------------------------------------
	            
;------------------------------------------BASLANGIC----------------------------------------	

	;1 saniye araliklarla led yakip sondurme odevini delay alt programi ile yapiyoruz.
	MOV R0,#0x1000
	MOVT R0,#0x4001
	LDR R1,[R0,#0x4]
	ORR R1,#(1<<21)
	AND R1,#~(1<<22)
	STR R1,[R0,#0x4] ;PortC 13 numarali pin cikis olarak ayarlandi.

;loop2

    MOV R0,#0x1000
	MOVT R0,#0x4001
	LDR R1,[R0,#0xC]
	ORR R1,#(1<<13)
	STR R1,[R0,#0xC] ;13 numarali pin 1 olarak ayarlandi.
	
	BL delay         ;1 saniye bekle
	
	MOV R0,#0x1000
	MOVT R0,#0x4001
	LDR R1,[R0,#0xC]
	AND R1,#(~(1<<13))
	STR R1,[R0,#0xC] ;13 numarali pin 0 olarak ayarlandi.
	 
	BL delay         ;1 saniye bekle
	
;	B loop2  ;Sonsuz dongu olacagi icin alt satirlara gecmeyecektir o yuzden yorum satiri yaptim.
;--------------------------------------------BITIS------------------------------------------

;------------------------------------------BASLANGIC----------------------------------------

    ;void swap(char x, char y){
	;char t;
	;t=x;
	;x=y;
	;y=t;
	;}
	;Soru: verilen kodu assembly dilinde alt program kullanarak kodlayiniz.
	MOV R0,#5   ;x
	MOV R1,#6   ;y
	BL swap
;--------------------------------------------BITIS------------------------------------------
	
;------------------------------------------BASLANGIC----------------------------------------
	
	;SysTick ile 1 saniyelik bekleme 
	MOV R0,#0x1000
	MOVT R0,#0x4002
	MOV R1,#(1<<4)
	STR R1,[R0,#0x18]
	
	MOV R0,#0x1000
	MOVT R0,#0x4001
	LDR R1,[R0,#0x4]
	ORR R1,#(1<<21)
	AND R1,#~(1<<22)
	STR R1,[R0,#0x4] ;PortC 13 numarali pin cikis olarak ayarlandi.
	
	MOV R0,#0xE000E000    ;SysTick baslangic adresi
	MOV32 R1,#9000000     ;Islemin bir saniye surmesi icin bu degeri yukluyoruz
	STR R1,[R0,#0x14]     ;Reload Value Register'ina R1 degerini yukledik.
	MOV R1,#3             
	STR R1,[R0,#0x10]     ;Control Register'inda Enable bitini ve Tickint bitini 1 yapiyoruz.
	
	;Burada "BX SysTick_Handler" yazmamiza gerek yok, Tickint aktif ettigimiz icin girilen deger
	;sifira ulastiginda interrupt ile "SysTick_Handler" alt programi calisacaktir.
;--------------------------------------------BITIS------------------------------------------

loop
	B loop
	
	ENDP   ;"__main" programinin bittigini belirtir.
		
;------------------------------------------ACIKLAMA-----------------------------------------
	;Alt program bir method gibi dusunulebilir; "__main" methodu, "delay" methodu gibi.
	;Method tanimlarken etiket adinin yanina PROC yazilir.
	;Methodun bittigini belirtmek icin ENDP yazilir.
;-------------------------------------------------------------------------------------------

;----------------------------------------ALT PROGRAMLAR-------------------------------------

delay PROC	
	MOV32 R3,#10000000
dongu1
	SUB R3,#1
	CMP R3,#0
	BNE dongu1
	
	BX lr   ;BX Link Register, "__main" methodundan cagirabilmemiz icin gerekli
	ENDP    ;"delay" programinin bittigini belirtir.
		
;-------------------------------------------------------------------------------------------

swap PROC
	;R0: x, R1: y, R2: temp
	MOV R2,R0   ;temp = x
	MOV R0,R1   ;x = y
	MOV R1,R2   ;y = temp
	
	BX lr
	ENDP   ;"swap" programinin bittigini belirtir.
		
;-------------------------------------------------------------------------------------------

SysTick_Handler PROC
	EXPORT SysTick_Handler
		
	MOV R5,#0x1000
	MOVT R5,#0x4001
	LDR R6,[R5,#0xC]
	EOR R6,#(1<<13)    ;EOR komutu ledi yaniyorsa sonduruyor, sonuyorsa yakiyor.
	STR R6,[R5,#0xC]
	
	BX lr
	ENDP   ;"SysTick_Handler" programinin bittigini belirtir.
		
		
	END  ;Assembly kodunun bittigini belirtir.
		