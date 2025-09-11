#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
};

class BinarySearchTree {
public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int value) {
        root = insertRec(root, value);
    }

    void preorder() {
        preorderRec(root);
        cout << endl;
    }

    void inorder() {
        inorderRec(root);
        cout << endl;
    }

    void postorder() {
        postorderRec(root);
        cout << endl;
    }

    void deleteNode(int value) {
        root = deleteRec(root, value);
    }

private:
    Node* root;

    Node* insertRec(Node* node, int value) {
        if (node == nullptr) {
            node = new Node;
            node->data = value;
            node->left = node->right = nullptr;
        } else if ( value > node->data) {
            node->right = insertRec(node->right, value);
        } else {
            node->left = insertRec(node->left, value);
        }
    }

    void preorderRec(Node* node) {
        if (node != nullptr) {
            cout << node->data << " ";
            preorderRec(node->left);
            preorderRec(node->right);
        }
    }

    void inorderRec(Node* node) {
        if (node != nullptr) {
            inorderRec(node->left);
            cout << node->data << " ";
            inorderRec(node->right);
        }
    }

    void postorderRec(Node* node) {
        if (node != nullptr) {
            postorderRec(node->left);
            postorderRec(node->right);
            cout << node->data << " ";
        }
    }

    Node* minValueNode(Node* node) {
        if ( node == nullptr) {
            return node;
        }

        Node* ptr = node;
        while (ptr && ptr->left != nullptr) {
            ptr = ptr->left;
        }

        return ptr;
    }

    Node* deleteRec(Node* node, int value) {
        if ( node == nullptr) {
            return node;
        }

        if (value < node->data) {
            node->left = deleteRec(node->left, value);
        } else if ( value > node->data) {
            node->right = deleteRec(node->right, value);
        } else {
            if (node->left == nullptr) {
                Node* ptr = node->right;
                delete node;
                return ptr;
            } else if (node->right == nullptr) {
                Node* ptr = node->left;
                delete node;
                return ptr;
            } else {
                Node* ptr = minValueNode(node->right);
                node->data = ptr->data;
                node->right = deleteRec(node->right, ptr->data);
            }
        }
    }
};