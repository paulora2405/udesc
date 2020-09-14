%option noyywrap

%{
#include <stdio.h>

#define YY_DECL int yylex()

#include "trab.tab.h"

%}

DIGITO		[0-9]+
ID	[a-z]+[a-zA-Z0-9]*
TEXTO [ -~]
%%

[ \n\t]	; // ignore todos os espaços em branco
{DIGITO}+\.{DIGITO}+    {yylval.fval = atof(yytext); return T_REAL;}
{DIGITO}+			    {yylval.ival = atol(yytext); return T_INT;}

"bool"				{return T_BOOL;} 
"int"					{return T_INT;}
"float"				{return T_REAL;}
"TRUE"				{return T_TRUE;} 
"FALSE"				{return T_FALSE;} 
"["			      {return T_COL_ESQ;} 
"]" 					{return T_COL_DIR;} 
"{"			      {return T_CHA_ESQ;}
"}" 					{return T_CHA_DIR;}
"("						{return T_PAR_ESQ;}
")"						{return T_PAR_DIR;}
"while"				{return T_WHILE;}
"do"					{return T_DO;}
"main"				{return T_MAIN;}
"print"				{return T_PRINT;}
"read"				{return T_READ;}
"for"					{return T_FOR;}
"if"					{return T_IF;}
"else"				{return T_ELSE;}
"return"			{return T_RETURN;}
"or"					{return T_OR;}
"and"					{return T_AND;}
"+"						{return T_PLUS;}
"-"						{return T_MINUS;}
"*"						{return T_MULTIPLY;}
"/"						{return T_DIVIDE;}
"/!"					{return T_DIVIDE_INT;}
"^"						{return T_EXPOENT;}
"="						{return T_ATRIBUICAO;}
"=="					{return T_EQUALS;}
"!="					{return T_NOTEQUALS;}
"<"						{return T_MENOR_QUE;}
">"						{return T_MAIOR_QUE;}
"<="					{return T_MENOR_IGUAL_QUE;}
">="					{return T_MAIOR_IGUAL_QUE;}
";"						{return T_PONTO_VIRGULA;}
":"						{return T_DOIS_PONTOS;}
","						{return T_VIRGULA;}
"//"					{return T_COMENTARIO;}
"\""          {return T_ASPAS;}

{ID}+   {yylval.str = malloc(sizeof(char)*strlen(yytext)); memcpy(yylval.str,yytext,sizeof(char)*strlen(yytext));return T_IDENT;}
{TEXTO}* {yylval.str = malloc(sizeof(char)*strlen(yytext)); memcpy(yylval.str,yytext,sizeof(char)*strlen(yytext));return T_TEXT;}

.				        {printf("???????????... %s\n", yytext);}

%%