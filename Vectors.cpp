#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<stdexcept>
#include<sstream>
using namespace std;

template <typename T>
class MyVector
{
    private:
        T *data;                        //pointer to int(array) to store elements
        int v_size;                        //current size of vector (number of elements in vector)
        int v_capacity;                    //capacity of vector
    public:
        MyVector();                        //No argument constructor
        MyVector(int cap);                //One Argument Constructor
        ~MyVector();                    //Destructor
        void push_back(T element);        //Add an element at the end of vector
        void insert(int index, T element); //Add an element at the index
        void erase(int index);            //Removes an element from the index
        T& at(int index);                 //return reference of the element at index
        const T& front();                //Returns reference of the first element in the vector
        const T& back();                //Returns reference of the Last element in the vector
        int size() const;                //Return current size of vector
        int capacity() const;            //Return capacity of vector
        bool empty() const;             //Return true if the vector is empty, False otherwise
        void shrink_to_fit();            //Reduce vector capacity to fit its size
        void display();
        void reserve(int new_size);      //Increases the size of the vector by new_size.
};

void listCommands() {
    cout << "List of available Commands:" << endl
        << "display                  : Display the Vector" << endl
        << "push_back <element>      : Add an element to the end of the vector" << endl
        << "insert <index element>   : Insert an element at location index" << endl
        << "erase <index>            : Remove the element from index" << endl
        << "at <index>               : Returns a reference to an element at a specified location" << endl
        << "front                    : Return the (reference of) front element" << endl
        << "back                     : Returns a reference to the last element of the vector" << endl
        << "size                     : Returns the number of elements in the vector" << endl
        << "capacity                 : Returns the capacity of vector" << endl
        << "empty                    : Tests if the vector container is empty" << endl
        << "shrink                   : Reduce vector capacity to fit its size (shrink_to_fit)" << endl
        << "exit/quit                : Exit the Program" << endl;
}

//Main function
int main()
{

    
    MyVector<int> myVector;
    listCommands();
    string user_input;
    string command;
    string parameter1;
    string parameter2;


    do {
        cout << endl;
        cout << ">";
        getline(cin,user_input);

        //Parse userinput into command and parameter(s)
        stringstream sstr(user_input);
        getline(sstr,command,' ');
        getline(sstr,parameter1,' ');
        getline(sstr,parameter2);

        try {
            if(command=="display" or command=="d") {myVector.display(); }
            else if(command=="push_back" or command=="p" ) {static_cast<void>((myVector.push_back(stoi(parameter1)))), myVector.display(); }
            else if(command=="insert" or command=="i") {static_cast<void>((myVector.insert(stoi(parameter1), stoi(parameter2)))), myVector.display(); }
            else if(command=="erase" or command=="estatic_cast<void>(") {static_cast<void>((myVector.erase(stoi(parameter1)))), myVector.display(); }
            else if(command=="at" or command=="a") {cout << myVector.at(stoi(parameter1)) << endl; }
            else if(command=="front" or command=="f") {cout << myVector.front() << endl; }
            else if(command=="back" or command=="b") {cout << myVector.back() << endl; }
            else if(command=="size" or command=="s") {cout << myVector.size() << endl; }
            else if(command=="capacity" or command=="c") {cout << myVector.capacity() << endl; }
            else if(command=="empty" or command=="e") {cout << boolalpha << myVector.empty() << endl; }
            else if(command=="shrink") {(myVector.shrink_to_fit()); }
            else if(command == "help" or command=="?") {listCommands(); }
            else if(command == "exit" or command=="quit")  {break; }
            else
                cout << "Invalid Command!" << endl;
        }
        
        catch(exception &e) {
            cout << "Exception: " << e.what() << endl; }
    }
    while(command!="exit" and command!="quit");

    return EXIT_SUCCESS;
}


//=============================================CLASS DEFINITIONS=================================================
//Display Function: Displays the Vector
#ifndef _WIN32
template <typename T>
void MyVector<T>::display()
{
    cout<<"╔════";
    for(int i=0; i<v_capacity-1; i++)
        cout<<"╦════";
    cout<<"╗ size = "<<v_size<<endl;
    
    for(int i=0; i<v_capacity; i++)
    {
        if(i<v_size)
            cout<<"║"<<setw(4)<<data[i];
        else
            cout<<"║"<<setw(4)<<" ";
    }
    if(v_size==0) cout<<"║    ";
    cout<<"║"<<endl<<"╚════";
    for(int i=0; i<v_capacity-1; i++)
        cout<<"╩════";
    cout<<"╝ capacity = "<<v_capacity<<endl;
}

//======================================
#else
template <typename T>
void MyVector<T>::display()
{
    cout<<"+";
    for(int i=0; i<v_capacity; i++)
        cout<<"---+";
    cout<<" size = "<<v_size<<endl;
    
    for(int i=0; i<v_capacity; i++)
    {
        if(i<v_size)
            cout<<"|"<<setw(3)<<data[i];
        else
            cout<<"|"<<"   ";
    }
    cout<<"|"<<endl<<"+";
    for(int i=0; i<v_capacity; i++)
        cout<<"---+";
    cout<<" capacity = "<<v_capacity<<endl;
}
#endif

//No Argument Constructor: vector size and vector and capacity are 0 and the vector data is empty.
template <typename T> MyVector<T>::MyVector() {
    v_size = 0;
    v_capacity = 0;
    data = new int[0];
}

//One Argument Constructor: Updates only the capacity and creates a vector with this new capacity.
template <typename T> MyVector<T>::MyVector(int cap) {
    v_size = 0;
    v_capacity = cap;
    data = new int[cap];
}

//Destructor: Clears up memory of vector.
template <typename T> MyVector<T>::~MyVector() {
    delete[] data;
}

//Push_Back: Adds an element at the end of the vector.
template <typename T> void MyVector<T>::push_back(T element) {
   if(v_size == v_capacity) {
        reserve(max(1, 2*v_capacity));
    }

    data[v_size] = element;
    v_size++;
}

//Insert: Adds an element at a specific index within the scope of the vector size. If the index exceeds the vector size, it will display an error.
template <typename T> void MyVector<T>::insert(int index, T element){
    if(index > v_size-1) {
        throw runtime_error("Index is greater than current vector size!");
    }
    
    //Need to figure out how to shift elements along. Then insert and incerment size.
    else {
        for(int i = v_size-1; i >= index; i--) {
            if(v_size == v_capacity) {
                reserve(max(1, 2*v_capacity));
                data[i+1] = data[i];
            }
            
            else
                data[i+1] = data[i];
        }
        
        data[index] = element;
        v_size++;
    }
}

//Erase: Removes an element from a specific index.
template <typename T> void MyVector<T>::erase(int index) {
    if(index > v_size-1 || index < 0) {
        throw runtime_error("Index is greater than Vector Size!");
    }
    
    else if(index+1 == v_size) {
        v_size--;
    }
    
    else {
        int j = index +1;
        int i = index;
        while(j < v_size) {
            data[i] = data[j];
            j++;
            i++;
        }
        v_size--;
    }
}

//At: Returns the reference of the element at a specific index.
template <typename T> T& MyVector<T>::at(int index) {
    if(index < 0 || index > v_size) {
        throw runtime_error("Index is Out of Vector Bound!");
    }
    
    return (data[index]);
}

//Front: Returns the reference of the first element in the vector.
template <typename T> const T& MyVector<T>::front() {
    if(empty()) {
        throw runtime_error("Vector is Empty!");
    }
    
    return (data[0]);
}

//Back: Returns reference of the last element in the vector.
template <typename T> const T& MyVector<T>::back() {
    if(empty()) {
        throw runtime_error("Vector is Empty!");
    }

    return (data[v_size-1]);
}

//Size: Returns the current size of the vector.
template <typename T> int MyVector<T>::size() const {
    return (v_size);
}

//Capacity: Returns the capacity of the vector.
template <typename T> int MyVector<T>::capacity() const {
    return (v_capacity);
}

//Empty: Returns true if the vector is empty, false otherwise.
template <typename T> bool MyVector<T>::empty() const {
    return (v_size == 0);
}

//Shrink_to_fit: Reduces vector capcaity to fit its size, hence capcaity = size
template <typename T> void MyVector<T>::shrink_to_fit(){
    v_capacity = v_size;
    display();
}

template <typename T> void MyVector<T>::reserve(int new_size) {
    if(v_capacity < new_size) {
        T *temp = new int[new_size];
        
        for(int i = 0; i < v_size; i++) {
            temp[i] = data[i];
        }
       
        
        if(data != NULL) {
            delete[] data;
        }
        
        data = temp;
        v_capacity = new_size;
    }
}
