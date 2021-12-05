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

    Node(){
      int data = 0;
      Node *left = nullptr;
      Node *right = nullptr;
      Node *parent = nullptr;
      bool colour = false;
    }

};

typedef Node *Node_;

class RedBlackTree{
    private:
        Node_ root;
        Node_ iRoot;
        void printHelper(Node_, std::string, bool);
        void insertFix(Node_);
        void deleteFix(Node_);



    public:
        RedBlackTree() {    
          iRoot = new Node;
          iRoot->colour = false;
          iRoot->left = nullptr;
          iRoot->right = nullptr;
          root = iRoot;
          }
        void rotateLeft(Node_);
        void rotateRight(Node_);
        void Insert(int);
        void Delete(Node_, int);
        void printTree();
        void deleteExecute(int);
         void search(int);
        };


void RedBlackTree::rotateLeft(Node_ n){
  
    Node_ y = n->right;
    n->right = y->left;

    if (y->left != iRoot)
    {
        y->left->parent = n;
    }
    y->parent = n->parent;

    if (n->parent == NULL)
    { //n is the root
        root = y;
    }

    else if (n == n->parent->left)
    { // n is the left child
        n->parent->left = y;
    }

    else
    {
        n->parent->right = y;
    }

    y->left = n;
    n->parent = y;
}

void RedBlackTree::rotateRight(Node_ n){
    Node_ y = n->left;
    n->left = y->right;

    if (y->right != iRoot) 
    {
      y->right->parent = n;
    }
    y->parent = n->parent;

    if (n->parent == NULL) 
    {
      root = y;
    } 

    else if (n == n->parent->right) 
    {
      n->parent->right = y;
    } 

    else 
    {
      n->parent->left = y;
    }

    y->right = n;
    n->parent = y;
}

void RedBlackTree::insertFix(Node_ n)
{
    Node_ u; //uncle node
    while (n->parent->colour == true)
    {
        if (n->parent == n->parent->parent->left)
        {
            u = n->parent->parent->right; 

            if (u->colour == true)
            {
                u->colour = false;
                n->parent->colour = false;
                n->parent->parent->colour = true;
                n = n->parent->parent;
            }

            else
            {
                if (n == n->parent->right)
                {
                    n = n->parent;
                    rotateLeft(n);
                }

                n->parent->colour = false;
                n->parent->parent->colour = true;
                rotateRight(n->parent->parent);            
            }
        }

        else
        {
            u = n->parent->parent->left;

            if (u->colour == true){
                u->colour = false;
                n->parent->colour = false;
                n->parent->parent->colour = true;
                n = n->parent->parent;
            }
            else
            {
                if (n == n->parent->left)
                {
                    n = n->parent;
                    rotateRight(n);
                }

                n->parent->colour = false;
                n->parent->parent->colour = true;
                rotateLeft(n->parent->parent);        
            }
        }

        if (n == root) 
        {
            break;
        }
    }
  root->colour = false; 
}

void RedBlackTree::Insert(int input)
{

    Node_ N = new Node;
    N->data = input;
    N->colour = true;
    N->left = iRoot;
    N->right = iRoot;

    Node_ z = NULL;
    Node_ r = root;

    while (r != iRoot) 
    {
      z = r;
      if (N->data > r->data) 
        {
          r = r->right;
        } 
      else 
        {
          r = r->left;
        }
    }

    N->parent = z;

    if (z == NULL) 
    {
      root = N;
    } 
    else if (N->data > z->data) 
    {
      z->right = N;
    } 
    else 
    {
      z->left = N;
    }

    if (N->parent == NULL) {
      N->colour = false;
      return;
    }

    insertFix(N);
  }

  void RedBlackTree::deleteFix(Node_ x) {
    Node_ s;
                    
    while (x != root && x->colour == false) {
      if (x == x->parent->left) {
        s = x->parent->right;
        if (s->colour == true) {
          s->colour = false;
          x->parent->colour = true;
          rotateLeft(x->parent);
          s = x->parent->right;
        }

        if (s->left->colour == false && s->right->colour == false) {
          s->colour = true;
          x = x->parent;
        } else {
          if (s->right->colour == false) {
            s->left->colour = false;
            s->colour = true;
            rotateRight(s);
            s = x->parent->right;
          }

          s->colour = x->parent->colour;
          x->parent->colour = false;
          s->right->colour = false;
          rotateLeft(x->parent);
          x = root;
        }
      } else {
        s = x->parent->left;
        if (s->colour == true) {
          s->colour = false;
          x->parent->colour = true;
          rotateRight(x->parent);
          s = x->parent->left;
        }

        if (s->right->colour == false && s->right->colour == false) {
          s->colour = true;
          x = x->parent;
        } else {
          if (s->left->colour == false) {
            s->right->colour = false;
            s->colour = true;
            rotateLeft(s);
            s = x->parent->left;
          }

          s->colour = x->parent->colour;
          x->parent->colour = false;
          s->left->colour = false;
          rotateRight(x->parent);
          x = root;
        }
      }
    }
    x->colour = false;
    root->colour = false;
  }

  void RedBlackTree::Delete(Node_ node, int key) {
    Node_ z = iRoot;
    Node_ x, y;
    while (node != iRoot) {
      if (node->data == key) {
        z = node;
      }

      if (node->data <= key) {
        node = node->right;
      } else {
        node = node->left;
      }
    }

    if (z == iRoot) {
      std::cout << "Key not found in the tree" << std::endl;
      return;
    }

    y = z;
    int y_orig_colour = y->colour;
    if (z->left == iRoot) 
    {
      x = z->right;
      if (z->parent == nullptr) {
        root = z->right;
      } else if (z == z->parent->left) {
        z->parent->left = z->right;
      } else {
        z->parent->right = z->right;
      }
      z->right->parent = z->parent;
    } 

  else if (z->right == iRoot) {
      x = z->left;
      if (z->parent == nullptr) {
        root = z->right;
      } else if (z == z->parent->left) {
        z->parent->left = z->right;
      } else {
        z->parent->right = z->right;
      }
      z->right->parent = z->parent;
  
    } else {
      Node_ y;
      while (z->right->left != iRoot) {
        z->right = z->right->left;
      }
      y = z->right;
  
      y_orig_colour = y->colour;
      x = y->right;
      if (y->parent == z) {
        x->parent = y;
      } else {
        if (y->parent == nullptr) {
          root = y->right;
        } else if (y == y->parent->left) {
          y->parent->left = y->right;
        } else {
          y->parent->right = y->right;
        }
        y->right->parent = y->parent;
  
        y->right = z->right;
        y->right->parent = y;
      }

 
      if (z->parent == nullptr) {
        root = y;
      } else if (z == z->parent->left) {
        z->parent->left = y;
      } else {
        z->parent->right = y;
      }
      y->parent = z->parent;
  
      y->left = z->left;
      y->left->parent = y;
      y->colour = z->colour;
    }
    delete z;
    if (y_orig_colour == 0) {
      deleteFix(x);
    }
  }

  void RedBlackTree::printHelper(Node_ root, std::string indent, bool last) {

    if (root != iRoot) {
      std::cout << indent;
      if (last) {
        std::cout << "R----";
        indent += "   ";
      } else {
        std::cout << "L----";
        indent += "|  ";
      }

      bool sColor = root->colour ? true : false;
      std::string sColour = (sColor == true) ? "RED" : "BLACK";
      std::cout << root->data << "(" << sColour << ")" << std::endl;
      printHelper(root->left, indent, false);
      printHelper(root->right, indent, true);
    }

  }

  void RedBlackTree::printTree() {

    if (root) {
      printHelper(root, "", true);
    }
  }

    void RedBlackTree::deleteExecute(int data) {
    Delete(root, data);
  }

  void RedBlackTree::search(int x)
{
     if(root==NULL)
     {
           std::cout<<"\nEmpty Tree\n" ;
           return  ;
     }

     std::cout<<"\n Enter key of the node to be searched: ";

     Node_ p=root;
     int found=0;
     while(p!=NULL&& found==0)
     {
            if(p->data==x)
                found=1;
            if(found==0)
            {
                 if(p->data<x)
                      p=p->right;
                 else
                      p=p->left;
            }
     }
     if(found==0)
          std::cout<<"\nElement Not Found.";
     else
     {
                std::cout<<"\n\t FOUND NODE: ";
                std::cout<<"\n Key: "<<p->data;
                std::cout<<"\n Colour: ";
    if(p->colour==false)
     std::cout<<"Black";
    else
     std::cout<<"Red";
                if(p->parent!=NULL)
                       std::cout<<"\n Parent: "<<p->parent->data;
                else
                       std::cout<<"\n There is no parent of the node.  ";
                if(p->right!=NULL)
                       std::cout<<"\n Right Child: "<<p->right->data;
                else
                       std::cout<<"\n There is no right child of the node.  ";
                if(p->left!=NULL)
                       std::cout<<"\n Left Child: "<<p->left->data;
                else
                       std::cout<<"\n There is no left child of the node.  ";
                std::cout<<std::endl;

     }
}

int main() {
  RedBlackTree bst;
  bst.Insert(50);
  bst.Insert(10);
  bst.Insert(2);
  bst.Insert(12);
  bst.search(2);

  bst.printTree();

  // std::cout<<"after delete"<< std::endl;
  // bst.deleteExecute(2);


  // bst.printTree();





}




