/* Autores: Dario Felix 2018275530 e Jose Marcelo Marques da Cruz 2017255151 | COMP PL3 2020/21 */

%X MULTICOMMENT CHARLIT

WHITESPACE					[\x20\x09]
NEWLINE						\n|\r\n|\r
CHRLIT 						[^\n\r'\\]|\\'|\\n|\\t|\\\\|\\\"|\\[0-7]{1,3}
CHAR						"char"
ELSE						"else"
WHILE						"while"
IF							"if"
INT							"int"
SHORT						"short"
DOUBLE						"double"
RETURN						"return"
VOID						"void"
BITWISEAND					"&"
BITWISEOR					"|"
BITWISEXOR					"\^"
AND							"&&"
ASSIGN						"="
MUL							"*"
COMMA						","
DIV							"/"
EQ							"=="
GE							">="
GT							">"
LBRACE						"{"
LE							"<="
LPAR						"("
LT							"<"
MINUS						"-"
MOD							"%"
NE							"!="
NOT							"!"
OR							"||"
PLUS						"+"
RBRACE						"}"
RPAR						")"
SEMI						";"
RESERVED					"["|"]"|"++"|"--"|"auto"|"break"|"case"|"const"|"continue"|"default"|"do"|"enum"|"extern"|"float"|"for"|"goto"|"inline"|"register"|"restrict"|"long"|"sizeof"|"signed"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"volatile"|"_Bool"|"_Complex"|"_Imaginary"
REALLIT						(([0-9]+"."[0-9]*|"."[0-9]+)(("E"|"e")("+"|"-")?[0-9]+)?)|([0-9]+("E"|"e")("+"|"-")?[0-9]+)
INTLIT						[0-9]+
ID							[a-zA-Z_][a-zA-Z0-9_]*
SINGLE_COMMENT				"//".*
		
%{
		unsigned int column_count = 1;
		unsigned int new_line_count = 0;
		unsigned int character_count = 0;
		int fator = 0;		/* (fator == 0) >> -e1 ou nada | (fator == 1) >> -l */
%}

%%

{NEWLINE}					{ yylineno++; column_count = 1; }
{CHAR}						{ column_count += yyleng; if(fator) { printf("CHAR\n"); } }
{ELSE}						{ column_count += yyleng; if(fator) { printf("ELSE\n"); } }
{WHILE}						{ column_count += yyleng; if(fator) { printf("WHILE\n"); } }
{IF}						{ column_count += yyleng; if(fator) { printf("IF\n"); } }
{INT}						{ column_count += yyleng; if(fator) { printf("INT\n"); } }
{SHORT}						{ column_count += yyleng; if(fator) { printf("SHORT\n"); } }
{DOUBLE}					{ column_count += yyleng; if(fator) { printf("DOUBLE\n"); } }
{RETURN}					{ column_count += yyleng; if(fator) { printf("RETURN\n"); } }
{VOID}						{ column_count += yyleng; if(fator) { printf("VOID\n"); } }
{BITWISEAND}				{ column_count += yyleng; if(fator) { printf("BITWISEAND\n"); } }
{BITWISEOR}					{ column_count += yyleng; if(fator) { printf("BITWISEOR\n"); } }
{BITWISEXOR}				{ column_count += yyleng; if(fator) { printf("BITWISEXOR\n"); } }
{AND}						{ column_count += yyleng; if(fator) { printf("AND\n"); } }
{ASSIGN}					{ column_count += yyleng; if(fator) { printf("ASSIGN\n"); } }
{MUL}						{ column_count += yyleng; if(fator) { printf("MUL\n"); } }
{COMMA}						{ column_count += yyleng; if(fator) { printf("COMMA\n"); } }
{DIV}						{ column_count += yyleng; if(fator) { printf("DIV\n"); } }
{EQ}						{ column_count += yyleng; if(fator) { printf("EQ\n"); } }
{GE}						{ column_count += yyleng; if(fator) { printf("GE\n"); } }
{GT}						{ column_count += yyleng; if(fator) { printf("GT\n"); } }
{LBRACE}					{ column_count += yyleng; if(fator) { printf("LBRACE\n"); } }
{LE}						{ column_count += yyleng; if(fator) { printf("LE\n"); } }
{LPAR}						{ column_count += yyleng; if(fator) { printf("LPAR\n"); } }
{LT}						{ column_count += yyleng; if(fator) { printf("LT\n"); } }
{MINUS}						{ column_count += yyleng; if(fator) { printf("MINUS\n"); } }
{MOD}						{ column_count += yyleng; if(fator) { printf("MOD\n"); } }
{NE}						{ column_count += yyleng; if(fator) { printf("NE\n"); } }
{NOT}						{ column_count += yyleng; if(fator) { printf("NOT\n"); } }
{OR}						{ column_count += yyleng; if(fator) { printf("OR\n"); } }
{PLUS}						{ column_count += yyleng; if(fator) { printf("PLUS\n"); } }
{RBRACE}					{ column_count += yyleng; if(fator) { printf("RBRACE\n"); } }
{RPAR}						{ column_count += yyleng; if(fator) { printf("RPAR\n"); } }
{SEMI}						{ column_count += yyleng; if(fator) { printf("SEMI\n"); } }
{RESERVED}					{ column_count += yyleng; if(fator) { printf("RESERVED(%s)\n", yytext); } }
{REALLIT}					{ column_count += yyleng; if(fator) { printf("REALLIT(%s)\n", yytext); } }
{INTLIT}					{ column_count += yyleng; if(fator) { printf("INTLIT(%s)\n", yytext); } }
'							{ character_count = yyleng; BEGIN CHARLIT; }

<CHARLIT>{CHRLIT}'									{ if(fator) { printf("CHRLIT('%s)\n", yytext);} column_count += (character_count + yyleng); BEGIN 0;}
<CHARLIT>((\\\\)*(\\')*([^\n\r'\\](\\\\)*(\\')*|[^\n\r'])*){NEWLINE}		{printf("Line %d, col %d: unterminated char constant\n", yylineno, column_count); column_count = 1; yylineno++; BEGIN 0;}
<CHARLIT>((\\\\)*(\\')*([^\n\r'\\](\\\\)*(\\')*|[^\n\r'])*)'						{printf("Line %d, col %d: invalid char constant ('%s)\n", yylineno, column_count, yytext); column_count += (character_count + yyleng); BEGIN 0;}
<CHARLIT>((\\\\)*(\\')*([^\n\r'\\](\\\\)*(\\')*|[^\n\r'])*)		{printf("Line %d, col %d: unterminated char constant\n", yylineno, column_count); column_count = 1; yylineno++; BEGIN 0;}

{ID}                        { column_count += yyleng; if(fator) { printf("ID(%s)\n", yytext); } }
{WHITESPACE}				{ column_count += yyleng; }
{SINGLE_COMMENT}			{ ; }
"/*"						{ new_line_count = 0; character_count = yyleng; BEGIN MULTICOMMENT; }

<MULTICOMMENT>{NEWLINE}		{ character_count = 0; new_line_count++; }
<MULTICOMMENT>.				{ character_count += yyleng; }
<MULTICOMMENT><<EOF>>			{ printf("Line %d, col %d: unterminated comment\n", yylineno, column_count); return 0; }
<MULTICOMMENT>"*/"			{ column_count += (character_count + yyleng); yylineno += new_line_count; BEGIN 0; }

.							{ printf("Line %d, col %d: illegal character (%s)\n", yylineno, column_count, yytext); column_count += yyleng;}

%%

int main(int argc, char *argv[ ]) {
	if (argc == 2) {
		if (strcmp (argv[1], "-l") == 0) {
			fator = 1;  /* -l -> deve emitir os tokens e as mensagens de erro para o stdout e terminar */
		}
		/* ELSE: (fator = 0) -> Na ausencia de qualquer opcao, ou se invocado com a opcao -e1, deve escrever no stdout apenas as mensagens de erro */
	}
	
	yylex(); 
	return 0;
}

int yywrap() {
	return 1;
}

