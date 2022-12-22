#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void findMinMax(int arrayPtr[], int arraySize, int& max, int& min);    //Function Declaration

int main() {
    
    //max = 0 as that is lowest value between 0-100, and min = 100 as that is highest value between 0-100.
    int arraySize, max(0), min(100);
    cout << "Enter the size of the array: " << endl;
    cin >> arraySize;
    
    int *arrayPtr = new int[arraySize];
    srand((unsigned int) time (NULL));
    
    for(int i = 0; i < arraySize; i++) {
        arrayPtr[i] = rand()%(101);
        cout << "array[" << i << "] = " << arrayPtr[i] << endl;
    }
    
    findMinMax(arrayPtr, arraySize, max, min);
    
    cout << "The maximum value in the array is: " << max << endl;
    cout << "The minimum value in the array is: " << min << endl;
    
    delete[] arrayPtr;
    
    return(EXIT_SUCCESS);
}

//Function computes the maximum and minimum value in the array.
void findMinMax(int arrayPtr[], int arraySize, int& max, int& min) {
    
    //Finding the max in the array:
    for(int i = 0; i < arraySize; i++) {
        if(arrayPtr[i] > max) {
            max = arrayPtr[i];
        }
        else {
            continue;
        }
    }
    
    //Finding the min in the array:
    for(int i = 0; i < arraySize; i++) {
        if(arrayPtr[i] < min) {
            min = arrayPtr[i];
        }
        else {
            continue;
        }
    }
}
