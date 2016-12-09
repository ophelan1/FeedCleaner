// uscheme.cpp
#include <iostream>
#include <string> 

using namespace std;

// Struct Node ------------------------------------------------------------------

    struct Node {

        Node(char value, Node *left=NULL, Node *right=NULL);
        ~Node();

        char value;
        Node * left;
        Node * right;

        friend ostream &operator<<(ostream &os, const Node &n);
    };

    Node::Node(char v, Node *l, Node *r): value(v), left(l), right(r){}
    Node::~Node(){}

    ostream &operator<<(ostream &cout, const Node &n) {
        // print current node
        cout << "(Node: value = " << n.value;

        // recursively call on left child
        if(n.left){
            cout << ", left = " << *(n.left);
        }
        // recursively call on right child
        if(n.right){
            cout << ", right = " << *(n.right);
        }
        cout << ")";
        return cout;
    }

// Class Tree ----------------------------------------------------------------
class Tree
{
    public:
        bTree(value);
        ~bTree();
        void destroy_tree(Node *leaf);

        void insert(string);
        Node* get_root();
        Node* find_LCA(int, int);

    private:    
        Node *root;
};

//Constructor requires an argument for the value of the root node
bTree::bTree(int root_val){root = new Node(root_val);}

//The destructor calls the function "destroy tree" recursively until all the leaves are freed
bTree::~bTree(){destroy_tree(root);}
void bTree::destroy_tree(Node *leaf){
  if(leaf!=NULL){
    destroy_tree(leaf->left);
    destroy_tree(leaf->right);
    delete leaf;
  }
}

void bTree::insert( s){

}

Node* bTree::get_root(){return(root);}

Node* bTree::find_LCA(int node1, int node2){
    Node* tmp = root;
    Node* parent = NULL;
    while(parent == NULL){
        //If they are both less than or equal to the node, check out the left branch
        if (  ( node1 < (tmp->value) ) && ( node2 < (tmp->value) )  ){
            tmp = tmp->left;
        }
        else if( ( node1 > (tmp->value) ) && ( node2 > (tmp->value) )  ){
            tmp = tmp->right;
        }
        else{
            parent = tmp;
        }
    }

    return parent;
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp: