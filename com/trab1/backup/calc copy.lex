%option noyywrap

%{
#include <stdio.h>

#define YY_DECL int yylex()

#include "calc.tab.h"

char *strdup(const char *src) {
    char *dst = malloc(strlen (src) + 1);  // Space for length plus nul
    if (dst == NULL) return NULL;          // No memory
    strcpy(dst, src);                      // Copy the characters
    return dst;                            // Return the new string
}

%}

DIGITO		[0-9]+
CARACTER    [a-zA-z]+

%%

[ \t]	; // ignore todos os espaços em branco // {CARACTER}			    {return T_CARAC;}
{DIGITO}+\.{DIGITO}+    {yylval.fval = atof(yytext); return T_REAL;}
{DIGITO}+			    {yylval.ival = atol(yytext); return T_INT;}

{CARACTER}+{DIGITO}*"="{DIGITO}  {
     
    int i;
    
    for(i=0; i<32; i++){
        if(yytext[i] == '='){
            i++;
            break;
        }
    }
    char value[32];
    int j=0;
    int k=i;
    for(;i <32-k; i++){
        if(yytext[i] != '\n'){
            value[j] = yytext[i];
            j++;
        }
        else
            break;
        
        
    }
    yylval.var=atof(value); return T_VAR;}
\n				        {return T_NEWLINE;}
"+"				        {return T_PLUS;}
"-"				        {return T_MINUS;}
"*"				        {return T_MULTIPLY;}
"/"				        {return T_DIVIDE;}
"/!"			        {return T_DIVIDE_INT;}
"^"				        {return T_EXPOENT;}
"("				        {return T_LEFT;}
")"				        {return T_RIGHT;}
"="				        {return T_EQUALS;}
"fora"			        {return T_QUIT;}
"sair"			        {return T_QUIT;}
.				        {printf("Caracter misterioso... %s\n", yytext);}

%%