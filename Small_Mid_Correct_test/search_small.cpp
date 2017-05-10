//#include "variable_declaration.h"
//
//
//
//std::vector<int> throw_up;
//std::vector<std::vector<int>> search_small()
//{
//	std::vector<netNode_index> min_host, node_sort, node_not_sort, node_sort_dir, node_sort_notdir, consume_node_sort, consume_node_other;
//
//	std::vector<float> netNode_p, some_netNode_p;
//	const int range_const = 1;
//	int max_bandwidth_require = 0;
//	for (int i = 0; i < consumeNode_nums; i++)
//	{
//		max_bandwidth_require += requireBandWidth[i];
//	}
//	int max_consume_req = 0;
//	for (int i = 0; i < netNode_nums; i++)
//	{
//		if (requireBandWidth[i] > max_consume_req && requireBandWidth[i] != INF)
//		{
//			max_consume_req = requireBandWidth[i];
//		}
//	}
//	std::vector<netNode_index> G(netNode_nums, 0);
//	for (int i = 0; i < consumeNode_nums; i++)
//	{
//		G[consumeNodeList[i]] = 1;
//	}
//	std::vector<int> out_degree_per_point, out_degree_per_point_tmp;
//	std::vector<float> out_degree_avg, out_degree_avg_tmp;
//	int total_out_degree = 0;
//	for (int i = 0; i < netNode_nums; i++)
//	{
//		int _tmp_out_degree = 0;
//		for (int j = 0; j < netNode_nums; j++)
//		{
//			if (i != j)
//			{
//				_tmp_out_degree += netNode_MGraph_BandWidth[i][j];
//			}
//		}
//		total_out_degree += _tmp_out_degree;
//		out_degree_per_point.push_back(_tmp_out_degree);
//		out_degree_avg.push_back(_tmp_out_degree / float(Graph_Adj[i].size()));
//	}
//	out_degree_per_point_tmp = out_degree_per_point;
//	out_degree_avg_tmp = out_degree_avg;
//	//对节点进行负载大小排序
//	int some_out_degree = 0;
//	int count = consumeNode_nums / 2;
//	std::vector<int>  node_sort_avg_consume;
//	for (int i = 0; i < netNode_nums; i++)
//	{
//		node_not_sort.push_back(i);
//		int max = 0, max_avg = 0;
//		int max_index = -1, max_avg_idx = -1;
//		for (int j = 0; j < netNode_nums; j++) {
//			//出度排序
//			if (out_degree_per_point_tmp[j] > max) {
//				max_index = j;
//				max = out_degree_per_point_tmp[j];
//			}
//			//平均出度排序
//			/*if (out_degree_avg_tmp[j] > max_avg) {
//			max_avg_idx = j;
//			max_avg = out_degree_per_point_tmp[j];
//			}*/
//		}
//		out_degree_per_point_tmp[max_index] = 0;
//		some_out_degree += out_degree_per_point[max_index];
//		node_sort.push_back(max_index);
//		//out_degree_per_point_tmp[max_avg_idx] = 0;
//		//node_sort_avg.push_back(max_avg_idx);
//		if (!count&&G[max_index])
//		{
//			consume_node_other.push_back(max_index);
//		}
//
//		if (count&&G[max_index])
//		{
//			consume_node_sort.push_back(max_index);
//			count--;
//		}
//		/*if (G[max_avg_idx])
//		{
//		node_sort_avg_consume.push_back(max_avg_idx);
//		}*/
//	}
//
//	//将除直连消费节点外节点排序
//	for (int i = 0; i < netNode_nums / range_const; i++)
//	{
//		if (!G[node_sort[i]]) {
//			node_sort_notdir.push_back(i);
//		}
//		if (G[node_sort[i]]) {
//			node_sort_dir.push_back(i);
//		}
//	}
//	int min = INF;
//
//	std::vector<int> result;
//	std::vector<int> collection;
//	/*for (int i = 0; i < consumeNode_nums; i++)
//	{
//	node_sort_notdir.push_back(consumeNodeList[i]);
//	}*/
//	collection.clear();
//	/*for (int i = 0; i < netNode_nums/2; i++)
//	{
//	collection.push_back(i);
//	}*/
//
//	collection = node_not_sort;
//	//collection = { 173,6,195,25,226,271,30,272,62,293,32,225,163,216,114,115,51,103,104,239,52,289,97,14,125,105,233,220,240,129,53,4,59,89,73,202,230,35,121,29,83,142,252,198,88,135,128,259,174,208,282,86,219,39,299,171,87,234,235,26,27,75,211,80,72,229,150,119,267,20,117,122,85,13,203,7,24,31,108,54,172,270,107,192,45,165,294,116,21,106,288,246,276,210,280,281,227,147,149,82,265,169,78,250,65,61,199,76,295,144,296,249,159,162,139,213,256,156,201,148,60,124,16,152,145,221,222,189,190,254,245,286,118,28,48,8,100,155,160,161,126,166,176,98,19,10,214,110,99,209 };
//	int size_j = collection.size();
//	int size_i = size_j - 1;
//	int count_exc = node_sort.size() / 9;
//	std::vector<int> collection_tmp, sub_collection_tmp;// = collection;
//
//	for (int i = 0; i < 290; i++)
//	{
//		//std::vector<int> r(netNode_nums);
//		//Cij_search(size_j, size_i, r, size_i, collection, &min, collection_tmp);
//		while (count_exc)
//		{
//			int m = rand_gen_int(0, size_j);
//			int n = rand_gen_int(0, size_j);
//			while (m == n) {
//				n = rand_gen_int(0, size_j);
//			}
//			int tmp = collection[m];
//			collection[m] = collection[n];
//			collection[n] = tmp;
//			count_exc--;
//		}
//		//std::vector<int> cccc;
//		//Cij_search_loop_big_rand(size_j, size_i, collection, &min, collection_tmp, cccc);
//		//Cij_search_loop(size_j, size_i, collection, &min, collection_tmp);
//		//Cij_search_loop_big(size_j, size_i, collection, &min, collection_tmp, consume_node_sort);
//		collection.clear();
//		collection = collection_tmp;
//		size_j = collection.size();
//		size_i = size_j - 1;
//		std::cout << min << std::endl;
//	}
//	int sub_min = INF;
//
//	//for small graph
//	Cij_search_loop_double(size_j, size_i, collection, &min, &sub_min, collection_tmp, sub_collection_tmp);
//	size_j = collection_tmp.size();
//	size_i = size_j - 1;
//	int min_1 = INF, sub_min_1 = INF, min_2 = INF, sub_min_2 = INF;
//	std::vector<int> collection_tmp_1, collection_tmp_2;
//	std::vector<int> sub_collection_tmp_1, sub_collection_tmp_2;
//	//for (int i = 0; i < 100; i++)
//	//{
//	//	Cij_search_loop_double(size_j, size_i, collection_tmp, &min_1, &sub_min_1, collection_tmp_1, sub_collection_tmp_1);
//	//	Cij_search_loop_double(size_j, size_i, sub_collection_tmp, &min_2, &sub_min_2, collection_tmp_2, sub_collection_tmp_2);
//	//	collection_tmp.clear();
//	//	sub_collection_tmp.clear();
//
//	//	/*if (min_1<min_2)
//	//	{
//	//		min = min_1;
//	//		collection_tmp = collection_tmp_1;
//	//		if (sub_min_1<min_2)
//	//		{
//	//			sub_collection_tmp = sub_collection_tmp_1;
//	//		}
//	//		else {
//	//			sub_collection_tmp = collection_tmp_2;
//	//		}
//	//	}
//	//	else {
//	//		min = min_2;
//	//		collection_tmp = collection_tmp_2;
//	//		if (sub_min_2<min_1)
//	//		{
//	//			sub_collection_tmp = sub_collection_tmp_2;
//	//		}
//	//		else {
//	//			sub_collection_tmp = collection_tmp_1;
//	//		}
//	//	}*/
//	//	collection_tmp = collection_tmp_1;
//	//	sub_collection_tmp = collection_tmp_2;
//	//	if (min_1<min_2)
//	//	{
//	//		min = min_1;
//	//	}
//	//	else
//	//	{
//	//		min = min_2;
//	//	}
//	//	size_j = collection_tmp.size();
//	//	size_i = size_j - 1;
//	//	std::cout << min << std::endl;
//	//}
//	std::ofstream SaveFile;
//	SaveFile.open("Host2.txt");
//	for (auto &h : collection)
//	{
//		std::cout << h << " ";
//		SaveFile << h << ",";
//	}
//	SaveFile << '\n';
//	std::cout << std::endl;
//	std::cout << collection.size() << " " << std::endl;
//	for (auto &h : consume_node_sort)
//	{
//		std::cout << h << " ";
//		SaveFile << h << ",";
//	}
//	SaveFile << '\n';
//	std::cout << std::endl;
//	std::cout << consume_node_sort.size() << " " << std::endl;
//	SaveFile.close();
//	////Cij_search(netNode_nums, netNode_nums -5, r, netNode_nums - 1, result, &min, collection_tmp);
//	////std::vector<int> r(3);
//	////std::vector<std::vector<int>> result;
//	////Cij(5, 3 ,r, 3, result);
//	//std::cout << std::endl;
//}
//
////void Cij_search(int i, int j, std::vector<int> &r, int num, std::vector<int> & result, int *min, std::vector<int> &netnodes)
////{
////
////	if (j == 1)
////	{
////		for (int k = 0; k < i; k++)
////		{
////			std::vector<int> temp(num);
////			r[num - 1] = k;
////			for (int i = 0; i < num; i++)
////			{
////				temp[i] = r[i];
////				//cout << r[i] << ' ';  
////			}
////			/*	result.push_back(temp);
////			cout << endl; */
////			int _size = temp.size();
////			std::vector<int> host;
////			for (auto &c : temp)
////				host.push_back(result[c]);
////			auto host_tmp = host;
////			clock_t start, finish;
////			start = clock();
////			auto x = Max_Flow_Min_Cost(host);
////			finish = clock();
////			//std::cout << (finish - start) << "ms" << std::endl;
////			//if (_size==temp.size())
////			//{
////			/*std::cout << x.back()[0] << std::endl;*/
////			if (x.back()[0]<*min)
////			{
////				*min = x.back()[0];
////				netnodes.clear();
////				netnodes = host_tmp;
////			}
////			//std::cout << *min << std::endl;
////			//}
////		}
////	}
////	else if (j == 0)
////	{
////		//do nothing!  
////	}
////	else
////	{
////		for (int k = i; k >= j; k--)
////		{
////			r[j - 2] = k - 1;
////			Cij_search(k - 1, j - 1, r, num, result, min, netnodes);
////		}
////	}
////}
//
//void Cij_search_loop_big_rand(int size_i, int size_j, std::vector<int> & result, int *min, std::vector<int> &netnodes, std::vector<int> &first_half_consume)
//{
//	//std::vector<int> tmp = result;
//	std::vector<bool> vis(size_i, false);
//	srand((unsigned)time(NULL));
//	int n1, n2;
//	int len = size_i;
//	std::vector<int> host;
//	for (int i = 0; i < len; i++)
//	{
//		n1 = rand_gen_int(0, size_i - 1);
//		auto tmp = result;
//		/*while (n1==i && vis[n1])
//		{
//		n1 = rand_gen_int(0, size_i - 1);
//		}*/
//		n2 = rand_gen_int(0, size_i - 1);
//		/*while (n2 == i && vis[n1] && n2 == n1)
//		{
//		n2 = rand_gen_int(0, size_i - 1);
//		}*/
//		tmp[i] = -1;
//		tmp[n1] = -1;
//		//tmp[n2] = -1;
//		vis[i] = true;
//		vis[n1] = true;
//		//vis[n2] = true;
//		host.clear();
//		for (int j = 0; j < size_i; j++)
//		{
//			if (tmp[j] != -1)
//			{
//				host.push_back(result[j]);
//			}
//
//		}
//		auto host_tmp = host;
//		for (auto &c : first_half_consume)
//			host.push_back(c);
//		auto x = Max_Flow_Min_Cost(host);
//		//auto x = DFS_MCMF(host);
//		if (x.back()[0]<*min && x.back()[0] != INF)
//		{
//			*min = x.back()[0];
//			netnodes.clear();
//			netnodes = host_tmp;
//		}
//	}
//}
//
//void Cij_search_loop(int size_i, int size_j, std::vector<int> & result, int *min, std::vector<int> &netnodes)
//{
//	std::vector<int> tmp;
//	for (int i = 0; i < size_j; i++)
//	{
//		tmp.clear();
//		for (int j = 0; j< size_j; j++)
//		{
//			tmp.push_back((i + j) % size_i);
//		}
//		int _size = tmp.size();
//		std::vector<int> host;
//		for (auto &c : tmp)
//			host.push_back(result[c]);
//		auto host_tmp = host;
//		clock_t start, finish;
//		start = clock();
//		auto x = Max_Flow_Min_Cost(host);
//		finish = clock();
//		if (x.back()[0]<*min)
//		{
//			throw_up.push_back((i - 1 + size_i) % size_i);
//			*min = x.back()[0];
//			netnodes.clear();
//			netnodes = host_tmp;
//		}
//		//std::cout << std::endl;
//	}
//}
//
//void Cij_search_loop_double(int size_i, int size_j, std::vector<int> & result, int *min, int *sub_min, std::vector<int> &netnodes, std::vector<int> &sub_netnodes)
//{
//	std::vector<int> tmp;
//	for (int i = 0; i < size_j; i++)
//	{
//		tmp.clear();
//		for (int j = 0; j< size_j; j++)
//		{
//			tmp.push_back((i + j) % size_i);
//		}
//		int _size = tmp.size();
//		std::vector<int> host;
//		for (auto &c : tmp)
//			host.push_back(result[c]);
//		auto host_tmp = host;
//		clock_t start, finish;
//		start = clock();
//		auto x = Max_Flow_Min_Cost(host);
//		finish = clock();
//		if (x.back()[0]<*min)
//		{
//			*sub_min = *min;
//			sub_netnodes.clear();
//			sub_netnodes = netnodes;
//			*min = x.back()[0];
//			netnodes.clear();
//			netnodes = host_tmp;
//		}
//		//std::cout << std::endl;
//	}
//}
//
//void Cij_search_loop_big(int size_i, int size_j, std::vector<int> & result, int *min, std::vector<int> &netnodes, std::vector<int> &first_half_consume)
//{
//	std::vector<int> tmp;
//	for (int i = 0; i < size_j; i++)
//	{
//		tmp.clear();
//		for (int j = 0; j< size_j; j++)
//		{
//			tmp.push_back((i + j) % size_i);
//		}
//		int _size = tmp.size();
//		std::vector<int> host;
//		for (auto &c : tmp)
//			host.push_back(result[c]);
//		auto host_tmp = host;
//		for (auto &c : first_half_consume)
//			host.push_back(c);
//
//		//clock_t start, finish;
//		//start = clock();
//		//auto x = Max_Flow_Min_Cost(host);
//		auto x = DFS_MCMF(host);
//		//std::cout << x.back()[0]<<std::endl;
//		//finish = clock();
//		if (x.back()[0]<*min)
//		{
//			*min = x.back()[0];
//			netnodes.clear();
//			netnodes = host_tmp;
//		}
//
//	}
//}
//
//
//std::vector<netNode_index> find_location() {
//	std::vector<netNode_index> location;
//	int Q[NET_NODE_MAXSIZE];
//	memset(Q, 0, sizeof(Q));
//	bool vis[NET_NODE_MAXSIZE];
//	int stack[NET_NODE_MAXSIZE];
//	for (size_t i = 0; i < consumeNode_nums; i++)
//	{
//		memset(vis, false, sizeof(vis));
//
//		int top = 0;
//		int bottom = -1;
//
//		int dir = consumeNodeList[i];
//
//		stack[top] = dir;
//
//		/*for (int j = 0; j < Graph_Adj[dir].size(); j++)
//		{
//		stack[top++] = Graph_Adj[dir][j];
//		vis[Graph_Adj[dir][j]] = true;
//		}*/
//		//top--;
//		while (top != bottom)
//		{
//			int out = stack[top];
//			top--;
//			if (!Q[out]) {
//				Q[out] = 1;
//				location.push_back(out);
//			}
//			if (!vis[out])
//			{
//				vis[out] = true;
//				int min = INF;
//				for (int k = 0; k < Graph_Adj[out].size(); k++)
//				{
//					if (!vis[Graph_Adj[out][k]] && (min>netNode_MGraph_RentCost[out][Graph_Adj[out][k]]))
//					{
//						min = netNode_MGraph_RentCost[out][Graph_Adj[out][k]];
//					}
//				}
//				for (int k = 0; k < Graph_Adj[out].size(); k++)
//				{
//					if (min == netNode_MGraph_RentCost[out][Graph_Adj[out][k]])
//					{
//						stack[++top] = Graph_Adj[out][k];
//					}
//				}
//
//			}
//		}
//	}
//	return location;
//}