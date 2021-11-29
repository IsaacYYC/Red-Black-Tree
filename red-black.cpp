#include <iostream>

// a red black tree is a binary search tree in which each node is either red, or black

// properties 
// 1. every node is red or black
// 2. the root of the tree is black
// 3. if a node is red, both children must be black
// 4. Every simple path from a node to a descendant leaf contains the same number of black nodes. 
// 5. Every leaf (NULL) is black. 

class Node {
    private:

    public:
    int data;
    bool colour;
    Node *left, *right, *parent;
    
    Node(){
        data = 0;
        // false = black
        colour = false;
        parent = left = right = NULL;
    }
    Node(int data){
        data = data;
        // false = black
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
        // insertion pseudocode
        // 1. do a normal binary search tree insertion
        // 2. make the inserted node red
        // 3. fix the red-black properties

        // step 1.
        Node BSTInsert(Node *root, int data);

        // how to fix the properties
        // there are several cases we need to consider
        // 1. tree is empty. if so, make the inserted "N" the root and color it black
        // 2. Parent is black (that sounds weird). Nothing is needed to be done, and we are finished
        // 3. Parent is red. There are 3 more subcases when this occurs, they are as follows
        //    Side note. We always move our N to the violating node. If one of the fixes moves the violation higher up, we reaply (so im assuming we use recursion)
        //     3.1: Parent(P) is red, uncle(U) is red. In this case, we flip the color of nodes P,U, and G(grandparent). That means, P becomes black, 
        //          U becomes black and, G becomes red. One thing we need to be careful in this case is when G is a root of T. 
        //          If that is the case, we do not recolor G as it violates property 2.
        //     3.2: P is red, U is black (we all have black uncles in comp sci I guess). 
        //          3.2.1: P is right child of G and N is right child of P. We first perform the left-rotation at G that makes G the new sibling S of N. 
        //                 Next, we change the color of S(sibling) to red and P to black. 
        //          3.2.2: P is right child of G and N is left child of P. In this case, we first do the right-rotation at P
        //          3.2.3: P is left child of G and N is left child of P. This is the mirror of case 3.2.1. Therefore the solution is symmetric to the solution of case 3.2.1.
        //          3.2.4: P is left child of G and N is right child of P. This is the mirror of case 3.2.2. Therefore, the solution is symmetric to the solution of case 3.2.2.
       
        // implimented the pseudo code down below
       
        // Pseudo code for all of that so we dont have to try and reinvent the wheel lol. also k in the pseudo code is N above
        //  RB-INSERT(T, k)
        //  BST-INSERT(T, k) //normal BST insertion
        //  while k.parent.color == RED
        //      if k.parent == k.parent.parent.right
        //         u = k.parent.parent.left //uncle
        //          if u.color == RED // case 3.1
        //             u.color = BLACK
        //             k.parent.color = BLACK
        //             k.parent.parent.color = RED
        //             k = k.parent.parent
        //          else if k == k.parent.left // case 3.3.1 and 3.3.2
        //                 k = k.parent
        //                 LEFT-ROTATE(T, k)
        //             k.parent.color = BLACK
        //             k.parent.parent.color = RED
        //             RIGHT-ROTATE(T, k.parent.parent)
        //     else (same as then clause with “left” and “right” exchanged)
        //  T.root.color = BLACK

        void rotateLeft(Node *root, Node *N);
        void rotateRight(Node *root, Node *N);
        void insertFix(Node *root, Node *N);
        
};

// binary search tree insert. probably not needed, just coded out for refernce
Node *BSTInsert(Node *root, int data){
    if (root == NULL){
        return new Node(data);
    }

    else if (data <= root->data){
        root->left = BSTInsert(root->left, data);
    }

    else{
        root->right = BSTInsert(root->right, data);
    }
    return root;
}

// modified to RBTree insert. 
// need to make the new node red, not done yet
Node *Insert(Node *root, Node *N){
    if (root == NULL){
        return N;
    }

    else if (N->data <= root->data){
        root->left = Insert(root->left, N);
        root->left->parent = root;
    }

    else{
        root->right = Insert(root->right, N);
        root->right->parent = root;
    }
    return root;
}

void rotateLeft(Node *root, Node *N){

}

void rotateRight(Node *root, Node *N){

}


void insertFix(Node *root, Node *n){
    Node *u; //uncle node
    while (n->parent->colour == true){
        if (n->parent == n->parent->parent->right)
            u = n->parent->parent->left; 
            if (u->colour == true){
                u->colour = false;
                n->parent->colour = false;
                n->parent->parent->colour = true;
                n = n->parent->parent;
            }
            else{
                if (n == n->parent->left){
                    n = n->parent;
                    rotateLeft(root, n);
                }
                n->parent->colour = false;
                n->parent->parent->colour = true;
                rotateRight(root, n->parent->parent);            
                }
        else{
            u = n->parent->parent->right;

            if (u->colour == true){
                u->colour = false;
                n->parent->colour = false;
                n->parent->parent->colour = true;
                n = n->parent->parent;
            }
            else{
                if (n == n->parent->right){
                    n = n->parent;
                    rotateLeft(root, n);
                }
                n->parent->colour = false;
                n->parent->parent->colour = true;
                rotateRight(root, n->parent->parent);        
                }
            }
        if (n == root) {
            break;
        }
    }
        root->colour = false; 
}

int main() {

}