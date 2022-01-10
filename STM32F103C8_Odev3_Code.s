	AREA odev3, CODE
	EXPORT __main
		
__main PROC
	
	BL swap

loop
	B loop
	ENDP
		
swap PROC ; Alt program
	
x DCD 3
y DCD 5		
	
	LDR R0,=x
	LDR R1,=y
	LDR R0,[R0]
	LDR R1,[R1]
	
	;R0: x, R1: y, R2: temp
	MOV R2,R0
	MOV R0,R1
	MOV R1,R2
	
	BX lr
	ENDP
	END
		