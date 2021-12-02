#include <iostream>

// a red black tree is a binary search tree in which each node is either red, or black

// properties 
// 1. every node is red or black
// 2. the root of the tree is black
// 3. if a node is red, both children must be black
// 4. Every simple path from a node to a descendant leaf contains the same number of black nodes. 
// 5. Every leaf (NULL) is black. 

struct Node {
  int data;
  Node *parent;
  Node *left;
  Node *right;
  bool colour;
};

typedef Node *Node_;

class RedBlackTree{
    private:
        Node_ root;
        void printHelper(Node_ root, std::string indent, bool last);

    public:
        RedBlackTree() {root = NULL;}
        // insertion pseudocode
        // 1. do a normal binary search tree insertion
        // 2. make the inserted node red
        // 3. fix the red-black properties

        // step 1.
        void rotateLeft(Node_ n);
        void rotateRight(Node_ n);
        void insertFix(Node_ n);
        void Insert(int input);
        void printTree();
};
// modified to RBTree insert. 
// need to make the new node red, not done yet


void RedBlackTree::rotateLeft(Node_ n){
    Node_ y = n->right;
    n->right = y->left;
    if (y->left != NULL){
        y->left->parent = n;
    }
    y->parent = n->parent;
    if (n->parent == NULL){ //n is the root
        root = y;
    }
    else if (n == n->parent->left){ // n is the left child
        n->parent->left = y;
    }
    else{
        n->parent->right = y;
    }
    y->left = n;
    n->parent = y;

}

void RedBlackTree::rotateRight(Node_ n){
    Node_ y = n->left;
    n->left = y->right;
    if (y->right != NULL) {
      y->right->parent = n;
    }
    y->parent = n->parent;
    if (n->parent == NULL) {
      root = y;
    } 
    else if (n == n->parent->right) {
      n->parent->right = y;
    } 
    else {
      n->parent->left = y;
    }
    y->right = n;
    n->parent = y;
}

void RedBlackTree::insertFix(Node_ n){
    Node_ u; //uncle node
    while (n->parent->colour == true){
        if (n->parent == n->parent->parent->right){

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
                    rotateLeft(n);
                }
                n->parent->colour = false;
                n->parent->parent->colour = true;
                rotateRight(n->parent->parent);            
                }
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
                    rotateLeft(n);
                }
                n->parent->colour = false;
                n->parent->parent->colour = true;
                rotateRight(n->parent->parent);        
                }
            }
        if (n == root) {
            break;
        }
    }
        root->colour = false; 
}

void RedBlackTree::Insert(int input){
    Node_ N = new Node;
    N->data = input;
    N->colour = true;

    Node_ r = root;
    Node_ y = NULL;

    
    if (root == NULL){
        root = N;
        N->parent = NULL;
    }

    else{
        while(root != NULL){
            y = r;
            if (N->data <= r->data){
                r = r->left;
            }
            else{
                r = r->right;
            }
        }
        N->parent = y;
        if (y->data < N->data){
            y->right = N;
        }
        else{
            y->left = N;
        }
        insertFix(N);

    }


}



  void RedBlackTree::printHelper(Node_ root, std::string indent, bool last) {

    if (root != NULL) {
      std::cout << indent;
      if (last) {
        std::cout << "R----";
        indent += "   ";
      } else {
        std::cout << "L----";
        indent += "|  ";
      }

      bool sColor = root->colour ? true : false;
      std::cout << root->data << "(" << sColor << ")" << std::endl;
      printHelper(root->left, indent, false);
      printHelper(root->right, indent, true);
    }
  }

  void RedBlackTree::printTree() {
    if (root) {
      printHelper(this->root, "", true);
    }
  }

int main() {
  RedBlackTree bst;
  bst.Insert(55);
// once it inserts more than once, the print function breaks and no longer prints 
  bst.printTree();


}




