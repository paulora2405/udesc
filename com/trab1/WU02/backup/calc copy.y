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
	float var;
	//float carac;

}

/* Declaração dos tokens... */

%token<ival> T_INT
%token<fval> T_REAL
%token<var> T_VAR
//%token<carac> T_CARAC
%token T_PLUS T_MINUS T_MULTIPLY T_DIVIDE T_LEFT T_RIGHT T_DIVIDE_INT T_EXPOENT T_EQUALS
%token T_NEWLINE T_QUIT
%left T_PLUS T_MINUS
%left T_MULTIPLY T_DIVIDE T_DIVIDE_INT
%left T_EXPOENT

%type<ival> expr
%type<fval> mixed_expr
%type<var> var
//%type<carac> carac

%start calculation

%%

calculation:	/* Aqui temos a representação do epsilon na gramática... */
	| calculation line
	;

line: T_NEWLINE
	| mixed_expr T_NEWLINE					{ printf("\tResultado: %f\n", $1);}
	| expr T_NEWLINE						{ printf("\tResultado: %li\n", $1); }
	| var T_NEWLINE							{ printf("\tResultado: %f\n", $1); }
	//| var T_NEWLINE							{ printf("\tResultado: %f\n", $1); }
	| T_QUIT T_NEWLINE						{ printf("Até mais...\n"); exit(0); }
	;

mixed_expr: T_REAL							{ $$ = $1; }
	| mixed_expr T_PLUS mixed_expr			{ $$ = $1 + $3; }
	| mixed_expr T_MINUS mixed_expr			{ $$ = $1 - $3; }
	| mixed_expr T_MULTIPLY mixed_expr		{ $$ = $1 * $3; }
	| mixed_expr T_DIVIDE mixed_expr		{ $$ = $1 / $3; }
	| mixed_expr T_EXPOENT mixed_expr		{ $$ = pow($1, $3); }
	| T_LEFT mixed_expr T_RIGHT				{ $$ = $2; }
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
	| T_LEFT expr T_RIGHT					{ $$ = $2; }
	//| T_CARAC								{$$ = $1;}
	;

var: T_VAR									{ a = $1; }
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
