/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CHRLIT = 258,
    INTLIT = 259,
    REALLIT = 260,
    ID = 261,
    VOID = 262,
    CHAR = 263,
    INT = 264,
    SHORT = 265,
    DOUBLE = 266,
    SEMI = 267,
    COMMA = 268,
    LBRACE = 269,
    RBRACE = 270,
    LPAR = 271,
    RPAR = 272,
    ASSIGN = 273,
    PLUS = 274,
    MINUS = 275,
    MUL = 276,
    DIV = 277,
    MOD = 278,
    OR = 279,
    AND = 280,
    BITWISEAND = 281,
    BITWISEOR = 282,
    BITWISEXOR = 283,
    EQ = 284,
    NE = 285,
    LE = 286,
    GE = 287,
    LT = 288,
    GT = 289,
    NOT = 290,
    WHILE = 291,
    IF = 292,
    ELSE = 293,
    RETURN = 294,
    RESERVED = 295
  };
#endif
/* Tokens.  */
#define CHRLIT 258
#define INTLIT 259
#define REALLIT 260
#define ID 261
#define VOID 262
#define CHAR 263
#define INT 264
#define SHORT 265
#define DOUBLE 266
#define SEMI 267
#define COMMA 268
#define LBRACE 269
#define RBRACE 270
#define LPAR 271
#define RPAR 272
#define ASSIGN 273
#define PLUS 274
#define MINUS 275
#define MUL 276
#define DIV 277
#define MOD 278
#define OR 279
#define AND 280
#define BITWISEAND 281
#define BITWISEOR 282
#define BITWISEXOR 283
#define EQ 284
#define NE 285
#define LE 286
#define GE 287
#define LT 288
#define GT 289
#define NOT 290
#define WHILE 291
#define IF 292
#define ELSE 293
#define RETURN 294
#define RESERVED 295

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 35 "uccompiler.y"

int intValue;
double doubleValue;
char* stringValue;

ast_node* ast;

#line 145 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
