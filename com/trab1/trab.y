%{

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

extern int yylex();
extern int yyparse();
extern FILE* yyin;

float a = 0;

void yyerror(const char* s);
%}

%union {
	long int ival;
	float fval;
	int bool;
	char *str;
}

/* Declaração dos tokens... */

%token<ival> T_INT
%token<fval> T_REAL
%token<bool> T_BOOL


%token T_PLUS T_MINUS T_MULTIPLY T_DIVIDE T_DIVIDE_INT T_EXPOENT
%token T_ATRIBUICAO T_EQUALS T_NOTEQUALS T_MENOR_QUE T_MAIOR_QUE T_MENOR_IGUAL_QUE T_MAIOR_IGUAL_QUE 
%token T_PONTO_VIRGULA T_DOIS_PONTOS T_VIRGULA  
%token T_PRINT T_READ T_FOR T_IF T_ELSE T_MAIN T_WHILE T_DO T_RETURN
%token T_OR T_AND T_TRUE T_FALSE T_COL_ESQ T_COL_DIR T_CHA_ESQ T_CHA_DIR T_PAR_ESQ T_PAR_DIR 
%token T_COMENTARIO
%token T_IDENT T_TEXT
%left T_PLUS T_MINUS
%left T_MULTIPLY T_DIVIDE T_DIVIDE_INT 
%left T_EXPOENT

/*%type<ival> expr*/
/*%type<fval> mixed_expr*/

%start algoritimo

%%

algoritimo:	/* epsilon */
	| var_global funcao_main outras_funcoes
	| var_global funcao_main
	| funcao_main outras_funcoes
	| funcao_main
	;

var_global: var_global init_vars
	| init_vars
	;

outras_funcoes: outras_funcoes funcao
	| funcao
	;

funcao: tipo_var nome_func T_PAR_ESQ argumentos T_PAR_DIR T_CHA_ESQ codigo T_CHA_DIR
	;

argumentos: tipo_var valor
	| tipo_var valor T_VIRGULA argumentos
	;

funcao_main: tipo_var T_MAIN T_PAR_ESQ T_PAR_DIR T_CHA_ESQ codigo T_CHA_DIR
	;

codigo: codigo linha
	| linha
	;

linha: variaveis
	| lacos
	| io
	| condicional
	;

condicional: ifelse
	| if
	;

if: T_IF T_PAR_ESQ condicao T_PAR_DIR T_CHA_ESQ codigo T_CHA_DIR 
	| T_IF T_PAR_ESQ condicao T_PAR_DIR linha
	;

ifelse: T_IF T_PAR_ESQ condicao T_PAR_DIR T_CHA_ESQ codigo T_CHA_DIR T_ELSE T_CHA_ESQ codigo T_CHA_DIR 
	| T_IF T_PAR_ESQ condicao T_PAR_DIR linha T_ELSE T_CHA_ESQ linha T_CHA_DIR
	| T_IF T_PAR_ESQ condicao T_PAR_DIR linha T_ELSE T_CHA_ESQ codigo T_CHA_DIR
	| T_IF T_PAR_ESQ condicao T_PAR_DIR T_CHA_ESQ codigo T_CHA_DIR T_ELSE linha
	;

io: read
	| print
	;

read: T_READ nome_var T_PONTO_VIRGULA
	;

print: T_PRINT print2
	;

/* --------------- analisar mais a fundo -----------*/
print2: print2 texto
	| print2 nome_var
	| texto
	| nome_var
	;

lacos: do
	| while
	| for
	;

do: T_DO T_CHA_ESQ codigo T_CHA_DIR T_WHILE T_PAR_ESQ condicao T_PAR_DIR T_PONTO_VIRGULA
	;

while: T_WHILE T_PAR_ESQ condicao T_PAR_DIR T_DOIS_PONTOS T_CHA_ESQ codigo T_CHA_DIR T_PONTO_VIRGULA 
	| T_WHILE T_PAR_ESQ condicao T_PAR_DIR T_DOIS_PONTOS T_CHA_ESQ linha T_CHA_DIR T_PONTO_VIRGULA
	;

for: T_FOR T_PAR_ESQ nome_var T_DOIS_PONTOS valor T_VIRGULA valor T_VIRGULA valor T_PAR_DIR T_DOIS_PONTOS T_CHA_ESQ codigo T_CHA_DIR T_PONTO_VIRGULA 
	| T_FOR T_PAR_ESQ nome_var T_DOIS_PONTOS valor T_VIRGULA valor T_VIRGULA valor T_PAR_DIR T_DOIS_PONTOS linha T_PONTO_VIRGULA
	;

condicao: condicao T_OR condicao
	| condicao T_AND condicao
	| expr_cond
	;

expr_cond: expressao op_logico expressao
	;

op_logico: T_ATRIBUICAO
	| T_EQUALS
	| T_NOTEQUALS
	| T_MAIOR_QUE
	| T_MENOR_QUE
	| T_MAIOR_IGUAL_QUE
	| T_MENOR_IGUAL_QUE
	;

variaveis: init_vars
	| atribuir_var
	;

atribuir_var: nome_var T_ATRIBUICAO expressao T_PONTO_VIRGULA
	;

init_vars: tipo_var nome_var T_ATRIBUICAO expressao T_PONTO_VIRGULA
	| tipo_var nome_var T_PONTO_VIRGULA
	;

expressao: term T_PLUS expressao
	| term T_MINUS expressao
	| term
	;

term: factor T_MULTIPLY term
	| factor T_DIVIDE term
	| factor
	;

factor: expo T_EXPOENT factor
	| expo
	;

expo: T_PAR_ESQ expressao T_PAR_DIR
	| valor
	| chamada_func
	;

chamada_func: nome_func T_PAR_ESQ parametros T_PAR_DIR
	| nome_func T_PAR_ESQ T_PAR_DIR
	;

parametros: valor
	| valor T_VIRGULA parametros
	;

tipo_var: T_BOOL
	| T_INT
	| T_REAL
	;

valor: valor_inteiro
	| valor_float
	;

valor_inteiro: T_INT
	;

valor_float: T_REAL
	;

nome_var: T_IDENT
	;

nome_func: T_IDENT
	;

texto: /* epislon */
	| T_TEXT
	;

/*---------------------------------------------------------------*/
/*
valor:  mixed_expr					{ printf("\tResultado: %f\n", $1);}
	| expr 								{ printf("\tResultado: %li\n", $1); }
	;

mixed_expr: T_REAL							{ $$ = $1; }
	| mixed_expr T_PLUS mixed_expr			{ $$ = $1 + $3; }
	| mixed_expr T_MINUS mixed_expr			{ $$ = $1 - $3; }
	| mixed_expr T_MULTIPLY mixed_expr		{ $$ = $1 * $3; }
	| mixed_expr T_DIVIDE mixed_expr		{ $$ = $1 / $3; }
	| mixed_expr T_EXPOENT mixed_expr		{ $$ = pow($1, $3); }
	| T_PAR_ESQ mixed_expr T_PAR_DIR				{ $$ = $2; }
	| expr T_PLUS mixed_expr				{ $$ = $1 + $3; }
	| expr T_MINUS mixed_expr				{ $$ = $1 - $3; }
	| expr T_MULTIPLY mixed_expr			{ $$ = $1 * $3; }
	| expr T_DIVIDE mixed_expr				{ $$ = $1 / $3; }
	| expr T_EXPOENT mixed_expr				{ $$ = pow($1, $3); }
	| mixed_expr T_PLUS expr				{ $$ = $1 + $3; }
	| mixed_expr T_MINUS expr				{ $$ = $1 - $3; }
	| mixed_expr T_MULTIPLY expr			{ $$ = $1 * $3; }
	| mixed_expr T_DIVIDE expr				{ $$ = $1 / $3; }
	| mixed_expr T_EXPOENT expr				{ $$ = pow($1, $3); }
	| expr T_DIVIDE expr					{ $$ = $1 / (float)$3; }
	| expr T_DIVIDE_INT expr				{ $$ = $1 / $3; }
	| expr T_EXPOENT expr					{ $$ = pow($1, $3); }
	;

expr: T_INT									{ $$ = $1; }
	| expr T_PLUS expr						{ $$ = $1 + $3; }
	| expr T_MINUS expr						{ $$ = $1 - $3; }
	| expr T_MULTIPLY expr					{ $$ = $1 * $3; }
	| T_PAR_ESQ expr T_PAR_DIR					{ $$ = $2; }
	;
*/

%%

int main() {
	yyin = stdin;

	do {
		yyparse();
		
	} while(!feof(yyin));

	return 0;
}

void yyerror(const char* s) {
	fprintf(stderr, "Erro de análise (sintática): %s\n", s);
	exit(1);
}
