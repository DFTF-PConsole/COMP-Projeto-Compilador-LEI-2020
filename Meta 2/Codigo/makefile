compile: uccompiler.l uccompiler.y functions.c
	lex uccompiler.l
	yacc -d uccompiler.y
	gcc lex.yy.c y.tab.c functions.c -o uccompiler 