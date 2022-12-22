#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <exception>
using namespace std;

class Node
{
    private:
        int elem; //Data element
        Node *next; //Link pointer for each element
        friend class MyLinkedList; //Gives MyLinkedList access to private variables
};

class MyLinkedList
{
    private:
        Node *head;
    
    public:
        MyLinkedList(); //Empty list constructor
        ~MyLinkedList(); //Destructor to clean up all nodes
        bool empty() const; //Returns true if the list is empty
        void addFront(int elem); //Add a new Node at the front of the list
        void removeFront(); //Remove front Node from the list
        unsigned int countElem(int elem); //Count frequency of an element in the list
        int getIndexOf(int elem); //Returns first index of an element in the list, -1 if the element is not present
        void display() const; //Prints out the Singly Linked List
        void loadData(string); //Read a file and load it into the linked list
        void dumpData(string) const; //Write the linked list to a file
        void sort();  //Sorts the elements of the list (Bubble Sort)
};

void ListCommands () {
    cout << "List of available Commands:" << endl
        << "display            : Display the Linked List" << endl
        << "addFront <element> : Add <element> to the front of the Linked List" << endl
        << "removeFront        : Remove the front node of the Linked List" << endl
        << "count              : Count frequency of an element in the list" << endl
        << "indexOf            : Return first index of an element in the list (-1 of not present)" << endl
        << "load <file_name>   : Load the data from <file> and add it into the Linked List" << endl
        << "dump <file_name>   : Dump the contents of the Linked list to <file>" << endl
        << "sort               : Sort the Linked List using Bubble Sort Algorithm" << endl
        << "help               : Display the list of available commands" << endl
        << "exit               : Exit the Program" << endl;
}

int main() {
    
    MyLinkedList myList;
    ListCommands();
    string user_input;
    string command;
    string parameter;
    
    do {
        cout << endl;
        cout << ">";
        getline(cin, user_input);
        
        stringstream sstr(user_input);
        getline(sstr,command,' ');
        getline(sstr,parameter);
        
        if(command == "display") {myList.display(); }
        else if(command == "add" or command == "addFront") {static_cast<void>(myList.addFront(stoi(parameter))), myList.display(); }
        else if(command == "remove" or command == "removeFront") {static_cast<void>(myList.removeFront()), myList.display(); }
        else if(command == "count") {
            cout << parameter << " occurs "<< myList.countElem(stoi(parameter)) << " time(s) in the list" << endl;
        }
        else if(command == "indexOf") {
            cout << "First index of " << parameter << " in the list is: " << myList.getIndexOf(stoi(parameter)) << endl;
        }
        else if(command == "load") {static_cast<void>(myList.loadData(parameter)), myList.display(); }
        else if (command == "dump") {myList.dumpData(parameter); }
        else if(command == "sort") {static_cast<void>(myList.sort()), myList.display(); }
        else if(command == "help") {ListCommands(); }
        else if (command == "exit") {break; }
        else
            cout << "Invalid Input!" << endl;
    }
    while(command != "exit");
        
    return EXIT_SUCCESS;
}

//Constructor:
MyLinkedList::MyLinkedList() {this->head = NULL; }

//Destructor for cleaning up the nodes:
MyLinkedList::~MyLinkedList() {while(!empty()) removeFront(); }

//Empty: Checking if the list is empty (returns true if it is, false otherwise):
bool MyLinkedList::empty() const {return head == NULL; }

//AddFront: This will add a node object to the front of the list and will print it:
void MyLinkedList::addFront(int elem) {
    Node *front = new Node;
    front->elem = elem;
    front->next = head;
    head = front;
}

//RemoveFront: This will remove the node object that is in the front of the list and will print it:
//Check that you can't remove when list is empty
void MyLinkedList::removeFront() {
    if(head != NULL) {
        Node *old = head;
        head = old->next;
        delete old;
    }
    
    else
        cout << "List is empty!" << endl;
}

//CountElem: This will count the frequency of occurence of an element in the list:
unsigned int MyLinkedList::countElem(int elem) {
    Node *check = head;
    int count = 0;
    while(check != NULL) {
        if(check->elem == elem) {
            count++;
        }
        check = check->next;
    }
    return count;
}

//GetIndex: This will get the first index of the element in the list, will return -1 if element isn't in the list.
int MyLinkedList::getIndexOf(int elem){
    Node *check = head;
    int index = 0;
    bool in(false);
    
    while(check != NULL) {
        if(check->elem == elem) {
            in = true;
            return index;
        }
        else
            index++;
        
        check = check->next;
    }
    
    if(in == false) {
        index = -1;
    }
    return index;
}

//Display: Will print the list
void MyLinkedList::display() const {
    Node *print = head;
    
    if(print == NULL) {
        cout << "Head->Null" << endl;
    }
    
    else {
        cout << "Head->";
        while(print != NULL) {
            cout << print->elem << "->"; 
            print = print->next;
        }
        cout << "NULL" << endl;
    }
}


//Sort: This will sort the elments of the list using Bubble Sort in ascending order:
void MyLinkedList::sort() {
    int temp, swap;
    Node *ptr, *endptr(NULL);
    
    do {
        swap = 0;
        ptr = head;
        
        while(ptr->next != endptr) {
            if(ptr->elem > ptr->next->elem) {
                temp = ptr->elem;
                ptr->elem = ptr->next->elem;
                ptr->next->elem = temp;
                swap = 1;
            }
            ptr = ptr->next;
        }
        endptr = ptr;
    } while(swap);
}

//LoadData: This will read integer data from a file and add it to the Linked List:
void MyLinkedList::loadData(string path) {
    ifstream inFile(path);
    if (inFile.fail()) {
        cout << "File " << path << " could not be opened.";
    }

    int integer;
    while(!inFile.eof()) {
        inFile >> integer;
        addFront(integer);
    }
    
    inFile.close();
}

//DumpData: This will write the contents of the list to a file:
void MyLinkedList::dumpData(string path) const {
    ofstream outFile(path);
    if (outFile.fail()) {
        cout << "File " << path << " could not be opened.";
    }
    
    Node *print = head;
    while(print != NULL) {
        outFile << print->elem << endl;
        print = print->next;
    }
    
    cout << "File " << path << " created and contents written!" << endl;
    outFile.close();
}
