#include "variable_declaration.h"



void search()
{
	std::vector<netNode_index> min_host, node_sort, node_sort_notdir;

	std::vector<float> netNode_p, some_netNode_p;
	const int range_const = 2;
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
;
	}
	out_degree_per_point_tmp = out_degree_per_point;
	//�Խڵ���и��ش�С����
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

	//����ֱ�����ѽڵ���ڵ�����
	//for (int i = 0; i < netNode_nums; i++)
	//{
	//	if (!G[node_sort[i]]) {
	//		node_sort_notdir.push_back(i);
	//	}
	//}
	int min = INF;
	std::vector<int> r(netNode_nums - 1);
	std::vector<int> result;
	std::vector<int> collection;
	for (int i = 0; i < netNode_nums; i++)
	{
		collection.push_back(i);
	}
	
	int size_j = netNode_nums;
	int size_i = size_j - 1;
	std::vector<int> collection_tmp;
	
	for (int i = 0; i < 200; i++)
	{
		Cij_search(size_j, size_i, r, size_i, collection, &min, collection_tmp);
		collection.clear();
		collection = collection_tmp;
		size_j = collection.size();
		size_i = size_j - 1;
		std::cout << netNode_nums - i << " " << min << std::endl;
	}
	std::ofstream SaveFile;
	SaveFile.open("Host1.txt");
	for (auto &h : collection)
	{
		std::cout << h << " ";
		SaveFile << h << ",";
	}
	SaveFile.close();
	//Cij_search(netNode_nums, netNode_nums -5, r, netNode_nums - 1, result, &min, collection_tmp);
	//std::vector<int> r(3);
	//std::vector<std::vector<int>> result;
	//Cij(5, 3 ,r, 3, result);
	std::cout << std::endl;
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
			clock_t start, finish;
			start = clock();
			auto x = Max_Flow_Min_Cost(host);
			finish = clock();
			std::cout << (finish - start) << "ms" << std::endl;
			//if (_size==temp.size())
			//{
				/*std::cout << x.back()[0] << std::endl;*/
				if (x.back()[0]<*min)
				{
					*min = x.back()[0];
					netnodes.clear();
					netnodes = host;
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