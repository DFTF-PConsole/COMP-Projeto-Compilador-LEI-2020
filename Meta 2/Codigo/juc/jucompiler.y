%{
	// Escolhemos criar uma Expr1 por causa da precedencia
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "functionsAST.h"
	#include "y.tab.h"	

	is_program* myprogram;
	extern void printTree(is_program* ip);
	extern void cleanTree(is_program* ip);
	
	extern int yylex(void);
    void yyerror(const char* s);   
%}

%token PUBLIC CLASS STATIC SEMICOLON VOID LPAR RPAR RETURN PRINT WHILE IF ELSE COMMA STRING PARSEINT LSQ RSQ LBRACE RBRACE INT BOOL DOUBLE DOTLENGTH ARROW RESERVED
%right ASSIGN
%left OR
%left AND
%left XOR
%left EQ NE
%left GE GT LE LT
%left LSHIFT RSHIFT
%left PLUS MINUS
%left STAR DIV MOD
%left NOT
%nonassoc RPAR
%nonassoc ELSE

%token<id>ID 
%token<intlit>INTLIT
%token<reallit>REALLIT
%token<boollit>BOOLLIT
%token<strlit>STRLIT

%type<ip>Program

%type<ic>Choose
%type<imd>MethodDecl
%type<imh>MethodHeader
%type<ifp>FormalParams
%type<ipl>ParamsList
%type<imb>MethodBody
%type<imbl>MethodBodyList
%type<ivd>VarDecl
%type<ifd>FieldDecl
%type<ial>ArgList
%type<is>Statement
%type<isl>StatementList
%type<imi>MethodInvocation
%type<iel>ExprList
%type<ia>Assignment
%type<ipa>ParseArgs
%type<ie>Expr
%type<ie1>Expr1
%type<_type>Type

%union{
	char* intlit;
	char* reallit;
	char* id;
	char* boollit;
	char* strlit;

    is_program* ip;
	
    is_choose* ic;
    is_method_decl* imd;
	is_method_header* imh;
	is_formal_params* ifp;
	is_params_list* ipl;
	is_method_body* imb;
	is_method_body_list* imbl;
	is_var_decl* ivd;
	is_field_decl* ifd;
	is_arg_list* ial;
	is_statement* is;
	is_statement_list* isl;
	is_method_invocation* imi;
	is_expr_list* iel;
	is_assignment* ia;
	is_parse_args* ipa;
	is_expr* ie;
	is_expr1* ie1;

	save_id_type* ibt;
	save_id_type* iit;
	save_id_type* idt;
	save_id_type* ivt;

	char* _type;
}

%% 
Program:
	CLASS ID LBRACE Choose RBRACE						{$$=myprogram = insert_program($2, $4);}
	;

Choose: 
        MethodDecl Choose								{$$=insert_choose_list_method_decl($2, $1);}
	|   FieldDecl Choose								{$$=insert_choose_list_field_decl($2, $1);}
	|   SEMICOLON Choose								{$$=insert_choose_list_semicolon($2);}
	|	/*empty*/										{$$=NULL;}
    ;

MethodDecl:
	    PUBLIC STATIC MethodHeader MethodBody			{$$=insert_method_decl($3, $4);}
    ;

MethodHeader:
	    Type ID LPAR FormalParams RPAR 					{$$=insert_method_header($1, $2, $4);}
	|   VOID ID LPAR FormalParams RPAR					{$$=insert_method_header("VOID", $2, $4);}
	;

FormalParams:
	    Type ID ParamsList								{$$=insert_formal_params_type($1, $2, $3);}
	|   STRING LSQ RSQ ID								{$$=insert_formal_params_string($4);}
	|	/*empty*/										{$$=NULL;}
    ;

ParamsList:
		/*empty*/										{$$=NULL;}
	|   COMMA Type ID ParamsList						{$$=insert_params_list($2, $3, $4);}
    ;

MethodBody:
	    LBRACE MethodBodyList RBRACE 					{$$=insert_method_body($2);}
    ;

MethodBodyList:
		/*empty*/										{$$=NULL;}
	|   Statement MethodBodyList						{$$=insert_methods_body_list_statement($1, $2);}
	|   VarDecl MethodBodyList							{$$=insert_methods_body_list_vardecl($1, $2);}
    ;	

VarDecl:
        Type ID ArgList SEMICOLON						{$$=insert_var_decl($1, $2, $3);}
    ;

FieldDecl:
		error SEMICOLON									{$$=NULL;}
	|   PUBLIC STATIC Type ID ArgList SEMICOLON			{$$=insert_field_decl($3, $4, $5);}
    ;

ArgList:
		/*empty*/										{$$=NULL;}
	|   COMMA ID ArgList								{$$=insert_arg_list($2, $3);}
    ;

Statement:	
		error SEMICOLON									{$$=NULL;}
	|   LBRACE StatementList RBRACE						{$$=insert_statement_statement_list($2);}
	|   IF LPAR Expr RPAR Statement						{$$=insert_statement_if($3, $5);}
	|   IF LPAR Expr RPAR Statement ELSE Statement		{$$=insert_statement_if_else($3, $5, $7);}
	|   WHILE LPAR Expr RPAR Statement					{$$=insert_statement_while($3, $5);}
	|   RETURN SEMICOLON								{$$=insert_statement_return_only();}
	|   RETURN Expr SEMICOLON							{$$=insert_statement_return($2);}
	|   SEMICOLON										{$$=NULL;}
	|   ParseArgs SEMICOLON								{$$=insert_statement_parse_args($1);}
	|   Assignment SEMICOLON							{$$=insert_statement_assignment($1);}
	|   MethodInvocation SEMICOLON						{$$=insert_statement_method_invocation($1);}
	|   PRINT LPAR Expr RPAR SEMICOLON					{$$=insert_statement_print($3);}
    |   PRINT LPAR STRLIT RPAR SEMICOLON				{$$=insert_statement_strlit($3);}
    ;

StatementList:
		/*empty*/										{$$=NULL;}
    |   Statement StatementList 						{$$=insert_statement_list($1, $2);}
    ;


MethodInvocation:
		ID LPAR error RPAR 								{$$=NULL;}
	|   ID LPAR RPAR									{$$=insert_method_invocation($1);}
	|   ID LPAR Expr ExprList RPAR						{$$=insert_method_invocation_expr($1, $3, $4);}
    ;

ExprList:
		/*empty*/										{$$=NULL;}
	|   COMMA Expr ExprList								{$$=insert_expr_list($2, $3);}
    ;

Assignment:
        ID ASSIGN Expr 									{$$=insert_assignment($1, $3);}
	;

ParseArgs:
		PARSEINT LPAR error RPAR 						{$$=NULL;}
	|   PARSEINT LPAR ID LSQ Expr RSQ RPAR				{$$=insert_parse_args($3,$5);}
    ;

Expr:
	  Expr1												{$$=insert_expr_expr1($1);}
	| Assignment										{$$=insert_expr_assign($1);}
	;

Expr1:
		LPAR error RPAR									{$$=NULL;}
	|   Expr1 PLUS Expr1 								{$$=insert_expr1_oper($1,$3,0);}
	|	Expr1 MINUS Expr1								{$$=insert_expr1_oper($1,$3,1);}
	|	Expr1 DIV Expr1									{$$=insert_expr1_oper($1,$3,2);}
	|	Expr1 STAR Expr1								{$$=insert_expr1_oper($1,$3,3);}
	|	Expr1 MOD Expr1 								{$$=insert_expr1_oper($1,$3,4);}
	|   Expr1 EQ Expr1  								{$$=insert_expr1_oper($1,$3,5);}
	|   Expr1 GE Expr1  								{$$=insert_expr1_oper($1,$3,6);}
	|   Expr1 GT Expr1  								{$$=insert_expr1_oper($1,$3,7);}
	|   Expr1 LT Expr1  								{$$=insert_expr1_oper($1,$3,8);}
	|   Expr1 LE Expr1  								{$$=insert_expr1_oper($1,$3,9);}
	|   Expr1 NE Expr1  								{$$=insert_expr1_oper($1,$3,10);}
	|   Expr1 AND Expr1 								{$$=insert_expr1_oper($1,$3,11);}
	|   Expr1 OR Expr1  								{$$=insert_expr1_oper($1,$3,12);}
	|   Expr1 XOR Expr1 								{$$=insert_expr1_oper($1,$3,13);}
	|   Expr1 LSHIFT Expr1								{$$=insert_expr1_oper($1,$3,14);}
	|   Expr1 RSHIFT Expr1								{$$=insert_expr1_oper($1,$3,15);}
	|   MINUS Expr1 %prec STAR							{$$=insert_expr1_oper2($2,0);}
	|   NOT Expr1										{$$=insert_expr1_oper2($2,1);}
	|   PLUS Expr1	%prec STAR						 	{$$=insert_expr1_oper2($2,2);}
	|   LPAR Expr RPAR  								{$$=insert_expr1_ParExpr($2);}
	|   MethodInvocation								{$$=insert_expr1_method_invocation($1);}
	|   ParseArgs										{$$=insert_expr1_parse_args($1);}
	|   ID		 										{$$=insert_expr1_id($1);}
	|   ID DOTLENGTH									{$$=insert_expr1_id_dotLength($1);}
	|   INTLIT 											{$$=insert_expr1_intLit($1);}
	|   REALLIT											{$$=insert_expr1_realLit($1);}
	|   BOOLLIT											{$$=insert_expr1_boolLit($1);}
    ;

Type:
	    BOOL											{$$="BOOL";}										
	|   INT												{$$="INT";}										
	|   DOUBLE											{$$="DOUBLE";}										
    ;

%%
