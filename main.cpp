//
//  main.cpp
//  HW3
//
//  Created by Tanay Jaiman on 10/17/23.
//

#include <iostream>
#include <cstdlib>

using namespace std;

class BinarySearchTree {
private:
    class Node {
    public:
        Node * parent;
        Node * left;
        Node * right;
        int key;
        string data;
    };
    
public:
    Node * root;
    
    BinarySearchTree() {
        root = nullptr;
    }
    
    bool is_empty() { return root == nullptr; }
    void INORDER_TREE_WALK(Node *);
    void PREORDER_TREE_WALK(Node *);
    void POSTORDER_TREE_WALK(Node *);
    void TREE_INSERT(int);
    void TREE_FIND_MAX(Node *);
    void TREE_REMOVE_MAX(Node *);
    Node * TREE_SUCCESSOR(Node *);
    void DELETE(Node *);
    Node * TREE_SEARCH(int);
};

int main(int argc, const char * argv[]) {
    BinarySearchTree bst;
    int choice, key;
    
    while (true) {
        cout << endl << endl;
        cout << " Binary Search Tree Example " << endl;
        cout << " ----------------------------- " << endl;
        cout << " 1. Insertion " << endl;
        cout << " 2. Pre-Order Traversal " << endl;
        cout << " 3. Post-Order Traversal " << endl;
        cout << " 4. In-Order Traversal " << endl;
        cout << " 5. Find Max " << endl;
        cout << " 6. Remove Max " << endl;
        cout << " 7. Successor " << endl;
        cout << " 8. Delete Node " << endl;
        cout << " 9. Exit " << endl;
        cout << " Enter your choice : ";
        
        cin >> choice;
        switch (choice) {
            case 1:
                cout << " Enter key (int value) to be inserted : ";
                cin >> key;
                bst.TREE_INSERT(key);
                break;
            case 2:
                cout << endl;
                cout << " Pre-Order Traversal " << endl;
                cout << " -------------------" << endl;
                bst.PREORDER_TREE_WALK(bst.root);
                break;
            case 3:
                cout << endl;
                cout << " Post-Order Traversal " << endl;
                cout << " -------------------" << endl;
                bst.POSTORDER_TREE_WALK(bst.root);
                break;
            case 4:
                cout << endl;
                cout << " In-Order Traversal " << endl;
                cout << " -------------------" << endl;
                bst.INORDER_TREE_WALK(bst.root);
                break;
            case 5:
                cout << endl;
                bst.TREE_FIND_MAX(bst.root);
                break;
            case 6:
                cout << endl;
                bst.TREE_REMOVE_MAX(bst.root);
                break;
            case 7:
                cout << endl;
                cout << " Enter key (int value) : ";
                cin >> key;
                cout << " Successor of " << key << " is : " << bst.TREE_SUCCESSOR(bst.TREE_SEARCH(key))->key << endl;
                break;
            case 8:
                cout << endl;
                cout << " Enter key (int value) : ";
                cin >> key;
                bst.DELETE(bst.TREE_SEARCH(key));
                break;
            case 9:
                system("pause");
                return 0;
                break;
            default:
                cout << "Invalid choice";
        }
    }
}

void BinarySearchTree::PREORDER_TREE_WALK(Node * node) {
    if (is_empty()) {
        cout << " The BST is empty!";
        return;
    }
    
    if (node != nullptr) {
        cout << " " << node->key << " ";
        if (node->left) PREORDER_TREE_WALK(node->left);
        if (node->right) PREORDER_TREE_WALK(node->right);
    }
}

void BinarySearchTree::POSTORDER_TREE_WALK(Node * node) {
    if (is_empty()) {
        cout << " The BST is empty!";
        return;
    }
    
    if (node != nullptr) {
        if (node->left) POSTORDER_TREE_WALK(node->left);
        if (node->right) POSTORDER_TREE_WALK(node->right);
        cout << " " << node->key << " ";
    }
}

void BinarySearchTree::INORDER_TREE_WALK(Node * node) {
    if (is_empty()) {
        cout << " The BST is empty!";
        return;
    }
    
    if (node != nullptr) {
        if (node->left) INORDER_TREE_WALK(node->left);
        cout << " " << node->key << endl;
        if (node->right) INORDER_TREE_WALK(node->right);
    }
}

void BinarySearchTree::TREE_INSERT(int key) {
    Node * new_node = new Node;
    new_node->key = key;
    
    if (root == nullptr) {
        root = new_node;
        return;
    }
    
    Node * parent = nullptr;
    Node * iterator = root;
    
    while (iterator != nullptr) {
        parent = iterator;
        
        if (key < iterator->key) iterator = iterator->left;
        else iterator = iterator->right;
    }
    
    if (key < parent->key) {
        parent->left = new_node;
        new_node->parent = parent;
        return;
    }
    
    parent->right = new_node;
    new_node->parent = parent;
}

void BinarySearchTree::TREE_FIND_MAX(Node * node) {
    Node * iterator = node;
    
    if (is_empty()) {
        cout << " The BST is empty!" << endl;
        return;
    }
    
    while (iterator->right) {
        iterator = iterator->right;
    }
    
    cout << " The max value is : " << iterator->key;
}

void BinarySearchTree::TREE_REMOVE_MAX(Node * node) {
    Node * iterator = node;
    
    if (is_empty()) {
        cout << " The BST is empty!";
        return;
    }
    
    if (!iterator->right) {
        if (iterator->left) {
            root = iterator->left;
            return;
        }
        
        root = nullptr;
        return;
    }
    
    while (iterator->right->right) {
        iterator = iterator->right;
    }
    
    if (iterator->right->left) {
        iterator->right = iterator->right->left;
        return;
    }
    
    iterator->right = nullptr;
}

BinarySearchTree::Node * BinarySearchTree::TREE_SUCCESSOR(Node * node) {
    Node * iterator = node;
    
    if (iterator->right) {
        iterator = iterator->right;
        
        while (iterator->left) {
            iterator = iterator->left;
        }
    }
    
    else {
        if (!iterator->parent) {
            cout << " Successor does not exist!" << endl;
        }
        
        while (iterator->parent && iterator->parent->right == iterator) {
            iterator = iterator->parent;
        }
        
        iterator = iterator->parent;
    }
    return iterator;
}

void BinarySearchTree::DELETE(Node * node) {
    Node * temp_node_x = nullptr;
    Node * temp_node_y = nullptr;
    
    if (!node->left || !node->right) {
        temp_node_y = node;
    }
    
    else temp_node_y = TREE_SUCCESSOR(node);
    
    if (temp_node_y->left) {
        temp_node_x = temp_node_y->left;
    }
    
    else temp_node_x = temp_node_y->right;
    
    if (temp_node_x) {
        temp_node_x->parent = temp_node_y->parent;
    }
    
    if (!temp_node_y) root = temp_node_x;
    
    else {
        if (temp_node_y->parent->left == temp_node_y) temp_node_y->parent->left = temp_node_x;
        else temp_node_y->parent->right = temp_node_x;
    }
    
    if (node != temp_node_y) node->key = temp_node_y->key;
}

BinarySearchTree::Node * BinarySearchTree::TREE_SEARCH(int key) {
    Node * iterator = root;
    
    while (iterator) {
        if (key < iterator->key) {
            iterator = iterator->left;
        }
        
        else if (key == iterator->key) {
            break;
        }
        
        else {
            iterator = iterator->right;
        }
    }
    
    return iterator;
}
