#ifndef TREE_H
#define TREE_H

// Node type for the parse tree
typedef struct Node {
    char* token;           // The token string (e.g., "E", "T", "+", "id")
    struct Node *left;     // Left child (can be null)
    struct Node *right;    // Right child (can be null)
} Node;

// Function to create a new node
Node* create_node(char* token, Node* left, Node* right);

// Function to print the parse tree (pre-order traversal)
void print_tree(Node* node, int level);

#endif // TREE_H
