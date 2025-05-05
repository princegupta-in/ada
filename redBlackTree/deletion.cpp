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

    // Case when the node to be deleted has two children
    void replaceNode(Node* &oldNode, Node* &newNode) {
        if (oldNode->parent == nullptr) root = newNode;
        else if (oldNode == oldNode->parent->left) oldNode->parent->left = newNode;
        else oldNode->parent->right = newNode;

        if (newNode != nullptr) newNode->parent = oldNode->parent;
    }

    // Fix the Red-Black Tree after deletion
    void fixAfterDeletion(Node* &x) {
        while (x != root && (x == nullptr || x->color == BLACK)) {
            if (x == x->parent->left) {
                Node* sibling = x->parent->right;
                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    x->parent->color = RED;
                    rotateLeft(x->parent);
                    sibling = x->parent->right;
                }

                if ((sibling->left == nullptr || sibling->left->color == BLACK) && (sibling->right == nullptr || sibling->right->color == BLACK)) {
                    sibling->color = RED;
                    x = x->parent;
                } else {
                    if (sibling->right == nullptr || sibling->right->color == BLACK) {
                        if (sibling->left != nullptr) sibling->left->color = BLACK;
                        sibling->color = RED;
                        rotateRight(sibling);
                        sibling = x->parent->right;
                    }

                    sibling->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (sibling->right != nullptr) sibling->right->color = BLACK;
                    rotateLeft(x->parent);
                    x = root;
                }
            } else {
                Node* sibling = x->parent->left;
                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    x->parent->color = RED;
                    rotateRight(x->parent);
                    sibling = x->parent->left;
                }

                if ((sibling->left == nullptr || sibling->left->color == BLACK) && (sibling->right == nullptr || sibling->right->color == BLACK)) {
                    sibling->color = RED;
                    x = x->parent;
                } else {
                    if (sibling->left == nullptr || sibling->left->color == BLACK) {
                        if (sibling->right != nullptr) sibling->right->color = BLACK;
                        sibling->color = RED;
                        rotateLeft(sibling);
                        sibling = x->parent->left;
                    }

                    sibling->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (sibling->left != nullptr) sibling->left->color = BLACK;
                    rotateRight(x->parent);
                    x = root;
                }
            }
        }

        if (x != nullptr) x->color = BLACK;
    }

    // Delete the node with the given value
    void deleteNodeHelper(Node* &root, int value) {
        Node* nodeToDelete = searchHelper(root, value);
        if (nodeToDelete == nullptr) return;

        Node* child;
        Node* replacement;
        bool originalColor = nodeToDelete->color;

        if (nodeToDelete->left == nullptr) {
            replacement = nodeToDelete->right;
            replaceNode(nodeToDelete, nodeToDelete->right);
        } else if (nodeToDelete->right == nullptr) {
            replacement = nodeToDelete->left;
            replaceNode(nodeToDelete, nodeToDelete->left);
        } else {
            replacement = minimum(nodeToDelete->right);
            originalColor = replacement->color;
            child = replacement->right;
            if (replacement->parent == nodeToDelete) child->parent = replacement;
            else {
                replaceNode(replacement, replacement->right);
                replacement->right = nodeToDelete->right;
                replacement->right->parent = replacement;
            }

            replaceNode(nodeToDelete, replacement);
            replacement->left = nodeToDelete->left;
            replacement->left->parent = replacement;
            replacement->color = nodeToDelete->color;
        }

        if (originalColor == BLACK) fixAfterDeletion(child);
    }

    Node* minimum(Node* node) {
        while (node->left != nullptr) node = node->left;
        return node;
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

    bool search(int value) {
        Node* result = searchHelper(root, value);
        return result != nullptr;
    }

    void deleteNode(int value) {
        deleteNodeHelper(root, value);
    }
};

int main() {
    RBTree tree;

    int n, val, searchVal, deleteVal;
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

    cout << "\nEnter value to delete from the tree: ";
    cin >> deleteVal;
    tree.deleteNode(deleteVal);
    tree.inorder();

    return 0;
}
