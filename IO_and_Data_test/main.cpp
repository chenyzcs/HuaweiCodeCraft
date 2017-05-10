#include <iostream>
#include <ctime>
#include "variable_declaration.h"
#include "io_c_ver.h"

using namespace std;

int main()
{
	const char * filename_c = "F:\\Huawei\\case_example\\case4.txt";
	
	clock_t start, finish;
	start = clock();
	Init_netNode(netNode_MGraph_BandWidth, netNode_MGraph_RentCost);
	Init_consumeNode(consumeNodeList, requireBandWidth);
	finish = clock();
	cout << finish - start << "/" << CLOCKS_PER_SEC << endl;
	start = clock();
	readFile_c_ver(filename_c);
	finish = clock();
	cout << finish - start << "/" << CLOCKS_PER_SEC << endl;
	return 0;
}