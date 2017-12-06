#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>
#include <stdlib.h>
#include <vector>
#include <algorithm>

//to increase heap size
#pragma comment(linker, "/HEAP:4000000") 
#pragma comment(linker, "/STACK:6000000")

using namespace std; 

double dist(pair<int, int>, pair<int, int>); 
//double divideAndConquer(vector <pair<int, int> >, vector <pair<int, int>>, int); 
double recursiveClosest(vector<pair<int, int>>, vector<pair<int, int>>); 
double bruteForceUtility(vector<pair<int, int>>); 
double findMin(double, double); 
double closestInArea(vector <pair<int, int>>, double, int);
bool sortbysec(const pair<int, int> &, const pair<int, int> &);

const int MAXINPUT = 100000; //max input size

int main()
{
	int n = 1000; //initial input, also input size counter
	pair <int, int> tempPair; 
	const int PLANESIZE = 1000; //plane size ex(100 by 100)
	const int SKIPBY = 100; 
	int run = 1; //to keep track of run #
	int trial = 1; //to keep track of trial # per run
	double average = 0; 
	double toAverage[3] = { 0,0,0 };
	int random = 0; //create the random variable
	srand(time(NULL)); //seed the random variable

	vector < pair<int, int> > data;
	pair<int, int> BFdata[MAXINPUT]; 

	double minimumDistance = sqrt(2 * pow(PLANESIZE,2)); //to hold minimum distance for brute force 

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
				tempPair.first = ((rand() % PLANESIZE) + 1); //populate x
				tempPair.second = ((rand() % PLANESIZE) + 1); // populate y
				data.push_back(tempPair); //populate vector
			}

			auto start = chrono::steady_clock::now();

			vector< pair<int, int> > dataX; //create array for sorting by x
			vector< pair<int, int> > dataY; //create array for sorting by y
			for (int i = 0; i < n; i++)
			{
				dataX.push_back(data[i]); 
				dataY.push_back(data[i]);
			}

			sort (dataX.begin(), dataX.end()); 
			sort (dataY.begin(), dataY.end(), sortbysec);

			//divideAndConquer(dataX, dataY, n);
			recursiveClosest(dataX, dataY); 

			auto end = chrono::steady_clock::now();

			toAverage[trial - 1] = chrono::duration_cast<chrono::milliseconds>(end - start).count();

			outDivConq << "Trial " << trial << ": " << toAverage[trial - 1] << " ";
			trial++;
		}
		average = (toAverage[0] + toAverage[1] + toAverage[2]) / 3.0; //avg trials
		outDivConq << "Run: " << run << " Average: " << average << endl;
		cout << "Run: " << run << endl; 

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


double findMin(double first, double second)
{
	if (first < second) return first;
	else return second; 
}
//to find the distance between closest points in given area

double closestInArea(vector < pair<int, int> > area, double distance, int n)
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


// utility function to sort the vector elements by second element of pairs
bool sortbysec(const pair<int, int> &a, const pair<int, int> &b)
{
	return (a.second < b.second);
}

double recursiveClosest(vector <pair<int, int>> dataX, vector <pair<int, int>> dataY)
{	//dataX is pairs sorted by X value, dataY is pairs sorted by Y value 
	double distanceLeft; //distance between closest pair found on left on middle line
	double distanceRight; //distance betweenclosest pair found on right side of middle line
	double distanceMiddle; //distance between closest pair split by the middle line
	double minimumDistance; //to hold minimum distance 

	vector <pair<int, int>> dataXleft; //to hold X sorted data on left of middle line
	vector <pair<int, int>> dataXright; //to hold X sorted data on right of middle line 
	vector <pair<int, int>> dataYleft; //to hold Y sorted data on left of middle line
	vector <pair<int, int>> dataYright; //to hold Y sorted data on right of middle line 


	if (dataX.size() <= 3)
	{
		//brute force solve and return 
		cout << "time for brute force!\n"; 
		return bruteForceUtility(dataX); 
	}

	int middleIndex = (dataX.size() / 2) - 1; //finds the index middle point which defines vertical line 

	for (int i = 0; i < dataX.size(); i++)
	{
		if (dataX[i].first <= dataX[middleIndex].first)
			dataXleft.push_back(dataX[i]); //X sorted points on left side of line 
		else
			dataXright.push_back(dataX[i]); //X sorted points on right side of line 

		if (dataY[i].first <= dataX[middleIndex].first)
			dataYleft.push_back(dataY[i]); //Y sorted points on left side of line
		else
			dataYright.push_back(dataY[i]); // Y sorted points on left side of line
	}

	distanceLeft = recursiveClosest(dataXleft, dataYleft); //recursive call for left side
	distanceRight = recursiveClosest(dataXright, dataYleft); //recursive call for right side 





	return 0; 
}

double bruteForceUtility (vector <pair<int, int>> data) //utility for recursiveClosest
{
	return 1; //test purposes 
	double minimumDistance = 0; 

	for (int i = 0; i < data.size() - 1; i++)
	{
		for (int j = (i + 1); j < data.size(); j++)
		{
			if (dist(data[i], data[j]) < minimumDistance)
			{
				minimumDistance = dist(data[i], data[j]);
			}
		}
	}
	return minimumDistance; 
}
