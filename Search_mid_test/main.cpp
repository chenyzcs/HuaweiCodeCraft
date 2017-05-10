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
//F:\Huawei\20170323\case_example\第二批练习用例\0 初级
	const char * filename_c = "F:\\Huawei\\case_example\\0\\case0.txt";
	//const char * filename_c = "F:\\Huawei\\case_example\\123.txt";
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

	std::vector<netNode_index> require_band_width_to_netNode(netNode_nums, 0);
	Init_req_bandwidth_to_netNode(require_band_width_to_netNode);
	/*start = clock();
	algorithm_Dijkstra(consumeNodeList_vec);
	finish = clock();
	cout << (finish - start) << "ms" << endl;
	Init_netNode_bandWidth_left(netNode_MGraph_BandWidth_Left_vec);
	auto res = output_ans(consumeNodeList_vec);*/
	/*cout << endl;
	start = clock();
	auto r = out_degree_max();
	finish = clock();
	cout << (finish - start) << "ms" << endl;
	cout << endl;
	start = clock();*/
	
	/*std::default_random_engine generator(time(NULL));
	std::uniform_int_distribution<int> dis_n(2, consumeNode_nums - 1);
	for (int i = 0; i < 50; i++)
	{
		cout << dis_n(generator) << endl;
	}

	for (int i = 0; i < 8; i++)
	{
		std::vector<int> r(i);
		std::vector<std::vector<int>> result;
		Cij(8, i, r, i, result);
	}*/
	
	// search
	search();

	/*finish = clock();
	cout << (finish - start) << "ms" << endl;
	auto s = output_ans_after_link_merge(r);
	cout << endl;
	cout << s;
	cout << endl;*/
	//spfa(7,15,netNode_MGraph_RentCost_vec,netNode_MGraph_BandWidth);
	cout << "Max_Flow_Min_Cost" << endl;
	start = clock();

	//std::vector<netNode_index> x{ 12,32,52,72,92,112,132,152 };
	//auto dd = Max_Flow_Min_Cost(x);
	//cout << dd.back()[0] << endl;
	finish = clock();
	cout << (finish - start) << "ms" << endl;
	start = clock();
	float min_cost;
	gen(&min_cost);
	
	auto xx = exchange_host_list(&min_cost);
	auto yy = Max_Flow_Min_Cost(xx);
	//c.erase(remove(c.begin(), c.end(), 1963), c.end());
	cout << yy.back()[0] << endl;
	//yy.erase(remove(yy.end()), yy.end());
	//xx.erase(xx.end());
	
	//auto yy = Max_Flow_Min_Cost(xx);
	//auto zz = output_ans_after_link_merge(yy);
	//cout << zz;

	finish = clock();
	cout << (finish - start) << "ms" << endl;
	auto zz = output_ans_after_link_merge(yy);
	cout << zz;

	auto s = output_direct_link();
	cout << s;
	cout << endl;
	//random_alg();
	//dijkstra_priority_queue(0,22, netNode_MGraph_BandWidth_Left_vec,);
	priority_queue<int> s1;
	s1.push(15);
	s1.push(11);
	s1.push(90);
	s1.push(7);
	auto t = s1.top();
	return 0;
}