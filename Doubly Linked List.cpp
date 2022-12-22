#include <iostream>
#include<string>
#include<sstream>
#include<iomanip>
#include<exception>
using namespace std;

class Node
{
    private:
        string elem; //Data element (type string in this case)
        Node* next; //Link (pointer) to the next Node
        Node* prev; //Link (pointer) to the previous Node
        friend class DoublyLinkedList;
        
    public:
        Node(): next(NULL), prev(NULL) {}
        Node(string elem) : elem(elem), next(NULL), prev(NULL) {}
};

class DoublyLinkedList
{
    private:
        Node* head; //Pointer to the head of List
        Node* tail; //Pointer to the tail of List
    
    public:
        DoublyLinkedList(); //Constructor to create dummy head and tail nodes
        ~DoublyLinkedList(); //Destructor to clean all nodes
        bool empty() const; //Return true if the list is empty
        const string& front() const; //Return the element from the first valid Node of list, throw an exception if the list is empty
        const string& back() const; //Return the element from last valid Node of the list, throw an exception if the list is empty
        void addBefore(Node *ptr, const string& elem); //Add a new node before a node pointed by ptr
        void addFront(const string& elem); //Add a new node to the front of list (after head)
        void addBack(const string & elem); //Add a new node to the back of the list (before tail)
        void removeFront(); //Remove front node from list, throw an exception if the list is empty
        void removeBack();  //Remove last node from list, throw an exception if the list is empty
        void reverseList(); //Reverses the list
        bool isPalindrome(); //Return true if the list is Palindrome, false otherwise
        void display() const; //display all element of the list
};

void listCommands()
{
    cout << "List of available Commands:" << endl
        << "display            : Display the Doubly Linkled List" << endl
        << "front              : Display the first element of the List" << endl
        << "back               : Display the last element of the List" << endl
        << "addFront <elem>    : Add a new Node at the begining of the List" << endl
        << "addBack  <elem>    : Add a new Node at the end of the List" << endl
        << "removeFront        : Remove the first Node of the Linked List" << endl
        << "removeBack         : Remove the last  Node of the Linked List" << endl
        << "isempty            : Check if the List is empty?" << endl
        << "reverse            : Reverse the Linked List" << endl
        << "isPalindrome       : Check if the List is Palindrome or not?" << endl
        << "help               : Display the list of available commands" << endl
        << "exit               : Exit the Program" << endl;
}

int main() {
    
    DoublyLinkedList myList;
    listCommands();
    string user_input;
    string command;
    string parameter;

    do {
        cout << endl;
        cout << ">";
        getline(cin, user_input);

        //Parse userinput into command and parameter(s)
        stringstream sstr(user_input);
        getline(sstr, command,' ');
        getline(sstr, parameter);
        
        try {
            if(command=="display") {myList.display(); }
            else if(command=="front") {
                cout << "Front = " << myList.front() << endl; }
            else if(command=="back") {
                cout << "Back = " << myList.back() << endl; }
            else if(command=="addFront") {static_cast<void>(myList.addFront(parameter)), myList.display(); }
            else if(command=="addBack") {static_cast<void>(myList.addBack(parameter)),myList.display(); }
            else if(command=="removeFront") {static_cast<void>(myList.removeFront()),myList.display(); }
            else if(command=="removeBack") {static_cast<void>(myList.removeBack()), myList.display(); }
            else if(command=="isempty") {
                cout << "List is " << (myList.empty()? "Empty":"Not Empty") << endl; }
            else if(command=="reverse") {static_cast<void>(myList.reverseList()), myList.display(); }
            else if(command=="isPalindrome") {
                cout << "List is " << (myList.isPalindrome()? "Palindrome":"Not Palindrome") << endl; }
            else if(command == "help") {listCommands(); }
            else if(command == "exit" or command == "quit") {break; }
            else
                cout<<"Invalid Commad !!"<<endl;
            }
            catch(exception &e) {cout << "Exception: " << e.what() << endl; }

        }
    while(command != "exit" and command != "quit");
    
    return EXIT_SUCCESS;
}

//Constructor to create dummy head and tail nodes
DoublyLinkedList::DoublyLinkedList() {
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
}

//Destructor to clean up all nodes
DoublyLinkedList::~DoublyLinkedList() {
    while(!empty()) removeFront();
    delete head;
    delete tail;
}

//Return true if the list is empty
bool DoublyLinkedList::empty() const {return(head->next == tail and tail->prev == head); }

//Return the element from the first valid Node of list, throw an exception if the list is empty
const string& DoublyLinkedList::front() const {
    if(empty()) {
        throw runtime_error("List is empty! No Front!");
    }
    
    else
        return (head->next->elem); }

//Return the element from last valid Node of the list, throw an exception if the list is empty
const string& DoublyLinkedList::back() const {
    if(empty()) {
        throw runtime_error("List is empty! No Back!");
    }
    
    else
        return (tail->prev->elem);
}

//Add a new node before a node pointed by ptr
void DoublyLinkedList::addBefore(Node *ptr, const string& elem) {
    Node *u = new Node(elem);
    u->next = ptr;
    u->prev = ptr->prev;
    ptr->prev->next = u;
    ptr->prev = u;
}

//Add a new node to the front of list (after head)
void DoublyLinkedList::addFront(const string& elem) {
    addBefore(head->next, elem);
}

//Add a new node to the back of the list (before tail)
void DoublyLinkedList::addBack(const string & elem) {
    Node *u = new Node(elem);
    u->next = tail;
    u->prev = tail->prev;
    tail->prev->next = u;
    tail->prev = u;
}

//Remove front node from list, throw an exception if the list is empty
void DoublyLinkedList::removeFront() {
    if(empty()) {
        throw runtime_error("List is empty! No Front!");
    }
    
    else {
        Node *v = head->next;
        Node *w = head->next->next;
        head->next = w;
        w->prev = head;
        delete v;
    }
}

//Remove last node from list, throw an exception if the list is empty
void DoublyLinkedList::removeBack() {
    if(empty()) {
        throw runtime_error("List is empty! No Back!");
    }
    
    else {
        Node *v = tail->prev;
        Node *w = tail->prev->prev;
        tail->prev = w;
        w->next = tail;
        delete v;
    }
}

//Reverses the list
void DoublyLinkedList::reverseList() {
    if(empty()) {
        throw runtime_error("List is empty! Cannot execute reverse!");
    }
    
    if(isPalindrome() == true) {
        NULL;
    }
    
    else {
        Node *current = head;
        Node *nextnode = current->next;
    
        while(current != tail) {
            current->next = current->prev;
            current->prev = nextnode;
            current = nextnode;
            nextnode = nextnode->next;
        }
    
        tail->next = tail->prev;;
        tail->prev = NULL;
    
        current = head;;
        head = tail;
        tail = current;
    }
}

//Return true if the list is Palindrome, false otherwise
bool DoublyLinkedList::isPalindrome() {
    Node *front = head->next;
    Node *back = tail->prev;
    
    while(front != back) {
        if(front->elem == back->elem) {NULL; }
        else {return false; }
        
        front = front->next;
        back = back->prev;
    }
    
    return true;
}

//Displays all of the elements in the list
void DoublyLinkedList::display() const {
    Node *curr = head;
    while(curr != NULL)
    {
        cout << "+------";
        curr = curr->next;
    }
    cout << "+" << endl << "|";
    curr = head;
    while(curr != NULL)
    {
        if (curr == head) {
            cout<<" Head |"; }
        else if(curr == tail) {
            cout<<" Tail |"; }
        else
            cout << setw(5) << curr->elem << " |";
    
        curr = curr->next;
    }
    curr = head;
    cout << endl;
    while(curr != NULL) {
        cout << "+------";
        curr = curr->next;
    }
    cout << "+" << endl;
}
