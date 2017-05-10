#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "variable_declaration.h"

int C = consumeNode_nums;
int V = 20;
const int GA_times = 20;
float apt[GA_times];
int apt_2[GA_times];
int min_idx;
const int range_const = 1;
//int min_cost;
std::vector<netNode_index> min_host, node_sort,node_sort_notdir;

std::vector<std::vector<netNode_index>> host_location(GA_times);
std::vector<std::vector<netNode_index>> host_location_list(GA_times);
std::vector<float> netNode_p, some_netNode_p;
std::vector<netNode_index> select_coll;

std::vector<netNode_index> N;
std::vector<std::vector<netNode_index>> gen_matrix(GA_times);

//generate 20 
int gen(float *min_cost, std::vector<std::vector<netNode_index>> &bestcnn) {
	int max_bandwidth_require = 0;
	for (int i = 0; i < consumeNode_nums; i++)
	{
		max_bandwidth_require += requireBandWidth[i];
	}
	int max_consume_req = 0;
	for (int i = 0; i < netNode_nums; i++)
	{
		if (requireBandWidth[i] > max_consume_req && requireBandWidth[i] != INF)
		{
			max_consume_req = requireBandWidth[i];
		}
	}
	std::vector<netNode_index> G(netNode_nums, 0);
	for (int i = 0; i < consumeNode_nums; i++)
	{
		G[consumeNodeList[i]] = 1;
	}
	std::vector<int> out_degree_per_point, out_degree_per_point_tmp;

	int total_out_degree = 0;
	for (int i = 0; i < netNode_nums; i++)
	{
		int _tmp_out_degree = 0;
		for (int j = 0; j < netNode_nums; j++)
		{
			if (i != j)
			{
				_tmp_out_degree += netNode_MGraph_BandWidth[i][j];
			}
		}
		total_out_degree += _tmp_out_degree;
		out_degree_per_point.push_back(_tmp_out_degree);
		out_degree_per_point_tmp.push_back(_tmp_out_degree);
	}
	for (int i = 0; i < netNode_nums; i++)
	{
		netNode_p.push_back(float(out_degree_per_point[i]) / total_out_degree);
	}
	//对节点进行负载大小排序
	int some_out_degree = 0;
	for (int i = 0; i < netNode_nums / range_const; i++)
	{
		int max = 0;
		int max_index = -1;
		for (int j = 0; j < netNode_nums; j++) {
			if (out_degree_per_point_tmp[j] > max ) {
				max_index = j;
				max = out_degree_per_point_tmp[j];
			}
		}
		out_degree_per_point_tmp[max_index] = 0;
		some_out_degree += out_degree_per_point[max_index];
		node_sort.push_back(max_index);
	}

	for (int i = 0; i < netNode_nums; i++)
	{
		if (!G[node_sort[i]]) {
			node_sort_notdir.push_back(i);
		}
	}
	
	for (int i = 0; i < netNode_nums / range_const; i++)
	{
{
			some_netNode_p.push_back(float(out_degree_per_point[node_sort[i]]) / some_out_degree);
		}
	}

	std::vector<netNode_index> element = {
		467,525,273,371,605,17,299,100,725,424,539,507,351,654,655,234,79,631,42,52,149,168,316,90,638,415,192,72,73,529,395,361,699,755,756,56,474,244,245,308,328,18,702,623,743,557,309,576,659,253,254,158,429,45,95,645,548,81,82,562,545,176,125,365,199,386,84,85,188,38,599,224,128,402,78,172,105,271,69,586,688,715,716,632,119,153,154,504,577,578,778,174,409,410,726,226,350,355,509,263,214,215,691,210,658,23,534,416,157,423,662,483,677,150,104,222,575,288,358,620,461,427,721,700,701,61,197,160,580,704,70,460,532,763,484,433,766,558,559,675,653,454,516,747,439,94,389,144,106,436,714,660,587,405,406,272,30,83,311,470,368,617,496,497,624,628,629,500,135,761,762,55,383,80,455,456,779,163,109,180,466,388,502,256,787,462,527,732,611,186,585,217,630,579,431,419,318,606,796,568,179,798,503,239,673,589,248,379,212,476,123,124,58,87,760,237,324,486,221,718,259,298,471,327,650,143,54,387,310,57,65,767,22,413,795,353,286,296,289,267,268,93,651,759,39,40,59,522,181,399,418,218,274,396,564,233,397,556,784,77,63,131,744,260,27,31,138,336,608,609,615,738,739,322,549,391,99,459,67,508,475,707,566,567,50,772,533,314,665,329,91,434,519,520,713,211,614,505,728,187,276,537,53,531,664,354,769,198,550,280,464,643,709,285,789,319,741,663,485,323,407,641,75,68,794,362,363,265,301,178,710,711,161,330,400,213,536,404,166,333,468,469,243,477,610,618,619,421,132,495,241,780,479,547,356,141,142,490,162,535,600,515,251,232,432,270,425,603,451,240,62,510,195,378,209,458,506,364,194,563,48,300,494,692,102,220,332,266,501,247,730,41,758,523,648,649,621,719,720,453,666,422
	};


	std::vector<int>::iterator biggest = std::max_element(
		std::begin(out_degree_per_point), std::end(out_degree_per_point));
	std::vector<int>::iterator minnest = std::min_element(
		std::begin(out_degree_per_point), std::end(out_degree_per_point));
	//int max_pos = std::distance(std::begin(out_degree_per_point), biggest);
	int min_host_num = max_bandwidth_require / *biggest + 1;
	//std::vector<int> r(min_host_num);
	//std::vector<std::vector<int>> result;
	//Cij(min_host_num, min_host_num, r, min_host_num, result);
	srand((unsigned)time(NULL));

	for (int i = 0; i < GA_times; i++) {
		for (int j = 0; j < netNode_nums/* - consumeNode_nums*/; j++)
		{
			gen_matrix[i].push_back(0);
		}
	}

	//std::vector<netNode_index> G(netNode_nums, 0);

	//for (int i = 0; i < consumeNode_nums; i++)
	//{
	//	G[consumeNodeList[i]] = 1;
	//}
	for (int i = 0; i < netNode_nums; i++)
	{
		if (!G[i]) {
			N.push_back(i);
			//std::cout << i << std::endl;
		}
	}

	

	//int t = 0;
	//for (int i = 0; i < GA_times/* - 1*/; i++)
	//{
	//	// 随机生成n个服务器
	//	int n = rand_gen_int(min_host_num, consumeNode_nums - 1);//random numbers in (0,C-1)
	//												  //std::cout <<n<<std::endl;
	//	std::vector<netNode_index> Q(netNode_nums, 0);


	//	//轮盘赌获得n个服务器的位置
	//	while (n > 0) {
	//		//float r = rand_gen_float();
	//		//int m = RWS(r);
	//		int m = rand_gen_int(0, netNode_nums - consumeNode_nums - 1);
	//		//int m = rand_gen_int(0, element.size() - 1);
	//		//m = element[m];

	//		if (!Q[m]) {
	//			gen_matrix[i][m] = 1;
	//			Q[m] = 1;
	//			host_location[i].push_back(N[m]);
	//			n--;
	//		}
	//	}
	//	auto x = Max_Flow_Min_Cost(host_location[i], bestcnn);
	//	//std::cout << x.back()[0] << std::endl;
	//	if (x.back()[0] != INF)
	//	{
	//		apt[i] = x.back()[0];
	//		std::cout << t << std::endl;
	//		t++;
	//	}
	//	else
	//	{
	//		host_location[i].clear();
	//		i--;
	//	}
	//	

	//}

	for (int i = 0; i < GA_times-1; i++)
	{
		for (int j = 0; j < (netNode_nums-consumeNode_nums)/GA_times; j++)
		{
			host_location[i].push_back(node_sort_notdir[i + j*GA_times]);
			gen_matrix[i][node_sort_notdir[i + j*GA_times]] = 1;
		}
//		auto x = Max_Flow_Min_Cost(host_location[i], bestcnn);
		//apt[i] = x.back()[0];
		apt[i] = INF;
	}

	
	for (int i = 0; i < consumeNode_nums; i++)
	{
		host_location[GA_times - 1].push_back(consumeNodeList[i]);
		gen_matrix[GA_times - 1][consumeNodeList[i]] = 1;
	}
	apt[GA_times - 1] = serverCost*consumeNode_nums;
	float min_apt_tmp = INF;
	for (int i = 0; i < GA_times; i++)
	{
		if (apt[i]</*<*/min_apt_tmp)
		{
			min_apt_tmp = apt[i];
			min_idx = i;
		}
	}

	min_host = host_location[min_idx];


	*min_cost = min_apt_tmp;
	std::cout << *min_cost << std::endl;
	return 1;
}

float cross_p = 0.8;
float mutation_p = 0.01;
//轮盘赌算法
int RWS(float r)
{
	float m = 0;
	int i = 0;
	for (; i <netNode_nums / range_const; i++)
	{
		m = m + some_netNode_p[i];
		if (r <= m) return i;
	}
	return i - 1;
}

std::vector<netNode_index> exchange_host_list(float *min_cost, std::vector<std::vector<netNode_index>> &bestcnn)
{

	srand((unsigned)time(NULL));
/*	vestd::ctor<std::vector<netNode_index>> gen_matrix(GA_times,
		std::vector<netNode_index>(netNode_nums, 0))*/;
	float min_cost_tmp = *min_cost;
	int max_gen_times = 1000;
	int time_limt = 0;
	int gen_tmp_times = 0;
	int tmp_cost = 0;
	clock_t start, finish;
	std::vector<std::vector<netNode_index >> host_col;
	
	auto t_begin = print_time();
	auto t_end = t_begin;
	
	for (int gen_times = 0; gen_times < max_gen_times; gen_times++)
	{
		//std::cout << gen_times << std::endl;
		gen_tmp_times++;
		//if (*min_cost<1)
		//{
		//	host_col.push_back(min_host);
		//}
		
		start = clock();
		if (min_cost_tmp == *min_cost && gen_tmp_times > 5)
		{
			//cross_p -= 0.01;
			mutation_p += 0.01;
			if (mutation_p > 0.1)
			{
				mutation_p = 0.1;
			}
			/*if (cross_p<0.5)
			{
				cross_p = 0.5;
			}*/
			tmp_cost = *min_cost;
		}
		if (min_cost_tmp>*min_cost)
		{
			cross_p = 0.8;
			mutation_p = 0.01;
			gen_tmp_times = 0;
			min_cost_tmp = *min_cost;
			//min_cost_tmp = *min_cost;
		}
		//std::cout << gen_times << " " << cross_p << " " << mutation_p << std::endl;
		//mutation_p = mutation_p + (gen_times / max_gen_times)*0.2;
		// 随机选择两个个体比较
		/*for (int i = 0; i < GA_times; i++)
		{
			host_location_list[i].clear();
			for (int k = 0; k < host_location[i].size(); k++)
			{
				host_location_list[i].push_back(host_location[i][k]);
			}
		}*/

			for (int i = 0; i < GA_times; i++)
			{
				
				//int n1 = rand_gen_int(0, GA_times);;
				int n1 = rand_gen_int(0, GA_times - 1);
				while (n1 == min_idx)
				{
					n1 = rand_gen_int(0, GA_times - 1);
				}
				int n2 = rand_gen_int(0, GA_times - 1);
				while (n2 == n1 || n2 == min_idx)
				{
					n2 = rand_gen_int(0, GA_times - 1);
				}

				//host_location_list[i] = (apt[n2] < apt[n1]) ? host_location[n2] : host_location[n1];
				if (apt[n2]<apt[n1])
				{
					for (int k = 0; k < host_location[n2].size(); k++)
					{
						host_location_list[i].push_back(host_location[n2][k]);
					}
				}
				else
				{
					for (int k = 0; k < host_location[n1].size(); k++)
					{
						host_location_list[i].push_back(host_location[n1][k]);
					}
				}
			}



		// 将比较结果放入矩阵


		// 交叉
		for (int i = 0; i < GA_times; i++)
		{
			//float cross_rate = float(dis_2(generator)) / 100000;
			float cross_rate = rand_gen_float();
			//std::cout << cross_rate << std::endl;
			if (cross_rate < cross_p)
			{
				int n1 = rand_gen_int(0, GA_times - 1);
				while (n1 == min_idx)
				{
					n1 = rand_gen_int(0, GA_times - 1);
				}
	
				//int n2 = min_idx;
				int n2 = rand_gen_int(0, GA_times - 1);
				while (n2 == n1 || n2 == min_idx)
				{
					n2 = rand_gen_int(0, GA_times - 1);
				}
				int n3 = rand_gen_int(0, netNode_nums  - 1);
				for (int j = n3; j <netNode_nums ; j++)
				{
					int tmp = gen_matrix[n1][j];
					gen_matrix[n1][j] = gen_matrix[n2][j];
					gen_matrix[n2][j]=tmp;
				}
			}
		}
		// 变异20次
		for (int i = 0; i < GA_times; i++)
		{
			int n1 = rand_gen_int(0, GA_times - 1);
			while (n1 == min_idx)
			{
				n1 = rand_gen_int(0, GA_times - 1);;
			}

			for (int j = 0; j < netNode_nums ; j++)
			{
				float mutation_rate = rand_gen_float();

				if (mutation_rate < mutation_p)
				{
					//std::cout << mutation_rate << std::endl;
					gen_matrix[n1][j] = 1 - gen_matrix[n1][j];
				}
			}
		}


		float min_apt_var = INF;
		float max_apt_var = 0;
		/*std::vector<netNode_index> min_host_list;
		std::vector<netNode_index> max_host_list;*/
		int min_host_index;
		int max_host_index;
		//std::vector<std::vector<std::vector<netNode_index>>> apt_tmp;
		//int xxx;
		for (int i = 0; i < GA_times; i++)
		{
			//apt_tmp.clear();
			host_location[i].clear();
			for (int j = 0; j < netNode_nums ; j++)
			{
				if (gen_matrix[i][j] == 1)
				{
					host_location[i].push_back(j);
				}
			}

			if (host_location[i].size()>consumeNode_nums)
			{
				//apt[i] = serverCost*consumeNode_nums;
				host_location[i].clear();
				/*for (int l = 0; l < consumeNode_nums; l++)
				{
				host_location[i].push_back(consumeNodeList[l]);
				}*/
				//apt[i] = INF+1;
				int n = rand_gen_int(1, consumeNode_nums - 1);//random numbers in (0,C-1)
															  //std::cout <<n<<std::endl;
				std::vector<netNode_index> Q(netNode_nums, 0);

				while (n > 0) {
					//float r = rand_gen_float();
					//int m = RWS(r);
					int m = rand_gen_int(0, netNode_nums  - 1);
					//int m = rand_gen_int(0, element.size() - 1);
					//m = element[m];

					if (!Q[m]) {
						gen_matrix[i][m] = 1;
						Q[m] = 1;
						host_location[i].push_back(m);
						n--;
					}
				}
		
				auto apt_ = Max_Flow_Min_Cost(host_location[i], bestcnn);
				apt[i] = apt_.back()[0];
			}

			else
			{
				auto apt_ = Max_Flow_Min_Cost(host_location[i], bestcnn);
				apt[i] = apt_.back()[0];
				//apt_tmp.push_back(apt_);
			}

			if (apt[i]<min_apt_var)
			{
				min_apt_var = apt[i];
				min_host_index = i;
			}
			if (apt[i] > max_apt_var)
			{
				max_apt_var = apt[i];
				max_host_index = i;
			}
		}
		if (*min_cost < max_apt_var)
		{
			host_location[max_host_index].clear();
			for (int k = 0; k < min_host.size(); k++)
			{
				host_location[max_host_index].push_back(min_host[k]);
			}
		}

		if (*min_cost>min_apt_var)
		{
			*min_cost = min_apt_var;
			min_host.clear();
			for (int k = 0; k < host_location[min_host_index].size(); k++)
			{
				min_host.push_back(host_location[min_host_index][k]);
			}
		}
		std::cout << *min_cost << " " << min_apt_var << std::endl;
		min_idx = min_host_index;
		finish = clock();
		//time_limt += (finish - start);
		auto t_tmp = print_time();
		t_end += t_tmp;
		//std::cout << t_end - t_begin << std::endl;
		if (t_end - t_begin > 25)
			break;
		/*if (time_limt>85000)
		{
			break;
		}*/
	}
	std::ofstream SaveFile;
	SaveFile.open("Host.txt");
	for (auto &h : min_host)
	{
		std::cout << h << " ";
		SaveFile << h << ",";
	}
	SaveFile.close();
	std::cout << std::endl;
	std::ofstream SaveFile2;
	SaveFile2.open("Consu.txt");
	for (size_t i = 0; i < consumeNode_nums; i++)
	{
		std::cout << consumeNodeList[i] << " ";
		SaveFile2 << consumeNodeList[i] << " ";
	}
	SaveFile2.close();
	std::cout << std::endl;
	Max_Flow_Min_Cost(min_host, bestcnn);
	ANS:return min_host;
}
//产生x-y的随机数，包括x和y
int rand_gen_int(int x, int y) {
	int k = rand() % (y - x + 1) + x;
	return k;
}
float rand_gen_float() {
	float k = rand() / 32767.0;
	return k;
}
void random_alg()
{
	//int max_bandwidth_require = 0;
	//for (int i = 0; i < consumeNode_nums; i++)
	//{
	//	max_bandwidth_require += requireBandWidth[i];
	//}
	//int max_consume_req = 0;
	//for (int i = 0; i < netNode_nums; i++)
	//{
	//	if (requireBandWidth[i] > max_consume_req && requireBandWidth[i] != INF)
	//	{
	//		max_consume_req = requireBandWidth[i];
	//	}
	//}
	//std::vector<int> out_degree_per_point, out_degree_per_point_tmp;
	//for (int i = 0; i < netNode_nums; i++)
	//{
	//	int _tmp_out_degree = 0;
	//	for (int j = 0; j < netNode_nums; j++)
	//	{
	//		if (i != j)
	//		{
	//			_tmp_out_degree += netNode_MGraph_BandWidth[i][j];
	//		}
	//	}
	//	out_degree_per_point.push_back(_tmp_out_degree);
	//	out_degree_per_point_tmp.push_back(_tmp_out_degree);
	//}
	//std::vector<int>::iterator biggest = std::max_element(
	//	std::begin(out_degree_per_point), std::end(out_degree_per_point));
	//std::vector<int>::iterator minnest = std::min_element(
	//	std::begin(out_degree_per_point), std::end(out_degree_per_point));
	////int max_pos = std::distance(std::begin(out_degree_per_point), biggest);
	//int min_host_num = max_bandwidth_require / *biggest + 1;

	//std::default_random_engine generator(time(NULL));
	//std::uniform_int_distribution<int> dis_n(min_host_num, consumeNode_nums - 1);
	//std::uniform_int_distribution<int> dis_m(0, netNode_nums - 1);
	//std::vector<netNode_index> host_list;

	//int _low_cost = serverCost*consumeNode_nums;
	//std::vector<netNode_index> _low_host;

	//// 随机生成n个服务器
	//for (int rand_time = 0; rand_time < 10000; rand_time++)
	//{
	//	std::vector<netNode_index> Q(netNode_nums, 0);
	//	int n = dis_n(generator);// dis_n(generator);//random numbers in (0,C-1)
	//	while (n > 0) {
	//		// 在m号网络节点处设立服务器
	//		int m = dis_m(generator); //random location in (0,V)

	//		if (!Q[m]) {
	//			Q[m] = 1;
	//			host_list.push_back(m);
	//			n--;
	//		}
	//	}
	//	auto x = Max_Flow_Min_Cost(host_list);
	//	if (x.back()[0] < _low_cost)
	//	{
	//		_low_cost = x.back()[0];
	//		_low_host.clear();
	//		_low_host = host_list;
	//	}
	//	else {
	//		continue;
	//	}
	//	host_list.clear();
	//}
	//std::cout << std::endl;
	//std::cout << _low_cost << std::endl;
}