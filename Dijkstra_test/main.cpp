#include <iostream>
#include <ctime>
#include "variable_declaration.h"
#include "io_c_ver.h"

using namespace std;

int server_Num;
std::vector<std::vector<netNode_index>> netNode_MGraph_BandWidth_Left_vec;
std::vector<consumeNode_index> consumeNodeList_vec;

int main()
{
	const char * filename_c = "F:\\Huawei\\case_example\\easy2.txt";
	clock_t start, finish;

	start = clock();
	Init_netNode(netNode_MGraph_BandWidth, netNode_MGraph_RentCost);
	Init_consumeNode(consumeNodeList, requireBandWidth);
	finish = clock();
	cout << (finish - start) << "ms" << endl;
	start = clock();
	readFile_c_ver(filename_c);
	finish = clock();
	cout << (finish - start) << "ms" << endl;
	server_Num = consumeNode_nums;

	// 链路剩余容量初始化
	std::vector<std::vector<netNode_index>> netNode_MGraph_BandWidth_Left_vec(netNode_nums,
		std::vector<netNode_index>(netNode_nums, INF));
	std::vector<consumeNode_index> consumeNodeList_vec(consumeNode_nums, INF);
	Init_netNode_bandWidth_left(netNode_MGraph_BandWidth_Left_vec);
	Init_consumeNode_vec(consumeNodeList_vec);
	auto ans = Dijkstra_original(consumeNodeList[1], consumeNodeList[0], 1,
		netNode_MGraph_RentCost);
	print_Dijkstra_ShortPath(ans, consumeNodeList[1], consumeNodeList[0]);
	start = clock();
	for (int i = 0; i < consumeNode_nums; i++)
	{
		for (int j = 0; j < consumeNode_nums; j++)
		{
			if (j != i)
			{
				cout << i << " " << j << ":" << "\t" <<
					consumeNodeList[i] << "----->" << consumeNodeList[j] << endl;

				cout << "路径长度:";
				auto ans = Dijkstra_original(consumeNodeList[i], consumeNodeList[j], i,
					netNode_MGraph_RentCost);

				
				cout << ans[0][consumeNodeList[j]] << "*" << requireBandWidth[i] << "=" << ans[0][consumeNodeList[j]] * requireBandWidth[i] << "\t";
				print_Dijkstra_ShortPath(ans, consumeNodeList[i], consumeNodeList[j]);
			}
		}
	}
	finish = clock();
	cout << (finish - start) << "ms" << endl;
	// Floyd 算法
	/*start = clock();
	Floyd_original();
	finish = clock();
	cout << (finish - start) << "ms" << endl*/;


	auto ans1 = Dijkstra_original(consumeNodeList[0], consumeNodeList[2], 0,
		netNode_MGraph_RentCost);
	auto ans2 = Dijkstra_original(consumeNodeList[2], consumeNodeList[0], 1,
		netNode_MGraph_RentCost);
	//merge_Dijkstra_server(consumeNodeList_vec, ans1, ans2, 0, 2);
	start = clock();
	algorithm_Dijkstra(consumeNodeList_vec);
	finish = clock();
	cout << (finish - start) << "ms" << endl;
	return 0;
}