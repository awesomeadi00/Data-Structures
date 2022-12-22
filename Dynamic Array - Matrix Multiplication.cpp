#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;

int **add(int **matrix1, int **matrix2, int rows, int cols);
int **subtract(int **matrix1, int **matrix2, int rows, int cols);
int **multiply(int **matrix1, int **matrix2, int rows1, int cols1, int rows2, int cols2);
void fill(int** matrix, int rows, int cols);
void display(int** matrix, int rows, int cols);
void cleanup(int** matrix, int rows);

int main()
{
    
    int **matrix1 = NULL;
    int **matrix2 = NULL;
    int rows1, cols1, rows2, cols2;
    int **ans1 = NULL, **ans2 = NULL, **ans3 = NULL;
    
    cout << "Enter the number of rows for first Matrix: ";
    cin >> rows1;
    cout << "Enter the number of columns for first Matrix: ";
    cin >> cols1;
    cout << "Enter the number of rows for second Matrix: ";
    cin >> rows2;
    cout << "Enter the number of columns for second Matrix: ";
    cin >> cols2;
    cout << endl;
    
    // Create dynamic 2D arrays for both matricies:
    matrix1 = new int*[rows1]; //Creates array of pointers.
    for(int i=0; i < rows1; i++)
        matrix1[i] = new int[cols1]; //Fills each pointer in the array with its own array, resembles cols.
        
    matrix2 = new int*[rows2];
    for(int i=0; i<rows2; i++)
        matrix2[i] = new int[cols2];
    
    srand((unsigned int) time(NULL)); //Seed set based on time for random generation.
    
    //Time to fill both matricies:
    fill(matrix1, rows1, cols1);
    fill(matrix2, rows2, cols2);
    
    //Time to display both matricies:
    cout << "Matrix 1: " << endl;
    display(matrix1, rows1, cols1);
    
    cout << "Matrix 2: " << endl;
    display(matrix2, rows2, cols2);
    
    
    //Pefrom addition and subtraction only if both matrices have same dimensions
    if(rows1 == rows2 && cols1 == cols2)
    {
        ans1 = add(matrix1, matrix2, rows1, cols1);
        cout<<"Matrix1 + Matrix2:: "<<endl;
        display(ans1, rows1, cols1);

        ans2 = subtract(matrix1, matrix2, rows1, cols1);
        cout<<"Matrix1 - Matrix2:: "<<endl;
        display(ans2, rows1, cols1);
    }

    else {
        cout << "Cannot compute Addition or Subtraction as rows and columns of both matricies are different." << endl;
        cout << endl;
    }

    //Perform mutliplicaiton if columns of first matrix are rows to the columns of second matrix
    if(cols1 == rows2)
    {
        ans3 = multiply(matrix1, matrix2, rows1, cols1, rows2, cols2);
        cout<<"Matrix1 * Matrix2: "<<endl;
        display(ans3, rows1, cols2);
    }

    else {
        cout << "Cannot compute Multiplication as rows of Matrix 1 does not equal the columns of Matrix 2." << endl;
        cout << endl;
    }
    
    
    //Perform necessary cleanup (delete dynamically created memory)
    cleanup(matrix1, rows1);
    cleanup(matrix2, rows2);
    cleanup(ans1, rows1);
    cleanup(ans2, rows2);
    cleanup(ans3, rows1);
    
    return(EXIT_SUCCESS);
}

//Function to add both matricies.
int **add(int **matrix1, int **matrix2, int rows, int cols)
{
    int **add = new int*[rows];
    
    //Initializing and creating a 2D Dynamic Array for the Final Addition Matrix:
    for(int i = 0; i < rows; i++)
    {
        add[i] = new int[cols];
    }
    
    //Populating the values in the Addition Matrix:
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            add[i][j] = matrix1[i][j] + matrix2[i][j];
            //add works
        }
    }
    
    return add;
}

//Function to subtract both matricies.
int **subtract(int **matrix1, int **matrix2, int rows, int cols)
{
    int **sub = new int*[rows];
    
    //Initializing and creating a 2D Dynamic Array for the Final Subtraction Matrix:
    for(int i = 0; i < rows; i++)
    {
        sub[i] = new int[cols];
    }
    
    //Populating the Subtraction Matrix:
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            sub[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }
    
    return sub;
}

//Function to multiply both matricies.
int **multiply(int **matrix1, int **matrix2, int rows1, int cols1, int rows2, int cols2)
{
    int mul_row = rows1;
    int mul_col = cols2;
    int **mul = new int*[mul_row];
    
    //Initializing and creating a 2D Dynamic Array for the Final Multiplication Matrix:
    for(int i = 0; i < mul_row; i++)
    {
        mul[i] = new int[mul_col];
    }
    
    //Populating the Multiplication Matrix:
    for(int i = 0; i < mul_row; i++)
    {
        for(int j = 0; j < mul_col; j++)
        {
            for(int k = 0; k < cols1; k++)
            {
                mul[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    
    return mul;
}

//Function to populate matrix with random values between 0-20.
void fill(int** matrix, int rows, int cols)
{
    for(int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] = rand()%(21);
        }
    }
}

//Function that prints out the matrix.
void display(int** matrix, int rows, int cols)
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            cout << setw(10) << right << matrix[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

//Function that deletes any allocated memory in the heap for matricies.
void cleanup(int** matrix, int rows)
{
    if(matrix != NULL) {
        for(int i = 0; i < rows; i++) //First deallocate every pointer in the array of pointers (rows).
        {
            delete[] matrix[i];
        }
        
        delete[] matrix; //Finally deallocate the double pointer array.
    }
}

 
