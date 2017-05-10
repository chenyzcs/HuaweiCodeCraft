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
	//const char * filename_c = "F:\\Huawei\\case_example\\0\\case2.txt";
	const char * filename_c = "F:\\Huawei\\case_example\\123.txt";
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
	//std::vector<int> t00 = { 210,798,292,224,470,141,644,431,512,519,618,736,542,417,442,312,492,151,707,665,91,344,627,100,625,23,401,579,240,130,502,316,108,178,404,588,503,51,608,483,506,245,751,97,293,83,631,88,685,117,143,687,16,121,14,638,58,754,232,45,126,40,345,336,376,326,287,465,774,378,239,258,447,620,710,131,19,200,561,767,105,449,82,128,142,337,302,513,686,584,593,349,773,366,700,622,632,42,43,113,127,204,206,521,476,183,269,424,477,661,248,85,637,380,675,44,259,195,560,660,253,634};
	//auto _ret00= Max_Flow_Min_Cost(t00);
	//std::cout << _ret00.back()[0] << std::cout;
	std::vector<int> xxxxx = { 0,1};
	//auto _ret0000 = Max_Flow_Min_Cost(xxxxx);
	auto xxxx = zkw_mcmf(xxxxx);
	start = clock();
	// search
	auto out = search();
	std::vector<int> consum;
	for (int i = 0; i < out.size()-1; i++)
	{
		std::cout << out[i][out[i].size() - 2] << " ";
		consum.push_back(out[i][out[i].size() - 2]);
	}
	std::cout << std::endl;
	std::cout << std::endl;
	std::sort(consum.begin(), consum.end());
	consum.erase(unique(consum.begin(), consum.end()), consum.end());
	std::cout << consum.size() << std::endl;
	for (auto &c : consum)
		std::cout << c << " ";
	std::cout << std::endl;
	auto out_msg = output_ans_after_link_merge(out);
	//cout << out_msg;

	/*finish = clock();
	cout << (finish - start) << "ms" << endl;
	auto s = output_ans_after_link_merge(r);
	cout << endl;
	cout << s;
	cout << endl;*/
	//spfa(7,15,netNode_MGraph_RentCost_vec,netNode_MGraph_BandWidth);
	//cout << "Max_Flow_Min_Cost" << endl;
	std::vector<int> bw_(netNode_nums + 1, 0);
	for (int i = 0; i < out.size()-1; i++)
	{
		bw_[out[i][out[i].size() - 2]] += out[i][out[i].size() - 1];
		bw_[netNode_nums+1]+=out[i][out[i].size() - 1];
	}
	std::cout << "bw_:" << bw_[netNode_nums + 1] << std::endl;
	//std::vector<netNode_index> x{ 173,135,271,180,142,48,79,98,87,158,250,146,217,218,75,157,284,174,38,144,91,131,229,26,279,264,28,292,139,82,152,77,179,12,242,85,230,95,246,285,65,147,238,192,69,68,241,103,92,110,25,19,287,196,90,111,198,23,167,53,32,227,133,13,253,291,112,105,236,10,39,210,20,29,171,96,165,137,8,176,109,213,161,160,232,117,296 };
	//auto dd = Max_Flow_Min_Cost(x);
	//cout << dd.back()[0] << endl;
	finish = clock();
	std::cout << (finish - start) << "ms" << endl;
	start = clock();
	float min_cost;
	gen(&min_cost);
	
	auto xx = exchange_host_list(&min_cost);
	auto yy = Max_Flow_Min_Cost(xx);
	//c.erase(remove(c.begin(), c.end(), 1963), c.end());
	std::cout << yy.back()[0] << endl;
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