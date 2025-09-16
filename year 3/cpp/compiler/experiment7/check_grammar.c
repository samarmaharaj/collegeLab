#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define a structure to hold the productions of the grammar
#define MAX_PRODUCTIONS 10
#define MAX_RHS_LEN 50

typedef struct {
    char lhs;
    char rhs[MAX_PRODUCTIONS][MAX_RHS_LEN];
    int count; // Number of productions for this LHS
} ProductionRule;

// Function to find the longest common prefix between two strings
int find_common_prefix_len(const char *s1, const char *s2) {
    int len = 0;
    while (s1[len] && s2[len] && s1[len] == s2[len]) {
        len++;
    }
    return len;
}

// Function to check for direct left recursion
void check_left_recursion(const ProductionRule *rules, int n) {
    printf("\n--- Checking for Direct Left Recursion ---\n");
    int found_recursion = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < rules[i].count; j++) {
            // A -> A... is a direct left recursion
            if (rules[i].lhs == rules[i].rhs[j][0]) {
                printf("Direct Left Recursion found in rule: %c -> %s\n", rules[i].lhs, rules[i].rhs[j]);
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
void check_left_factoring(const ProductionRule *rules, int n) {
    printf("\n--- Checking for Left Factoring ---\n");
    int needs_factoring = 0;

    for (int i = 0; i < n; i++) {
        // We only need to check if a non-terminal has more than one production
        if (rules[i].count < 2) {
            continue;
        }

        // Compare each pair of productions for the same non-terminal
        for (int j = 0; j < rules[i].count - 1; j++) {
            for (int k = j + 1; k < rules[i].count; k++) {
                int common_len = find_common_prefix_len(rules[i].rhs[j], rules[i].rhs[k]);
                if (common_len > 0) {
                    char prefix[MAX_RHS_LEN];
                    strncpy(prefix, rules[i].rhs[j], common_len);
                    prefix[common_len] = '\0';
                    
                    printf("Grammar needs Left Factoring for non-terminal '%c'.\n", rules[i].lhs);
                    printf("Common prefix '%s' found in productions:\n", prefix);
                    printf("  - %c -> %s\n", rules[i].lhs, rules[i].rhs[j]);
                    printf("  - %c -> %s\n", rules[i].lhs, rules[i].rhs[k]);
                    needs_factoring = 1;
                    
                    // Go to the next non-terminal once factoring is detected for the current one
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


int main() {
    int n;
    printf("Enter the number of production rules: ");
    scanf("%d", &n);
    getchar(); // Consume the newline character left by scanf

    if (n <= 0) {
        printf("Invalid number of rules.\n");
        return 1;
    }

    ProductionRule rules[n];
    
    printf("\nEnter the grammar rules (e.g., E->E+T|T):\n");

    for (int i = 0; i < n; i++) {
        char buffer[256];
        printf("Rule %d: ", i + 1);
        fgets(buffer, sizeof(buffer), stdin);
        
        // Remove newline character if present
        buffer[strcspn(buffer, "\n")] = 0;

        // Parse the input string
        char *lhs_ptr = strtok(buffer, "->");
        char *rhs_ptr = strtok(NULL, "");
        
        if (lhs_ptr == NULL || rhs_ptr == NULL || strlen(lhs_ptr) != 1) {
            printf("Invalid rule format. Please use 'A->alpha|beta'. Skipping this rule.\n");
            i--; // Retry this rule
            continue;
        }

        rules[i].lhs = lhs_ptr[0];
        rules[i].count = 0;

        // Split the RHS by '|'
        char *token = strtok(rhs_ptr, "|");
        while (token != NULL) {
            if (rules[i].count < MAX_PRODUCTIONS) {
                strcpy(rules[i].rhs[rules[i].count], token);
                rules[i].count++;
            } else {
                printf("Warning: Exceeded maximum productions for one non-terminal.\n");
                break;
            }
            token = strtok(NULL, "|");
        }
    }
    
    // Perform checks
    check_left_recursion(rules, n);
    check_left_factoring(rules, n);

    return 0;
}
