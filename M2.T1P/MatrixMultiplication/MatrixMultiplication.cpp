#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>

using namespace std;

const int maxNum = 100;
const int arrSize = 1000;

//Writes an input Array to an external text file
void writeFile(long array[arrSize][arrSize])
{
	int i, j;
	ofstream ArrayFile;
	ArrayFile.open("FinalOutput.txt");
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


int main()
{
	int i, j, k;
	srand(time(NULL));
	cout << "Array Size:  " << arrSize << endl;
	static int A[arrSize][arrSize], B[arrSize][arrSize];
	static long int C[arrSize][arrSize];
	initArray(A, arrSize);
	initArray(B, arrSize);

	cout << "Starting Matrix Multiplication..." << endl;

	clock_t a = clock();//Timer begins

	//Matrix Multiplication
	for (i = 0; i < arrSize; ++i)
	{
		for (j = 0; j < arrSize; ++j)
		{
			for (k = 0; k < arrSize; ++k)
			{
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}

	clock_t b = clock();//Timer Stops
	cout << "Array Multiplication Completed!" << endl;

	double timeTaken = double(b - a) / CLOCKS_PER_SEC;//Time taken from time a to b

	cout << "Processing Time: " << timeTaken << " secs" << endl;

	cout << "Multiplication done! Please check external file for results." << endl;

	writeFile(C);//Writes the resulting array to textfile

	return 0;
}