%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

// External declarations for Flex
extern int yylex();
extern char* yytext;

// Function to report parsing errors
void yyerror(const char *s);

// Root of our parse tree
Node *root = NULL;

%}

// Define the union for token values
%union {
    char *sval; // String value for identifiers and numbers
    struct Node* nval; // Node value for grammar rules
}

// Define token types and their associated union member
%token <sval> ID NUM
%token ADD MUL LPAREN RPAREN

// Define non-terminal types and their associated union member
%type <nval> E T F

// Grammar rules
%%

program:
    E { root = $1; printf("Parsing successful. String belongs to the grammar.\n"); }
    ;

E:
    E ADD T { $$ = create_node("+", $1, $3); }
    | T       { $$ = $1; }
    ;

T:
    T MUL F { $$ = create_node("*", $1, $3); }
    | F       { $$ = $1; }
    ;

F:
    LPAREN E RPAREN { $$ = $2; } // We pass the E node up
    | ID             { $$ = create_node($1, NULL, NULL); }
    | NUM            { $$ = create_node($1, NULL, NULL); }
    ;

%%

// C code to be included in the final C file
#include "tree.h"

// Function to create a new node for the parse tree
Node* create_node(char* token, Node* left, Node* right) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        yyerror("Memory allocation failed");
        exit(1);
    }
    newNode->token = strdup(token);
    newNode->left = left;
    newNode->right = right;
    return newNode;
}

// Function to print the parse tree (pre-order traversal)
void print_tree(Node* node, int level) {
    if (!node) {
        return;
    }
    printf("|");
    for (int i = 0; i < level; i++) {
        printf("    |");
    }
    printf("-- %s\n", node->token);
    print_tree(node->left, level + 1);
    print_tree(node->right, level + 1);
}

// Main function to drive the parser
int main() {
    printf("Enter an arithmetic expression (e.g., 'a * (b + 2)'):\n");
    yyparse(); // Start parsing

    if (root) {
        printf("\n--- Parse Tree ---\n");
        print_tree(root, 0);
    }
    return 0;
}

// Error reporting function
void yyerror(const char *s) {
    fprintf(stderr, "Parsing Error: %s\n", s);
}
