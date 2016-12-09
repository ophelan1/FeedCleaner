// uscheme.cpp
#include <iostream>
#include <string> 

using namespace std;

// Struct Node ------------------------------------------------------------------

struct Node {

    Node(string value, Node *left=NULL, Node *right=NULL);
    ~Node();

    string value;
    int length;
    Node * left;
    Node * right;

    // compare returns an integer value equal to the number of letters in common, starting at 1 (0 letters in common)
    // If the return value > 0, the Node value is larger, if it is < 0, the compStr is larger. == 0, they are the same
    int compare(string compStr){
        int i;
        for(i = 0 ; i < length && i < compStr.length() ; i++){
            if(value[i] > compStr[i]){
                return i+1;
            }
            else if(value[i] < compStr[i]){
                int tmp = i + 1;
                return tmp*(-1);
            }
        }
        if(compStr.length() == length){
            return 0;
        }
        else if(i == compStr.length()){
            return i;
        }
        else if(i == length){
            return -i;
        }
    }

    void truncate(int position){

    }
};

Node::Node(string v, Node *l, Node *r): value(v), length(value.length()), left(l), right(r){}
Node::~Node(){}


// Class Tree ----------------------------------------------------------------
class strTree
{
    public:
        strTree(string);

        void insert(string);
        void insertRec(Node*, string);

        Node* root;
    private:

};
// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:

strTree::strTree(string startString){
    root = new Node(startString);
}

void strTree::insert(string inputString){
    insertRec(root, inputString);
}
void strTree::insertRec(Node* curr, string inputString){
    int result = curr->compare(inputString);
    if(result > 0){
        cout << "Current Node is larger than new node" << endl;
    }
    else if(result < 0){
        cout << "Current Node is less than new node" << endl;
        cout << "Matched Until StringValue[" << result*-1 << "]" << endl;
    }
    else{
        cout << "Current Node are the same" << endl;
    }
}