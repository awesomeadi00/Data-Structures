#include<iostream>
#include<fstream>
#include<sstream>
#include<math.h>
#include<list>

using namespace std;
class HashNode
{
    private:
        string key;
        string value;
    public:
        HashNode(string key, string value)
        {
            this->key = key;
            this->value = value;
        }
        friend class HashTable;
};

class HashTable
{
    private:
        HashNode **nodeArray;           // Array of Pointers to Hash Nodes for Lin, Quad Probing
        list<HashNode> *buckets;        // Array of lists of type Hash Nodes for Chaining
        int size;                       // Current Size of HashTable
        int capacity;                   // Total Capacity of HashTable
        int probes;                     // Total Number of probes (Collisions avoided)
        int method;                     // 1 Linear Probing, 2 Quadratic, 3 Chaining
    
    public:
        HashTable(int capacity, int method);
        unsigned long hashCode(string key);
        void insert(string key, string value);
        string search(string key);
        void erase(string key);
        int getSize();
        int getprobes();
        ~HashTable();

};
//======================================================
int main(void)
{
    ifstream fin;
    fin.open("zipcodes.csv");
    if(!fin){
        cout << "Can not open the file <zipcodes.txt>!" << endl;
        exit(-1);
    }
    int method;
    do {
        cout << "Following are available collision resolution methods:" << endl;
        cout << "1: Linear Probing" << endl << "2: Quadratic Probing" << endl << "3: Chaining" << endl;
        cout << "Please select a method: ";
        cin >> method;
        fflush(stdin);
        cin.clear();
    } while(cin.fail() or method < 1 or method > 3);

    string line;
    HashTable myHashTable(24851,method);    //Prime number bigger than >24850 (19880*1.25) (Cap = 24851)
    getline(fin,line);                      //Skip first line
    while(!fin.eof())
    {
        string key, value;
        getline(fin,key,',');
        getline(fin,value);
        //cout << key << ":" << value << endl;
        myHashTable.insert(key,value);
    }
    fin.close();
    
    cout << "===================================================" << endl;
    cout << "Hash Table size = " << myHashTable.getSize() << endl;
    cout << "Total Number of probes = " << myHashTable.getprobes() << endl;
    cout << "Avg. Number of probes Per Entry = " << float(myHashTable.getprobes())/myHashTable.getSize() << endl;
    cout << "===================================================" << endl;

    string user_input, command, argument1, argument2;

    while(true)
    {
        cout << endl;
        cout << ">";
        getline(cin,user_input);

        stringstream sstr(user_input);
        getline(sstr,command,' ');
        getline(sstr,argument1,',');
        getline(sstr,argument2);

        if(command == "search")
            cout << "Zip code for " << argument1 << " is: " << myHashTable.search(argument1) << endl;
            
        else if(command == "insert") {myHashTable.insert(argument1, argument2); }
            
        else if(command == "erase") {
            if(method != 3)  {cout << "Method only implemented for Chaining" << endl; }
            else
                myHashTable.erase(argument1);
        }
        
        else if(command == "help")
            cout << "Commands available \ninsert <key,value>\nsearch <key>\nerase <key>" << endl;
            
        else if(command == "exit") {break; }
        
        else
            cout << "Invalid command!!!" << endl;
        }
    return 0;
}
//===================================================
HashTable::HashTable(int capacity, int method)
{
    this->method = method;
    if(this->method != 3)
    {
        nodeArray = new HashNode*[capacity];           //Methods 1/2: Array of Pointers to Hash Nodes
        for(int i=0; i < capacity; i++)
            nodeArray[i] = nullptr;
    }
    else
        buckets = new list<HashNode>[capacity];       //Method 3: Each bucket has a list of HashNodes

    this->capacity = capacity;
    this->size = 0;
    this->probes = 0;
}
//===================================================
//Converts key to a specific unsigned long value which is the position in the Hash Table.
unsigned long HashTable::hashCode(string key)
{
    //Cycle shift Hash Code Implementation
    unsigned long code = 0;
    for(int i = 0; i < key.length(); i++){
        code = (code << 5) | (code >> 27);
        code += (unsigned long)key[i];
    }
    return code % capacity; //Ensures that hashed code is within Capacity
}
//================================================
//This will take the hashcoded key and insert the value into the Hash Table.
void HashTable::insert(string key, string value)
{
    //Assign index of key through the hashCode() function.
    unsigned long index = hashCode(key);
    
    //Linear Probing: Method 1
    if(method == 1) {
        //Checks if the the Hash Table is full, we cannot insert anymore.
        if(size == capacity) {
            cout << "Hash Table is Full!" << endl;
            return;
        }
        
        //While the nodeArray[index] has an entry and the index of the entry(key) is not the same. Increment index in linear fashion.
        while(nodeArray[index] != nullptr and nodeArray[index]->key != key) {
            index++;
            index %= capacity;
            probes++;
        }
        
        //If the key is the same key, the update it instead of creating another node.
        if(nodeArray[index]->key == key) {
            nodeArray[index]->value = value;
        }
        
        //Otherwise, just create another HashNode and increment the size.
        else {
            nodeArray[index] = new HashNode(key, value);
            size++;
        }

    }
    
    //Quadratic Probing: Method 2
    else if(method == 2) {
        int base = 1;
        //Checks if the the Hash Table is full, we cannot insert anymore.
        if(size == capacity) {
            cout << "Hash Table is Full!" << endl;
            return;
        }
        
        //While the nodeArray[index] has an entry and the index of the entry(key) is not the same. Increment index in quadratic fashion.
        while(nodeArray[index] != nullptr and nodeArray[index]->key != key) {
            index = index + pow(base, 2);
            index %= capacity;
            probes++;
            base++;
        }
        
        //If the key is the same key, the update it instead of creating another node.
        if(nodeArray[index]->key == key) {
            nodeArray[index]->value = value;
        }
        
        //Otherwise, just create another HashNode and increment the size.
        else {
            nodeArray[index] = new HashNode(key, value);
            size++;
        }
    }
    
    
    //Seperate Chaining: Method 3
    else if(method == 3) {
        //Let there be an iterator to first cycle through the bucket and check if there is already an existing HashNode with this same key, if so then we can simply update the HashNode instead of pushing back another one.
        list<HashNode>::iterator it;
        it = buckets[index].begin();
    
        //Iterate through the bucket.
        while(true){
            //If the key found is the same as the key in the bucket, we can simply update the HashNode's value.
            if(it->key == key) {
                it->value = value;
                break;
            }
            
            //If it reaches to the end of the bucket, it means it's not in the Hash Table, hence pushback
            else if(it == buckets[index].end()) {
                buckets[index].push_back(HashNode(key, value));
                size++;
                break;
            }
            
            //Iterate to the next HashNode in the bucket (list). Each time we iterate, there is a collision, hence we probe.
            it++;
            probes++;
        }
    }
}
//===================================================
//This function will search the hashtable for the string (depending on whichever method is selected, a different operation is conducted)
string HashTable::search(string key) {
    unsigned long index = hashCode(key);
    
    //Linear Probing: Method 1
    if(method == 1) {
        int count = 0;
        
        //If the key is not found, it will keep iterating the Hash Table to find the index at which the key is in.
        if(nodeArray[index] != nullptr and nodeArray[index]->key != key) {
            while(nodeArray[index] != nullptr and nodeArray[index]->key != key) {
                //To avoid infinte looping, if the count exceeds the capacity, it is clearly not in the Hash Table
                if(count == capacity) {
                    return "Not Found!";
                }
                
                //If the key is found, the value of that index is returned
                if(nodeArray[index]->key == key) {
                    return nodeArray[index]->value;
                }
                
                //Increment index in linear fashion.
                count++;
                index++;
                index %= capacity;
            }
            
            //After incrementation, we do one last check, if the index is at NULL, then we return "Not Found!"
            if(nodeArray[index] == nullptr) {
                return "Not Found!";
            }
            
            //Else we return the value.
            return nodeArray[index]->value;
        }
        
        //If the key is immediately found, then no need to enter the loop, simply return the value.
        else
            if(nodeArray[index] == nullptr) {
                return "Not Found!";
            }
            else {
                return nodeArray[index]->value;}
    }
    
    
    //Quadratic Probing: Method 2
    else if(method == 2) {
        int count(0), base(0);
        
        //If the key is not found, it will keep iterating the Hash Table to find the index at which the key is in.
        if(nodeArray[index] != nullptr and nodeArray[index]->key != key) {
            while(nodeArray[index] != nullptr and nodeArray[index]->key != key) {
                //To avoid infinte looping, if the count exceeds the capacity, it is clearly not in the Hash Table
                if(count == capacity) {
                    return "NULL";
                }
                
                //If the key is found, the value of that index is returned
                if(nodeArray[index]->key == key) {
                    return nodeArray[index]->value;
                }
                
                //Increment index in quadratic fashion.
                count++;
                base++;
                index = index + pow(base, 2);
                index %= capacity;
            }
            
            //After incrementation, we do one last check, if the index is at NULL, then we return "Not Found!"
            if(nodeArray[index] == nullptr) {
                return "Not Found!";
            }
            
            //Else we return the value.
            return nodeArray[index]->value;
        }
        
        //If the key is immediately found, then no need to enter the loop, simply return the value.
        else
            if(nodeArray[index] == nullptr) {
                return "NULL";
            }
            else
                return nodeArray[index]->value;
    }
    
    
    //Seperate Chaining: Method 3
    else {
        list<HashNode>::iterator it;
        
        for(it = buckets[index].begin(); it != buckets[index].end(); it++) {
            if(it->key == key) {
                return it->value;
            }
        }
        return "Not Found!";
    }
}
//=====================================================
//This function is only utilized for method 3. This will erase an entry with a particular key from the bucket.
void HashTable::erase(string key)
{
    unsigned long index = hashCode(key);
    
    //Find the key
    list<HashNode>::iterator it;
    
    //If the bucket is empty, they key is not in the Hash Table.
    if(buckets[index].empty()) {
        cout << "Key is not in Hash Table!" << endl;
    }
    
    
    for(it = buckets[index].begin(); it != buckets[index].end(); it++){
        //If the key is found, then check if the iterator is at the end of the list. If not, it implies the key is inside the bucket at index iterator.
        if(it->key == key){
            buckets[index].erase(it); //Erase the list index if it is not at the end of the list.
            size--;
            cout << "Successfully Erased!" << endl;
            break;
        }
    }
}
//=====================================================
//Returns the size of the Hash Table.
int HashTable::getSize()
{
    return this->size;
}
//======================================================
//Returns the number of probes (collisions handled)
int HashTable::getprobes()
{
    return this->probes;
}
//======================================================
//Destructor: Clears up memory
HashTable::~HashTable()
{
    if(method == 3) {
        while(!buckets->empty())
            buckets->pop_front();
    }
    
    else
        delete[] nodeArray;
}
//======================================================

