#include <iostream>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    bool color;
    Node *left, *right, *parent;

    Node(int data) : data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RBTree {
private:
    Node* root;

    void rotateLeft(Node* &x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nullptr) y->left->parent = x;
        y->parent = x->parent;

        if (x->parent == nullptr) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    void rotateRight(Node* &x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != nullptr) y->right->parent = x;
        y->parent = x->parent;

        if (x->parent == nullptr) root = y;
        else if (x == x->parent->right) x->parent->right = y;
        else x->parent->left = y;

        y->right = x;
        x->parent = y;
    }

    void fixViolation(Node* &z) {
        while (z->parent != nullptr && z->parent->color == RED) {
            Node* grandparent = z->parent->parent;
            if (z->parent == grandparent->left) {
                Node* uncle = grandparent->right;
                if (uncle != nullptr && uncle->color == RED) {
                    // Case 1
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    z = grandparent;
                } else {
                    // Case 2 or 3
                    if (z == z->parent->right) {
                        z = z->parent;
                        rotateLeft(z);
                    }
                    z->parent->color = BLACK;
                    grandparent->color = RED;
                    rotateRight(grandparent);
                }
            } else {
                Node* uncle = grandparent->left;
                if (uncle != nullptr && uncle->color == RED) {
                    // Case 1
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    z = grandparent;
                } else {
                    // Case 2 or 3
                    if (z == z->parent->left) {
                        z = z->parent;
                        rotateRight(z);
                    }
                    z->parent->color = BLACK;
                    grandparent->color = RED;
                    rotateLeft(grandparent);
                }
            }
        }
        root->color = BLACK;
    }

    void inorderHelper(Node* root) {
        if (root == nullptr) return;
        inorderHelper(root->left);
        cout << root->data << (root->color == RED ? " (R) " : " (B) ");
        inorderHelper(root->right);
    }

    // Helper function for search
    Node* searchHelper(Node* root, int value) {
        if (root == nullptr || root->data == value)
            return root;
        if (value < root->data)
            return searchHelper(root->left, value);
        return searchHelper(root->right, value);
    }

public:
    RBTree() : root(nullptr) {}

    void insert(int data) {
        Node* newNode = new Node(data);
        Node* y = nullptr;
        Node* x = root;

        while (x != nullptr) {
            y = x;
            if (newNode->data < x->data) x = x->left;
            else x = x->right;
        }

        newNode->parent = y;
        if (y == nullptr) root = newNode;
        else if (newNode->data < y->data) y->left = newNode;
        else y->right = newNode;

        fixViolation(newNode);
    }

    void inorder() {
        cout << "In-order Traversal: ";
        inorderHelper(root);
        cout << "\n";
    }

    // Search for a node
    bool search(int value) {
        Node* result = searchHelper(root, value);
        if (result == nullptr)
            return false;  // Node not found
        else
            return true;   // Node found
    }
};

int main() {
    RBTree tree;

    int n, val, searchVal;
    cout << "Enter number of nodes to insert: ";
    cin >> n;

    cout << "Enter values:\n";
    for (int i = 0; i < n; ++i) {
        cin >> val;
        tree.insert(val);
    }

    tree.inorder();

    cout << "\nEnter value to search in the tree: ";
    cin >> searchVal;

    if (tree.search(searchVal)) {
        cout << "Node with value " << searchVal << " found in the tree.\n";
    } else {
        cout << "Node with value " << searchVal << " not found in the tree.\n";
    }

    return 0;
}
