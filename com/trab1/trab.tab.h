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

#ifndef YY_YY_TRAB_TAB_H_INCLUDED
# define YY_YY_TRAB_TAB_H_INCLUDED
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
    T_INT = 258,
    T_REAL = 259,
    T_BOOL = 260,
    T_PLUS = 261,
    T_MINUS = 262,
    T_MULTIPLY = 263,
    T_DIVIDE = 264,
    T_DIVIDE_INT = 265,
    T_EXPOENT = 266,
    T_ATRIBUICAO = 267,
    T_EQUALS = 268,
    T_NOTEQUALS = 269,
    T_MENOR_QUE = 270,
    T_MAIOR_QUE = 271,
    T_MENOR_IGUAL_QUE = 272,
    T_MAIOR_IGUAL_QUE = 273,
    T_PONTO_VIRGULA = 274,
    T_DOIS_PONTOS = 275,
    T_VIRGULA = 276,
    T_PRINT = 277,
    T_READ = 278,
    T_FOR = 279,
    T_IF = 280,
    T_ELSE = 281,
    T_MAIN = 282,
    T_WHILE = 283,
    T_DO = 284,
    T_RETURN = 285,
    T_OR = 286,
    T_AND = 287,
    T_TRUE = 288,
    T_FALSE = 289,
    T_COL_ESQ = 290,
    T_COL_DIR = 291,
    T_CHA_ESQ = 292,
    T_CHA_DIR = 293,
    T_PAR_ESQ = 294,
    T_PAR_DIR = 295,
    T_COMENTARIO = 296,
    T_IDENT = 297
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 16 "trab.y"

	long int ival;
	float fval;
	int bool;
	char *str;

#line 107 "trab.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_TRAB_TAB_H_INCLUDED  */
