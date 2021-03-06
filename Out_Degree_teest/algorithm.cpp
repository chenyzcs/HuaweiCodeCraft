#include "variable_declaration.h"

std::vector<std::vector<netNode_index>> out_degree_max()
{
	// 将消费节点映射到网络节点
	std::vector<netNode_index> req_bandwidth_2_netNode(netNode_nums, 0);
	for (int i = 0; i < consumeNode_nums; i++)
	{
		int idx = consumeNodeList[i];
		req_bandwidth_2_netNode[idx] = requireBandWidth[i];
	}
	// 找出出度带宽最大的满足要求点的集合
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
	std::vector<std::vector<int>> host_list;
	host_list.clear();
	int _tmp_host_num = /*min_host_num + 2;*/out_degree_per_point.size();
	std::vector<int> _tmp;
	while (_tmp_host_num--)
	{
		std::vector<int>::iterator biggest = std::max_element(
			std::begin(out_degree_per_point), std::end(out_degree_per_point));
		if (*biggest<max_consume_req)
		{
			continue;
		}
		int max_pos = std::distance(std::begin(out_degree_per_point), biggest);
		
		_tmp.push_back(max_pos);
		/*_tmp.push_back(*biggest);
		host_list.push_back(_tmp);*/
		out_degree_per_point[max_pos] = 0;
	}
	int low_;
	for (int i = 0; i < _tmp.size() - 1;i++)
	{
		if ((out_degree_per_point_tmp[_tmp[i]] + out_degree_per_point_tmp[_tmp[i + 1]]) < max_bandwidth_require)
		{
			low_ = i;
			break;
		}
	}
	std::vector<std::vector<netNode_index>> netNode_BandWidth_out_degree(netNode_nums, std::vector<netNode_index>(netNode_nums, 0));
	std::vector<std::vector<netNode_index>> netNode_BandWidth_out_degree_tmp(netNode_nums, std::vector<netNode_index>(netNode_nums, 0));

	for (int i = 0; i < netNode_nums; i++)
	{
		for (int j = 0; j < netNode_nums; j++)
		{
			netNode_BandWidth_out_degree[i][j] = netNode_MGraph_BandWidth[i][j];
			netNode_BandWidth_out_degree_tmp[i][j] = netNode_MGraph_BandWidth[i][j];
		}
	}
	std::vector<int> r(min_host_num);
	std::vector<std::vector<int>> result;
	Cij(/*low_+2*/min_host_num, min_host_num, r, min_host_num, result);
	int minsize = INF;
	int minpos = -1;
	int mincot = 0;
	for (int i = 0; i < result.size(); i++)
	{
		
		std::vector<int> _l;
		for (int j = 0; j < min_host_num; j++)
		{
			_l.push_back(_tmp[result[i][j]]);
		}
		auto ans = merge_host_2_consumme(_l, netNode_BandWidth_out_degree, netNode_BandWidth_out_degree_tmp, req_bandwidth_2_netNode);
		/*std::cout << std::endl;
		for (auto &c : _l)
			std::cout << c << " ";
		std::cout << "net" << std::endl;*/
		std::vector<netNode_index> last_consume_nums;
		for (int i = 0; i < netNode_nums; i++)
		{
			if (req_bandwidth_2_netNode[i] != 0)
			{
				//std::cout << i << " " << req_bandwidth_2_netNode[i] << std::endl;
				last_consume_nums.push_back(i);
			}
		}
		if (last_consume_nums.size() < minsize)
		{
			minsize = last_consume_nums.size();
			for (int l = 0; l < result[i].size(); l++)
			{
				mincot += result[i][l];
			}
			minpos = i;
		}
		else if (last_consume_nums.size() == minsize)
		{
			int tmp_cot = 0;
			for (int l = 0; l < result[i].size(); l++)
			{
				tmp_cot += result[i][l];
			}
			if (tmp_cot < mincot)
			{
				minsize = last_consume_nums.size();
				minpos = i;
			}
		}

	}
	std::vector<int> sx;
	for (int i = 0; i < result[minpos].size(); i++)
	{
		sx.push_back(_tmp[result[minpos][i]]);
	}
	for (int i = 0; i < netNode_nums; i++)
	{
		for (int j = 0; j < netNode_nums; j++)
		{
			netNode_BandWidth_out_degree[i][j] = netNode_MGraph_BandWidth[i][j];
			netNode_BandWidth_out_degree_tmp[i][j] = netNode_MGraph_BandWidth[i][j];
		}
	}
	auto _t= merge_host_2_consumme(sx, netNode_BandWidth_out_degree, netNode_BandWidth_out_degree_tmp, req_bandwidth_2_netNode);
	/*std::cout << std::endl;
	for (auto &c : sx)
		std::cout << c << " ";
	std::cout << "net" << std::endl;*/
	std::vector<netNode_index> last_consume_nums_;
	for (int i = 0; i < netNode_nums; i++)
	{
		if (req_bandwidth_2_netNode[i] != 0)
		{
			//std::cout << i << " " << req_bandwidth_2_netNode[i] << std::endl;
			last_consume_nums_.push_back(i);
		}
	}
	
	std::vector<std::vector<int>> _ans;
	std::vector<int> nohost_;
	for (int i = 1; i < 2/*last_consume_nums_.size()*/; i++)
	{
		std::vector<int> r(1);
		std::vector<std::vector<int>> result;
		Cij(last_consume_nums_.size(), 1, r, 1, result);
		for (int j = 0; j < result.size(); j++)
		{
			std::vector<int> tmp_res;
			for (int k = 0; k < sx.size(); k++)
			{
				tmp_res.push_back(sx[k]);
			}
			for (int k = 0; k < result[j].size(); k++)
			{
				tmp_res.push_back(last_consume_nums_[result[j][k]]);
			}
			for (int k = 0; k < consumeNode_nums; k++)
			{
				int idx = consumeNodeList[k];
				req_bandwidth_2_netNode[idx] = requireBandWidth[k];
			}
			for (int k = 0; k < netNode_nums; k++)
			{
				for (int l = 0; l < netNode_nums; l++)
				{
					netNode_BandWidth_out_degree[k][l] = netNode_MGraph_BandWidth[k][l];
					netNode_BandWidth_out_degree_tmp[k][l] = netNode_MGraph_BandWidth[k][l];
				}
			}
			_ans= merge_host_2_consumme(tmp_res, netNode_BandWidth_out_degree, netNode_BandWidth_out_degree_tmp, req_bandwidth_2_netNode);
			std::vector<netNode_index> last_consume_nums__;
			for (int k = 0; k < netNode_nums; k++)
			{
				if (req_bandwidth_2_netNode[k] != 0)
				{
					//std::cout << k << " " << req_bandwidth_2_netNode[k] << std::endl;
					last_consume_nums__.push_back(k);
				}
			}
			if (last_consume_nums__.size() == 0)//< last_consume_nums_.size())
			{

				std::cout << "host is" << std::endl;
				for (auto s : tmp_res)
					std::cout << s << " ";
				/*for (int l = 0; l < last_consume_nums_.size(); l++)
				{
					for (int m = 0; m < last_consume_nums__.size(); m++)
					{
						
					}
				}*/
				goto ANS;
			}
			if (last_consume_nums__.size()<last_consume_nums_.size())
			{
				nohost_.push_back(last_consume_nums_[result[j][0]]);
			}
		}
	}
	
	//return ans_;
	for (int i = 0; i < nohost_.size(); i++)
	{
		sx.push_back(nohost_[i]);
	}
	std::cout << "host is" << std::endl;
	for (auto s : sx)
		std::cout << s << " ";
	for (int k = 0; k < consumeNode_nums; k++)
	{
		int idx = consumeNodeList[k];
		req_bandwidth_2_netNode[idx] = requireBandWidth[k];
	}
	for (int i = 0; i < netNode_nums; i++)
	{
		for (int j = 0; j < netNode_nums; j++)
		{
			netNode_BandWidth_out_degree[i][j] = netNode_MGraph_BandWidth[i][j];
			netNode_BandWidth_out_degree_tmp[i][j] = netNode_MGraph_BandWidth[i][j];
		}
	}
	_ans= merge_host_2_consumme(sx, netNode_BandWidth_out_degree, netNode_BandWidth_out_degree_tmp, req_bandwidth_2_netNode);

	ANS:return _ans;
}


std::vector<std::vector<netNode_index>> merge_host_2_consumme(std::vector<netNode_index> &host_list,
	std::vector<std::vector<netNode_index>> &netNode_BandWidth_out_degree,
	std::vector<std::vector<netNode_index>> &netNode_BandWidth_out_degree_tmp,
	std::vector<netNode_index> &req_bandwidth_2_netNode)
{
	 
	for (int i = 0; i < netNode_nums; i++)
	{
		for (int j = 0; j < netNode_nums; j++)
		{
			netNode_BandWidth_out_degree[i][j] = netNode_MGraph_BandWidth[i][j];
			netNode_BandWidth_out_degree_tmp[i][j] = netNode_MGraph_BandWidth[i][j];
		}
	}
	for (int i = 0; i < consumeNode_nums; i++)
	{
		int idx = consumeNodeList[i];
		req_bandwidth_2_netNode[idx] = requireBandWidth[i];
	}

	std::vector<std::vector<int>> link_list2;
	I:for (int i = 0; i < consumeNode_nums; i++)
	{
		int merge_times = 0;
		int _tmp_req_bw = req_bandwidth_2_netNode[consumeNodeList[i]];
		for (int j = 0; j < host_list.size(); j++)
		{
			int is_path = -1;
			int _tmp_cost = 0;
			int _tmp_bw = 0;
			if (host_list[j] == consumeNodeList[i])
			{
				//host_list.push_back(consumeNodeList[i]);
				std::vector<netNode_index> _tmp_equ;
				_tmp_equ.push_back(host_list[j]);
				_tmp_equ.push_back(consumeNodeList[i]);
				_tmp_equ.push_back(requireBandWidth[i]);
				link_list2.push_back(_tmp_equ);
				req_bandwidth_2_netNode[consumeNodeList[i]] = 0;
				break;
				//goto I;
				continue;
			}
			while (is_path != INF && req_bandwidth_2_netNode[consumeNodeList[i]] > 0)
			{
				bool another_host = false;
				auto _tmp_ans = Dijkstra_2_links(host_list[j], consumeNodeList[i],
					netNode_MGraph_RentCost, netNode_BandWidth_out_degree);
				_tmp_bw = _tmp_ans[0].back();
				std::vector<netNode_index> _tmp_list;
				for (int k = 1; k < _tmp_ans[1].size(); k++)
				{
					for (int l = 0; l < host_list.size(); l++)
					{
						if (host_list[l] == _tmp_ans[1][k])
						{
							another_host = true;
						}
					}
				}
				if (another_host)
					break;

				if (_tmp_bw > req_bandwidth_2_netNode[consumeNodeList[i]])
				{
					_tmp_bw = req_bandwidth_2_netNode[consumeNodeList[i]];
					is_path = _tmp_ans[0][consumeNodeList[i]];
					_tmp_cost += is_path*_tmp_bw;
					req_bandwidth_2_netNode[consumeNodeList[i]] = 0;
				}
				else
				{
					req_bandwidth_2_netNode[consumeNodeList[i]] -= _tmp_bw;
					is_path = _tmp_ans[0][consumeNodeList[i]];
					_tmp_cost += is_path*_tmp_bw;
				}

				if (_tmp_cost > serverCost)
				{
					req_bandwidth_2_netNode[consumeNodeList[i]] += _tmp_bw;
					break;
				}
				_tmp_list.assign(_tmp_ans[1].begin(), _tmp_ans[1].end());
				_tmp_list.push_back(i);
				_tmp_list.push_back(_tmp_bw);
				link_list2.push_back(_tmp_list);
				merge_times++;

				if (_tmp_ans[0][consumeNodeList[i]] != INF)
				{
					for (int k = 0; k < _tmp_ans[1].size(); k++)
					{
						if (k + 1 < _tmp_ans[1].size())
						{
							netNode_BandWidth_out_degree[_tmp_ans[1][k]][_tmp_ans[1][k + 1]] -= _tmp_bw;
						}
					}
				}


				//std::cout << _tmp_cost << std::endl;
			}
		}
		if (req_bandwidth_2_netNode[consumeNodeList[i]] != 0)
		{
			for (int l = 0; l < merge_times; l++)
			{
				link_list2.pop_back();
			}
			for (int m = 0; m < netNode_nums; m++)
			{
				for (int n = 0; n < netNode_nums; n++)
				{
					netNode_BandWidth_out_degree[m][n] = netNode_BandWidth_out_degree_tmp[m][n];
				}
			}
			req_bandwidth_2_netNode[consumeNodeList[i]] = _tmp_req_bw;
			std::vector<netNode_index> _tmp_list;
			_tmp_list.push_back(consumeNodeList[i]);
			_tmp_list.push_back(i);
			_tmp_list.push_back(requireBandWidth[i]);
			link_list2.push_back(_tmp_list);
		}
		else
		{
			for (int m = 0; m < netNode_nums; m++)
			{
				for (int n = 0; n < netNode_nums; n++)
				{
					netNode_BandWidth_out_degree_tmp[m][n] = netNode_BandWidth_out_degree[m][n];
				}
			}
			//is_host[i] = 1;
		}
	}
	return link_list2;
}
	
void Cij(int i, int j, std::vector<int> &r, int num, std::vector<std::vector<int>> & result)
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
			result.push_back(temp);
			//cout << endl;  
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
			Cij(k - 1, j - 1, r, num, result);
		}
	}
}