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

const int MAXINPUT = 100000; //max input size

int main()
{
	int n = 1000; //initial input, also input size counter
	pair <int, int> tempPair;
	const int PLANESIZE = 1000; //plane size ex(100 by 100)
	const int SKIPBY = 1000;
	int run = 1; //to keep track of run #
	int trial = 1; //to keep track of trial # per run
	double average = 0;
	double toAverage[3] = { 0,0,0 };
	int random = 0; //create the random variable
	srand(time(NULL)); //seed the random variable

	vector < pair<int, int> > data;
	pair<int, int> BFdata[MAXINPUT];

	double minimumDistance = sqrt(2 * pow(PLANESIZE, 2)); //to hold minimum distance for brute force 

	//Test file creation
	ofstream outBruteForce;
	
	
	//ENSURE TEST FILE IS CREATED ON COMPUTER RUNNING FINAL TRIALS
	outBruteForce.open("C:\\Users\\YOUR_NAME_HERE\\Documents\\BruteForceOutput.txt", ios::trunc); //trunc to delete previous test file
	outBruteForce.close();
	outBruteForce.open("C:\\Users\\YOUR_NAME_HERE\\Documents\\BruteForceOutput.txt", ios::app); //open append mode to add new writes to file
	outBruteForce << "Writing brute force trial output to a file:\n"; //write
	//-------------------------------------------------------------------------------------
	n = 1000;
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
			toAverage[trial-1] = chrono::duration_cast<chrono::seconds>(end - start).count();
			//outBruteForce << "Trial " << trial << ": " << toAverage[trial-1] << " ";
			trial++;
		}
		average = (toAverage[0] + toAverage[1] + toAverage[2])/3;
		outBruteForce << average << endl;
		n = n + SKIPBY; //incriment input size
		run++; //incriment run number
		} while (n < MAXINPUT);
	//-------------------------------------------------------------------------------------
	outBruteForce.close();
	

	std::cout << "test complete " << endl; //ADD CORRECT STATEMENT, MOVE TO CORRECT SPOT 
	std::system("pause");

	return 0;
}

double dist(pair<int, int> a, pair<int, int> b)
{
	int distancex = (a.first - b.first)*(a.first - b.first);
	int distancey = (a.second - b.second)*(a.second - b.second);
	double distance = sqrt(abs(distancex - distancey));
	return distance;
}