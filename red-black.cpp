#include <iostream>

class Node {
    private:
    Node *parent;
    bool colour;

    public:
    int data;
    Node *left, *right;
    

    Node(int data){
        data = 0;
        colour = false;
        parent = left = right = NULL;
    }
    ~Node() {	
    delete left;
	delete right;
    }
};

class RedBlackTree{
    private:
        Node *root;
    public:
        RedBlackTree() {root = NULL;}
        void inOrderTraversalHelper(Node);
};

void inOrderTraversalHelper(Node *root){
    if (root == NULL)
        return;

    inOrderTraversalHelper(root->left);
    inOrderTraversalHelper(root->right);
}

int main() {

    
    return 0;
}