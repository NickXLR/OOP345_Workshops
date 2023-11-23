// Workshop 9 - Multi-threading, Thread class 
// w9_p2.cpp 
// 2022/1/5 - Jeevan Pant
// 2023/11/17 - Cornel

#include <iostream>
#include <iomanip>
#include <chrono>
#include <fstream>
#include "process_data.h"

void printHead(const std::string& str); // prints header text, embeds str into the text
void printFoot(); // prints footer text
void compareFiles(const std::string& fileName1, const std::string& fileName2);

int cout = 0;

/*
Source data file "data_int.dat" contains data in binary format. First 4 bytes (int size) 
	in the file contain a value representing total number of data items stored in the file. From 
	5th byte to the end of the file, the data items are stored consecutively, where each data item 
	is stored in a memory space of 4 bytes (int size). 
In the target data file "data_int_target.dat", your code will save the data, read from 
   "data_int.dat", in binary format. 
*/

int main(int argc, char** argv)
{
	std::cout << "Command Line:\n";
	std::cout << "--------------------------\n";
	for (int i = 0; i < argc; i++)
		std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
	std::cout << "--------------------------\n\n";

	std::string fname_source, fname_target;
	if (argc > 1)
		fname_source = argv[1];
	if (argc > 2)
		fname_target = argv[2];
	
	// The following code block creates function object pd_obj. fname_source is supplied to the 
	//   constructor, which reads number-of-data-items and the data items from the file and 
	//   copies to instance variables. The constructor stores data items in a resource array, and 
	//   prints some data items on the standard output. Invocation of the function object pd_obj 
	//   calls the global functions computeAvgFactor and computeVarFactor to compute average and 
	//   variance of the data stored in the resource arrry, and saves the same data into the file 
	//   fname_target supplied as argument. avg and var are passed by reference, so they carry 
	//   the average and variance after the invocation of the function object.

		printHead("Average and variance of record-values using a functor.");
		std::chrono::steady_clock::time_point t_before, t_after;

		sdds::ProcessData pd_obj(fname_source); // creates function object 
		if (pd_obj) {
			try {
				double avg = 0.0, var = 0.0;

				t_before = std::chrono::steady_clock::now();
				pd_obj(fname_target, avg, var); // invokes function object for input files, last two parameters are output parametes
				t_after = std::chrono::steady_clock::now();

				// sanity check
				compareFiles(fname_source, fname_target);

				std::cout << "Data statistics (\"" << fname_source << "\"):\n";
				std::cout.setf(std::ios::fixed);
				std::cout << " Average:  " << std::setw(16) << avg << std::endl;
				std::cout << " Variance: " << std::setw(16) << var << std::endl;
				std::cout.unsetf(std::ios::fixed);
				std::cout << "Time required to compute average and variance: "
				          << (std::chrono::duration_cast<std::chrono::milliseconds>(t_after - t_before)).count() 
				          << " milliseconds.\n";
			}
			catch (const std::string& msg) {
				std::cout << "ERROR: " << msg << std::endl;
			}
			catch (...) {
				std::cout << "ERROR: Something Bad Happened!\n";
			}
		}
		printFoot();
	
	return cout;
}

void printHead(const std::string& str) {
	std::cout << std::setw(90) << std::setfill('=') << "" << std::endl << std::setfill(' ');
	std::cout << std::setw(45 - str.length() / 2) << "" << str << std::endl;
	std::cout << std::setw(90) << std::setfill('-') << "" << std::endl << std::setfill(' ');
}
void printFoot() {
	std::cout << std::setw(90) << std::setfill('=') << "" << std::endl << std::endl << std::endl;
}

void compareFiles(const std::string& fileName1, const std::string& fileName2)
{
	std::ifstream file1(fileName1), file2(fileName2);
	int cnt = 0;
	while (file1 && file2)
	{
		if (file1.get() != file2.get())
		{
			std::string up("The output file doesn't have the correct binary content as the input file.\n"
			                  "  Byte " + std::to_string(cnt) + " is wrong.\n"
			                  "  Check the 'operator()' implementation to fix.\n");
			throw up;
		}
		++cnt;
	}
	std::cout << "Read [" << cnt << "] bytes from the files; the content is the same.\n";
}
