#include "variable_declaration.h"

//std::vector<std::vector<int>> Dijkstra_original(netNode_index v0, netNode_index tag, consumeNode_index n,
//	netNode_index (*rc)[NET_NODE_MAXSIZE])
//{
//	int v, w, k, min;
//	
//	std::vector<int> final(netNode_nums, 0);
//	std::vector<int> D(netNode_nums, INF);
//	std::vector<int> P(netNode_nums, -1);
//	std::vector<int> _ret;
//	std::vector<std::vector<int>> _ans;
//	std::vector<int> _tmp_loc;
//
//	int pos = v0;
//	int noPath = -1;
//	int idx = 1;
//	
//	for (v = 0; v < netNode_nums; v++)
//	{
//		D[v] = rc[v0][v];
//	}
//	final[v0] = 1;
//	for (v = 1; v < netNode_nums; v++)
//	{
//		min = INF;
//		k = -1;
//		for (w = 0; w < netNode_nums; w++)
//		{
//			/*std::cout << v0 << "-->" << tag << "\t" << w << "\t " <<
//				D[w] << "\t" << min << "\t" << netNode_MGraph_BandWidth_Left[v0][w] << "\t " << requireBandWidth[n] << std::endl;*/
//
//			if (!final[w] && ((D[w]) < min )
//				&& (netNode_MGraph_BandWidth_Left[pos][w] >= requireBandWidth[n])
//				&& (w != noPath))
//			{
//				//std::cout << v0 << "-->" << tag << "\t" << w << "\t " <<
//				//	D[w]<<"\t"<<min<<"\t"<< netNode_MGraph_BandWidth_Left[v0][w] << "\t " << requireBandWidth[n] << std::endl;
//				k = w;
//				min = D[w];
//			}
//		}
//
//		if (k == -1 && pos == v0)
//		{
//			break;
//		}
//		if (k == -1)/*&& P[pos] != -1 && !final[tag])*/
//		{
//			///*int i = idx;
//			//noPath = pos;
//			//_tmp_loc.push_back(noPath);
//			//
//			//for (int i = 0; i < netNode_nums; i++)
//			//{
//			//	final[i] = 0;
//			//}
//			//while (i)
//			//{
//			//	final[v0] = 1;
//			//	final[_tmp_loc[_tmp_loc.size()-i--]] = 1;
//			//}
//			//pos = v0;
//			//idx++;
//			//v = netNode_nums - idx - 3;*/
//			continue;
//		}
//		//if (k == -1 )//&& final[tag])&& pos == -1)
//		//{
//		//	break;
//		//}
//		
//		final[k] = 1;
//		pos = k;
//
//		for (w = 0; w < netNode_nums; w++)
//		{
//			if (!final[w] && (min + rc[k][w]) < D[w]
//				&& (netNode_MGraph_BandWidth_Left[k][w] >= requireBandWidth[n]))
//				//&& (netNode_MGraph_BandWidth_Left[v0][w] >= requireBandWidth[n]))
//			{
//				if (P[k] == -1 && (netNode_MGraph_BandWidth_Left[v0][k] >= requireBandWidth[n]))
//				{
//					//std::cout << k << "\t" << w << "\t" << pos << "\t" << noPath << std::endl;
//					D[w] = min + rc[k][w];
//					P[w] = k;
//				}
//				if (P[k] != -1)
//				{
//					//std::cout << k << "\t" << w << "\t" << pos << "\t" << noPath << std::endl;
//					D[w] = min + rc[k][w];
//					P[w] = k;
//				}
//				
//			}
//		}
//		
//	}
//	
//	int _tmp_p = tag;
//	_ret.push_back(tag);
//	while (P[_tmp_p] != v && P[_tmp_p] != -1)
//	{
//		_ret.push_back(P[_tmp_p]);
//		_tmp_p = P[_tmp_p];
//	}
//	_ret.push_back(v0);
//	for (int i = 0; i < _ret.size()/2; i++)
//	{
//		_ret[i] = _ret[i] ^ _ret[_ret.size() - i - 1];
//		_ret[_ret.size() - i - 1] = _ret[_ret.size() - i - 1] ^ _ret[i];
//		_ret[i] = _ret[i] ^ _ret[_ret.size() - i - 1];
//	}
//	_ans.push_back(D);
//	_ans.push_back(_ret);
//	return _ans;
//}

std::vector<std::vector<int>> Dijkstra_original(netNode_index v0, netNode_index tag, consumeNode_index n,
	netNode_index(*rc)[NET_NODE_MAXSIZE])
{
	int v, w, k, min;

	std::vector<int> final(netNode_nums, 0);
	std::vector<int> D(netNode_nums, INF);
	std::vector<int> P(netNode_nums, -1);
	std::vector<int> _ret;
	std::vector<std::vector<int>> _ans;
	std::vector<int> _tmp_loc;

	int pos = v0;
	int noPath = -1;
	int idx = 1;

	for (v = 0; v < netNode_nums; v++)
	{
		D[v] = rc[v0][v];
	}
	final[v0] = 1;
	for (v = 1; v < netNode_nums; v++)
	{
		min = INF;
		k = -1;
		for (w = 0; w < netNode_nums; w++)
		{
			if (!final[w] && ((D[w]) < min)
				//&& (netNode_MGraph_BandWidth_Left[pos][w] >= requireBandWidth[n])
				&& (w != noPath))
			{
				if (P[w] == -1 && (netNode_MGraph_BandWidth_Left[v0][w] >= requireBandWidth_after_merge[n]))
				{
					k = w;
					min = D[w];
				}
				if (P[w] != -1 && (netNode_MGraph_BandWidth_Left[P[w]][w] >= requireBandWidth_after_merge[n]))
				{
					k = w;
					min = D[w];
				}
			}
		}

		if (k == -1 && pos == v0)
		{
			break;
		}
		if (k == -1)/*&& P[pos] != -1 && !final[tag])*/
		{
			int i = idx;
			noPath = pos;
			_tmp_loc.push_back(noPath);
			
			for (int i = 0; i < netNode_nums; i++)
			{
				final[i] = 0;
			}
			while (i)
			{
				final[v0] = 1;
				final[_tmp_loc[_tmp_loc.size()-i--]] = 1;
			}
			pos = v0;
			idx++;
			v = netNode_nums - idx - 3;
			continue;
		}
		//if (k == -1 )//&& final[tag])&& pos == -1)
		//{
		//	break;
		//}

		final[k] = 1;
		pos = k;
		if (final[tag])
			break;
		for (w = 0; w < netNode_nums; w++)
		{
			
			if (!final[w] && (min + rc[k][w]) < D[w]
				&& (netNode_MGraph_BandWidth_Left[k][w] >= requireBandWidth_after_merge[n]))
			{
				//std::cout << k << "\t" << w << "\t" << pos << "\t" << noPath << std::endl;

				if (P[k] == -1 && (netNode_MGraph_BandWidth_Left[v0][k] >= requireBandWidth_after_merge[n]))
				{
					D[w] = min + rc[k][w];
					P[w] = k;
				}
				else if (P[k] != -1)
				{
					//std::cout << k << "\t" << w << "\t" << pos << "\t" << noPath << std::endl;
					D[w] = min + rc[k][w];
					P[w] = k;
				}
			}
		}

	}

	int _tmp_p = tag;
	_ret.push_back(tag);
	while (/*P[_tmp_p] != v && */P[_tmp_p] != -1)
	{
		_ret.push_back(P[_tmp_p]);
		_tmp_p = P[_tmp_p];
	}
	_ret.push_back(v0);
	for (int i = 0; i < _ret.size() / 2; i++)
	{
		_ret[i] = _ret[i] ^ _ret[_ret.size() - i - 1];
		_ret[_ret.size() - i - 1] = _ret[_ret.size() - i - 1] ^ _ret[i];
		_ret[i] = _ret[i] ^ _ret[_ret.size() - i - 1];
	}
	_ans.push_back(D);
	_ans.push_back(_ret);
	return _ans;
}

// 打印Dijkstra路径
void print_Dijkstra_ShortPath(const std::vector<std::vector<int>> &vec, int v, int tag)
{
	for (int i = 0; i < vec[1].size() - 1; i++)
	{
		if (vec[1][i] != -1)
		{
			std::cout << vec[1][i] << "==>";
		}
	}
	std::cout <<vec[1].back()<<std::endl;
}

// 合并相连节点
bool merge_Dijkstra_server(std::vector<consumeNode_index> &cnv, const std::vector<std::vector<int>> &v1, 
	const std::vector<std::vector<int>> &v2, 
	consumeNode_index n1, consumeNode_index n2 ,netNode_index *sever_loc)
{
	// netNode_index sever_loc;
	int _status;
	if (v1[0][cnv[n2]] != INF && v2[0][cnv[n1]] != INF)
	{
		if (requireBandWidth_after_merge[n1]>= requireBandWidth_after_merge[n2])
		{
			//if (v1[1].size() == 2 && v2[1].size() == 2)
			//{
			//	if (v1[0][cnv[n2] * requireBandWidth[n1]] < serverCost)
			//	{
			//		sever_loc = cnv[n1];
			//		//cnv[n2] = sever_loc;
			//		server_Num--;
			//	}
			//}
			//else if (v1[1].size() == 2 && v2[1].size() > 2)
			//{
			//	sever_loc = cnv[n1];
			//	cnv[n2] = sever_loc;
			//	server_Num--;
			//}
			//else if (v1[1].size() > 2 && v2[1].size() == 2)
			//{
			//	sever_loc = cnv[n2];
			//	cnv[n1] = sever_loc;
			//	server_Num--;
			//}
			//else
			//{
				int pos = select_Point(v1, v2, n1, n2);
				if (pos == -1)
					return false;
				*sever_loc = v1[1][pos];
				server_Num--;
			/*}
			_status = 1*/;
		}
		else
		{
			/*if (v1[1].size() == 2 && v2[1].size() == 2)
			{
				sever_loc = cnv[n2];
				cnv[n1] = sever_loc;
				server_Num--;
			}
			else if (v1[1].size() == 2 && v2[1].size() > 2)
			{
				sever_loc = cnv[n2];
				cnv[n1] = sever_loc;
				server_Num--;
			}
			else if (v1[1].size() > 2 && v2[1].size() == 2)
			{
				sever_loc = cnv[n1];
				cnv[n2] = sever_loc;
				server_Num--;
			}
			else
			{*/
				int pos = select_Point(v2, v1, n2, n1);
				if (pos == -1)
					return false;
				*sever_loc = v2[1][pos];
				server_Num--;
			/*}
			_status = 2*/;
		}
	}
	else if (v1[0][cnv[n2]] == INF && v2[0][cnv[n1]] * requireBandWidth_after_merge[n1] < serverCost)
	{
		*sever_loc = cnv[n1];
		//cnv[n2] = sever_loc;
		server_Num--;
		_status = 1;
	}
	else if (v1[0][cnv[n2]] * requireBandWidth_after_merge[n2] < serverCost && v2[0][cnv[n1]] == INF)
	{
		*sever_loc = cnv[n2];
		//cnv[n1] = sever_loc;
		server_Num--;
		_status = 2;
	}
	else
	{
		*sever_loc = -1;
	}
	if (*sever_loc != -1)
	{
		std::cout << n1 << " " << n2 << "\t" << cnv[n1] << "与" << cnv[n2] << "合并为：\t" << *sever_loc << "\t剩余" << server_Num << "个服务器" << std::endl;
		return true;
	}
	else
	{
		return false;
	}
	//std::cout << n1 << " " << n2 << "\t" << consumeNodeList[n1] << "与" << consumeNodeList[n2] << "合并为：\t" << sever_loc << "\t剩余" << server_Num << "个服务器" << std::endl;
}

// 选取公共点
int select_Point(const std::vector<std::vector<int>> &v1,
	const std::vector<std::vector<int>> &v2, 
	consumeNode_index n1, consumeNode_index n2)
{
	int _ans = -1;
	int _min = serverCost;
	int cost1, cost2;

	for (int i = 0; i < v1[1].size(); i++)
	{
		for (int j = 0; j < v2[1].size(); j++)
		{
			if (v1[1][i] == v2[1][j])
			{
				cost1 = (v1[0][v2[1][j]] == INF) ? 0 : v1[0][v2[1][j]];
				cost2 = (v2[0][v1[1][i]] == INF) ? 0 : v2[0][v1[1][i]];
				
				if ((requireBandWidth_after_merge[n1] * cost1 + requireBandWidth_after_merge[n2] * cost2) < _min)
				{
					_min = requireBandWidth_after_merge[n1] * cost1 + requireBandWidth_after_merge[n2] * cost2;
					// std::cout << _min << std::endl;
					_ans = i;
				}
			}
		}
	}
	//server_Num--;
	return _ans;
}

void algorithm_Dijkstra(std::vector<consumeNode_index> &cnv)
{
	std::vector<std::vector<int>> link_List;
	std::vector<std::vector<int>> _ans1, _ans2;
	int _index_first = 0;
	int _index_second = 0;
	std::vector<int> same_factor;
	std::vector<bool> _status(consumeNode_nums, true);
	bool _merge_flag;
	
	netNode_index id;
	int _size = (consumeNode_nums % 2 == 0) ? consumeNode_nums - 2 : consumeNode_nums - 2 - 1;
	for (int w = 0; w < consumeNode_nums; w++)
	{
		int _merge_times = 0;
		for (int i = 0; i < consumeNode_nums; i++)
		{
			for (int j = i + 1; j < consumeNode_nums; j++)
			{
				if (j >= consumeNode_nums)
					break;
				if (cnv[i] == cnv[j])
				{
					same_factor.push_back(j);
					continue;
				}
				if (cnv[i] != cnv[j])// /*&& _status[i] */&& _status[j])
				{
					_ans1 = Dijkstra_original(cnv[i], cnv[j], i,
						netNode_MGraph_RentCost);
					//print_Dijkstra_ShortPath(_ans1, cnv[i], cnv[j]);
					_ans2 = Dijkstra_original(cnv[j], cnv[i], j,
						netNode_MGraph_RentCost);
					//print_Dijkstra_ShortPath(_ans2, cnv[j], cnv[i]);
					_merge_flag = merge_Dijkstra_server(cnv, _ans1, _ans2, i, j, &id);
				}
				if (_merge_flag)
				{
					cnv[i] = id;
					requireBandWidth_after_merge[i] += requireBandWidth_after_merge[j];
					cnv[j] = id;
					requireBandWidth_after_merge[j] = requireBandWidth_after_merge[i];
					for(int j = 0; j < same_factor.size(); j++)
						cnv[same_factor[j]] = id;
					for (int w = 0; w < _ans1[1].size(); w++)
					{
						if (w > 0)
							netNode_MGraph_BandWidth_Left[_ans1[1][w - 1 ]][_ans1[1][w]] -= requireBandWidth[i];
						if (_ans1[1][w] == id)
							break;
					}
					for (int w = 0; w < _ans2[1].size(); w++)
					{
						if (w > 0)
							netNode_MGraph_BandWidth_Left[_ans2[1][w - 1 ]] [_ans2[1][w]]-= requireBandWidth[j];
						if (_ans2[1][w] == id)
							break;
					}
					_merge_times++;
					_status[j] = false;
					same_factor.clear();
					break;
				}
					
			}
			if (_merge_flag)
			{
				_status[i] = false;
				i++;
				continue;
			}
		}
		if (!_merge_times)
			break;
	}
	server_Num;
}