	AREA Odev_2, CODE
	EXPORT __main
	 
__main
						           
	MOV R0,#0x1000
	MOVT R0, #0x4002       
	LDR R1,[R0,#0x18]      
	MOV R2, #(1<<4)        
	STR R2,[R0,#0x18]      
	
	MOV R0,#0x1000
	MOVT R0, #0x4001      
	LDR R1,[R0,#0x04]      
	ORR R1, #(1<<21)      
	AND R1,#~(1<<22)     
	STR R1,[R0,#0x04]   
	
loop
	LDR R1,[R0,#0x0C]   
	ORR R1, #(1<<13)      
	STR R1,[R0,#0x0C] 
	
	MOV32 R4,#10000000
dongu
	SUB R4,R4,#1         
	CMP R4,#0
	BNE dongu ; ZF 1 oldugunda donguden cikar
	
	LDR R1,[R0,#0x0C]   
	AND R1, #~(1<<13) 
	STR R1,[R0,#0x0C] 
	
	MOV32 R5,#10000000
dongu1
	SUB R5,R5,#1          
	CMP R5,#0
	BNE dongu1
	
	B loop 
	END
		 