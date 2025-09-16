%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// External declarations for Flex
extern int yylex();
extern int yyparse();
extern FILE *yyin;
void yyerror(const char *s);

// --- Data Structures ---
#define MAX_RULES 50
#define MAX_PRODUCTIONS 20
#define MAX_RHS_LEN 50
#define EPSILON "e"

typedef struct {
    char lhs;
    char rhs[MAX_PRODUCTIONS][MAX_RHS_LEN];
    int count;
    bool visited; // For analysis
} ProductionRule;

ProductionRule grammar[MAX_RULES];
int rule_count = 0;
int current_lhs_index = -1;

// --- Helper Functions ---
int find_or_add_rule(char lhs);
void print_grammar();
char get_new_non_terminal();
void eliminate_left_recursion();
void eliminate_left_factoring();

// Find or add a non-terminal to our grammar structure
int find_or_add_rule(char lhs) {
    for (int i = 0; i < rule_count; i++) {
        if (grammar[i].lhs == lhs) return i;
    }
    if (rule_count < MAX_RULES) {
        grammar[rule_count].lhs = lhs;
        grammar[rule_count].count = 0;
        grammar[rule_count].visited = false;
        return rule_count++;
    }
    return -1; // Error: Too many rules
}

// Get an unused non-terminal character, starting from Z
char get_new_non_terminal() {
    for (char nt = 'Z'; nt >= 'A'; --nt) {
        bool used = false;
        for (int i = 0; i < rule_count; i++) {
            if (grammar[i].lhs == nt) {
                used = true;
                break;
            }
        }
        if (!used) return nt;
    }
    return '\0'; // No available non-terminals
}

// --- Transformation Logic ---

void eliminate_left_recursion() {
    printf("\n--- Step 1: Eliminating Direct Left Recursion ---\n");
    bool changed = false;

    // Iterate over a copy of the initial rule count, as we might add new rules
    int original_rule_count = rule_count;
    for (int i = 0; i < original_rule_count; i++) {
        char current_lhs = grammar[i].lhs;
        char recursive[MAX_PRODUCTIONS][MAX_RHS_LEN];
        char non_recursive[MAX_PRODUCTIONS][MAX_RHS_LEN];
        int rec_count = 0, non_rec_count = 0;

        // Partition productions into recursive and non-recursive
        for (int j = 0; j < grammar[i].count; j++) {
            if (grammar[i].rhs[j][0] == current_lhs) {
                strcpy(recursive[rec_count++], grammar[i].rhs[j] + 1); // Store alpha
            } else {
                strcpy(non_recursive[non_rec_count++], grammar[i].rhs[j]); // Store beta
            }
        }

        if (rec_count > 0) {
            changed = true;
            if (non_rec_count == 0) {
                printf("Warning: Grammar has non-terminating rule %c that cannot be fixed automatically.\n", current_lhs);
                continue;
            }

            char new_lhs = get_new_non_terminal();
            if (new_lhs == '\0') {
                printf("Error: Ran out of non-terminals to use for left recursion elimination.\n");
                return;
            }
            
            // 1. Rewrite the original rule: A -> beta A'
            grammar[i].count = 0;
            for (int k = 0; k < non_rec_count; k++) {
                // Handle epsilon case for beta
                if (strcmp(non_recursive[k], EPSILON) == 0) {
                     sprintf(grammar[i].rhs[grammar[i].count++], "%c", new_lhs);
                } else {
                     sprintf(grammar[i].rhs[grammar[i].count++], "%s%c", non_recursive[k], new_lhs);
                }
            }

            // 2. Create the new rule: A' -> alpha A' | e
            int new_rule_idx = find_or_add_rule(new_lhs);
            for (int k = 0; k < rec_count; k++) {
                sprintf(grammar[new_rule_idx].rhs[grammar[new_rule_idx].count++], "%s%c", recursive[k], new_lhs);
            }
            strcpy(grammar[new_rule_idx].rhs[grammar[new_rule_idx].count++], EPSILON);
        }
    }
    if (!changed) {
        printf("No direct left recursion was found.\n");
    }
}

void eliminate_left_factoring() {
    printf("\n--- Step 2: Eliminating Left Factoring ---\n");
    bool changed_in_pass = true;
    int pass = 0;

    while (changed_in_pass) {
        changed_in_pass = false;
        pass++;

        for (int i = 0; i < rule_count; i++) {
            for (int j = 0; j < grammar[i].count; j++) {
                char prefix[MAX_RHS_LEN] = {0};
                char common_group[MAX_PRODUCTIONS][MAX_RHS_LEN];
                int common_indices[MAX_PRODUCTIONS];
                int common_count = 0;

                // Find productions with a common prefix starting from rhs[j]
                if (strlen(grammar[i].rhs[j]) > 0 && grammar[i].rhs[j][0] != '\0') {
                    strncpy(prefix, grammar[i].rhs[j], 1);
                    common_indices[common_count] = j;
                    strcpy(common_group[common_count++], grammar[i].rhs[j]);
                } else {
                    continue; // Skip empty productions for prefix search
                }

                for (int k = j + 1; k < grammar[i].count; k++) {
                    if (strncmp(grammar[i].rhs[j], grammar[i].rhs[k], 1) == 0) {
                        common_indices[common_count] = k;
                        strcpy(common_group[common_count++], grammar[i].rhs[k]);
                    }
                }
                
                if (common_count > 1) {
                    changed_in_pass = true;

                    char new_lhs = get_new_non_terminal();
                    if (new_lhs == '\0') {
                        printf("Error: Ran out of non-terminals for left factoring.\n");
                        return;
                    }
                    
                    int new_rule_idx = find_or_add_rule(new_lhs);
                    
                    // Add suffixes to the new rule A'
                    for(int k = 0; k < common_count; k++) {
                        char* suffix = common_group[k] + 1;
                        if (strlen(suffix) == 0) {
                            strcpy(grammar[new_rule_idx].rhs[grammar[new_rule_idx].count++], EPSILON);
                        } else {
                            strcpy(grammar[new_rule_idx].rhs[grammar[new_rule_idx].count++], suffix);
                        }
                    }

                    // Remove old productions from A by shifting
                    for (int k = common_count - 1; k >= 0; k--) {
                        int idx_to_remove = common_indices[k];
                        for (int m = idx_to_remove; m < grammar[i].count - 1; m++) {
                            strcpy(grammar[i].rhs[m], grammar[i].rhs[m + 1]);
                        }
                        grammar[i].count--;
                    }
                    
                    // Add the new factored production to A
                    sprintf(grammar[i].rhs[grammar[i].count++], "%s%c", prefix, new_lhs);

                    goto next_rule; // Restart scan for this rule
                }
            }
        next_rule:;
        }
    }
    if (pass == 1 && !changed_in_pass) {
        printf("Grammar does not require left factoring.\n");
    }
}


// --- Printing and Main Logic ---

void print_grammar() {
    printf("\n--- Final Transformed Grammar ---\n");
    for (int i = 0; i < rule_count; i++) {
        printf("%c -> ", grammar[i].lhs);
        for (int j = 0; j < grammar[i].count; j++) {
            printf("%s", grammar[i].rhs[j]);
            if (j < grammar[i].count - 1) {
                printf(" | ");
            }
        }
        printf("\n");
    }
     printf("---------------------------------\n");
}

%}

%union { char *str; }

%token <str> NON_TERMINAL TERMINAL
%token ARROW PIPE SEMICOLON

%type <str> production symbol_sequence symbol

%start grammar_input

%%

grammar_input:
    rules {
        printf("\nGrammar parsed successfully. Applying transformations...\n");
        eliminate_left_recursion();
        eliminate_left_factoring();
        print_grammar();
    }
;

rules: | rules rule ;

rule:
    NON_TERMINAL ARROW productions SEMICOLON { free($1); }
;

productions:
    production {
        current_lhs_index = find_or_add_rule($<str>0[0]);
        if(current_lhs_index != -1 && grammar[current_lhs_index].count < MAX_PRODUCTIONS) {
            strcpy(grammar[current_lhs_index].rhs[grammar[current_lhs_index].count++], $1);
        }
        free($1);
    }
    | productions PIPE production {
        if(current_lhs_index != -1 && grammar[current_lhs_index].count < MAX_PRODUCTIONS) {
            strcpy(grammar[current_lhs_index].rhs[grammar[current_lhs_index].count++], $3);
        }
        free($3);
    }
;

production:
    /* empty production is not allowed, use 'e' for epsilon */
    symbol_sequence { $$ = $1; }
;

symbol_sequence:
    symbol { $$ = $1; }
    | symbol_sequence symbol {
        char* temp = malloc(strlen($1) + strlen($2) + 2); // space for null and char
        sprintf(temp, "%s%s", $1, $2);
        $$ = temp;
        free($1);
        free($2);
    }
;

symbol: NON_TERMINAL { $$ = $1; } | TERMINAL { $$ = $1; };

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
        printf("Enter grammar rules. End each rule with ; and press Ctrl+D when done.\n");
        yyin = stdin;
    }
    yyparse();
    if (yyin != stdin) fclose(yyin);
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
}
