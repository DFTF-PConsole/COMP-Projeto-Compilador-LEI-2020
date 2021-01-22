/* YACC - SINTATICA | Autores: Dario Felix 2018275530 e Jose Marcelo Marques da Cruz 2017255151 | COMP PL3 2020/21 | Meta 2 */


/* variaveis, declaracoes, bibliotecas, prototipos */
%{
	#include <stdio.h>
	#include <string.h>
	extern int yylex();
	
	void yyerror (char *s);
	int fator = 0;
%}


/* %token <tipo de token> TOKEN | %type <tipo> simboloNaoTerminal */
%token <stringValue> CHRLIT
%token <intValue> INTLIT
%token <doubleValue> REALLIT
%token <stringValue> ID
%token VOID CHAR INT SHORT DOUBLE
%token SEMI COMMA LBRACE RBRACE LPAR RPAR ASSIGN
%token PLUS MINUS MUL DIV MOD
%token OR AND BITWISEAND BITWISEOR BITWISEXOR EQ NE LE GE LT GT NOT
%token WHILE IF ELSE RETURN RESERVED


/* yylval.xxx (tipo de token) */
%union{
int intValue;
double doubleValue;
char* stringValue;
}


/* precedências */
%left COMMA
%right ASSIGN
%left OR
%left AND
%left BITWISEOR
%left BITWISEXOR
%left BITWISEAND
%left EQ NE
%left LT LE GT GE
%left PLUS MINUS
%left MUL DIV MOD
%right NOT /* neste nível de prioridade incluí-se também os operadores MINUS e PLUS se forem unários */
%left LPAR RPAR
%nonassoc ELSE


/* gramatica */
%%
Start							: FunctionDefinition FunctionsAndDeclarations
								| FunctionDeclaration FunctionsAndDeclarations
								| Prod1 FunctionsAndDeclarations
								;
								
Prod1							: Declaration
								| error SEMI
								;
								
FunctionsAndDeclarations		: Start
								|
								;
								
FunctionDefinition				: TypeSpec FunctionDeclarator FunctionBody
								;
								
FunctionBody					: LBRACE DeclarationsAndStatements RBRACE
								;
								
DeclarationsAndStatements		: Prod2 DeclarationsAndStatements
								|
								;
								
Prod2							: Declaration
								| Statement
								| error SEMI
								;
								
FunctionDeclaration				: TypeSpec FunctionDeclarator SEMI
								;
								
FunctionDeclarator				: ID LPAR ParameterList RPAR
								;
								
ParameterList					: ParameterDeclaration ParameterListRecursivo
								;
								
ParameterListRecursivo			: COMMA ParameterDeclaration ParameterListRecursivo
								| 
								;
								
ParameterDeclaration			: TypeSpec
								| TypeSpec ID
								;
								
Declaration						: TypeSpec Declarator DeclarationPrime SEMI
								;
								
DeclarationPrime 				: COMMA Declarator DeclarationPrime
								|
								;
								
TypeSpec						: CHAR
								| INT
								| VOID
								| SHORT
								| DOUBLE
								;
								
Declarator 						: ID ASSIGN Expr
								| ID
								;
								
Statement						: Expr SEMI
								| SEMI
								| LBRACE StatementRecursivo RBRACE
								| IF LPAR Expr RPAR StatementEspecial 
								| IF LPAR Expr RPAR StatementEspecial ELSE StatementEspecial
								| WHILE LPAR Expr RPAR StatementEspecial
								| RETURN Expr SEMI
								| RETURN SEMI
								| LBRACE error RBRACE
								;
								
StatementEspecial				: Statement
								| error SEMI
								;

StatementRecursivo: 			StatementEspecial StatementRecursivo
								|
								;
								
Expr							: INTLIT
								| CHRLIT
								| REALLIT
								| PLUS Expr %prec NOT
								| MINUS Expr %prec NOT
								| NOT Expr
								| ID
								| ID LPAR RPAR
								| ID LPAR Expr RPAR 									/* pode gerar as COMMA Expr seguindo por Expr -> Expr COMMA Expr */
								| ID LPAR error RPAR
								| LPAR Expr RPAR
								| LPAR error RPAR
								| Expr ASSIGN Expr
								| Expr COMMA Expr
								| Expr PLUS Expr
								| Expr MINUS Expr
								| Expr MUL Expr
								| Expr DIV Expr
								| Expr MOD Expr
								| Expr OR Expr
								| Expr AND Expr
								| Expr BITWISEAND Expr
								| Expr BITWISEOR Expr
								| Expr BITWISEXOR Expr
								| Expr EQ Expr
								| Expr NE Expr
								| Expr LE Expr
								| Expr GE Expr
								| Expr LT Expr
								| Expr GT Expr
								;
								
%%


/* funcoes */
int main(int argc, char *argv[ ]){
	if (argc == 2) {
	/* FLAG | DESCRICAO | FATOR
	* <sem flag> | Apenas escrever no stdout as mensagens de erro correspondentes aos erros lexicais e de sintaxe | fator=0 == fator=4 == -e2
	* -l | Apenas realiza analise lexical - emitir os tokens e as mensagens de erro | fator=1
	* -e1 | Apenas realiza analise lexical - apenas as mensagens de erro | fator=2
	* -t | Imprimir a arvore de sintaxe | fator=3
	* -e2 | Apenas as mensagens de erro relativas aos erros sintáticos e lexicais | fator=4
	*/
		if (strcmp (argv[1], "-l") == 0) {
			fator = 1;  /* -l */
		} else {
			if (strcmp (argv[1], "-e1") == 0) {
				fator = 2;  /* -e1 */
			} else {
				if (strcmp (argv[1], "-t") == 0) {
					fator = 3;  /* -t */
				} else {
					if (strcmp (argv[1], "-e2") == 0) {
						fator = 4;  /* -e2 */
					} else {
						/* ERRO NA FLAG == <sem flag>, fator=0 == fator=4 == -e2 */
						fator = 4;
					}
				}
			}
		}
	} else {
		/* ELSE: (fator = 0), <sem flag>, fator=0 == fator=4 == -e2 */
		fator = 4;
	}
	
	yyparse();
	return 0;
}


int yywrap() {
	return 1;
}


