#include<iostream>
#include<iomanip>
#include<time.h>
using namespace std;

#define SIZE 10000
#define MAX 50000

int debug = 0;         //If 1 it will print the arrays before and after sorting
int Shuffle = true;   //If true array will be shuffled before being passed to the next sorting function

template <typename T> void selection_sort(T array[], int n);
template <typename T> void bubble_sort(T array[], int n);
template <typename T> void insertion_sort(T array[], int n);
template <typename T> void merge_sort(T array[], int left, int right);
template <typename T> void merge(T array[], int left, int right, int mid);
template <typename T> void quick_sort(T array[], int left, int right);
template <typename T> int partition(T array[], int left, int right);
template <typename T> void print(T array[], int size);

int main() {
    int array[SIZE];
    srand((unsigned int)time(NULL));
    
    //Populate the array with random values
    for(int i =0 ; i < SIZE; i++)
        array[i] = rand() % MAX;

    if(debug) {
        cout << "Original Array:" << endl;
        print(array, SIZE);
        cout << "============================================================" << endl;
    }
    
    clock_t start, stop;
    
    //Selection Sort Timing:
    start = clock();
    selection_sort(array, SIZE);
    stop = clock();
    cout << "Selection Sort:      " << setw(8) << float(stop - start)/CLOCKS_PER_SEC*1000 << " milliseconds" << endl;
    if(debug) {
        print(array, SIZE);
        cout << "============================================================" << endl;
    }
    
    //Insertion Sort Timing:
    if(Shuffle) {random_shuffle(array, array + SIZE); } //Shuffle the contents of the array before sorting again
    start = clock();
    insertion_sort(array, SIZE);
    stop = clock();
    cout << "Insrtion Sort:       " << setw(8) << float(stop - start)/CLOCKS_PER_SEC*1000 << " milliseconds" << endl;
    if (debug) {
        print(array,SIZE);
        cout << "============================================================" << endl;
    }
    
    //Bubble Sort Timing:
    if(Shuffle) {random_shuffle(array, array + SIZE); } //Shuffle the contents of the array before sorting again
    start = clock();
    bubble_sort(array, SIZE);
    stop = clock();
    cout << "Bubble Sort:         " << setw(8) << float(stop - start)/CLOCKS_PER_SEC*1000 << " milliseconds" << endl;
    if (debug) {
        print(array, SIZE);
        cout << "============================================================" << endl;
    }
    
    //Merge Sort Timing:
    if(Shuffle) {random_shuffle(array, array + SIZE); } //Shuffle the contents of the array before sorting again
    start = clock();
    merge_sort(array, 0, SIZE-1);
    stop = clock();
    cout << "Merge Sort:          " << setw(8) << float(stop - start)/CLOCKS_PER_SEC*1000 << " milliseconds" << endl;
    if (debug) {
        print(array, SIZE);
        cout << "============================================================" << endl;
    }

    //Quick Sort Timing:
    if(Shuffle) {random_shuffle(array, array + SIZE); } //Shuffle the contents of the array before sorting again
    start = clock();
    quick_sort(array, 0, SIZE-1);
    stop = clock();
    cout << "Quick Sort:          " << setw(8) << float(stop - start)/CLOCKS_PER_SEC*1000 << " milliseconds" << endl;
    if (debug) {
        print(array, SIZE);
        cout << "============================================================" << endl;
    }
   
    return EXIT_SUCCESS;
}
//========================================================
//Function to print out the entire array
template <typename T> void print(T array[], int size) {
    for(int i =0 ; i < size; i++)
        cout << array[i] << " ";
    cout << endl;
}


//========================================================
//Selection Sort Algorithm: Selects the smallest value and then swaps then one by one in a sorted manner.
template <typename T> void selection_sort(T array[], int n) {
    T temp;
    int m;
    
    for(int i = 0; i < n-1; i++) {
        //Cycle through the entire array and find the smallest value which will be 'm'.
        m = i;
        for (int j = i+1; j < n; j++) {
            if (array[j] < array[m])
                m = j;
        }
        
        //Once the smallest is found, exchange it with value at i
        temp = array[m];
        array[m] = array[i];
        array[i] = temp;
    }
}

//========================================================
//Insertion Sort Algorithm: For each element, it inserts the smallest one into the sorted array.
template <typename T> void insertion_sort(T array[], int n) {
    int m, j;
    
    for (int i = 1; i < n; i++) {
        m = array[i];
        j = i - 1;

        while (j >= 0 and array[j] > m) {
            array[j+1] = array[j];
            j--;
        }
        array[j + 1] = m;
    }
}

//========================================================
//Bubble Sort Algorithm: Compares two elements side by side in n-1 passes of the array and sorts in this manner.
template <typename T> void bubble_sort(T array[], int n) {
    int i, j;
    int temp;             //Holding variable
        
    for(i = 0; i < n-1; i++)
    {
        for (j = 0; j < n-i-1; j++)
        {
            if (array[j+1] < array[j])  //If the value at j+1 is smaller than the one at j, we swap
            {
                temp = array[j];       //swap elements
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}

//========================================================
//Merge Sort Algorithm: Splits the array into halves until they are sorted, then merges them together in a sorted manner.
template <typename T> void merge_sort(T array[], int left, int right) {
    int m;
    
    if(left < right) {
        m = (left + right)/2;
        merge_sort(array, left, m);
        merge_sort(array, m+1, right);
        merge(array, left, right, m);
    }
    
    else
        return;
}

//Merge Helper Function: Will merge A[left...mid] with A[mid+1...right]
template <typename T> void merge(T array[], int left, int right, int mid) {
    int B[(right-left)+1]; //Create temporary array for storing the merged output.
    
    int i = left;
    int j = mid+1;
    int k = 0;
    
    while(i <= mid and j <= right) {
        //Next item will come from the left sub-array
        if(array[i] <= array[j]) {
            B[k] = array[i];
            i++; k++;
        }
        
        //Otherwise next item will come from the right sub-array
        else {
            B[k] = array[j];
            j++; k++;
        }
    }
    
    //Copy any left-over elements into the temporary array
    while(i <= mid) {B[k] = array[i]; i++; k++; }
    while(j <= right) {B[k] = array[j]; j++; k++; }
    
    //Copy the output back into the main array
    for(k = 0; k < (right-left)+1 ; k++) {
        array[left+k] = B[k];
    }
}

//========================================================
//Quick Sort Algorithm:
template <typename T> void quick_sort(T array[], int left, int right) {
    //Base case
    if (left >= right)
        return;
    
    //Partitioning the array
    int p = partition(array, left, right);
    
    //Sorting the left part
    quick_sort(array, left, p-1);
    
    //Sorting the right part
    quick_sort(array, p+1, right);
}



//Partition Helper Function:
template <typename T> int partition(T array[], int left, int right) {
    int temp;
    
    int pivot = array[right]; //let pivot be the rightmost element of the array/subarray
      
    int pivotindex = left; //pivotindex for swapping with the greatest element

    //Cycle through the entire array and compare each element with the pivot
    for (int i = left; i < right; i++) {
        //If the element is smaller than the pivot, then swap it with pivotindex and incremenet pivotindex.
        if (array[i] <= pivot) {
            temp = array[pivotindex];
            array[pivotindex] = array[i];
            array[i] = temp;
            
            pivotindex++;
        }
    }
     
    //After the cycling, we will swap the pivot with the pivotindex.
    temp = array[pivotindex];
    array[pivotindex] = array[right];
    array[right] = temp;
    
    //Return partition point
    return (pivotindex);
}
