#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>
#include <stdlib.h>

//to increase heap size
#pragma comment(linker, "/HEAP:4000000") 

using namespace std; 

double dist(pair<int, int>, pair<int, int>); 
int compareX(const void*, const void*); 
int compareY(const void*, const void*); 
double divideAndConquer(pair<int, int>[], pair<int, int>[], int); 
double findMin(double, double); 
double closestInArea(pair<int, int>, double, int); 

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
	pair<int, int> BFdata[MAXINPUT]; 

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
				data[i].first = ((rand() % PLANESIZE) + 1); //populate x
				data[i].second = ((rand() % PLANESIZE) + 1); // populate y
			}

			auto start = chrono::steady_clock::now();

			pair<int, int> dataX[MAXINPUT]; //create array for sorting by x
			pair<int, int> dataY[MAXINPUT]; //create array for sorting by y
			for (int i = 0; i < n; i++)
			{
				dataX[i] = data[i]; 
				dataY[i] = data[i]; 
			}

			qsort(dataX, n, sizeof(pair<int, int>), compareX); 
			qsort(dataY, n, sizeof(pair<int, int>), compareY); 

			divideAndConquer(dataX, dataY, n);

			auto end = chrono::steady_clock::now();

			toAverage[trial - 1] = chrono::duration_cast<chrono::milliseconds>(end - start).count();

			outDivConq << "Trial " << trial << ": " << toAverage[trial - 1] << " ";
			trial++;
		}
		average = (toAverage[0] + toAverage[1] + toAverage[2]) / 3; //avg trials
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
				BFdata[i].first = ((rand() % PLANESIZE) + 1);
				BFdata[i].second = ((rand() % PLANESIZE) + 1);
			}

			auto start = chrono::steady_clock::now();

			//brute force algorithm logic goes here 
			for (int i = 0; i < n; i++)
			{
				for (int j = (i + 1); j <= n; j++)
				{
					if (dist(BFdata[i], BFdata[j]) < minimumDistance)
					{
						minimumDistance = dist(BFdata[i], BFdata[j]);
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
{	//utility for qsort
	pair<int, int> *p1 = (pair<int, int>*)a; 
	pair<int, int> *p2 = (pair<int, int>*)b; 
	return (p1->first - p2->first); 
}

int compareY(const void* a, const void* b)
{	//utility for qsort
	pair<int, int> *p1 = (pair<int, int>*)a;
	pair<int, int> *p2 = (pair<int, int>*)b;
	return (p1->second - p2->second);
}

double findMin(double first, double second)
{
	if (first < second) return first;
	else return second; 
}
//to find the distance between closest points in given area
double closestInArea(pair<int, int> area[], double distance, int n)
{
	double closestDistance = distance; //set initial closest distance 
	
	//brute force Y sorted points to find two closest
	for (int i = 0; i < n; ++i)
	{
		for (int j = i + 1; j < n && (area[j].second - area[i].second) < closestDistance; ++j)
		{
			if (dist(area[i], area[j]) < closestDistance)
			{
				closestDistance = dist(area[i], area[j]); 
			}
		}
	}
	return closestDistance; 
}

double divideAndConquer(pair<int, int> dataX[], pair<int, int> dataY[], int n)
{
	int leftIndex = 0; 
	int rightIndex = 0; 
	double distanceLeft = 0, distanceRight = 0, distance = 0; 
	double PLANESIZE = 1000; //REMEMBER
	double minimumDistance = sqrt(2 * pow(PLANESIZE, 2)); //REMEMBER //to hold minimum distance 

	if (n <= 3)
	{ //essentially brute force if there are 3 or less pairs remaining 
		for (int i = 0; i < n; i++)
		{
			for (int j = (i + 1); j <= n; j++)
			{
				if (dist(dataX[i], dataX[j]) < minimumDistance)
				{
					minimumDistance = dist(dataX[i], dataX[j]); //not needed for analysis but should be here for correctness
				}
			}
		}
		return minimumDistance; 

	}

	//find the midpoint
	int middle = floor(n / 2);
	pair<int, int> midpoint = dataX[middle]; 

	//Divide dataY[] based on midpoint 
	//Divide Y sorted pairs to left of line on middle point
	pair<int, int> *dataYleft = new pair<int,int> [middle + 1]; //REMEMBER TO FREE UP MEMORY
	//Divide Y sorted pairs to right of line on middle point
	pair<int, int> *dataYright = new pair<int, int>[n - middle - 1]; //REMEMBER TO FREE

	for (int i = 0; i < n; i++)
	{
		if (dataY[i].first <= midpoint.first)
		{ //if point is less than midpoint, sort to left???? REMEMBER to correct
			dataYleft[leftIndex++] = dataY[i]; 
		}
		else
		{ //if point is greater than midpoint, sort to right??? REMEMBER to correct
			dataYright[rightIndex++] = dataY[i];
		}
	}

	//find shortest distance on left and right side of middle point 
	distanceLeft = divideAndConquer(dataX, dataYleft, middle); //left side
	distanceRight = divideAndConquer(dataX + middle, dataYright, n - middle); //right side
	distance = findMin(distanceLeft, distanceRight); 

	//narrow down points closer than d to middle line into array
	pair<int, int> * area = new pair<int, int>[n]; //REMEMBER TO DELETE 
	int counter = 0; 
	for (int i = 0; i < n; i++)
	{
		if (abs(dataY[i].first - midpoint.first) < distance)
		{
			area[counter] = dataY[i]; 
			counter++; 
		}
	}

	//find closest points in selected area 
	//compare new distance to previous and return minimum
	double result = findMin(distance, closestInArea(area, distance, counter)); 
	
	//free memory
	
	delete[] dataYright; 
	dataYright = NULL; 
	delete[] dataYleft; 
	dataYleft = NULL; 
	delete[] area; 
	area = NULL; 
	
	return result; 	
}

