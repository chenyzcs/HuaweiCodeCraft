#include "variable_declaration.h"

// 网络节点拓扑初始化
void Init_netNode(netNode_index (*bw)[NET_NODE_MAXSIZE],
	netNode_index (*rc)[NET_NODE_MAXSIZE])
{
	for (int i = 0; i < NET_NODE_MAXSIZE; i++)
	{
		for (int j = 0; j < NET_NODE_MAXSIZE; j++)
		{
			bw[i][j] = 0;
			rc[i][j] = INF;
		}
		/*std::fill_n(rc[i], NET_NODE_MAXSIZE, INF);
		std::fill_n(bw[i], NET_NODE_MAXSIZE, INF)*/;
	}
	
}

// 消费节点初始化
void Init_consumeNode(consumeNode_index *ci,
	require_bandwidth *rb)
{
	for (int i = 0; i < CONSUME_NODE_MAXSIZE; i++)
	{
		ci[i] = INF;
		rb[i] = INF;
	}
	
}

// 初始化每条链路剩余带宽

void Init_netNode_bandWidth_left(std::vector<std::vector<netNode_index>> &bdl)
{
	for (int i = 0; i < netNode_nums; i++)
	{
		for (int j = 0; j < netNode_nums; j++)
		{
			bdl[i][j] = netNode_MGraph_BandWidth[i][j];
		}
	}
}

// 初始化消费节点
void Init_consumeNode_vec(std::vector<consumeNode_index> &cnv)
{
	for (int i = 0; i < consumeNode_nums; i++)
	{
		cnv[i] = consumeNodeList[i];
	}
}

void Init_req_bandwidth_to_netNode(std::vector<netNode_index> &req_bw_2_net)
{
	for (int i = 0; i < consumeNode_nums; i++)
	{
		req_bw_2_net[consumeNodeList[i]] = requireBandWidth[i];
	}
}

// 输出答案
std::string output_ans(std::vector<consumeNode_index> &cnv)
{
	int links = 0;
	std::string _res;
	std::vector<std::string> str;
	for (int i = 0; i < consumeNode_nums; i++)
	{
		if (consumeNodeList[i] != cnv[i])
		{
			auto ans = Dijkstra_original(consumeNodeList[i], cnv[i], i,
				netNode_MGraph_RentCost, netNode_MGraph_BandWidth, requireBandWidth);
			for (int j = 0; j < ans[1].size(); j++)
			{
				str.push_back(std::to_string(ans[1][ans[1].size() - 1 - j]) + " ");
			}
			links += (ans[1].size() - 1);
		}
		else
		{
			str.push_back(std::to_string(consumeNodeList[i]) + " ");
		}
		if (i == consumeNode_nums - 1)
		{
			str.push_back(std::to_string(i) + " " + std::to_string(requireBandWidth[i]));
		}
		else
		{
			str.push_back(std::to_string(i) + " " + std::to_string(requireBandWidth[i]) + "\n");
		}
	}
	_res = std::to_string(links) + "\n\n";
	for (auto &c : str)
		_res += c;
	return _res;
}

// 两条链路合并交点
std::vector<std::vector<netNode_index>> merge_2_links(std::vector<consumeNode_index> &cnv)
{
	int links = 0;
	std::string _res;
	std::vector<std::vector<netNode_index>> merge_links(consumeNode_nums);
	for (int i = 0; i < consumeNode_nums; i++)
	{
		if (consumeNodeList[i] != cnv[i])
		{
			auto ans = Dijkstra_original(consumeNodeList[i], cnv[i], i,
				netNode_MGraph_RentCost, netNode_MGraph_BandWidth, requireBandWidth);
			for (int j = 0; j < ans[1].size(); j++)
			{
				merge_links[i].push_back(ans[1][j]);
			}
			links += (ans[1].size() - 1);
		}
		else
		{
			merge_links[i].push_back(consumeNodeList[i]);
		}
	}
	std::vector<netNode_index> req_bandwidth_2_netNode(netNode_nums, 0);
	for (int i = 0; i < consumeNode_nums; i++)
	{
		int idx = consumeNodeList[i];
		req_bandwidth_2_netNode[idx] = requireBandWidth[i];
	}
	std::vector<netNode_index> serveNode_list;
	// 合并交点
	for (int w = 0; w < consumeNode_nums; w++)
	{
		for (int i = 0; i < consumeNode_nums; i++)
		{
			bool merge_links_flag = false;
			int id_i, id_j;
			if (merge_links[i].size() == 1)
				continue;
			for (int j = i + 1; j < consumeNode_nums; j++)
			{
				if (merge_links[j].size() == 1)
					continue;
				for (int k = 0; k < merge_links[i].size(); k++)
				{
					for (int l = 0; l < merge_links[j].size(); l++)
					{
						if (merge_links[i][k] == merge_links[j][l])
						{
							//std::cout << merge_links[i][k] << std::endl;
							if ((k + 1 < merge_links[i].size() - 1) && (l + 1 < merge_links[j].size() - 1))
							{
								if (merge_links[i][k + 1] != merge_links[j][l + 1])
								{
									merge_links_flag = true;
									id_i = k;
									id_j = l;
								}
							}
							else if ((k + 1 == merge_links[i].size() - 1) || (l + 1 == merge_links[j].size() - 1))
							{
								merge_links_flag = true;
								id_i = k;
								id_j = l;
							}
							else
							{
								/*k++;
								l++;
								goto I_;*/
								continue;
							}
							if (merge_links_flag)
								break;
						}
						if (merge_links_flag)
							break;
					}
					if (merge_links_flag)
						break;
				}
				if (merge_links_flag)
				{
					int tar_i = -1, tar_j = -1;
					for (int i_ = 0; i_ < consumeNode_nums; i_++)
					{
						if (merge_links[i_].size() == 1 && merge_links[i_][0] == merge_links[i].back())
						{
							tar_i = i_;
							break;
						}
					}
					for (int j_ = 0; j_ < consumeNode_nums; j_++)
					{
						if (merge_links[j_].size() == 1 && merge_links[j_][0] == merge_links[j].back())
						{
							tar_j = j_;
							break;
						}
					}
					if (tar_i != -1)
					{
						merge_links[tar_i].clear();
						merge_links[tar_i].assign(merge_links[i].begin() + id_i, merge_links[i].end());
						std::reverse(merge_links[tar_i].begin(), merge_links[tar_i].end());
						int low_bw = INF;
						for (int m = 0; m < merge_links[tar_i].size(); m++)
						{
							if (m + 1 <= merge_links[tar_i].size() - 1)
							{
								if (netNode_MGraph_BandWidth_Left[merge_links[tar_i][m]][merge_links[tar_i][m + 1]] < low_bw)
								{
									low_bw = netNode_MGraph_BandWidth_Left[merge_links[tar_i][m]][merge_links[tar_i][m + 1]];
								}
							}
						}
						req_bandwidth_2_netNode[merge_links[tar_i].front()] = (req_bandwidth_2_netNode[merge_links[tar_i].back()]>=low_bw)?
							req_bandwidth_2_netNode[merge_links[tar_i].front()] - low_bw : 0;
					}
					if (tar_j != -1)
					{
						int low_bw = INF;
						merge_links[tar_j].clear();
						merge_links[tar_j].assign(merge_links[j].begin() + id_j, merge_links[j].end());
						std::reverse(merge_links[tar_j].begin(), merge_links[tar_j].end());
						for (int m = 0; m < merge_links[tar_j].size(); m++)
						{
							if (m + 1 <= merge_links[tar_j].size() - 1)
							{
								if (netNode_MGraph_BandWidth_Left[merge_links[tar_j][m]][merge_links[tar_j][m + 1]] < low_bw)
								{
									low_bw = netNode_MGraph_BandWidth_Left[merge_links[tar_j][m]][merge_links[tar_j][m + 1]];
								}
							}
						}
						req_bandwidth_2_netNode[merge_links[tar_j].front()] = (req_bandwidth_2_netNode[merge_links[tar_j].back()] >= low_bw) ?
							req_bandwidth_2_netNode[merge_links[tar_j].front()] - low_bw : 0;
					}
					
					merge_links[i].erase(merge_links[i].begin() + id_i + 1, merge_links[i].end());
					merge_links[j].erase(merge_links[j].begin() + id_j + 1, merge_links[j].end());
					req_bandwidth_2_netNode[merge_links[i].front()] = 0;
					req_bandwidth_2_netNode[merge_links[j].front()] = 0;
					serveNode_list.push_back(merge_links[i][id_i]);
					break;
				}
			}
			
		}
	}
	std::sort(serveNode_list.begin(), serveNode_list.end());
	auto t_pos = std::unique(serveNode_list.begin(), serveNode_list.end());
	serveNode_list.erase(t_pos, serveNode_list.end());
	
	std::vector<std::vector<netNode_index>> netNode_bandWidth_after_2_links(netNode_nums, std::vector<netNode_index>(netNode_nums, 0));
	std::vector<std::vector<netNode_index>> netNode_bandWidth_after_2_links_tmp(netNode_nums, std::vector<netNode_index>(netNode_nums, 0));


	for (int i = 0; i < netNode_nums; i++)
	{
		for (int j = 0; j < netNode_nums; j++)
		{
			netNode_bandWidth_after_2_links[i][j] = netNode_MGraph_BandWidth[i][j];
			netNode_bandWidth_after_2_links_tmp[i][j] = netNode_MGraph_BandWidth[i][j];
		}
	}
	std::vector<int> is_host(merge_links.size(), 0);
	for (int i = 0; i < merge_links.size(); i++)
	{
		for (int j = 0; j < merge_links.size(); j++)
		{
			if (i != j && merge_links[i][0] == merge_links[j].back())
			{
				is_host[i] = -1;
				//is_host[j] = true;
			}
		}
	}
	for (int i = 0; i < merge_links.size(); i++)
	{
		for (int j = 0; j < merge_links.size(); j++)
		{
			if (is_host[i] == -1 && i != j && merge_links[j].back() == merge_links[i][0])
				is_host[j] = -1;
		}
	}
	// 利用交点补偿带宽需求大的消费节点
	std::vector<std::vector<int>> link_list2;
	for (int i = 0; i < merge_links.size(); i++)
	{
		int merge_times = 0;
		int _tmp_req_bw = req_bandwidth_2_netNode[merge_links[i].front()];
		if (req_bandwidth_2_netNode[merge_links[i].front()] != 0
			&& merge_links[i].size() == 1 && is_host[i] != -1)
		{
			for (int j = 0; j < serveNode_list.size(); j++)
			{
				int is_path = -1;
				int _tmp_cost = 0;
				int _tmp_bw = 0;
				while (is_path != INF && req_bandwidth_2_netNode[merge_links[i].front()] > 0)
				{
					auto _tmp_ans = Dijkstra_2_links(merge_links[i].front(), serveNode_list[j], netNode_MGraph_RentCost, netNode_bandWidth_after_2_links);
					_tmp_bw = _tmp_ans[0].back();
					std::vector<netNode_index> _tmp_list;
					bool another_host = false;
					
					if (_tmp_bw > req_bandwidth_2_netNode[merge_links[i].front()])
					{
						_tmp_bw = req_bandwidth_2_netNode[merge_links[i].front()];
						is_path = _tmp_ans[0][serveNode_list[j]];
						_tmp_cost += is_path*_tmp_bw;
						req_bandwidth_2_netNode[merge_links[i].front()] = 0;
					}
					else
					{
						req_bandwidth_2_netNode[merge_links[i].front()] -=_tmp_bw;
						is_path = _tmp_ans[0][serveNode_list[j]];
						_tmp_cost += is_path*_tmp_bw;
					}
					
					if (_tmp_cost > serverCost)
					{
						req_bandwidth_2_netNode[merge_links[i].front()] += _tmp_bw;
						break;
					}
					
					for (int l = 0; l < serveNode_list.size(); l++)
					{
						for (int m = 1; m < _tmp_ans[1].size() - 1; m++)
						{
							if (_tmp_ans[1][m]==serveNode_list[l])
							{
								another_host = true;
							}
						}
					}

					/*if (another_host)
					{
						break;
					}*/

					_tmp_list.assign(_tmp_ans[1].begin(), _tmp_ans[1].end());
					_tmp_list.push_back(i);
					link_list2.push_back(_tmp_list);
					merge_times++;
					
					if (_tmp_ans[0][serveNode_list[j]] != INF)
					{
						for (int k = 0; k < _tmp_ans[1].size(); k++)
						{
							if (k + 1 < _tmp_ans[1].size())
							{
								netNode_bandWidth_after_2_links[_tmp_ans[1][k]][_tmp_ans[1][k + 1]] -= _tmp_ans[0].back();
							}
						}
					}
					
					
					//std::cout << _tmp_cost << std::endl;
				}
			}
			if (req_bandwidth_2_netNode[merge_links[i].front()] != 0)
			{
				for (int l = 0; l < merge_times; l++)
				{
					link_list2.pop_back();
				}
				for (int m = 0; m < netNode_nums; m++)
				{
					for (int n = 0; n < netNode_nums; n++)
					{
						netNode_bandWidth_after_2_links[m][n] = netNode_bandWidth_after_2_links_tmp[m][n];
					}
				}
				req_bandwidth_2_netNode[merge_links[i].front()] = _tmp_req_bw;
			}
			else
			{
				for (int m = 0; m < netNode_nums; m++)
				{
					for (int n = 0; n < netNode_nums; n++)
					{
						netNode_bandWidth_after_2_links_tmp[m][n] = netNode_bandWidth_after_2_links[m][n];
					}
				}
				is_host[i] = 1;
			}
		}
	}
	
	std::vector<std::vector<netNode_index>> ret;

	for (int i = 0; i < is_host.size(); i++)
	{
		std::vector<netNode_index> _tmp;
		if (is_host[i]!=1)
		{
			for (int j = merge_links[i].size()-1; j >= 0; j--)
			{
				_tmp.push_back(merge_links[i][j]);
			}
			_tmp.push_back(i);
			_tmp.push_back(requireBandWidth[i]);
			ret.push_back(_tmp);
		}
		_tmp.clear();
	}
	for (int i = 0; i < link_list2.size(); i++)
	{
		std::vector<netNode_index> _tmp;
		for (int j = link_list2[i].size() - 2; j >= 0; j--)
		{
			_tmp.push_back(link_list2[i][j]);
		}
		_tmp.push_back(link_list2[i].back());
		_tmp.push_back(requireBandWidth[link_list2[i].back()]);
		ret.push_back(_tmp);
		_tmp.clear();
	}
	return ret;
}

// 合并链路后输出结果
std::string output_ans_after_link_merge(std::vector<std::vector<netNode_index>> &v)
{
	std::vector<std::string> _tmp_str;
	std::string _ret_str;
	int links = 0;
	for (int i = 0; i < v.size(); i++)
	{
		for (int j = 0; j < v[i].size(); j++)
		{
			if (j < v[i].size() - 1)
			{
				_tmp_str.push_back(std::to_string(v[i][j]) + " ");
			}
			else
			{
				_tmp_str.push_back(std::to_string(v[i][j]));
			}
		}
		if (i != v.size() - 1)
		{
			_tmp_str.push_back("\n");
		}
		links += v[i].size() - 3;
	}
	_ret_str += std::to_string(links) + "\n\n";
	for (auto &c : _tmp_str)
		_ret_str += c;
	return _ret_str;
}