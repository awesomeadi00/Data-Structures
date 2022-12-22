#include<iostream>
#include<exception>
#include<math.h>
#include<iomanip>
#include<sstream>
using namespace std;
class Heap
{
    private:
        int *array;
        int capacity;
        int size;
    
    public:
        Heap(int cap);
        ~Heap();
        void insert(int key);
        int removeMin();
        int getMin();
        int parent(int k);
        int left(int k);
        int right(int k);
        void siftup(int k);
        void siftdown(int k);
        void print(int k=-1);
        void sort();
    private:
        void adjustSize();
};

void listCommands()
{
    cout<<"-----------------------------------------------------------------"<<endl;
    cout<<"display            :Display the Heap"<<endl
        <<"insert <key>       :Insert a new element in the Heap"<<endl
        <<"getMin             :Get the element with Min. Key in the Heap"<<endl
        <<"removeMin          :Remove the element with Min. Key from Heap"<<endl
        <<"sort               :Sort the Heap"<<endl
        <<"help               :Display the available commands"<<endl
        <<"exit               :Exit the program"<<endl;
    cout<<"-----------------------------------------------------------------"<<endl;
}
//=============================================
void demo(Heap &myHeap)
{
    srand((unsigned int) time(NULL));
    
    for (int i=0; i<10; i++)
    {
        int n = rand()%100;
        myHeap.insert(n);
    }
    myHeap.print();
}
//=============================================
int main()
{
    Heap myHeap(15);
    string user_input;
    string command;
    string argument;

    listCommands();

    while(true)
    {
        try
        {
            cout << endl;
            cout<<">";
            getline(cin,user_input);

            // parse userinput into command and parameter(s)
            stringstream sstr(user_input);
            getline(sstr,command,' ');
            getline(sstr,argument);
            
        
            if(command =="display" or command=="d") {myHeap.print(); }
            else if(command =="insert"  or command=="i") {myHeap.insert(stoi(argument)); myHeap.print(); }
            else if(command =="getMin") {cout << "Minimum Key = " << myHeap.getMin() << endl; }
            else if(command =="removeMin" or command=="r") {
                cout << myHeap.removeMin() << " has been removed!" << endl; myHeap.print(); }
            else if(command =="sort") {myHeap.sort(); myHeap.print(); }
            else if(command == "help") {listCommands(); }
            else if(command == "demo") {demo(myHeap); }
            else if(command == "exit" or command == "quit") {break; }
            else
                cout << "Invalid command!!!" << endl;
    
        }
        catch (exception &e)
        {
            cout << "Exception: " << e.what() << endl;
        }
    }
    return EXIT_SUCCESS;
}
//=============================================
void Heap::adjustSize()
{
    int *newArray = new int[capacity*2];
    for(int i=0; i<capacity; i++)
        newArray[i] = array[i];
    delete[] array;
    array = newArray;
    capacity = capacity*2;
}
//==================================================
// Constructor: Initializes the capacity with (cap), size with 0 by default and an array with size cap.
Heap::Heap(int cap)
{
    capacity = cap;
    size = 0;
    array = new int[cap];
}

//Destructor: Clears memory.
Heap::~Heap() {delete[] array; }

// Return (but don't remove) the minimum value from the Heap
int Heap::getMin() {return array[0]; }

// Returns the index of the parent of the node i
int Heap::parent(int i) {return((i-1)/2); }

// Returns the index of the left child of the node i
int Heap::left(int i) {return((2*i)+1); }

// Returns the index of the right child of the node i
int Heap::right(int i) {return((2*i)+2); }

// Insert an element in Heap keeping the Heap property intact
void Heap::insert(int key)
{
    array[size] = key;  //Insert element at the end of the array
    siftup(size);       //Execute the siftup operation to keep Heap order intact
    size++;             //Increment the size
}

// Remove the minimum value from Heap keeping the Heap property intact
int Heap::removeMin()
{
    int temp;
    //If the heap is empty, then return -1
    if(size == 0) {
        cout << "Heap is empty!" << endl;
        return -1;
    }
    
    //If the heap has only one element, remove it directly.
    else if(size == 1) {
        temp = array[0];
        size--;
        return temp;
    }
    
    //If the heap has more than one element, swap the last with the root and call sift-down.
    else {
        temp = array[0];
        array[0] = array[size-1];
        size--;
        siftdown(0);
        return temp;
    }
}

// Sift-up an element at index i
void Heap::siftup(int i) {
    int temp;
    while(array[i] != array[0]) { //While i is not at the root (so 1st position)
        int j = parent(i); //Make j the parent of i
        
        //If i > j, it implies that the child is bigger than the parent.
        //Cannot sift-up anymore and the heap is ordered, thus break.
        if(array[i] > array[j]) {break; }
        
        //Swap the keys
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
        
        //Then initialize i's value with j
        i = j;
    }
}

// Sift-down an element at index k
void Heap::siftdown(int i)
{
    int min, temp; //min = minimum index (either l or r) and temp is used for swapping
    int l, r; //l = left index of i and r = right index of i
    
    while(left(i) <= size) {
        l = left(i);
        r = right(i);
        min = l; //Initially the left of i is the minimum
        
        //If the right of i is smaller than the left of i, it implies that r is the new min for swapping.
        if(right(i) <= size and array[r] < array[l]) {
            min = r;
        }
        
        //Checks, if the child is smaller than the parent, then swap.
        if(array[min] < array[i]) {
            temp = array[min];
            array[min] = array[i];
            array[i] = temp;
            i = min;
        }
        
        //Else we are finished and we break the loop.
        else
            break;
    }
}

//==================================================================
// This method prints a Heap in 2D format.
//Optional argument k is the index of element which will be printed in red color
//if not argument provided, the entire array/tree will be printed in white color.
void Heap::print(int k)
{
    //cout << "\033[1;31mbold red text\033[0m\n";
    if(size >0)
    {
        int levels = int(log2(size));
        int *spaces = new int[levels+1];
        spaces[levels]=0;

        for(int j=levels-1; j>=0; j--)
        {
                spaces[j]=2*spaces[j+1]+1;
        }
        
        int level=0;
        for (int i=0; i<size; i++)
        {
            if(i == (pow(2,level)-1))
            {
                cout<<endl<<endl;
            
                for(int k=0; k<spaces[level]; k++)
                cout<<"   ";
                level++;
        
            }
            if(i==k)
                cout<<std::left<<"\033[1;31m"<<setw(3)<<array[i]<<"\033[0m";
            else
                cout<<std::left<<setw(3)<<array[i];
            
            if(level>1)
            {
                for(int k=0; k<spaces[level-2]; k++)
                    cout<<"   ";
            }
            
        }

        cout<<endl;
        
        for(int i=0; i<spaces[0]*log2(size/2)+4; i++)
            cout<<"__";
        
        cout<<endl;
        delete[] spaces;
    }

}
//=====================================
// This method will sort the internal array
// Hint: keep extracting the min value from the heap and add it into a new array. Replace the original internal array with the new array
void Heap::sort()
{
    //If the heap is empty, we cannot sort, hence print error.
    if(size == 0) {
        cout << "Heap is empty!" << endl;
    }
    
    int sort_size = size;      //Size of the temp array
    int *temp = new int[size]; //Create a temporary array to fill in sorted order.
    
    //Extracting the minimum value from the heap and storing it into the temp array each time.
    for(int i=0; i < sort_size; i++) {
        temp[i] = removeMin();
    }

    //Inserts the elements into the heap in sorted order each time.
    for(int i = 0; i < sort_size; i++) {
        insert(temp[i]);
    }
    
    delete[] temp;
}

//=============================================

