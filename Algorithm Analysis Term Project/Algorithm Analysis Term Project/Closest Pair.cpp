#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>
#include <stdlib.h>

using namespace std; 

int main()
{
	int n = 1000; //initial input, also input size counter
	const int MAXINPUT = 100000; //max input size
	const int PLANESIZE = 100; //plane size ex(100 by 100)
	int trial = 1; //to keep track of trial #
	int random = 0; //create the random variable
	srand(time(NULL)); //seed the random variable
	pair<int, int> data[MAXINPUT];

	//Test file creation
	ofstream myfile;

	//ENSURE TEST FILE IS CREATED ON COMPUTER RUNNING FINAL TRIALS
	myfile.open("C:\\Users\\Tucker\\Documents\\test.txt", ios::trunc); //trunc to delete previous test file 
	myfile.close(); 
	myfile.open("C:\\Users\\Tucker\\Documents\\test.txt", ios::app); //open append mode to add new writes to file
	myfile << "Writing this to a file.\n"; //test write
	
	//-------------------------------------------------------------------------------------
	do {
		myfile << "Trial number: " << trial << " "; 
		myfile << "Trial imput size: " << n << " "; 

		//create input files here
		for (int i = 1; i <= n; i++)
		{
			data[i].first = ((rand() % PLANESIZE) + 1); 
			data[i].second = ((rand() % PLANESIZE) + 1);
		}

		auto start = chrono::steady_clock::now(); 
		//algorithm logic goes here 





		auto end = chrono::steady_clock::now(); 

		myfile << "Elapsed time (s): " << chrono::duration_cast<chrono::seconds>(end - start).count() << " " << endl;
		//myfile << "Value: " << random << endl;

		n = n + 10; //incriment input size
		trial++; //incriment trial
	} while (n <= MAXINPUT);
	//-------------------------------------------------------------------------------------

	myfile.close();

	std::cout << "test complete " << endl;;
	std::system("pause");

	return 0;
}