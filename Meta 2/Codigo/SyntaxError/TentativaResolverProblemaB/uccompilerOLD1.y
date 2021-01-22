
%{
	#include <stdio.h>
	extern int yylex();
	
	void yyerror (const char *s);
%}

%left COMMA							// reduce - ex: (...) LPAR CHAR ID . COMMA (...) RPAR			// . marca o sitio do parser

%%

calc: FunctionsAndDeclarations

FunctionsAndDeclarations			: TypeSpec FunctionsAndDeclarationsFactorization2				// DONE
									;
									
FunctionsAndDeclarationsFactorization2: FunctionDeclarator Opcoes FunctionsAndDeclarationsFactorization	// DONE
									| Declaration FunctionsAndDeclarationsFactorization
									;
									
Opcoes								: FunctionDefinition											// DONE
									| FunctionDeclaration
									;
									
FunctionsAndDeclarationsFactorization: TypeSpec FunctionsAndDeclarationsFactorization2				// DONE
									|
									;
									
Declaration							: Declarator DeclarationFactorization SEMI						// DONE
									| error SEMI													// ERRO LOCAL - DONE
									|
									;

DeclarationFactorization 			: COMMA Declarator DeclarationFactorization						// DONE
									|
									;

FunctionDeclaration					: SEMI															// DONE
									;
									
FunctionDefinition					: FunctionBody													// DONE
									;
									
FunctionBody						: LBRACE FunctionBodyFactorization								// DONE
									;
									
FunctionBodyFactorization			: DeclarationsAndStatements RBRACE								// DONE
									| RBRACE
									;
									
DeclarationsAndStatements			: Statement DeclarationsAndStatementsFactorization				// DONE
									| Declaration DeclarationsAndStatementsFactorization
									;
									
DeclarationsAndStatementsFactorization: DeclarationsAndStatements									// DONE
									|
									;
									
FunctionDeclarator					: ID LPAR ParameterList RPAR									// DONE
									;
									
ParameterList						: ParameterDeclaration ParameterListFactorization					// DONE
									;
									
ParameterListFactorization			: COMMA ParameterDeclaration ParameterListFactorization				// DONE
									|
									;
									
ParameterDeclaration				: TypeSpec ParameterDeclarationFactorization						// DONE
									;
									
ParameterDeclarationFactorization	: ID																// DONE
									|
									;
									
TypeSpec							: CHAR																// DONE
									| INT
									| VOID
									| SHORT
									| DOUBLE
									;

Declarator							: ID DeclaratorFactorization										// DONE
									;
									
DeclaratorFactorization				: ASSIGN Expr														// DONE
									|
									;

Statement							: SEMI																// DONE
									| Expr SEMI
									| error SEMI														// ERRO LOCAL - DONE
									| LBRACE StatementFactorization3
									| IF LPAR Expr RPAR Statement StatementFactorization
									| WHILE LPAR Expr RPAR Statement
									| RETURN StatementFactorization2
									;
									
StatementFactorization3				: StatementRecursion RBRACE											// DONE
									| error RBRACE														// ERRO LOCAL - DONE
									;
									
StatementRecursion					: Statement StatementRecursion										// DONE
									|
									;
									
StatementFactorization				: ELSE Statement													// DONE
									|
									;
									
StatementFactorization2				: SEMI																// DONE
									| Expr SEMI
									;
									
Expr								: Expr ASSIGN Expr													// NAO TERMINADO - Recursividade?
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
									| PLUS Expr
									| MINUS Expr
									| NOT Expr
									| ID ExprFactorization2
									| INTLIT
									| CHRLIT
									| REALLIT
									| LPAR ExprFactorization
									;

Recursion							: COMMA Expr Recursion												// DONE
									|
									;

ExprFactorization					: Expr RPAR															// DONE
									| error RPAR														// ERRO LOCAL - DONE
									;
									
ExprFactorization2					: LPAR ExprFactorization2Factorization								// DONE
									|
									;
									
ExprFactorization2Factorization		: RPAR																// DONE
									| Expr Recursion RPAR
									| error RPAR														// ERRO LOCAL - DONE
									;

%%

int main(){
	yyparse();
	return 0;
}

void yyerror(char *s){
	printf("%s\n", s);
}