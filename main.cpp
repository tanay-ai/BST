//
//  main.cpp
//  HW3
//
//  Created by Tanay Jaiman on 10/17/23.
//

#include <iostream>
#include <cstdlib>

using namespace std;

// BST Class
class BinarySearchTree {
private:
    class Node {
    public:
        Node * parent;  // Stores the parent node ptr
        Node * left;    // Stores the left node ptr
        Node * right;   // Stores the right node ptr
        int key;        // Stores the key
        string data;    // Stores data
    };
    
public:
    Node * root;
    
    BinarySearchTree() {
        root = nullptr; // Root ptr initialized to NULL when constructor is called
    }
    
    // Forward declarations
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
        
        // Recording user choice...
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
            // 1. Insert
            case 1:
                cout << " Enter key (int value) to be inserted : ";
                cin >> key;
                bst.TREE_INSERT(key);
                break;
                
            // 2. Pre-Order Traversal
            case 2:
                cout << endl;
                cout << " Pre-Order Traversal " << endl;
                cout << " -------------------" << endl;
                bst.PREORDER_TREE_WALK(bst.root);
                break;
                
            // 3. Post-Order Traversal
            case 3:
                cout << endl;
                cout << " Post-Order Traversal " << endl;
                cout << " -------------------" << endl;
                bst.POSTORDER_TREE_WALK(bst.root);
                break;
                
            // 4. In-Order Traversal
            case 4:
                cout << endl;
                cout << " In-Order Traversal " << endl;
                cout << " -------------------" << endl;
                bst.INORDER_TREE_WALK(bst.root);
                break;
            
            // 5. Find Max
            case 5:
                cout << endl;
                bst.TREE_FIND_MAX(bst.root);
                break;
            
            // 6. Remove Max
            case 6:
                cout << endl;
                bst.TREE_REMOVE_MAX(bst.root);
                break;
                
            // 7. Find Successor
            case 7:
                cout << endl;
                cout << " Enter key (int value) : ";
                cin >> key;
                cout << " Successor of " << key << " is : " << bst.TREE_SUCCESSOR(bst.TREE_SEARCH(key))->key << endl;
                break;
                
            // 8. Delete
            case 8:
                cout << endl;
                cout << " Enter key (int value) : ";
                cin >> key;
                bst.DELETE(bst.TREE_SEARCH(key));
                break;
                
            // 9. Exit
            case 9:
                system("pause");
                return 0;
                break;
            
            // Invalid choice
            default:
                cout << " Invalid choice.";
        }
    }
}

// PREORDER_TREE_WALK : Preorder traversal of the BST.
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

// POSTORDER_TREE_WALK : Postorder traversal of BST.
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

// INORDER_TREE_WALK : Inorder traversal of BST.
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

// TREE_INSERT : Inserts a Node with the given "key"
void BinarySearchTree::TREE_INSERT(int key) {
    
    // new_node : Node to be inserted
    Node * new_node = new Node;
    new_node->key = key;
    
    // Case : BST is empty
    if (root == nullptr) {
        root = new_node;
        return;
    }
    
    // Iterate till you find the parent
    Node * parent = nullptr;
    Node * iterator = root;
    
    while (iterator != nullptr) {
        parent = iterator;
        
        if (key < iterator->key) iterator = iterator->left;
        else iterator = iterator->right;
    }
    
    // Insert on left if "key" < parent.key
    if (key < parent->key) {
        parent->left = new_node;
        new_node->parent = parent;
        return;
    }
    
    // Insert on right is "key" > parent.key
    parent->right = new_node;
    new_node->parent = parent;
}

// TREE_FIND_MAX : Find the maximum value in the BST
void BinarySearchTree::TREE_FIND_MAX(Node * node) {
    Node * iterator = node;
    
    if (is_empty()) {
        cout << " The BST is empty!" << endl;
        return;
    }
    
    // Iterate to find the right-most (max) value in the BST
    while (iterator->right) {
        iterator = iterator->right;
    }
    
    cout << " The max value is : " << iterator->key;
}

// TREE_REMOVE_MAX : Remove the maximum value in the BST
void BinarySearchTree::TREE_REMOVE_MAX(Node * node) {
    Node * iterator = node;
    
    if (is_empty()) {
        cout << " The BST is empty!";
        return;
    }
    
    // Iterate till you find the right-most (max) value
    while (iterator->right) {
        iterator = iterator->right;
    }
    
    // Remove and Delete the value from the BST
    DELETE(iterator);
}

// TREE_SUCCESSOR : Find the shortest possible value bigger than the node.key
BinarySearchTree::Node * BinarySearchTree::TREE_SUCCESSOR(Node * node) {
    Node * iterator = node;
    
    // If node has a child on right, find the shortest value in that sub-tree which is also the successor
    if (iterator->right) {
        iterator = iterator->right;
        
        while (iterator->left) {
            iterator = iterator->left;
        }
    }
    
    // Else iterate through the parents to find root of sub-tree, parent of that sub-tree is the successor
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

// DELETE : Remove and delete a node from the BST
void BinarySearchTree::DELETE(Node * node) {
    Node * temp_node_x = nullptr;
    Node * temp_node_y = nullptr;
    
    // If node has 0 or 1 children
    if (!node->left || !node->right) {
        temp_node_y = node;
    }
    
    // If node has 2 children
    else temp_node_y = TREE_SUCCESSOR(node);
    
    // If temp_node_y has child on left, temp_node_x points to that child
    if (temp_node_y->left) {
        temp_node_x = temp_node_y->left;
    }
    
    // Else temp_node_x points to the one on the right
    else temp_node_x = temp_node_y->right;
    
    // If temp_node_x is not empty (i.e. temp_node_y has children) parent of y is now also parent of x
    if (temp_node_x) {
        temp_node_x->parent = temp_node_y->parent;
    }
    
    // If y is NULL then, x is the root
    if (!temp_node_y) root = temp_node_x;
    
    else {
        if (temp_node_y->parent->left == temp_node_y) temp_node_y->parent->left = temp_node_x;
        else temp_node_y->parent->right = temp_node_x;
    }
    
    if (node != temp_node_y) node->key = temp_node_y->key;
    
    // de-allocate memory space by deleting the pointer
    delete temp_node_y;
}

// TREE_SEARCH : Perform a binary search on the BST
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
