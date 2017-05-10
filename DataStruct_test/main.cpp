#include <iostream>
#include <ctime>
#include "variable_declaration.h"


using namespace std;

int main()
{	
	clock_t start, finish;
	netNode_MGraph_BandWidth;
	netNode_MGraph_RentCost;
	start = clock();
	Init_netNode(netNode_MGraph_BandWidth, netNode_MGraph_RentCost);
	finish = clock();
	cout << finish - start << "/" << CLOCKS_PER_SEC << endl;
	start = clock();
	Init_consumeNode(consumeNodeList, requireBandWidth);
	finish = clock();
	cout << finish - start << "/" << CLOCKS_PER_SEC << endl;

	return 0;
}