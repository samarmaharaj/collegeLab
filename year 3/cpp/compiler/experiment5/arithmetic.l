/* Write a program Using flex to recognise a valid arithmetic 
expression and to recognise the identifiers and operators present */

%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char identifiers[100][100];
char operators[100][5];
char numbers[100][50];
int id_count = 0;
int op_count = 0;
int num_count = 0;
int valid_expression = 1;

void add_unique_identifier(char *ident) {
    for (int i = 0; i < id_count; i++) {
        if (strcmp(identifiers[i], ident) == 0) {
            return; // Already exists
        }
    }
    strcpy(identifiers[id_count++], ident);
}

void add_unique_operator(char *op) {
    for (int i = 0; i < op_count; i++) {
        if (strcmp(operators[i], op) == 0) {
            return; // Already exists
        }
    }
    strcpy(operators[op_count++], op);
}
%}

IDENT [a-zA-Z_][a-zA-Z0-9_]*
NUMBER [0-9]+(\.[0-9]+)?
OPERATOR [+\-*/%()\[\]{}]
ASSIGNMENT [=]
WHITESPACE [ \t]+

%%
{IDENT} {
    add_unique_identifier(yytext);
    printf("Identifier: %s\n", yytext);
}

{NUMBER} {
    strcpy(numbers[num_count++], yytext);
    printf("Number: %s\n", yytext);
}

{OPERATOR} {
    add_unique_operator(yytext);
    printf("Operator: %s\n", yytext);
}

{ASSIGNMENT} {
    add_unique_operator(yytext);
    printf("Assignment: %s\n", yytext);
}

{WHITESPACE} ; /* ignore whitespace */

\n {
    return 0; /* End of input */
}

. {
    printf("Invalid Character: %s\n", yytext);
    valid_expression = 0;
}

%%

int main(int argc, char **argv) {
    printf("Enter an arithmetic expression: ");
    
    printf("\n--- Parsing Input ---\n");
    yylex();
    
    printf("\n--- Results ---\n");
    
    if (valid_expression) {
        printf("✓ Expression parsing completed\n\n");
    } else {
        printf("✗ Invalid characters found in expression\n\n");
    }

    if (id_count > 0) {
        printf("Identifiers found (%d):\n", id_count);
        for (int i = 0; i < id_count; i++) {
            printf("  %d. %s\n", i+1, identifiers[i]);
        }
        printf("\n");
    } else {
        printf("No identifiers found.\n\n");
    }

    if (op_count > 0) {
        printf("Operators found (%d):\n", op_count);
        for (int i = 0; i < op_count; i++) {
            printf("  %d. %s\n", i+1, operators[i]);
        }
        printf("\n");
    } else {
        printf("No operators found.\n\n");
    }

    if (num_count > 0) {
        printf("Numbers found (%d):\n", num_count);
        for (int i = 0; i < num_count; i++) {
            printf("  %d. %s\n", i+1, numbers[i]);
        }
        printf("\n");
    } else {
        printf("No numbers found.\n\n");
    }

    return 0;
}

int yywrap() {
    return 1;
}