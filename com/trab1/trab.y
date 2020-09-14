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
%token T_IDENT
%left T_PLUS T_MINUS
%left T_MULTIPLY T_DIVIDE T_DIVIDE_INT 
%left T_EXPOENT

%type<ival> expr
%type<fval> mixed_expr

%start calculation

%%

calculation:	/* Aqui temos a representação do epsilon na gramática... */
	| calculation line
	;

line:  mixed_expr					{ printf("\tResultado: %f\n", $1);}
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
