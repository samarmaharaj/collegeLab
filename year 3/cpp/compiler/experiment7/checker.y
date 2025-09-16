%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// External declarations for Flex
extern int yylex();
extern int yyparse();
extern FILE *yyin;

void yyerror(const char *s);

// --- Data Structures (similar to the C-only version) ---
#define MAX_RULES 20
#define MAX_PRODUCTIONS 10
#define MAX_RHS_LEN 50

typedef struct {
    char lhs;
    char rhs[MAX_PRODUCTIONS][MAX_RHS_LEN];
    int count;
} ProductionRule;

ProductionRule grammar[MAX_RULES];
int rule_count = 0;
int current_lhs_index = -1;

// Helper to find or add a non-terminal to our grammar structure
int find_or_add_rule(char lhs) {
    for (int i = 0; i < rule_count; i++) {
        if (grammar[i].lhs == lhs) {
            return i;
        }
    }
    if (rule_count < MAX_RULES) {
        grammar[rule_count].lhs = lhs;
        grammar[rule_count].count = 0;
        return rule_count++;
    }
    return -1; // Error: Too many rules
}

// --- Analysis Functions (copied from the C-only version) ---

// Function to find the longest common prefix between two strings
int find_common_prefix_len(const char *s1, const char *s2) {
    int len = 0;
    while (s1[len] && s2[len] && s1[len] == s2[len] && s1[len] != ' ') {
        len++;
    }
    return len;
}

// Function to check for direct left recursion
void check_left_recursion() {
    printf("\n--- Checking for Direct Left Recursion ---\n");
    int found_recursion = 0;
    
    for (int i = 0; i < rule_count; i++) {
        for (int j = 0; j < grammar[i].count; j++) {
            if (grammar[i].lhs == grammar[i].rhs[j][0]) {
                printf("Direct Left Recursion found in rule: %c -> %s\n", grammar[i].lhs, grammar[i].rhs[j]);
                found_recursion = 1;
            }
        }
    }

    if (!found_recursion) {
        printf("No direct left recursion found in the grammar.\n");
    }
    printf("-----------------------------------------\n");
}

// Function to check for left factoring
void check_left_factoring() {
    printf("\n--- Checking for Left Factoring ---\n");
    int needs_factoring = 0;

    for (int i = 0; i < rule_count; i++) {
        if (grammar[i].count < 2) continue;

        for (int j = 0; j < grammar[i].count - 1; j++) {
            for (int k = j + 1; k < grammar[i].count; k++) {
                int common_len = find_common_prefix_len(grammar[i].rhs[j], grammar[i].rhs[k]);
                if (common_len > 0) {
                    char prefix[MAX_RHS_LEN];
                    strncpy(prefix, grammar[i].rhs[j], common_len);
                    prefix[common_len] = '\0';
                    
                    printf("Grammar needs Left Factoring for non-terminal '%c'.\n", grammar[i].lhs);
                    printf("Common prefix '%s' found in productions:\n", prefix);
                    printf("  - %c -> %s\n", grammar[i].lhs, grammar[i].rhs[j]);
                    printf("  - %c -> %s\n", grammar[i].lhs, grammar[i].rhs[k]);
                    needs_factoring = 1;
                    goto next_rule;
                }
            }
        }
    next_rule:;
    }

    if (!needs_factoring) {
        printf("The grammar does not require left factoring.\n");
    }
    printf("-------------------------------------\n");
}

%}

// Define the type of values for tokens
%union {
    char *str;
}

// Define tokens and their types
%token <str> NON_TERMINAL
%token <str> TERMINAL
%token ARROW PIPE SEMICOLON

// ***** FIX: Define types for non-terminals that return a value *****
%type <str> production symbol_sequence symbol

// The top-level rule
%start grammar_input

%%

grammar_input:
    rules {
        printf("\nGrammar parsed successfully. Running checks...\n");
        check_left_recursion();
        check_left_factoring();
    }
;

rules:
    /* empty */
    | rules rule
;

rule:
    NON_TERMINAL ARROW productions SEMICOLON {
        // We are done with this rule, free the LHS token string
        free($1);
    }
;

productions:
    production {
        // First production for this rule
        current_lhs_index = find_or_add_rule($<str>0[0]);
        if(current_lhs_index != -1 && grammar[current_lhs_index].count < MAX_PRODUCTIONS) {
            strcpy(grammar[current_lhs_index].rhs[grammar[current_lhs_index].count++], $1);
        }
        free($1);
    }
    | productions PIPE production {
        // Subsequent productions for the same rule
        if(current_lhs_index != -1 && grammar[current_lhs_index].count < MAX_PRODUCTIONS) {
            strcpy(grammar[current_lhs_index].rhs[grammar[current_lhs_index].count++], $3);
        }
        free($3);
    }
;

production:
    /* empty production */ { $$ = strdup(""); }
    | symbol_sequence    { $$ = $1; }
;

symbol_sequence:
    symbol { $$ = $1; }
    | symbol_sequence symbol {
        // Concatenate symbols to form the RHS string
        char* temp = malloc(strlen($1) + strlen($2) + 1);
        strcpy(temp, $1);
        strcat(temp, $2);
        $$ = temp;
        free($1);
        free($2);
    }
;

symbol:
    NON_TERMINAL { $$ = $1; }
    | TERMINAL   { $$ = $1; }
;

%%

int main(int argc, char **argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror(argv[1]);
            return 1;
        }
    } else {
        printf("Usage: %s <grammar_file>\n", argv[0]);
        printf("Reading grammar from standard input (end with Ctrl+D):\n");
        yyin = stdin;
    }

    yyparse();

    if (yyin != stdin) {
        fclose(yyin);
    }
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
}

