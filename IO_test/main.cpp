#include <iostream>
#include <string>
#include <ctime>
#include "io_cpp_ver.h"
#include "io_c_ver.h"

using namespace std;

int main()
{
	const string filename_cpp = "F:\\Huawei\\case_example\\case3.txt";
	const char * filename_c = "F:\\Huawei\\case_example\\case3.txt";

	clock_t start, finish;
	start = clock();
	readFile_cpp_ver(filename_cpp);
	finish = clock();
	cout << finish - start << "/" << CLOCKS_PER_SEC << endl;
	start = clock();
	readFile_c_ver(filename_c);
	finish = clock();
	cout << finish - start << "/" << CLOCKS_PER_SEC << endl;

	return 0;
}