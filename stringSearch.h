// uscheme.cpp
#include <iostream>
#include <string> 

using namespace std;

// Struct Node ------------------------------------------------------------------

    struct Node {

        Node(char value, int length, Node *left=NULL, Node *right=NULL);
        ~Node();

        char value;
        int length;
        Node * left;
        Node * right;

        void printNode();
    };

    Node::Node(char v, int t, Node *l, Node *r): value(v), length(t), left(l), right(r){}
    Node::~Node(){}

    void Node::printNode(){
        cout << "Value = " << value << ", Length = " << length << endl;
    }

// Class Tree ----------------------------------------------------------------
class bTree
{
    public:
        bTree();
        ~bTree();
        void destroy_tree(Node *leaf);

        void insertString(string);
        void insertChar(char, int);
        Node* get_root();
        void printTree();

    private:    
        Node *root;
};

//Constructor requires an argument for the value of the root node
bTree::bTree(){root = NULL;}

//The destructor calls the function "destroy tree" recursively until all the leaves are freed
bTree::~bTree(){destroy_tree(root);}
void bTree::destroy_tree(Node *leaf){
  if(leaf!=NULL){
    destroy_tree(leaf->left);
    destroy_tree(leaf->right);
    delete leaf;
  }
}

void bTree::insertString( string inputString ){
    for(int i = 0 ; i < inputString.length() ; i++){
        if(i + 1 != inputString.length()){
            insertChar(inputString[i], 0);
        }
        else{
            insertChar(inputString[i], inputString.length());
        }
    }
}

void bTree::insertChar( char inputChar, int length = 0 ){
    cout << "Input Char = " << inputChar << endl;
    Node* tmp = root;
    while(tmp != NULL){
        cout << "Tmp != NULL" << endl;
        if(inputChar >= tmp->value){
            cout << "tmp = tmp ->right" << endl;
            tmp = tmp->right;
        }
        else{
            tmp = tmp->left;
        }

    }
    cout << "Tmp == NULL" << endl;
    tmp = new Node(inputChar, length);

}

void bTree::printTree( ){
    Node* tmp = root;
    tmp->printNode();
}
  

Node* bTree::get_root(){return(root);}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp: