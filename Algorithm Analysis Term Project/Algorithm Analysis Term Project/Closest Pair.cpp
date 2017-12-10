#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>
#include <stdlib.h>
#include <vector>
#include <algorithm>

//increased stack reserve size to 32MB via properties->configuration properties->linker->system
//it still overflows :( issue terminating the recursion? 

using namespace std; 

double dist(pair<int, int>, pair<int, int>); 
double recursiveClosest(vector<pair<int, int>>, vector<pair<int, int>>); 
double bruteForceUtility(vector<pair<int, int>>); 
double findMin(double, double); 
bool sortbysec(const pair<int, int> &, const pair<int, int> &);
double areaClosest(vector<pair<int, int>>, double);

const int MAXINPUT = 100000; //max input size
const int PLANESIZE = 1000; //plane size ex(100 by 100)

int main()
{
	int n = 1000; //initial input, also input size counter
	pair <int, int> tempPair; 
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
				dataX.push_back(data.at(i)); 
				dataY.push_back(data.at(i));
			}

			sort (dataX.begin(), dataX.end()); //sort ascending according to X
			sort (dataY.begin(), dataY.end(), sortbysec); //sort ascending according to Y

			recursiveClosest(dataX, dataY); //call recursion

			auto end = chrono::steady_clock::now();

			toAverage[trial - 1] = chrono::duration_cast<chrono::milliseconds>(end - start).count();

			outDivConq << "Trial " << trial << ": " << toAverage[trial - 1] << " ";
			trial++;
		}
		average = (toAverage[0] + toAverage[1] + toAverage[2]) / 3.0; //avg trials
		outDivConq << "Run: " << run << " Average: " << average << endl
			<< "trial 1: " << toAverage[0] << " trial 2: " << toAverage[1] << " trial 3: \n";
		cout << "Run: " << run << endl; 

		n = n + SKIPBY; //incriment input size
		run++; //incriment run number 
	} while (n < MAXINPUT); 
	//-------------------------------------------------------------------------------------
	outDivConq.close(); 

	std::cout << "test complete " << endl; //ADD CORRECT STATEMENT, MOVE TO CORRECT SPOT 
	std::system("pause");

	return 0;
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
		cout << "time for brute force utility. now in conquer phase!\n"; //TEST STATEMENT
		return bruteForceUtility(dataX); 
	}

	int middleIndex = (dataX.size() / 2) - 1; //finds the index middle point which defines vertical line 

	for (int i = 0; i < dataX.size(); i++)
	{
		if (dataX.at(i).first <= dataX.at(middleIndex).first)
			dataXleft.push_back(dataX.at(i)); //X sorted points on left side of line 
		else
			dataXright.push_back(dataX.at(i)); //X sorted points on right side of line 

		if (dataY.at(i).first <= dataX.at(middleIndex).first)
			dataYleft.push_back(dataY.at(i)); //Y sorted points on left side of line
		else
			dataYright.push_back(dataY.at(i)); // Y sorted points on left side of line
	}
	dataX.clear();
	dataY.clear();

	distanceLeft = recursiveClosest(dataXleft, dataYleft); //recursive call for left side
	cout << "made it through left side\n"; //TEST STATEMENT
	dataXleft.clear();
	dataYleft.clear();

	distanceRight = recursiveClosest(dataXright, dataYright); //recursive call for right side 
	cout << "made it through right side\n"; //TEST STATEMENT
	dataXright.clear();
	dataYright.clear(); 

	minimumDistance = findMin(distanceLeft, distanceRight); //decide which has shorter distance
	distanceMiddle = areaClosest(dataY, minimumDistance); //find shortest distance in middle strip "area"

	minimumDistance = findMin(minimumDistance, distanceMiddle); 

	return minimumDistance; 
}

double areaClosest(vector<pair<int, int>> dataY, double d)
{
	double min = d; 
	for (int i = 0; i < dataY.size(); ++i)
	{
		for (int j = i + 1; j < dataY.size() && (dataY.at(j).second - dataY.at(i).second) < min; ++j)
		{
			if (dist(dataY.at(i), dataY.at(j)) < min)
			{
				min = dist(dataY.at(i), dataY.at(j)); 
			}
		}
	}
	return min; 
}

double bruteForceUtility (vector <pair<int, int>> data) //utility for recursiveClosest
{
	double minimumDistance = sqrt(2 * PLANESIZE*PLANESIZE); //to hold minimum distance for brute force; 
	double currentDistance = 0; 
	cout << "start brute force utility--"; //TEST STATEMENT
	for (int i = 0; i < data.size() - 1; i++)
	{
		for (int j = (i + 1); j < data.size(); j++)
		{
			currentDistance = dist(data.at(i), data.at(j));
			if (currentDistance < minimumDistance)
			{
				minimumDistance = currentDistance;
			}
		}
	}
	cout << "--end brute force utility\n"; //TEST STATEMENT
	return minimumDistance; 
}

double dist(pair<int, int> a, pair<int, int> b)
{
	int distancex = (a.first - b.first)*(a.first - b.first);
	int distancey = (a.second - b.second)*(a.second - b.second);
	double distance = sqrt(abs(distancex + distancey));
	return distance;
}

double findMin(double first, double second)
{
	if (first < second) return first;
	else return second;
}

// utility function to sort the vector elements by second element of pairs
bool sortbysec(const pair<int, int> &a, const pair<int, int> &b)
{
	return (a.second < b.second);
}