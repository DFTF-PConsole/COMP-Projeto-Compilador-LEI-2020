%{
#include "structsAST.h"
#include "y.tab.h"

/*
Marcelo Gomes 2017278985
João Leal 2017252301
*/

extern is_program* myprogram;
extern void printTree(is_program* ip);
extern void cleanTree(is_program* ip);

int flag = 0;
int yacc_flag = 0;
int errorflag=0;
int lineNum = 1;
int colNum = 1;
char aux[4096];
int save;
int saveLine;
int hasIllegal=0;
void print(); 
void joinText();
void count();
void yyerror(const char* s);

%}

ID              [a-zA-Z_$]+[a-zA-Z_$0-9]*

UDIGIT          ([_]*[0-9])*

EXP             [eE](("+"|"-")?)(([0-9]+{UDIGIT})+|[0])

INTLIT          0|([1-9]{UDIGIT})

REALLIT         (([0-9]+{UDIGIT})+"."([0-9]+{UDIGIT})*|"."([0-9]+{UDIGIT})+){EXP}?|([0-9]+{UDIGIT})+{EXP}

BOOLLIT         ("true"|"false")

RESERVED        ("--"|"++"|"null"|"Integer"|"System"|"abstract"|"continue"|"for"|"new"|"switch"|"assert"|"default"|"goto"|"package"|"synchronized"|"boolean"|"do"|"private"|"this"|"break"|"double"|"implements"|"protected"|"throw"|"byte"|"else"|"import"|"throws"|"case"|"enum"|"instanceof"|"transient"|"catch"|"extends"|"short"|"try"|"char"|"final"|"interface"|"finally"|"long"|"strictfp"|"volatile"|"const"|"float"|"native"|"super")

INVALID_ESCAPE_SEQ (\\[^fnrt\\])

%X STRL STRL2 COMMENT MCOMMENT 
%%
"//"                        {BEGIN COMMENT; count();}
<COMMENT>\r\n               {BEGIN 0; count();}
<COMMENT>\n                 {BEGIN 0; count();}
<COMMENT>\r                 {BEGIN 0; count();}
<COMMENT>.                  {count();}

\/\*                        {BEGIN MCOMMENT;save=colNum;saveLine=lineNum; count();}
<MCOMMENT>\r\n              {count();}
<MCOMMENT>\n                {count();}
<MCOMMENT>\r                {count();}
<MCOMMENT>\*\/              {BEGIN 0; count();}
<MCOMMENT><<EOF>>           {printf("Line %d, col %d: unterminated comment\n", saveLine, save); BEGIN 0;}
<MCOMMENT>.                 {count();}

\"                          {strcpy(aux,&yytext[0]);hasIllegal=0;save=colNum; count(); BEGIN STRL;}
<STRL>\"                    {count();
                                    strcat(aux,&yytext[0]);
                                    if(!hasIllegal){
                                        joinText("STRLIT", aux);
                                        BEGIN 0;
                                        if(yacc_flag){
                                            yylval.strlit=(char*)strdup(aux);
                                            return STRLIT;
                                        }
                                    }
                                    else { 
                                        BEGIN 0;
                                    }
                            }
<STRL><<EOF>>               {printf("Line %d, col %d: unterminated string literal\n", lineNum, save); BEGIN 0;}
<STRL>("\r\n"|"\n"|"\r")    {printf("Line %d, col %d: unterminated string literal\n", lineNum, save); count(); BEGIN 0;} 
<STRL>\\                    {count();strcat(aux,&yytext[0]); BEGIN STRL2;}
<STRL>.                     {count();strcat(aux,&yytext[0]);}

<STRL2>(f|n|r|t|\"|\\)      {strcat(aux,&yytext[0]);count(); BEGIN STRL;}
<STRL2><<EOF>>              {printf("Line %d, col %d: invalid escape sequence (\\)\n", lineNum, colNum-1); printf("Line %d, col %d: unterminated string literal\n", lineNum, save); BEGIN 0;}
<STRL2>("\r\n"|"\n"|"\r")   {printf("Line %d, col %d: invalid escape sequence (\\)\n", lineNum, colNum-1); printf("Line %d, col %d: unterminated string literal\n", lineNum, save); count();BEGIN 0;}
<STRL2>.                    {printf("Line %d, col %d: invalid escape sequence (\\%s)\n", lineNum, colNum-1, yytext);strcat(aux,&yytext[0]);hasIllegal=1; count(); BEGIN STRL;}

"class"                     {count(); print("CLASS");               if(yacc_flag){return CLASS;}        }
"public"                    {count(); print("PUBLIC");              if(yacc_flag){return PUBLIC;}       }
"static"                    {count(); print("STATIC");              if(yacc_flag){return STATIC;}       }
"void"                      {count(); print("VOID");                if(yacc_flag){return VOID;}         }
"&&"                        {count(); print("AND");                 if(yacc_flag){return AND;}          }
"="                         {count(); print("ASSIGN");              if(yacc_flag){return ASSIGN;}       }
"*"                         {count(); print("STAR");                if(yacc_flag){return STAR;}         }
","                         {count(); print("COMMA");               if(yacc_flag){return COMMA;}        }
"/"                         {count(); print("DIV");                 if(yacc_flag){return DIV;}          }
"=="                        {count(); print("EQ");                  if(yacc_flag){return EQ;}           }
">="                        {count(); print("GE");                  if(yacc_flag){return GE;}           }
">"                         {count(); print("GT");                  if(yacc_flag){return GT;}           }
"{"                         {count(); print("LBRACE");              if(yacc_flag){return LBRACE;}       }
"}"                         {count(); print("RBRACE");              if(yacc_flag){return RBRACE;}       }
"<="                        {count(); print("LE");                  if(yacc_flag){return LE;}           }
"<"                         {count(); print("LT");                  if(yacc_flag){return LT;}           }
"("                         {count(); print("LPAR");                if(yacc_flag){return LPAR;}         }
")"                         {count(); print("RPAR");                if(yacc_flag){return RPAR;}         }
"-"                         {count(); print("MINUS");               if(yacc_flag){return MINUS;}        }
"%"                         {count(); print("MOD");                 if(yacc_flag){return MOD;}          }
"!="                        {count(); print("NE");                  if(yacc_flag){return NE;}           }
"!"                         {count(); print("NOT");                 if(yacc_flag){return NOT;}          }
"||"                        {count(); print("OR");                  if(yacc_flag){return OR;}           }
"+"                         {count(); print("PLUS");                if(yacc_flag){return PLUS;}         }
"["                         {count(); print("LSQ");                 if(yacc_flag){return LSQ;}          }
"]"                         {count(); print("RSQ");                 if(yacc_flag){return RSQ;}          }
";"                         {count(); print("SEMICOLON");           if(yacc_flag){return SEMICOLON;}    }
"->"                        {count(); print("ARROW");               if(yacc_flag){return ARROW;}        }
"<<"                        {count(); print("LSHIFT");              if(yacc_flag){return LSHIFT;}       }
">>"                        {count(); print("RSHIFT");              if(yacc_flag){return RSHIFT;}       }
"^"                         {count(); print("XOR");                 if(yacc_flag){return XOR;}          }
"boolean"                   {count(); print("BOOL");                if(yacc_flag){return BOOL;}         }
".length"                   {count(); print("DOTLENGTH");           if(yacc_flag){return DOTLENGTH;}    }
"double"                    {count(); print("DOUBLE");              if(yacc_flag){return DOUBLE;}       }
"else"                      {count(); print("ELSE");                if(yacc_flag){return ELSE;}         }
"if"                        {count(); print("IF");                  if(yacc_flag){return IF;}           }
"int"                       {count(); print("INT");                 if(yacc_flag){return INT;}          }
"System.out.print"          {count(); print("PRINT");               if(yacc_flag){return PRINT;}        }
"Integer.parseInt"          {count(); print("PARSEINT");            if(yacc_flag){return PARSEINT;}     }
"return"                    {count(); print("RETURN");              if(yacc_flag){return RETURN;}       }
"String"                    {count(); print("STRING");              if(yacc_flag){return STRING;}       }
"while"                     {count(); print("WHILE");               if(yacc_flag){return WHILE;}        }
{BOOLLIT}                   {count(); joinText("BOOLLIT", yytext);  if(yacc_flag){yylval.boollit=(char*)strdup(yytext); return BOOLLIT;}}
{RESERVED}                  {count(); joinText("RESERVED", yytext); if(yacc_flag){return RESERVED;}}
{ID}                        {count(); joinText("ID", yytext);       if(yacc_flag){yylval.id=(char*)strdup(yytext); return ID;}}
{INTLIT}                    {count(); joinText("INTLIT", yytext);   if(yacc_flag){yylval.intlit=(char*)strdup(yytext); return INTLIT;}}
{REALLIT}                   {count(); joinText("REALLIT", yytext);  if(yacc_flag){yylval.reallit=(char*)strdup(yytext); return REALLIT;}}
\f	     	                {count();}
\r\n                        {count();}
\n                          {count();}
" "                         {count();}
\t                          {count();}
\r                          {count();}
.	                        {printf("Line %d, col %d: illegal character (%s)\n", lineNum, colNum, yytext); count();}
%%

int main(int argc, char *argv[])
{
    if(!strcmp(argv[argc-1], "-l")){
        flag = 1;
        yacc_flag = 0;
        yylex();
    }
    else if(!strcmp(argv[argc-1], "-e1")){
        flag = 0;
        yacc_flag = 0;
        yylex();
    }
    else if(!strcmp(argv[argc-1], "-t")){
        flag = 0;
        yacc_flag = 1;
        yyparse();
        if(!errorflag){
            printTree(myprogram);
        }
        cleanTree(myprogram);
    }
    else {
        flag = 0;
        yacc_flag = 1;
        yyparse();
        cleanTree(myprogram);
    }
    return 0;
}

int yywrap()
{
    return 1;
}

void print(char inputString[]){
    if(flag){
        printf("%s\n", inputString);
    }
}

void joinText(char str1[], char str2[]){
    char s[1024];
    sprintf(s, "%s(%s)", str1, str2);
    print(s);
}

void count(){    
    for(int i = 0; i < yyleng; i++){
        if(yytext[i] == '\n'||yytext[i]=='\r'){
            colNum = 1;
            lineNum++;
            break;
        }
        else{
            colNum += 1;
        }
    }
}

void yyerror (const char *s) {
    errorflag=1;
    int newCol;
    if(strcmp(yytext,"\"") ==0){
        newCol = (int) colNum-strlen(aux);
        printf ("Line %d, col %d: %s: %s\n", lineNum, newCol, s, aux);
    }
    else{
        newCol = (int) colNum-strlen(yytext);
        printf ("Line %d, col %d: %s: %s\n", lineNum, newCol, s, yytext);
    }
}

