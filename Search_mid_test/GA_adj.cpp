#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "variable_declaration.h"

int C = consumeNode_nums;
int V = 20;
int N = 50;
const int GA_times = 20;
int apt[GA_times];
int apt_2[GA_times];
int min_idx;
const int range_const = 1;
//int min_cost;
std::vector<netNode_index> min_host, node_sort, node_sort_notdir;
std::vector<std::vector<netNode_index>> host_location(GA_times);
std::vector<std::vector<netNode_index>> host_location_list(GA_times);
std::vector<float> netNode_p, some_netNode_p;

//generate 20 
int gen(float *min_cost) {
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
			if (out_degree_per_point_tmp[j] > max) {
				max_index = j;
				max = out_degree_per_point_tmp[j];
			}
		}
		out_degree_per_point_tmp[max_index] = 0;
		some_out_degree += out_degree_per_point[max_index];
		node_sort.push_back(max_index);
	}

	//将除直连消费节点外节点排序
	for (int i = 0; i < netNode_nums; i++)
	{
		if (!G[node_sort[i]]) {
			node_sort_notdir.push_back(i);
		}
	}

	for (int i = 0; i < netNode_nums / range_const; i++)
	{
		some_netNode_p.push_back(float(out_degree_per_point[node_sort[i]]) / some_out_degree);
	}

	std::vector<int>::iterator biggest = std::max_element(
		std::begin(out_degree_per_point), std::end(out_degree_per_point));
	std::vector<int>::iterator minnest = std::min_element(
		std::begin(out_degree_per_point), std::end(out_degree_per_point));
	//int max_pos = std::distance(std::begin(out_degree_per_point), biggest);
	int min_host_num = max_bandwidth_require / *biggest + 1;

	srand((unsigned)time(NULL));


	//for (int i = 0; i < GA_times/* - 1*/; i++)
	//{
	//	// 随机生成n个服务器
	//	int n = rand_gen_int(min_host_num, consumeNode_nums - 1);//random numbers in (0,C-1)
	//												  //std::cout <<n<<std::endl;
	//	std::vector<netNode_index> Q(netNode_nums, 0);


	//	//轮盘赌获得n个服务器的位置
	//	while (n > 0) {
	//		float r = rand_gen_float();
	//		int m = RWS(r);
	//		//int m = rand_gen_int(0, netNode_nums - 1);
	//		if (!Q[m]) {
	//			Q[m] = 1;
	//			host_location[i].push_back(m);
	//			n--;
	//		}
	//	}
	//	auto x = Max_Flow_Min_Cost(host_location[i]);
	//	//std::cout << x.back()[0] << std::endl;
	//	apt[i] = x.back()[0];

	//}

	/*for (int i = 0; i < GA_times-1; i++)
	{
		for (int j = 0; j < netNode_nums/GA_times; j++)
		{
			host_location[i].push_back(node_sort[i + j*GA_times]);
		}
		auto x = Max_Flow_Min_Cost(host_location[i]);
		apt[i] = x.back()[0];
	}*/
	for (int i = 0; i < GA_times - 1; i++)
	{
		for (int j = 0; j < (netNode_nums - consumeNode_nums) / GA_times; j++)
		{
			host_location[i].push_back(node_sort_notdir[i + j*GA_times]);

		}
		//		auto x = Max_Flow_Min_Cost(host_location[i], bestcnn);
		//apt[i] = x.back()[0];
		apt[i] = INF;
	}

	for (int i = 0; i < consumeNode_nums; i++)
	{
		host_location[GA_times - 1].push_back(consumeNodeList[i]);
		
	}
	apt[GA_times - 1] = 2.5*serverCost*consumeNode_nums;
	int min_apt_tmp = INF;
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

float cross_p = 0.6;
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

std::vector<netNode_index> exchange_host_list(float *min_cost)
{

	srand((unsigned)time(NULL));
	std::vector<std::vector<netNode_index>> gen_matrix(GA_times,
		std::vector<netNode_index>(netNode_nums, 0));
	int min_cost_tmp = *min_cost;
	int max_gen_times = 100;
	int time_limt = 0;
	int gen_tmp_times = 0;
	int tmp_cost = 0;
	clock_t start, finish;
	
	for (int gen_times = 0; gen_times < max_gen_times; gen_times++)
	{
		//std::cout << gen_times << std::endl;
		gen_tmp_times++;
		
		start = clock();
		if (min_cost_tmp == *min_cost && gen_tmp_times > 5)
		{
			cross_p = 0.8;
			mutation_p += 0.001;
			tmp_cost = *min_cost;
			if (mutation_p > 0.2)
			{
				mutation_p = 0.2;
			}
		}
		if (min_cost_tmp>*min_cost)
		{
			cross_p = 0.8;
			mutation_p = 0.001;
			gen_tmp_times = 0;
			min_cost_tmp = *min_cost;
			//min_cost_tmp = *min_cost;
		}
		std::cout << gen_times << " " << cross_p << " " << mutation_p << std::endl;
		//mutation_p = mutation_p + (gen_times / max_gen_times)*0.2;
		// 随机选择两个个体比较
		//for (int i = 0; i < GA_times; i++)
		//{
		//	host_location_list[i].clear();
		//	for (int k = 0; k < host_location[i].size(); k++)
		//	{
		//		host_location_list[i].push_back(host_location[i][k]);
		//	}
		//}

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
		for (int i = 0; i < GA_times; i++)
		{
			for (int j = 0; j < host_location_list[i].size(); j++)
			{
				gen_matrix[i][host_location_list[i][j]] = 1;
			}
		}

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
				int n3 = rand_gen_int(0, netNode_nums - 1);
				for (int j = n3; j <netNode_nums; j++)
				{

					gen_matrix[n1][j] = gen_matrix[n2][j];

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

			for (int j = 0; j < netNode_nums; j++)
			{
				float mutation_rate = rand_gen_float();

				if (mutation_rate < mutation_p)
				{
					//std::cout << mutation_rate << std::endl;
					gen_matrix[n1][j] = 1 - gen_matrix[n1][j];
				}
			}
		}


		int min_apt_var = INF;
		int max_apt_var = 0;
		/*std::vector<netNode_index> min_host_list;
		std::vector<netNode_index> max_host_list;*/
		int min_host_index;
		int max_host_index;
		//int xxx;
		for (int i = 0; i < GA_times; i++)
		{
			host_location[i].clear();
			for (int j = 0; j < netNode_nums; j++)
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
					int m = rand_gen_int(0, netNode_nums - 1);
					if (!Q[m]) {
						Q[m] = 1;
						host_location[i].push_back(m);
						n--;
					}
				}
				auto apt_ = Max_Flow_Min_Cost(host_location[i]);
				apt[i] = apt_.back()[0];
			}

			else
			{
				auto apt_ = Max_Flow_Min_Cost(host_location[i]);
				apt[i] = apt_.back()[0];
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
		time_limt += (finish - start);
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
	Max_Flow_Min_Cost(min_host);
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
	std::vector<int> out_degree_per_point, out_degree_per_point_tmp;
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
		out_degree_per_point.push_back(_tmp_out_degree);
		out_degree_per_point_tmp.push_back(_tmp_out_degree);
	}
	std::vector<int>::iterator biggest = std::max_element(
		std::begin(out_degree_per_point), std::end(out_degree_per_point));
	std::vector<int>::iterator minnest = std::min_element(
		std::begin(out_degree_per_point), std::end(out_degree_per_point));
	//int max_pos = std::distance(std::begin(out_degree_per_point), biggest);
	int min_host_num = max_bandwidth_require / *biggest + 1;

	std::default_random_engine generator(time(NULL));
	std::uniform_int_distribution<int> dis_n(min_host_num, consumeNode_nums - 1);
	std::uniform_int_distribution<int> dis_m(0, netNode_nums - 1);
	std::vector<netNode_index> host_list;

	int _low_cost = serverCost*consumeNode_nums;
	std::vector<netNode_index> _low_host;

	// 随机生成n个服务器
	for (int rand_time = 0; rand_time < 10000; rand_time++)
	{
		std::vector<netNode_index> Q(netNode_nums, 0);
		int n = dis_n(generator);// dis_n(generator);//random numbers in (0,C-1)
		while (n > 0) {
			// 在m号网络节点处设立服务器
			int m = dis_m(generator); //random location in (0,V)

			if (!Q[m]) {
				Q[m] = 1;
				host_list.push_back(m);
				n--;
			}
		}
		auto x = Max_Flow_Min_Cost(host_list);
		if (x.back()[0] < _low_cost)
		{
			_low_cost = x.back()[0];
			_low_host.clear();
			_low_host = host_list;
		}
		else {
			continue;
		}
		host_list.clear();
	}
	std::cout << std::endl;
	std::cout << _low_cost << std::endl;
}