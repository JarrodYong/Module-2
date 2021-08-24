#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <thread> //Initialising thread library this was used instead of Pthread becuase it wasn't working for me

using namespace std;

const int maxNum = 100;
const int arrSize = 1000;
const int maxThreads = 8;
static int A[arrSize][arrSize], B[arrSize][arrSize];
static long int C[arrSize][arrSize];
thread T[arrSize];

//Writes an input Array to an external text file
void writeFile(long array[arrSize][arrSize])
{
    int i, j;
    ofstream ArrayFile;
    ArrayFile.open("Output.txt");
    ArrayFile << "Result: " << endl;
    for (i = 0; i < arrSize; ++i)
        for (j = 0; j < arrSize; ++j)
        {
            ArrayFile << " " << array[i][j];
            if (j == arrSize - 1)
                ArrayFile << endl;
        }

    ArrayFile.close();
}

//Adding random integers to the Array
void initArray(int array[arrSize][arrSize], int size)
{
    int i, j;
    for (i = 0; i < size; ++i)
        for (j = 0; j < size; ++j)
        {
            array[i][j] = rand() % maxNum + 1;
        }
}

// Multiplying array a and b and storing in array c by dividing multiplication steps propotionally into a different threads.
void multiplication(int threadNo)
{
    int i, j, k;

    for (i = threadNo * arrSize / maxThreads; i < (threadNo + 1) * arrSize / maxThreads; i++)
    {
        for (j = 0; j < arrSize; j++)
        {
            for (k = 0; k < arrSize; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main()
{
    int i, j;
    srand(time(NULL));
    cout << "Array Size:  " << arrSize << endl;
    static int A[arrSize][arrSize], B[arrSize][arrSize];
    static long int arrayC[arrSize][arrSize];
    initArray(A, arrSize);
    initArray(B, arrSize);

    cout << "Starting Matrix Multiplication..." << endl;

    clock_t a = clock();//Timer begins

    for (i = 0; i < maxThreads; i++)//This sets up the threads for multiplication and divides the jobs accordingly
    {
        T[i] = thread(multiplication, i);
    }

    for (j = 0; j < maxThreads; j++)
    {
        T[j].join();//Stops other threads until job is complete
    }


    clock_t b = clock();//Stopping the timer
    cout << "Array Multiplication Completed!" << endl;

    double timeTaken = double(b - a) / CLOCKS_PER_SEC;

    cout << "Processing Time: " << timeTaken << " secs" << endl;

    cout << "Multiplication done! Please check external file for output." << endl;

    writeFile(C); //Writes the resulting array to textfile

    return 0;
}