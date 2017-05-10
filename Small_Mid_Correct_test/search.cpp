#include "variable_declaration.h"



std::vector<std::vector<netNode_index>> search()
{
	std::vector<netNode_index> min_host, node_sort, node_sort_notdir, consume_node_sort, consume_node_other;

	std::vector<float> netNode_p, some_netNode_p;
	std::vector<int> not_sort_net_nodes;
	const int range_const = 20;
	int max_bandwidth_require = 0;
	const int alg_choice = 800;
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
		not_sort_net_nodes.push_back(i);
	}
	std::vector<netNode_index> G(netNode_nums, 0);
	for (int i = 0; i < consumeNode_nums; i++)
	{
		G[consumeNodeList[i]] = 1;
	}
	std::vector<int> out_degree_per_point, out_degree_per_point_tmp;
	std::vector<float> out_degree_avg, out_degree_avg_tmp;
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
		out_degree_avg.push_back(float(_tmp_out_degree) / float(Graph_Adj[i].size()));
		
	}
	std::vector<int> fixed_point;
	bool QQ[NET_NODE_MAXSIZE];
	memset(QQ,false,sizeof(QQ));
	for (int i = 0; i < consumeNode_nums; i++)
	{
		if (requireBandWidth[i]>out_degree_per_point[consumeNodeList[i]])
		{
			fixed_point.push_back(consumeNodeList[i]);
			QQ[consumeNodeList[i]] = true;
		}
	}
	out_degree_per_point_tmp = out_degree_per_point;
	//对节点进行负载大小排序
	int some_out_degree = 0;
	int count;
	if (netNode_nums>= alg_choice)
	{
		count = consumeNode_nums / 3 -50-fixed_point.size();
	} 
	else
	{
		count = consumeNode_nums;
	}
	out_degree_avg_tmp = out_degree_avg;
	for (int i = 0; i < netNode_nums; i++)
	{
		int max = 0, max_avg = 0;
		int max_index = -1, max_avg_idx = -1;
		for (int j = 0; j < netNode_nums; j++) {
			if (out_degree_per_point_tmp[j] > max) {
				max_index = j;
				max = out_degree_per_point_tmp[j];
			}
			//平均出度排序
			if (out_degree_avg_tmp[j] > max) {
				max_avg_idx = j;
				max_avg = out_degree_per_point_tmp[j];
			}

		}
		out_degree_per_point_tmp[max_index] = 0;
		some_out_degree += out_degree_per_point[max_index];
		node_sort.push_back(max_index);
		if (!QQ[max_index]&&!count&&G[max_index])
		{
				consume_node_other.push_back(max_index);
		}

		if (!QQ[max_index] && count&&G[max_index])
		{
			consume_node_sort.push_back(max_index);
			count--;
		}

	}

	//将除直连消费节点外节点排序
	for (int i = 0; i < netNode_nums / range_const; i++)
	{
		if (!G[node_sort[i]]) {
			node_sort_notdir.push_back(i);
		}
	}
	int min = INF;

	std::vector<int> result;
	std::vector<int> collection;
	for (int i = 0; i < consumeNode_nums; i++)
	{
		node_sort_notdir.push_back(consumeNodeList[i]);
	}

	collection.clear();
	//collection = { 176,109,31,213,155,161,160,272,60,293,232,15,182,170,187,117,178,296,249,41,42,299,173,135,205,271,226,286,180,142,251,48,199,79,98,275,87,270,158,250,186,93,146,217,218,207,75,108,175,157,162,163,284,174,204,99,59,78,38,144,91,130,131,280,248,229,26,27,102,279,264,28,44,292,139,82,152,113,77,179,145,106,12,242,85,230,95,246,285,65,147,148,238,16,192,69,172,68,241,103,92,36,110,25,240,136,216,239,56,19,154,287,134,196,90,111,198,140,23,214,167,53,32,225,227,7,88,133,129,13,253,291,112,105,236,195,10,283,39,118,141,210,89,20,181,29,171,96,165,83,153,137,252,194,8 };
	//collection = { 467, 525, 273, 371, 605, 17, 299, 100, 725, 424, 539, 507, 351, 654, 655, 234, 79, 631, 42, 52, 149, 168, 316, 90, 638, 415, 192, 72, 73, 529, 395, 361, 699, 755, 756, 56, 474, 244, 245, 308, 328, 18, 702, 623, 743, 557, 309, 576, 659, 253, 254, 158, 429, 45, 95, 645, 548, 81, 82, 562, 545, 176, 125, 365, 199, 386, 84, 85, 188, 38, 599, 224, 128, 402, 78, 172, 105, 271, 69, 586, 688, 715, 716, 632, 119, 153, 154, 504, 577, 578, 778, 174, 409, 410, 726, 226, 350, 355, 509, 263, 214, 215, 691, 210, 658, 23, 534, 416, 157, 423, 662, 483, 677, 150, 104, 222, 575, 288, 358, 620, 461, 427, 721, 700, 701, 61, 197, 160, 580, 704, 70, 460, 532, 763, 484, 433, 766, 558, 559, 675, 653, 454, 516, 747, 439, 94, 389, 144, 106, 436, 714, 660, 587, 405, 406, 272, 30, 83, 311, 470, 368, 617, 496, 497, 624, 628, 629, 500, 135, 761, 762, 55, 383, 80, 455, 456, 779, 163, 109, 180, 466, 388, 502, 256, 787, 462, 527, 732, 611, 186, 585, 217, 630, 579, 431, 419, 318, 606, 796, 568, 179, 798, 503, 239, 673, 589, 248, 379, 212, 476, 123, 124, 58, 87, 760, 237, 324, 486, 221, 718, 259, 298, 471, 327, 650, 143, 54, 387, 310, 57, 65, 767, 22, 413, 795, 353, 286, 296, 289, 267, 268, 93, 651, 759, 39, 40, 59, 522, 181, 399, 418, 218, 274, 396, 564, 233, 397, 556, 784, 77, 63, 131, 744, 260, 27, 31, 138, 336, 608, 609, 615, 738, 739, 322, 549, 391, 99, 459, 67, 508, 475, 707, 566, 567, 50, 772, 533, 314, 665, 329, 91, 434, 519, 520, 713, 211, 614, 505, 728, 187, 276, 537, 53, 531, 664, 354, 769, 198, 550, 280, 464, 643, 709, 285, 789, 319, 741, 663, 485, 323, 407, 641, 75, 68, 794, 362, 363, 265, 301, 178, 710, 711, 161, 330, 400, 213, 536, 404, 166, 333, 468, 469, 243, 477, 610, 618, 619, 421, 132, 495, 241, 780, 479, 547, 356, 141, 142, 490, 162, 535, 600, 515, 251, 232, 432, 270, 425, 603, 451, 240, 62, 510, 195, 378, 209, 458, 506, 364, 194, 563, 48, 300, 494, 692, 102, 220, 332, 266, 501, 247, 730, 41, 758, 523, 648, 649, 621, 719, 720, 453, 666, 422 };
	if (netNode_nums>= alg_choice)
	{
		for (int i = 0; i < 60/*consume_node_other.size()*/; i++)
		{
			collection.push_back(consume_node_other[i]);
		}
		//collection = consume_node_other;
	}
	if(netNode_nums==300)
	{
		collection = consume_node_sort;
	}
	if (netNode_nums <= 161)
	{
		collection = not_sort_net_nodes;
	}
	
	int size_j = collection.size();
	int size_i = size_j - 1;
	std::vector<int> collection_tmp;// = collection;
	auto t_begin = print_time();
	auto t_end = t_begin;
	int val_tmp = INF;
	int equ_times = 0;
	int loop_times = netNode_nums - consumeNode_nums + 40;
	const int STEP = 10;
	std::vector<std::vector<int>> _ret_path;
	std::vector<netNode_index> _ret_host;
	if (netNode_nums>=alg_choice)
	{
		Cij_search_loop_big_host_loc(size_j, size_i, collection, &min, collection_tmp, consume_node_sort, _ret_path, _ret_host, fixed_point);
		//std::sort(collection.begin(), collection.end());
		//collection.erase(unique(collection.begin(), collection.end()), collection.end());
		size_j = collection.size();
		//std::cout << size_j << std::endl;
		size_i = size_j - 1;
	}
	
	for (int i = 0; i < 300; i++)
	{
		//std::vector<int> r(netNode_nums);
		
		//Cij_search(size_j, size_i, r, size_i, collection, &min, collection_tmp);
		if (netNode_nums>= alg_choice)
		{
			//if (min>295000)
			//{
			//	Cij_search_loop_big_sun(size_j, size_i, collection, &min, collection_tmp, consume_node_sort, _ret_path, _ret_host, fixed_point);
			//}
			//else if(min>250000 && min<295000)
			//{
			//	Cij_search_loop_big_rand(size_j, size_i, collection, &min, collection_tmp, consume_node_sort);
			//}
			//else
			//if (i<10)
			//{
				//Cij_search_loop_big_rand(size_j, size_i, collection, &min, collection_tmp, consume_node_sort, _ret_path);
			//}
			//else
			//{
			//if (i<10)
			//{
			//   Cij_search_loop_big_sun(size_j, size_i, collection, &min, collection_tmp, consume_node_sort, _ret_path, _ret_host, fixed_point);
			//}
			//else
			//{
				Cij_search_loop_big(size_j, size_i, collection, &min, collection_tmp, consume_node_sort, _ret_path, _ret_host, fixed_point);
			//}
			//}
							
			
			
		}
		if (netNode_nums <= 161)
		{
			//Cij_search_loop(size_j, size_i, collection, &min, collection_tmp, _ret_path);
			Cij_search_loop_big(size_j, size_i, collection, &min, collection_tmp, consume_node_sort, _ret_path, _ret_host, fixed_point);
		}
		
		
		collection.clear();
		collection = collection_tmp;
		std::ofstream SaveFile;
		SaveFile.open("Host2.txt");
		for (auto &h : _ret_host)
		{
			//std::cout << h << " ";
			SaveFile << h << ",";
		}
		
		SaveFile.close();
		size_j = collection.size();
		size_i = size_j - 1;
		std::cout << i << " " << min << " " << equ_times << " " << collection.size() << " " << consume_node_sort.size() << std::endl;

		// 定时器
		auto t_tmp = print_time();
		t_end += t_tmp;
		if (t_end - t_begin > 850)
			break;
		if (val_tmp == min)
		{
			equ_times++;
		}
		if (val_tmp==min && equ_times>=3)
		{
			//std::cout << i << " " << collection.size() << " " << consume_node_sort.size() << std::endl;
			for (int j = 0; j < STEP; j++)
			{
				collection.push_back(consume_node_sort[consume_node_sort.size()-1-j]);
				
				consume_node_sort.pop_back();
				
				//std::cout<< equ_times << " " << collection.size() << " " << consume_node_sort.size() << std::endl;
			}
			size_j += STEP;
			size_i = size_j - 1;
			//break;
			equ_times = 0;
		}
		else
		{
			val_tmp = min;
		}
		if (consume_node_sort.size() <= STEP*2)
		{
			break;
		}
	}
	auto _ret = Max_Flow_Min_Cost(_ret_host);
	std::cout << _ret.back()[0] << std::endl;
	return _ret;
}

void Cij_search(int i, int j, std::vector<int> &r, int num, std::vector<int> & result, int *min, std::vector<int> &netnodes)
{
	
	if (j == 1)
	{
		for (int k = 0; k < i; k++)
		{
			std::vector<int> temp(num);
			r[num - 1] = k;
			for (int i = 0; i < num; i++)
			{
				temp[i] = r[i];
				//cout << r[i] << ' ';  
			}
			/*	result.push_back(temp);
			cout << endl; */
			int _size = temp.size();
			std::vector<int> host;
			for (auto &c : temp)
				host.push_back(result[c]);
			auto host_tmp = host;
			clock_t start, finish;
			start = clock();
			auto x = Max_Flow_Min_Cost(host);
			finish = clock();
			//std::cout << (finish - start) << "ms" << std::endl;
			//if (_size==temp.size())
			//{
			/*std::cout << x.back()[0] << std::endl;*/
			if (x.back()[0]<*min)
			{
				*min = x.back()[0];
				netnodes.clear();
				netnodes = host_tmp;
			}
			//std::cout << *min << std::endl;
			//}
		}
	}
	else if (j == 0)
	{
		//do nothing!  
	}
	else
	{
		for (int k = i; k >= j; k--)
		{
			r[j - 2] = k - 1;
			Cij_search(k - 1, j - 1, r, num, result, min, netnodes);
		}
	}
}

void Cij_search_loop(int size_i, int size_j, std::vector<int> & result, int *min, std::vector<int> &netnodes, std::vector<std::vector<int>> &ret_path)
{
	std::vector<int> tmp;
	// std::vector<std::vector<netNode_index>> _ans;
	for (int i = 0; i < size_j; i++)
	{
		
		tmp.clear();
		for (int j = 0; j< size_j;j++)
		{
			tmp.push_back((i+j)% size_i);
		}
		int _size = tmp.size();
		std::vector<int> host;
		for (auto &c : tmp)
			host.push_back(result[c]);
		auto host_tmp = host;


		//auto x = Max_Flow_Min_Cost(host);
		auto x = zkw_mcmf(host);
		if (x/*.back()[0]*/<*min)
		{
			//_ans.clear();
			//_ans = x;
			*min = x/*.back()[0]*/;
			netnodes.clear();
			netnodes = host_tmp;
			//ret_path.clear();
			//ret_path = x;

		}
		//std::cout << std::endl;
	}
	// return _ans;
}

void Cij_search_loop_big(int size_i, int size_j, std::vector<int> & result, int *min, std::vector<int> &netnodes, std::vector<int> &first_half_consume, std::vector<std::vector<int>> &path, std::vector<int> & _host, std::vector<int> &static_point)
{
	std::vector<int> tmp;
	std::vector<int> host,host_tmp;
	for (int i = 0; i < size_j; i++)
	{
		tmp.clear();
		for (int j = 0; j< size_j; j++)
		{
			tmp.push_back((i + j) % size_i);
		}
		int _size = tmp.size();
		host.clear();
		for (auto &c : tmp)
			host.push_back(result[c]);
		host_tmp.clear();
		host_tmp = host;
		for (auto &c : first_half_consume)
			host.push_back(c);
		for (auto &c : static_point)
			host.push_back(c);

		clock_t start, finish;
		start = clock();
		//auto x = Max_Flow_Min_Cost(host);
		auto x = zkw_mcmf(host);
		/*auto link_cost = costflow();*/
		//auto x = DFS_MCMF(host);
		finish = clock();
		if (x/*.back()[0]*/<*min/* && x.back()[0]!=INF*/)
		{
			*min = x/*.back()[0]*/;
			netnodes.clear();
			netnodes = host_tmp;
			path.clear();
			//path = x;
			_host.clear();
			_host = host;
		}
		//std::cout << x.back()[0] << std::endl;
		
	}
}

void Cij_search_loop_big_host_loc(int size_i, int size_j, std::vector<int> & result, int *min, std::vector<int> &netnodes, std::vector<int> &first_half_consume, std::vector<std::vector<int>> &path, std::vector<int> & _host, std::vector<int> &static_point)
{
	std::vector<int> tmp;
	std::vector<int> host, host_tmp;
	std::vector<int> tmp_loc;
	for (int i = 0; i < size_j; i++)
	{
		tmp.clear();
		for (int j = 0; j< size_j; j++)
		{
			tmp.push_back((i + j) % size_i);
		}
		int _size = tmp.size();
		host.clear();
		for (auto &c : tmp)
			host.push_back(result[c]);
		host_tmp.clear();
		host_tmp = host;
		for (auto &c : first_half_consume)
			host.push_back(c);
		for (auto &c : static_point)
			host.push_back(c);

		clock_t start, finish;
		start = clock();
		auto org_size = host.size();
		//std::cout << org_size << " ";
		auto x = Max_Flow_Min_Cost(host);
		auto after_size = host.size();
		
		if (org_size<after_size)
		{
			tmp_loc.clear();
			//std::cout << org_size << " " << after_size << std::endl;
			for (int i = 0; i < after_size-org_size+1; i++)
			{
				tmp_loc.push_back(host[after_size - i - 1]);
			}
		}
		//auto x = DFS_MCMF(host);
		finish = clock();
		if (x.back()[0]<*min && x.back()[0] != INF)
		{
			*min = x.back()[0];
			netnodes.clear();
			netnodes = host_tmp;
			path.clear();
			path = x;
			_host.clear();
			_host = host;
		}

	}
	if (tmp_loc.size()>0)
	{
		for (auto &c: tmp_loc)
		{
			result.push_back(c);
		}
		
	}
}

void Cij_search_loop_big_rand(int size_i, int size_j, std::vector<int> & result, int *min, std::vector<int> &netnodes, std::vector<int> &first_half_consume, std::vector<std::vector<int>> &ret_path)
{
	//std::vector<int> tmp = result;
	std::vector<bool> vis(size_i, false);
	srand((unsigned)time(NULL));
	int n1, n2,n3;
	int len = size_i;
	std::vector<int> host;
	for (int i = 0; i < len; i++)
	{
		n1 = rand_gen_int(0, size_i - 1);
		auto tmp = result;
		/*while (n1==i && vis[n1])
		{
			n1 = rand_gen_int(0, size_i - 1);
		}*/
		n2= rand_gen_int(0, size_i - 1);
		/*while (n2 == i && vis[n1] && n2 == n1)
		{
			n2 = rand_gen_int(0, size_i - 1);
		}*/
		n3 = rand_gen_int(0, size_i - 1);
		tmp[i] = -1;
		tmp[n1] = -1;
		tmp[n2] = -1;
		//tmp[n3] = -1;
		vis[i] = true;
		vis[n1] = true;
		vis[n2] = true;
		//vis[n3] = true;
		host.clear();
		for (int j = 0; j < size_i; j++)
		{
			if (tmp[j]!=-1)
			{
				host.push_back(result[j]);
			}
			
		}
		auto host_tmp = host;
		for (auto &c : first_half_consume)
			host.push_back(c);
		auto x = Max_Flow_Min_Cost(host);
		//auto x = DFS_MCMF(host);
		if (x.back()[0]<*min && x.back()[0] != INF)
		{
			*min = x.back()[0];
			netnodes.clear();
			netnodes = host_tmp;
			ret_path.clear();
			ret_path = x;
		}
	}
}

void Cij_search_loop_big_sun(int size_i, int size_j, std::vector<int> & result, int *min, std::vector<int> &netnodes, std::vector<int> &first_half_consume, std::vector<std::vector<int>> &path, std::vector<int> & _host, std::vector<int> &static_point)
{
	//std::vector<int> tmp = result;
	std::vector<int> tmp;
	std::vector<int> host, host_tmp;
	for (int i = 0; i < size_j; i++)
	{
		tmp.clear();
		for (int j = 0; j< size_j; j++)
		{
			tmp.push_back((i + j) % size_i);
		}
		int _size = tmp.size();
		host.clear();
		for (auto &c : tmp)
			host.push_back(result[c]);
		host_tmp.clear();
		host_tmp = host;
		for (auto &c : first_half_consume)
			host.push_back(c);
		for (auto &c : static_point)
			host.push_back(c);

		clock_t start, finish;
		start = clock();
		//auto x = Max_Flow_Min_Cost(host);
		auto x = DFS_MCMF(host);
		finish = clock();
		if (x.back()[0]<*min && x.back()[0] != INF)
		{
			*min = x.back()[0];
			netnodes.clear();
			netnodes = host_tmp;
			path.clear();
			path = x;
			_host.clear();
			_host = host;
		}
		//std::cout << x.back()[0] << std::endl;
		if (x.back()[0] == INF)
		{
			//std::cout << std::endl;
		}
	}
}

///////////////////////////////////////

//#include "variable_declaration.h"
//
//
//
//
//
//
//
//std::vector<std::vector<netNode_index>> search()
//
//{
//
//	std::vector<netNode_index> min_host, node_sort, node_sort_notdir, consume_node_sort, consume_node_other;
//
//
//
//	std::vector<float> netNode_p, some_netNode_p;
//
//	const int range_const = 20;
//
//	int max_bandwidth_require = 0;
//
//	const int alg_choice = 800;
//
//	for (int i = 0; i < consumeNode_nums; i++)
//
//	{
//
//		max_bandwidth_require += requireBandWidth[i];
//
//	}
//
//	int max_consume_req = 0;
//
//	for (int i = 0; i < netNode_nums; i++)
//
//	{
//
//		if (requireBandWidth[i] > max_consume_req && requireBandWidth[i] != INF)
//
//		{
//
//			max_consume_req = requireBandWidth[i];
//
//		}
//
//	}
//
//	std::vector<netNode_index> G(netNode_nums, 0);
//
//	for (int i = 0; i < consumeNode_nums; i++)
//
//	{
//
//		G[consumeNodeList[i]] = 1;
//
//	}
//
//	std::vector<int> out_degree_per_point, out_degree_per_point_tmp;
//
//	int total_out_degree = 0;
//
//	for (int i = 0; i < netNode_nums; i++)
//
//	{
//
//		int _tmp_out_degree = 0;
//
//		for (int j = 0; j < netNode_nums; j++)
//
//		{
//
//			if (i != j)
//
//			{
//
//				_tmp_out_degree += netNode_MGraph_BandWidth[i][j];
//
//			}
//
//		}
//
//		total_out_degree += _tmp_out_degree;
//
//		out_degree_per_point.push_back(_tmp_out_degree);
//
//
//
//	}
//
//	std::vector<int> fixed_point;
//
//	bool QQ[NET_NODE_MAXSIZE];
//
//	memset(QQ, false, sizeof(QQ));
//	//for(int i=0; i<netNode_nums;i++)
//	//QQ[i]=false;
//
//	for (int i = 0; i < consumeNode_nums; i++)
//
//	{
//
//		if (requireBandWidth[i]>out_degree_per_point[consumeNodeList[i]])
//
//		{
//
//			fixed_point.push_back(consumeNodeList[i]);
//
//			QQ[consumeNodeList[i]] = true;
//
//		}
//
//	}
//
//
//
//	out_degree_per_point_tmp = out_degree_per_point;
//
//	//¶ÔœÚµãœøÐÐžºÔØŽóÐ¡ÅÅÐò
//
//	int some_out_degree = 0;
//
//	int count;
//
//	if (netNode_nums >= alg_choice)
//
//	{
//
//		count = consumeNode_nums / 3 + 40 - fixed_point.size();
//
//	}
//
//	else
//
//	{
//
//		count = consumeNode_nums;
//
//	}
//
//	for (int i = 0; i < netNode_nums; i++)
//
//	{
//
//		int max = 0;
//
//		int max_index = -1;
//
//		for (int j = 0; j < netNode_nums; j++) {
//
//			if (out_degree_per_point_tmp[j] > max) {
//
//				max_index = j;
//
//				max = out_degree_per_point_tmp[j];
//
//			}
//
//		}
//
//		out_degree_per_point_tmp[max_index] = 0;
//
//		some_out_degree += out_degree_per_point[max_index];
//
//		node_sort.push_back(max_index);
//
//		if (!QQ[max_index] && !count&&G[max_index])
//
//		{
//
//			consume_node_other.push_back(max_index);
//
//		}
//
//
//
//		if (!QQ[max_index] && count&&G[max_index])
//
//		{
//
//			consume_node_sort.push_back(max_index);
//
//			count--;
//
//		}
//
//
//
//	}
//
//
//
//	//œ«³ýÖ±Á¬Ïû·ÑœÚµãÍâœÚµãÅÅÐò
//
//	for (int i = 0; i < netNode_nums / range_const; i++)
//
//	{
//
//		if (!G[node_sort[i]]) {
//
//			node_sort_notdir.push_back(i);
//
//		}
//
//	}
//
//	int min = INF;
//
//
//
//	std::vector<int> result;
//
//	std::vector<int> collection;
//
//	for (int i = 0; i < consumeNode_nums; i++)
//
//	{
//
//		node_sort_notdir.push_back(consumeNodeList[i]);
//
//	}
//
//
//
//	collection.clear();
//
//	//collection = { 176,109,31,213,155,161,160,272,60,293,232,15,182,170,187,117,178,296,249,41,42,299,173,135,205,271,226,286,180,142,251,48,199,79,98,275,87,270,158,250,186,93,146,217,218,207,75,108,175,157,162,163,284,174,204,99,59,78,38,144,91,130,131,280,248,229,26,27,102,279,264,28,44,292,139,82,152,113,77,179,145,106,12,242,85,230,95,246,285,65,147,148,238,16,192,69,172,68,241,103,92,36,110,25,240,136,216,239,56,19,154,287,134,196,90,111,198,140,23,214,167,53,32,225,227,7,88,133,129,13,253,291,112,105,236,195,10,283,39,118,141,210,89,20,181,29,171,96,165,83,153,137,252,194,8 };
//
//	//collection = { 467, 525, 273, 371, 605, 17, 299, 100, 725, 424, 539, 507, 351, 654, 655, 234, 79, 631, 42, 52, 149, 168, 316, 90, 638, 415, 192, 72, 73, 529, 395, 361, 699, 755, 756, 56, 474, 244, 245, 308, 328, 18, 702, 623, 743, 557, 309, 576, 659, 253, 254, 158, 429, 45, 95, 645, 548, 81, 82, 562, 545, 176, 125, 365, 199, 386, 84, 85, 188, 38, 599, 224, 128, 402, 78, 172, 105, 271, 69, 586, 688, 715, 716, 632, 119, 153, 154, 504, 577, 578, 778, 174, 409, 410, 726, 226, 350, 355, 509, 263, 214, 215, 691, 210, 658, 23, 534, 416, 157, 423, 662, 483, 677, 150, 104, 222, 575, 288, 358, 620, 461, 427, 721, 700, 701, 61, 197, 160, 580, 704, 70, 460, 532, 763, 484, 433, 766, 558, 559, 675, 653, 454, 516, 747, 439, 94, 389, 144, 106, 436, 714, 660, 587, 405, 406, 272, 30, 83, 311, 470, 368, 617, 496, 497, 624, 628, 629, 500, 135, 761, 762, 55, 383, 80, 455, 456, 779, 163, 109, 180, 466, 388, 502, 256, 787, 462, 527, 732, 611, 186, 585, 217, 630, 579, 431, 419, 318, 606, 796, 568, 179, 798, 503, 239, 673, 589, 248, 379, 212, 476, 123, 124, 58, 87, 760, 237, 324, 486, 221, 718, 259, 298, 471, 327, 650, 143, 54, 387, 310, 57, 65, 767, 22, 413, 795, 353, 286, 296, 289, 267, 268, 93, 651, 759, 39, 40, 59, 522, 181, 399, 418, 218, 274, 396, 564, 233, 397, 556, 784, 77, 63, 131, 744, 260, 27, 31, 138, 336, 608, 609, 615, 738, 739, 322, 549, 391, 99, 459, 67, 508, 475, 707, 566, 567, 50, 772, 533, 314, 665, 329, 91, 434, 519, 520, 713, 211, 614, 505, 728, 187, 276, 537, 53, 531, 664, 354, 769, 198, 550, 280, 464, 643, 709, 285, 789, 319, 741, 663, 485, 323, 407, 641, 75, 68, 794, 362, 363, 265, 301, 178, 710, 711, 161, 330, 400, 213, 536, 404, 166, 333, 468, 469, 243, 477, 610, 618, 619, 421, 132, 495, 241, 780, 479, 547, 356, 141, 142, 490, 162, 535, 600, 515, 251, 232, 432, 270, 425, 603, 451, 240, 62, 510, 195, 378, 209, 458, 506, 364, 194, 563, 48, 300, 494, 692, 102, 220, 332, 266, 501, 247, 730, 41, 758, 523, 648, 649, 621, 719, 720, 453, 666, 422 };
//
//	if (netNode_nums >= alg_choice)
//
//	{
//
//		for (int i = 0; i < 70/*consume_node_other.size()*/; i++)
//
//		{
//
//			collection.push_back(consume_node_other[i]);
//
//		}
//		for (int i = 0; i<10; i++)
//		{
//			collection.push_back(consume_node_other[consume_node_other.size() - i - 1]);
//		}
//
//		//collection = consume_node_other;
//
//	}
//
//	else
//
//	{
//
//		collection = consume_node_sort;
//
//	}
//
//
//
//	int size_j = collection.size();
//
//	int size_i = size_j - 1;
//
//	std::vector<int> collection_tmp;// = collection;
//
//	auto t_begin = print_time();
//
//	auto t_end = t_begin;
//
//	int val_tmp = INF;
//
//	int equ_times = 0;
//
//	int loop_times = netNode_nums - consumeNode_nums + 40;
//
//	std::vector<std::vector<int>> ret_path;
//	std::vector<int> ret_host;
//
//	for (int i = 0; i < 300; i++)
//
//	{
//
//		//std::vector<int> r(netNode_nums);
//
//
//
//		//Cij_search(size_j, size_i, r, size_i, collection, &min, collection_tmp);
//
//		if (netNode_nums >= alg_choice)
//
//		{
//
//			Cij_search_loop_big(size_j, size_i, collection, &min, collection_tmp, consume_node_sort, fixed_point, ret_path, ret_host);
//
//		}
//
//		else
//
//		{
//
//			Cij_search_loop(size_j, size_i, collection, &min, collection_tmp);
//
//		}
//
//
//
//
//
//		collection.clear();
//
//		collection = collection_tmp;
//
//		size_j = collection.size();
//
//		size_i = size_j - 1;
//
//		//std::cout << i << " " << min << std::endl;
//
//		// ¶šÊ±Æ÷
//
//		auto t_tmp = print_time();
//
//		t_end += t_tmp;
//		//if(fixed_point.size()>0)
//		//	break;
//
//		if (min == INF)
//
//			break;
//
//		if (t_end - t_begin > 85)
//
//			break;
//
//		if (val_tmp == min)
//
//		{
//
//			equ_times++;
//
//		}
//
//		if (val_tmp == min && equ_times>1)
//
//		{
//
//			break;
//
//		}
//
//		else
//
//		{
//
//			val_tmp = min;
//
//		}
//
//
//
//	}
//
//	//return ret_path;
//	auto _ret = Max_Flow_Min_Cost_big(collection);
//	return _ret;
//
//	//if (netNode_nums >= alg_choice)
//
//	//{
//
//	//	for (auto &c : consume_node_sort)
//
//	//		collection.push_back(c);
//
//	//	auto _ret = Max_Flow_Min_Cost(collection);
//
//	//	return _ret;
//
//	//}
//
//
//
//	//else
//
//	//{
//
//	//	auto _ret = Max_Flow_Min_Cost(collection);
//
//	//	return _ret;
//
//	//}
//
//}
//
//
//
//void Cij_search(int i, int j, std::vector<int> &r, int num, std::vector<int> & result, int *min, std::vector<int> &netnodes)
//
//{
//
//
//
//	if (j == 1)
//
//	{
//
//		for (int k = 0; k < i; k++)
//
//		{
//
//			std::vector<int> temp(num);
//
//			r[num - 1] = k;
//
//			for (int i = 0; i < num; i++)
//
//			{
//
//				temp[i] = r[i];
//
//				//cout << r[i] << ' ';  
//
//			}
//
//			/*	result.push_back(temp);
//
//			cout << endl; */
//
//			int _size = temp.size();
//
//			std::vector<int> host;
//
//			for (auto &c : temp)
//
//				host.push_back(result[c]);
//
//			auto host_tmp = host;
//
//			clock_t start, finish;
//
//			start = clock();
//
//			auto x = Max_Flow_Min_Cost(host);
//
//			finish = clock();
//
//			//std::cout << (finish - start) << "ms" << std::endl;
//
//			//if (_size==temp.size())
//
//			//{
//
//			/*std::cout << x.back()[0] << std::endl;*/
//
//			if (x.back()[0]<*min)
//
//			{
//
//				*min = x.back()[0];
//
//				netnodes.clear();
//
//				netnodes = host_tmp;
//
//			}
//
//			//std::cout << *min << std::endl;
//
//			//}
//
//		}
//
//	}
//
//	else if (j == 0)
//
//	{
//
//		//do nothing!  
//
//	}
//
//	else
//
//	{
//
//		for (int k = i; k >= j; k--)
//
//		{
//
//			r[j - 2] = k - 1;
//
//			Cij_search(k - 1, j - 1, r, num, result, min, netnodes);
//
//		}
//
//	}
//
//}
//
//
//
//void Cij_search_loop(int size_i, int size_j, std::vector<int> & result, int *min, std::vector<int> &netnodes)
//
//{
//
//	std::vector<int> tmp;
//
//	// std::vector<std::vector<netNode_index>> _ans;
//
//	for (int i = 0; i < size_j; i++)
//
//	{
//
//
//
//		tmp.clear();
//
//		for (int j = 0; j< size_j; j++)
//
//		{
//
//			tmp.push_back((i + j) % size_i);
//
//		}
//
//		int _size = tmp.size();
//
//		std::vector<int> host;
//
//		for (auto &c : tmp)
//
//			host.push_back(result[c]);
//
//		auto host_tmp = host;
//
//
//
//
//
//		auto x = Max_Flow_Min_Cost(host);
//
//
//
//		if (x.back()[0]<*min)
//
//		{
//
//			//_ans.clear();
//
//			//_ans = x;
//
//			*min = x.back()[0];
//
//			netnodes.clear();
//
//			netnodes = host_tmp;
//
//		}
//
//		//std::cout << std::endl;
//
//	}
//
//	// return _ans;
//
//}
//
//
//
//void Cij_search_loop_big(int size_i, int size_j, std::vector<int> & result, int *min, std::vector<int> &netnodes, std::vector<int> &first_half_consume, std::vector<int> &static_point, std::vector<std::vector<int>> &path, std::vector<int> &host_list)
//
//{
//
//	std::vector<int> tmp;
//
//	for (int i = 0; i < size_j; i++)
//
//	{
//
//		tmp.clear();
//
//		for (int j = 0; j< size_j; j++)
//
//		{
//
//			tmp.push_back((i + j) % size_i);
//
//		}
//
//		int _size = tmp.size();
//
//		std::vector<int> host;
//
//		for (auto &c : tmp)
//
//			host.push_back(result[c]);
//
//		auto host_tmp = host;
//
//		for (auto &c : first_half_consume)
//
//			host.push_back(c);
//
//		for (auto &c : static_point)
//
//			host.push_back(c);
//
//
//
//		//clock_t start, finish;
//
//		//start = clock();
//
//		auto x = Max_Flow_Min_Cost(host);
//
//		//finish = clock();
//
//		if (x.back()[0]<*min && x.back()[0] != INF)
//
//		{
//
//			*min = x.back()[0];
//
//			netnodes.clear();
//
//			netnodes = host_tmp;
//
//			path.clear();
//
//			path = x;
//			host_list.clear();
//			host_list = host;
//
//		}
//
//		//std::cout << std::endl;
//
//	}
//
//}

