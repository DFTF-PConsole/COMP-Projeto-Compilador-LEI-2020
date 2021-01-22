/* LEX - LEXICAL | Autores: Dario Felix 2018275530 e Jose Marcelo Marques da Cruz 2017255151 | COMP PL3 2020/21 | Meta 2 */


%X MULTICOMMENT CHARLIT


WHITESPACE					[\x20\x09]
NEWLINE						\n|\r\n|\r
Chrlit						[^\n\r'\\]|\\'|\\n|\\t|\\\\|\\\"|\\[0-7]{1,3}
Char						"char"
Else						"else"
While						"while"
If							"if"
Int							"int"
Short						"short"
Double						"double"
Return						"return"
Void						"void"
Bitwiseand					"&"
Bitwiseor					"|"
Bitwisexor					"\^"
And							"&&"
Assign						"="
Mul							"*"
Comma						","
Div							"/"
Eq							"=="
Ge							">="
Gt							">"
Lbrace						"{"
Le							"<="
Lpar						"("
Lt							"<"
Minus						"-"
Mod							"%"
Ne							"!="
Not							"!"
Or							"||"
Plus						"+"
Rbrace						"}"
Rpar						")"
Semi						";"
Reserved					"["|"]"|"++"|"--"|"auto"|"break"|"case"|"const"|"continue"|"default"|"do"|"enum"|"extern"|"float"|"for"|"goto"|"inline"|"register"|"restrict"|"long"|"sizeof"|"signed"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"volatile"|"_Bool"|"_Complex"|"_Imaginary"
Reallit						(([0-9]+"."[0-9]*|"."[0-9]+)(("E"|"e")("+"|"-")?[0-9]+)?)|([0-9]+("E"|"e")("+"|"-")?[0-9]+)
Intlit						[0-9]+
Id							[a-zA-Z_][a-zA-Z0-9_]*
SINGLE_COMMENT				"//".*
	
		
%{
		#include "y.tab.h"
		unsigned int column_count = 1;
		unsigned int new_line_count = 0;
		unsigned int character_count = 0;
		extern int fator;
		int fator_coluna = 1;
		int fator_comment = 0;
%}


%%

{NEWLINE}					{ yylineno++; column_count = 1; }
{Char}						{ column_count += yyleng; if(fator == 1) { printf("CHAR\n"); } fator_coluna = 0; return CHAR; }
{Else}						{ column_count += yyleng; if(fator == 1) { printf("ELSE\n"); } fator_coluna = 0; return ELSE;}
{While}						{ column_count += yyleng; if(fator == 1) { printf("WHILE\n"); } fator_coluna = 0; return WHILE;}
{If}						{ column_count += yyleng; if(fator == 1) { printf("IF\n"); } fator_coluna = 0; return IF;}
{Int}						{ column_count += yyleng; if(fator == 1) { printf("INT\n"); } fator_coluna = 0; return INT;}
{Short}						{ column_count += yyleng; if(fator == 1) { printf("SHORT\n"); } fator_coluna = 0; return SHORT;}
{Double}					{ column_count += yyleng; if(fator == 1) { printf("DOUBLE\n"); } fator_coluna = 0; return DOUBLE;}
{Return}					{ column_count += yyleng; if(fator == 1) { printf("RETURN\n"); } fator_coluna = 0; return RETURN;}
{Void}						{ column_count += yyleng; if(fator == 1) { printf("VOID\n"); } fator_coluna = 0; return VOID;}
{Bitwiseand}				{ column_count += yyleng; if(fator == 1) { printf("BITWISEAND\n"); } fator_coluna = 0; return BITWISEAND;}
{Bitwiseor}					{ column_count += yyleng; if(fator == 1) { printf("BITWISEOR\n"); } fator_coluna = 0; return BITWISEOR;}
{Bitwisexor}				{ column_count += yyleng; if(fator == 1) { printf("BITWISEXOR\n"); } fator_coluna = 0; return BITWISEXOR;}
{And}						{ column_count += yyleng; if(fator == 1) { printf("AND\n"); } fator_coluna = 0; return AND;}
{Assign}					{ column_count += yyleng; if(fator == 1) { printf("ASSIGN\n"); } fator_coluna = 0; return ASSIGN;}
{Mul}						{ column_count += yyleng; if(fator == 1) { printf("MUL\n"); } fator_coluna = 0; return MUL;}
{Comma}						{ column_count += yyleng; if(fator == 1) { printf("COMMA\n"); } fator_coluna = 0; return COMMA;}
{Div}						{ column_count += yyleng; if(fator == 1) { printf("DIV\n"); } fator_coluna = 0; return DIV;}
{Eq}						{ column_count += yyleng; if(fator == 1) { printf("EQ\n"); } fator_coluna = 0; return EQ;}
{Ge}						{ column_count += yyleng; if(fator == 1) { printf("GE\n"); } fator_coluna = 0; return GE;}
{Gt}						{ column_count += yyleng; if(fator == 1) { printf("GT\n"); } fator_coluna = 0; return GT;}
{Lbrace}					{ column_count += yyleng; if(fator == 1) { printf("LBRACE\n"); } fator_coluna = 0; return LBRACE;}
{Le}						{ column_count += yyleng; if(fator == 1) { printf("LE\n"); } fator_coluna = 0; return LE;}
{Lpar}						{ column_count += yyleng; if(fator == 1) { printf("LPAR\n"); } fator_coluna = 0; return LPAR;}
{Lt}						{ column_count += yyleng; if(fator == 1) { printf("LT\n"); } fator_coluna = 0; return LT;}
{Minus}						{ column_count += yyleng; if(fator == 1) { printf("MINUS\n"); } fator_coluna = 0; return MINUS;}
{Mod}						{ column_count += yyleng; if(fator == 1) { printf("MOD\n"); } fator_coluna = 0; return MOD;}
{Ne}						{ column_count += yyleng; if(fator == 1) { printf("NE\n"); } fator_coluna = 0; return NE;}
{Not}						{ column_count += yyleng; if(fator == 1) { printf("NOT\n"); } fator_coluna = 0; return NOT;}
{Or}						{ column_count += yyleng; if(fator == 1) { printf("OR\n"); } fator_coluna = 0; return OR;}
{Plus}						{ column_count += yyleng; if(fator == 1) { printf("PLUS\n"); } fator_coluna = 0; return PLUS;}
{Rbrace}					{ column_count += yyleng; if(fator == 1) { printf("RBRACE\n"); } fator_coluna = 0; return RBRACE;}
{Rpar}						{ column_count += yyleng; if(fator == 1) { printf("RPAR\n"); } fator_coluna = 0; return RPAR;}
{Semi}						{ column_count += yyleng; if(fator == 1) { printf("SEMI\n"); } fator_coluna = 0; return SEMI;}
{Reserved}					{ column_count += yyleng; if(fator == 1) { printf("RESERVED(%s)\n", yytext); } fator_coluna = 0; return RESERVED;}
{Reallit}					{ column_count += yyleng; if(fator == 1) { printf("REALLIT(%s)\n", yytext); } yylval.doubleValue = atof(yytext); fator_coluna = 0; return REALLIT;}
{Intlit}					{ column_count += yyleng; if(fator == 1) { printf("INTLIT(%s)\n", yytext); } yylval.intValue = atoi(yytext); fator_coluna = 0; return INTLIT;}
'							{ character_count = yyleng; BEGIN CHARLIT; }

<CHARLIT>{Chrlit}'									{ if(fator == 1) { printf("CHRLIT('%s)\n", yytext);} column_count += (character_count + yyleng); BEGIN 0; yylval.stringValue = strdup(yytext); return CHRLIT;}
<CHARLIT>((\\\\)*(\\')*([^\n\r'\\](\\\\)*(\\')*|[^\n\r'])*){NEWLINE}		{ if(fator != 3) { printf("Line %d, col %d: unterminated char constant\n", yylineno, column_count); } column_count = 1; yylineno++; BEGIN 0;}
<CHARLIT>((\\\\)*(\\')*([^\n\r'\\](\\\\)*(\\')*|[^\n\r'])*)'						{ if(fator != 3) { printf("Line %d, col %d: invalid char constant ('%s)\n", yylineno, column_count, yytext); } column_count += (character_count + yyleng); BEGIN 0;}
<CHARLIT>((\\\\)*(\\')*([^\n\r'\\](\\\\)*(\\')*|[^\n\r'])*)		{ if(fator != 3) { printf("Line %d, col %d: unterminated char constant\n", yylineno, column_count); } column_count = 1; yylineno++; BEGIN 0;}

{Id}                        { column_count += yyleng; if(fator == 1) { printf("ID(%s)\n", yytext); } yylval.stringValue = strdup(yytext); fator_coluna = 0; return ID;}
{WHITESPACE}				{ column_count += yyleng; }
{SINGLE_COMMENT}			{ column_count += yyleng; }
"/*"						{ new_line_count = 0; character_count = yyleng; BEGIN MULTICOMMENT; }

<MULTICOMMENT>{NEWLINE}		{ character_count = 0; new_line_count++; }
<MULTICOMMENT>.				{ character_count += yyleng; }
<MULTICOMMENT><<EOF>>		{ if(fator != 3) { printf("Line %d, col %d: unterminated comment\n", yylineno, column_count); } return 0; }
<MULTICOMMENT>"*/"			{ column_count += (character_count + yyleng); yylineno += new_line_count; fator_comment = 1; BEGIN 0; }

.							{ if(fator != 3) { printf("Line %d, col %d: illegal character (%s)\n", yylineno, column_count, yytext); } column_count += yyleng;}


%%


void yyerror(char *s) {		// Analise Sintatica
	if(fator == 4) { if (fator_coluna == 1 && fator_comment == 1) { printf("Line %d, col %d: %s: %s\n", yylineno , column_count, s, yytext);} else {printf("Line %d, col %d: %s: %s\n", yylineno, column_count - (int) strlen(yytext), s, yytext);} }
}


/*
int main(int argc, char *argv[ ]) {
	if (argc == 2) {
		if (strcmp (argv[1], "-l") == 0) {
			fator = 1;  // -l -> deve emitir os tokens e as mensagens de erro para o stdout e terminar
		}
		// ELSE: (fator = 0) -> Na ausencia de qualquer opcao, ou se invocado com a opcao -e1, deve escrever no stdout apenas as mensagens de erro
	}
	
	yylex(); 
	return 0;
}

int yywrap() {
	return 1;
}

*/


