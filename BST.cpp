#include<iostream>
#include<cstdlib>
#include<sstream>
#include<iomanip>
#include<math.h>
#include<queue>
#include<vector>

using namespace std;

class Node
{
    private:
        int key;
        Node* left;
        Node* right;
        Node* parent;
    public:
        Node(int key): key(key),left(nullptr),right(nullptr), parent(nullptr) {}
        int getKey() { return this->key;}
        friend class BST;
};
//=============================================================================
class BST
{
    private:
        Node *root;
    public:
        BST();                                    //constructor
        ~BST();                                    //destructor
        Node* getRoot();                        //returns the root of the Tree
        void insert(Node* ptr,int key);            //Insert key into tree/subtree with root ptr
        int height(Node *ptr);                    //Find the height of a tree/subtree with root ptr
        Node* findMin(Node *ptr);                //Find and return the Node with minimum key value from a tree/subtree with root ptr
        Node* findMax(Node *ptr);                //Find and return the Node with Max key value from a tree/subtree with root ptr
        Node* findKey(Node *ptr,int key);        //Find and returns the node with key
        void remove(Node *ptr,int key);            //Remove a node with key from the tree/subtree with root
        void printInorder(Node* ptr);            //Traverse (inroder) and print the key of a tree/subtree with root ptr
        void printTree();                        //Print 2D Tree
};
//==========================================================
void listCommands()
{
            
    cout<<"________________________________________________________"<<endl;
    cout<<"display            :Display the BST Tree"<<endl
        <<"height             :Find the hieght of the Tree"<<endl
        <<"min                :Find the node with minimum key in BST"<<endl
        <<"max                :Find the node with maximum key in BST"<<endl
        <<"find <key>         :Find a node with a given key value in BST"<<endl
        <<"insert <key>       :Insert a new node in BST"<<endl
        <<"remove <key>       :Remove the node from BST "<<endl
        <<"inorder            :Print the BST in Inorder"<<endl
        <<"help               :Display the available commands"<<endl
        <<"exit               :Exit the program"<<endl;
}
//==========================================================
void demo( BST &myBST)
{
    myBST.insert(myBST.getRoot(),10);
    myBST.insert(myBST.getRoot(),5);
    myBST.insert(myBST.getRoot(),4);
    myBST.insert(myBST.getRoot(),7);
    myBST.insert(myBST.getRoot(),13);
    myBST.insert(myBST.getRoot(),15);
    myBST.insert(myBST.getRoot(),12);
    myBST.printTree();
}
//==========================================================
int main(void)
{
    BST myBST;
    listCommands();
    string user_input;
    string command;
    string key;

    while(true)
    {
        cout<<endl;
        cout<<">";
        getline(cin,user_input);

        // parse userinput into command and parameter(s)
        stringstream sstr(user_input);
        getline(sstr,command,' ');
        getline(sstr,key);
        
        Node* root = myBST.getRoot();    //get the root of the tree
        if( user_input =="display")    myBST.printTree();
        else if( command =="height")    cout<<"Height = "<<myBST.height(root)<<endl;
        else if( command =="min")
        {
            Node* min = myBST.findMin(root);
            cout<<"Min. key = "<<((min!=nullptr)? to_string(min->getKey()):" does not exist")<<endl;
        }
        else if( command =="max")
        {
            Node* max = myBST.findMax(root);
            cout<<"Max. key = "<<((max!=nullptr)? to_string(max->getKey()):" does not exist")<<endl;
        }
        else if( command =="find" or command =="f")    cout<<key<<(myBST.findKey(root,stoi(key))==nullptr ? " not found":" found")<<endl;
        else if( command =="insert" or command=="i")    { myBST.insert(root, stoi(key)); myBST.printTree();}
        else if( command =="remove" or command=="r")    { myBST.remove(root,stoi(key)); myBST.printTree();}
        else if( command =="inorder")    {myBST.printInorder(root); cout<<endl;}
        else if( command == "demo") demo(myBST);
        else if( command == "help") listCommands();
        else if( command =="exit" or command =="quit" or command =="q") break;
        else cout<<"Invalid command !!!"<<endl;

    }
    return 0;
}
//=====================================================================
BST::BST()
{
    root = NULL;
}
//=====================================================================
BST::~BST()
{
    delete root;
}
//=====================================================================
// Return the root of the tree
Node* BST::getRoot()
{
    return root;
}
//=====================================================================
//Insert recursively the key in the tree/subtree rooted at ptr
void BST::insert(Node *ptr, int key)
{
    //Case 1: When tree is empty, a new root node with 'key' will be created.
    if(root == NULL) {
        root = new Node(key);
    }
    
    //Case 2: When key is less than the rooted node, if the left of ptr is NULL, insert node. Otherwise, recursively call the function towards the left side of the tree.
    else if(key < ptr->key) {
        if(ptr->left == NULL) {
            ptr->left = new Node(key);
            ptr->left->parent = ptr;
        }
        
        else {
            insert(ptr->left, key);
        }
        
    }
    
    //Case 3: When key is greater than the rooted node, if the right of ptr is NULL, insert node. Otherwise, recursively call the function towards the right side of the tree.
    else if(key > ptr->key) {
        if(ptr->right == NULL) {
            ptr->right = new Node(key);
            ptr->right->parent = ptr;
        }
        
        else {
            insert(ptr->right, key);
        }
    }
    
    //Case 4: When the key is the same as the rooted node, then an error will be signaled: Cannot have duplicates within the tree (using the findKey function)
    else if(key == ptr->key) {
        cout << "Cannot have duplicates within the tree!" << endl;
    }
}
//=====================================================================
//Find the Height of the tree/subtree rooted at ptr
int BST::height(Node* ptr)
{
    int left_height, right_height;
    
    //Base Case (if the tree is empty, it implies that there are no levels in the tree, hence -1.
    if(ptr == NULL) {
        return -1;
    }
        
    left_height = height(ptr->left);
    right_height = height(ptr->right);
        
    return max(left_height, right_height)+1;
}
//=====================================================================
// Find recursively (or iteratively ) the key with minimum in the tree/subtree rooted at ptr
Node* BST::findMin(Node *ptr)
{
    if(root == NULL) {
        return ptr;
    }
    
    //Iteratively moves to the left most node with a left-child pointing to NULL - minimum
    while(ptr->left != NULL) {
        ptr = ptr->left;
    }
    return ptr;
}
//=====================================================================
// Find recursively (or iteratively ) the key with Maximum in the tree/subtree rooted at ptr
Node* BST::findMax(Node *ptr)
{
    if(root == NULL) {
        return ptr;
    }
    
    //Iteratively moves to the right most node with a right-child pointing to NULL - maximum
    while(ptr->right != NULL) {
        ptr = ptr->right;
    }
    return ptr;
}
//=====================================================================
// Find recursively the node with key value in the tree/subtree rooted at ptr
Node* BST::findKey(Node *ptr,int key)
{
    //This is the base case where if ptr == NULL, it means that the key does not exist in the tree.
    if(ptr == NULL) {
        return ptr;
    }
    
    //If the key is to the left side of the tree, it recurses by calling the function to the left child of ptr.
    else if(key < ptr->key) {
        return findKey(ptr->left, key);
    }
    
    //If the key is to the right side of the tree, it recurses by calling the function to the right child of ptr.
    else if(key > ptr->key) {
        return findKey(ptr->right, key);
    }
    
    //If the key is at ptr, it means the key is found and therefore we can return ptr.
    else if(key == ptr->key) {
        return ptr;
    }
    
    else
        throw runtime_error("No Key in the BST!");
}
//=========================================================
//Remove recursively the node with key value from the tree/subtree rooted at ptr
void BST::remove(Node *ptr,int key)
{
    if(ptr == NULL) {
        cout << "Cannot delete node as it does not exist!" << endl;
    }
    
    else if(key < ptr->key) {
        remove(ptr->left, key);
    }
    
    else if(key > ptr->key) {
        remove(ptr->right, key);
    }
    
    else if(key == ptr->key) {
        //Case 1: If the node is an external node.
        if(ptr->left == NULL and ptr->right == NULL) { //External nodes have no children
            if(ptr == root) {
                delete root;
                root = NULL;
            }
            
            else if(ptr->parent->left == ptr) {
                ptr->parent->left = NULL;
                delete ptr;
            }
            
            else if(ptr->parent->right == ptr) {
                ptr->parent->right = NULL;
                delete ptr;
            }
        }
        
        //Case 2a: If the node is an internal node (left is empty and right is not)
        else if(ptr->left == NULL and ptr->right != NULL) {
            if(ptr == root) {
                root = ptr->right;
                delete ptr;
            }
            
            else if(ptr->parent->left == ptr) {
                ptr->right->parent = ptr->parent;
                ptr->parent->left = ptr->right;
                delete ptr;
            }
            
            else if(ptr->parent->right == ptr) {
                ptr->right->parent = ptr->parent;
                ptr->parent->right = ptr->right;
                delete ptr;
            }
        }
        
        //Case 2b: If the node is an internal node (left not empty and right is empty)
        else if(ptr->left != NULL and ptr->right == NULL) {
            if(ptr == root) {
                root = ptr->left;
                delete ptr;
            }
            
            else if(ptr->parent->left == ptr) {
                ptr->left->parent = ptr->parent;
                ptr->parent->left = ptr->left;
                delete ptr;
            }
            
            else if(ptr->parent->right == ptr) {
                ptr->left->parent = ptr->parent;
                ptr->parent->right = ptr->left;
                delete ptr;
            }
        
        }
        
        //Case 4: If the node is an internal node, with two children.
        else {
            Node *temp = findMin(ptr->right);
            ptr->key = temp->key;
            remove(temp, temp->key);
        }
    }
}
//===============================================================
//Print recursively the tree/subtree rooted at ptr Inorder format
void BST::printInorder(Node *ptr)
{
    //We essentially do an inOrder Traversal and print when we visit a node:
    if (ptr == NULL)
          return;
    printInorder(ptr->left);
    cout << ptr->key << " ";
    printInorder(ptr->right);
}
//===============================================================
//Print a 2D Tree
void BST::printTree()
{
    cout<<"Tree:"<<endl;

    int levels = height(this->root);
    int max_nodes = pow(2,levels+1)-1;
    queue<Node*> myQueue;
    vector<Node*> myVector;
    myQueue.push(this->root);

    //Travers the tree in Breadth First Order and save each node into myVector
    for(int i=0; i<max_nodes; i++)
    {
        Node* cur = myQueue.front();
        myQueue.pop();
        myVector.push_back(cur);
        if(cur != nullptr)
        {
            myQueue.push(cur->left);
            myQueue.push(cur->right);
        }
        else //For Empty nodes push nullptr(placeholder) in Queue
        {
            myQueue.push(nullptr);
            myQueue.push(nullptr);
        }
    }

    if(max_nodes >0)            //if a non-empty tree
    {
        int *spaces = new int[levels+1];
        spaces[levels]=0;
        int level=0;

        for(int j=levels-1; j>=0; j--)
            spaces[j]=2*spaces[j+1]+1;
        
        for (int i=0; i<max_nodes; i++)
        {
            if(i == (pow(2,level)-1))    // if first node of a level
            {
                cout<<endl<<endl;        // go to next line
            
                for(int k=0; k<spaces[level]; k++)    //print sufficient spaces
                   cout<<"   ";
                
                level++;
            }
            if(myVector[i]!=nullptr)     cout<<std::left<<setw(3)<<myVector[i]->getKey();
            else                         cout<<std::left<<setw(3)<<" ";
            
            if(level>1)
                for(int k=0; k<spaces[level-2]; k++)    // print spaces between two nodes on same level
                    cout<<"   ";
        }

        cout<<endl;
        for(int i=0; i<pow(levels,2.5); i++)    //Add last line with ----
            cout<<"___";
        
        cout<<endl;
        delete[] spaces;
    }
}
