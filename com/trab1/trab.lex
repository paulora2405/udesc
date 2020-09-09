%option noyywrap

%{
#include <stdio.h>

#define YY_DECL int yylex()

#include "calc.tab.h"

%}

DIGITO		[0-9]+
CARACTER    [a-zA-Z]+
CARACTER_MIN    [a-z]+
INDENTIFICADOR	{CARACTER_MIN}+ ({CARACTER_MIN}|{CARACTER}|{DIGITO})*

%%

[ \t]	; // ignore todos os espaços em branco // {CARACTER}			    {return T_CARAC;}
{DIGITO}+\.{DIGITO}+    {yylval.fval = atof(yytext); return T_REAL;}
{DIGITO}+			    {yylval.ival = atol(yytext); return T_INT;}

// int matriz [3][3]: 1 2 3, 4 3 2, 8 9 7;
"bool"					{return T_BOOL;}
"int"					{return T_INT;}
"float"					{return T_FLOAT;}
"TRUE"					{return T_TRUE;}
"FALSE"					{return T_FALSE;}
"["			            {return T_COL_ESQ;}
"]" 					{return T_COL_DIR;}
"while"					{return T_WHILE;}
"do"					{return T_DO;}
"main"					{return T_MAIN;}
"print"					{return T_PRINT;}
"read"					{return T_READ;}
"for"					{return T_FOR;}
"if"					{return T_IF;}
"else"					{return T_ELSE;}
"return"				{return T_RETURN;}
"or"					{return T_OR;}
"and"					{return T_AND;}
\n						{return T_NEWLINE;}
"+"						{return T_PLUS;}
"-"						{return T_MINUS;}
"*"						{return T_MULTIPLY;}
"/"						{return T_DIVIDE;}
"/!"					{return T_DIVIDE_INT;}
"^"						{return T_EXPOENT;}
"("						{return T_PAR_ESQ;}
")"						{return T__PAR_DIR;}
"="						{return T_ATRIBUICAO;}
"=="					{return T_EQUALS;}
"!="					{return T_NOTEQUALS;}
"<"						{return T_MENOR_QUE;}
">"						{return T_MAIOR_QUE;}
"<="					{return T_MENOR_IGUAL_QUE;}
">="					{return T_MAIOR_IGUAL_QUE;}
";"						{return T_PONTO_VIRGULA;}
":"						{return T_DOIS_PONTOS;}
","						{return T_VIRGULA}
"//"					{return T_COMENTARIO;}
{ID}+                   {yylval.str = malloc(sizeof(char)*strlen(yytext)); memcpy(yylval.str,yytext,sizeof(char)*strlen(yytext));return T_IDENT;}


.				        {printf("???????????... %s\n", yytext);}

%%