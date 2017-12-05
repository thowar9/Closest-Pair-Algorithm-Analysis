#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>
#include <stdlib.h>

using namespace std; 

int main()
{
	int n = 1000; //initial input 
	int trial = 1; //to keep track of trial #
	int random = 0; //create the random variable
	srand(time(NULL)); //seed the random variable

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
		random = ((rand() % 100) + 1); 

		auto start = chrono::steady_clock::now(); 
		
		//algorithm logic goes here 




		auto end = chrono::steady_clock::now(); 

		myfile << "Elapsed time (s): " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " ";
		myfile << "Value: " << random << endl;

		n = n + 10; //incriment input size
		trial++; //incriment trial
	} while (n <= 100000); 
	//-------------------------------------------------------------------------------------
	myfile.close();

	std::cout << "test";
	std::system("pause");
	return 0;
}