
	AREA vize_1, CODE
	EXPORT __main

__main
	
	MOV32 R0,#40021000
	LDR R1,[R0,#0x18]
	ORR R1,#(1<<11)
	STR R1,[R0,#0x18]
	
	MOV32 R0,#40012C00
	LDR R1,[R0]
	ORR R1,#1
	STR R1,[R0]
	MOV R1,#5000
	STR R1,[R0,#0x2C]
	
loop
	B loop
	
	END
	