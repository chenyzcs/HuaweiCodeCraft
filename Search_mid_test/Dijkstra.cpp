#include "variable_declaration.h"

std::vector<std::vector<int>> Dijkstra_max_flow_min_cost(netNode_index v0, netNode_index tag,
	std::vector<std::vector<netNode_index>> &rc, std::vector<std::vector<netNode_index>> &bw)
{
	int v, w, k, min;

	std::vector<int> final(netNode_nums + 2, 0);
	std::vector<int> D(netNode_nums + 2, INF);
	std::vector<int> P(netNode_nums + 2, -1);
	std::vector<int> _ret;
	std::vector<std::vector<int>> _ans;
	std::vector<int> _tmp_loc;

	int pos = v0;
	int noPath = -1;
	int idx = 1;

	for (v = 0; v < netNode_nums + 2; v++)
	{
		if (bw[v0][v] > 0)
			D[v] = rc[v0][v];
	}
	final[v0] = 1;
	for (v = 1; v <  netNode_nums + 2; v++)
	{
		min = INF;
		k = -1;
		for (w = 0; w <  netNode_nums + 2; w++)
		{
			if (!final[w] && ((D[w]) < min)
				//&& (netNode_MGraph_BandWidth_Left[pos][w] >= requireBandWidth[n])
				&& (w != noPath))
			{
				if (P[w] == -1 && (bw[v0][w] > 0))
				{
					k = w;
					min = D[w];
				}
				if (P[w] != -1 && (bw[P[w]][w] > 0))
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
		//if (k == -1)/*&& P[pos] != -1 && !final[tag])*/
		//{
		//	int i = idx;
		//	noPath = pos;
		//	_tmp_loc.push_back(noPath);

		//	for (int i = 0; i <  netNode_nums + 2; i++)
		//	{
		//		final[i] = 0;
		//	}
		//	while (i)
		//	{
		//		final[v0] = 1;
		//		final[_tmp_loc[_tmp_loc.size() - i--]] = 1;
		//	}
		//	pos = v0;
		//	idx++;
		//	v = netNode_nums + 2 - idx - 3;
		//	continue;
		//}
		//if (k == -1 )//&& final[tag])&& pos == -1)
		//{
		//	break;
		//}

		if (k==-1)
		{
			break;
		}
		final[k] = 1;
		pos = k;
		if (final[tag])
			break;
		for (w = 0; w <  netNode_nums + 2; w++)
		{

			if (!final[w] && (min + rc[k][w]) < D[w]
				&& (bw[k][w] > 0))
			{
				//std::cout << k << "\t" << w << "\t" << pos << "\t" << noPath << std::endl;

				if (P[k] == -1 && (bw[v0][k] > 0))
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
	int low = INF;
	for (int i = 0; i < _ret.size(); i++)
	{
		if (i + 1<_ret.size())
		{
			if (bw[_ret[i]][_ret[i + 1]] < low)
				low = bw[_ret[i]][_ret[i + 1]];
		}
	}
	D.push_back(low);
	_ans.push_back(D);
	_ans.push_back(_ret);
	return _ans;
}

std::vector<std::vector<int>> Dijkstra_2_links(netNode_index v0, netNode_index tag,
	netNode_index(*rc)[NET_NODE_MAXSIZE], std::vector<std::vector<netNode_index>> &bw)
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
		if (bw[v0][v] > 0)
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
				if (P[w] == -1 && (bw[v0][w] > 0))
				{
					k = w;
					min = D[w];
				}
				if (P[w] != -1 && (bw[P[w]][w] > 0))
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
				final[_tmp_loc[_tmp_loc.size() - i--]] = 1;
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
				&& (bw[k][w] > 0))
			{
				//std::cout << k << "\t" << w << "\t" << pos << "\t" << noPath << std::endl;

				if (P[k] == -1 && (bw[v0][k] > 0))
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
	int low = INF;
	for (int i = 0; i < _ret.size(); i++)
	{
		if (i+1<_ret.size())
		{
			if (bw[_ret[i]][_ret[i + 1]] < low)
				low = bw[_ret[i]][_ret[i + 1]];
		}
	}
	D.push_back(low);
	_ans.push_back(D);
	_ans.push_back(_ret);
	return _ans;
}

std::vector<std::vector<int>> Dijkstra_original(netNode_index v0, netNode_index tag, consumeNode_index n,
	netNode_index(*rc)[NET_NODE_MAXSIZE], netNode_index(*bw)[NET_NODE_MAXSIZE], consumeNode_index *req)
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
		if(bw[v0][v] >= req[n])
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
				if (P[w] == -1 && (bw[v0][w] >= req[n]))
				{
					k = w;
					min = D[w];
				}
				if (P[w] != -1 && (bw[P[w]][w] >= req[n]))
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
				&& (bw[k][w] >= req[n]))
			{
				//std::cout << k << "\t" << w << "\t" << pos << "\t" << noPath << std::endl;

				if (P[k] == -1 && (bw[v0][k] >= req[n]))
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
	else// if(v1[0][cnv[n2]] == INF && v2[0][cnv[n1]] == INF)
	{
		*sever_loc = -1;
	}
	if (*sever_loc != -1)
	{
		std::cout << n1 << " " << n2 << "\t" << cnv[n1] << "与" << cnv[n2] << "合并为：\t" << *sever_loc << "\t剩余" << server_Num << "个服务器" << std::endl;
		return true;
	}
	else if(*sever_loc == -1)
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

// 随机两两合并消费节点
void algorithm_Dijkstra(std::vector<consumeNode_index> &cnv)
{
	std::vector<std::vector<int>> link_List;
	std::vector<std::vector<int>> _ans1, _ans2;
	std::vector<int> same_factor;
	std::vector<bool> _status(consumeNode_nums, true);
	
	std::vector<bool> is_rand(consumeNode_nums, false);
	std::vector<netNode_index> random_list_index(consumeNode_nums, -1);
	std::default_random_engine generator(time(NULL));
	std::uniform_int_distribution<int> dis(0, consumeNode_nums - 1);
	int rand_num = 0;
	int rand_index = 0;
	while (rand_num < consumeNode_nums)
	{
		int _tmp_rand = dis(generator);
		if (!is_rand[_tmp_rand])
		{
			random_list_index[rand_index++] = _tmp_rand;
			is_rand[_tmp_rand] = true;
			rand_num++;
		}
	}
	for (int i = 0; i < random_list_index.size(); i++)
	{
		std::cout << random_list_index[i] << " ";
	}
	std::cout << std::endl;
	netNode_index id = -1;
	for (int w = 0; w < consumeNode_nums; w++)
	{
		
		int _merge_times = 0;
		for (int i = 0; i < consumeNode_nums; i++)
		{
			bool _merge_flag = false;
			same_factor.clear();
			for (int j = i + 1; j < consumeNode_nums; j++)
			{
				if (j >= consumeNode_nums)
					break;
				if (cnv[random_list_index[i]] == cnv[random_list_index[j]])
				{
					same_factor.push_back(j);
					continue;
				}
				if (cnv[random_list_index[i]] != cnv[random_list_index[j]])
				{
					_ans1 = Dijkstra_original(cnv[random_list_index[i]], cnv[random_list_index[j]], random_list_index[i],
						netNode_MGraph_RentCost, netNode_MGraph_BandWidth_Left, requireBandWidth_after_merge);
					//print_Dijkstra_ShortPath(_ans1, cnv[i], cnv[j]);
					_ans2 = Dijkstra_original(cnv[random_list_index[j]], cnv[random_list_index[i]], random_list_index[j],
						netNode_MGraph_RentCost, netNode_MGraph_BandWidth_Left, requireBandWidth_after_merge);
					//print_Dijkstra_ShortPath(_ans2, cnv[j], cnv[i]);
					_merge_flag = merge_Dijkstra_server(cnv, _ans1, _ans2, random_list_index[i], random_list_index[j], &id);
				}
				if (_merge_flag)
				{
					cnv[random_list_index[i]] = id;
					requireBandWidth_after_merge[random_list_index[i]] += requireBandWidth_after_merge[random_list_index[j]];
					cnv[random_list_index[j]] = id;
					requireBandWidth_after_merge[random_list_index[j]] = requireBandWidth_after_merge[i];
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

typedef std::pair<int, int> Node;
//bool operator>(Node a, Node b)
//{
//	return a.first < b.first;
//}


std::vector<std::vector<int>> dijkstra_priority_queue(netNode_index v0, netNode_index tag,
	std::vector<std::vector<netNode_index>> &rc, std::vector<std::vector<netNode_index>> &bw)
{
	int v,min;
	
	std::vector<int> D(netNode_nums + 2, INF);
	std::vector<int> P(netNode_nums + 2, -1);
	std::vector<int> vis(netNode_nums + 2, 0);
	std::priority_queue<Node,std::vector<Node>,std::greater<Node>> q;
	std::vector<int> _ret;
	std::vector<std::vector<int>> _ans;
	/*for (v = 0; v < netNode_nums + 2; v++)
	{
		if (bw[v0][v] > 0)
			D[v] = rc[v0][v];
	}*/
	D[v0] = 0;
	q.push(std::make_pair(D[v0],v0));
	while (!q.empty()) {
		Node t = q.top();
		//std::cout << t.second << std::endl;
		q.pop();
		if (vis[t.second])
			continue;
		vis[t.second] = 1;
		for (int i = 0; i < netNode_nums+2; i++)
			if (!vis[i] && (D[i] > t.first + rc[t.second][i]) && (bw[t.second][i] > 0)) {
				P[i] = t.second;
				D[i] = t.first + rc[t.second][i];
				q.push(std::make_pair(D[i],i));
		}
	}
	//return d[n];
	int _tmp_p = tag;
	_ret.push_back(tag);
	while (P[_tmp_p] != v0 && P[_tmp_p] != -1)
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
	int low = INF;
	for (int i = 0; i < _ret.size(); i++)
	{
		if (i + 1<_ret.size())
		{
			if (bw[_ret[i]][_ret[i + 1]] < low)
				low = bw[_ret[i]][_ret[i + 1]];
		}
	}
	D.push_back(low);
	_ans.push_back(D);
	_ans.push_back(_ret);
	return _ans;
}