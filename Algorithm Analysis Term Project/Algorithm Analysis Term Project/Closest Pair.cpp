#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>
#include <stdlib.h>

using namespace std; 

double dist(pair<int, int>, pair<int, int>); 
int compareX(const void*, const void*); 
int compareY(const void*, const void*); 

int main()
{
	int n = 1000; //initial input, also input size counter
	const int MAXINPUT = 1250; //max input size
	const int PLANESIZE = 1000; //plane size ex(100 by 100)
	const int SKIPBY = 10; 
	int run = 1; //to keep track of run #
	int trial = 1; //to keep track of trial # per run
	double average = 0; 
	double toAverage[3] = { 0,0,0 };
	int random = 0; //create the random variable
	srand(time(NULL)); //seed the random variable

	pair<int, int> data[MAXINPUT];
	double minimumDistance = sqrt(2 * pow(PLANESIZE,2)); //to hold minimum distance 

	//Test file creation
	ofstream outBruteForce;
	ofstream outDivConq; 

	//MOVE TO CORRECT SPOT && ENSURE TEST FILE IS CREATED ON COMPUTER RUNNING FINAL TRIALS
	outDivConq.open("C:\\Users\\Tucker\\Documents\\DivideAndConquerOutput.txt", ios::trunc); //trunc to delete previous test file 
	outDivConq.close();
	outDivConq.open("C:\\Users\\Tucker\\Documents\\DivideAndConquerOutput.txt", ios::app); //open append mode to add new writes to file
	outDivConq << "Writing divide and conquer trial output to a file:\n"; //write

	//create input files here
	//-------------------------------------------------------------------------------------
	do {//Divide and conquer here 
		trial = 1;
		while (trial <= 3)
		{
			//create input files here
			for (int i = 0; i <= n - 1; i++)
			{
				data[i].first = ((rand() % PLANESIZE) + 1);
				data[i].second = ((rand() % PLANESIZE) + 1);
			}

			auto start = chrono::steady_clock::now();

			pair<int, int> dataX[MAXINPUT]; 
			pair<int, int> dataY[MAXINPUT];
			for (int i = 0; i < n; i++)
			{
				dataX[i] = data[i]; 
				dataY[i] = data[i]; 
			}

			qsort(dataX, n, sizeof(pair<int, int>), compareX); 
			qsort(dataY, n, sizeof(pair<int, int>), compareY); 

			//REMAINING LOGIC HERE



			auto end = chrono::steady_clock::now();

			toAverage[trial - 1] = chrono::duration_cast<chrono::milliseconds>(end - start).count();

			outDivConq << "Trial " << trial << ": " << toAverage[trial - 1] << " ";
			trial++;
		}
		average = (toAverage[0] + toAverage[1] + toAverage[2]) / 3;
		outDivConq << "Run: " << run << " Average: " << average << endl;

		n = n + SKIPBY; //incriment input size
		run++; //incriment run number 
	} while (n < MAXINPUT); 
	//-------------------------------------------------------------------------------------
	outDivConq.close(); 

	/*
	//ENSURE TEST FILE IS CREATED ON COMPUTER RUNNING FINAL TRIALS
	outBruteForce.open("C:\\Users\\Tucker\\Documents\\BruteForceOutput.txt", ios::trunc); //trunc to delete previous test file 
	outBruteForce.close();
	outBruteForce.open("C:\\Users\\Tucker\\Documents\\BruteForceOutput.txt", ios::app); //open append mode to add new writes to file
	outBruteForce << "Writing brute force trial output to a file:\n"; //write
	//-------------------------------------------------------------------------------------
	do { //brute force runs below
		trial = 1; 
		while (trial <= 3) 
		{
			//create input files here
			for (int i = 0; i <= n-1; i++)
			{
				data[i].first = ((rand() % PLANESIZE) + 1);
				data[i].second = ((rand() % PLANESIZE) + 1);
			}

			auto start = chrono::steady_clock::now();

			//brute force algorithm logic goes here 
			for (int i = 0; i < n; i++)
			{
				for (int j = (i + 1); j <= n; j++)
				{
					if (dist(data[i], data[j]) < minimumDistance)
					{
						minimumDistance = dist(data[i], data[j]);
					}
				}
			}
			auto end = chrono::steady_clock::now();

			toAverage[trial-1] = chrono::duration_cast<chrono::milliseconds>(end - start).count(); 

			outBruteForce << "Trial " << trial << ": " << toAverage[trial-1] << " "; 
			trial++;

		}

		average = (toAverage[0] + toAverage[1] + toAverage[2])/3; 
		outBruteForce << "Run: " << run << "Average: " << average << endl; 

		n = n + SKIPBY; //incriment input size
		run++; //incriment run number 

	} while (n < MAXINPUT);
	//-------------------------------------------------------------------------------------

	outBruteForce.close();
	*/

	std::cout << "test complete " << endl; //ADD CORRECT STATEMENT, MOVE TO CORRECT SPOT 
	std::system("pause");

	return 0;
}

double dist(pair<int, int> a, pair<int, int> b)
{
	return sqrt((a.first - b.first)*(a.first - b.first) + (a.second - b.second)*(a.second - b.second));
}

int compareX(const void* a, const void* b)
{
	pair<int, int> *p1 = (pair<int, int>*)a; 
	pair<int, int> *p2 = (pair<int, int>*)b; 
	return (p1->first - p2->first); 
}

int compareY(const void* a, const void* b)
{
	pair<int, int> *p1 = (pair<int, int>*)a;
	pair<int, int> *p2 = (pair<int, int>*)b;
	return (p1->second - p2->second);
}


