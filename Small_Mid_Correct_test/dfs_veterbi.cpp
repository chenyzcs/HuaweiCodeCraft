#include "variable_declaration.h"


// max flow min cost
std::vector<std::vector<int>>  DFS_MCMF(std::vector<netNode_index> &assign_host_nodes)
{
	// 生成动态带宽与租金矩阵
	// N维是服务器源点 N+1维是消费汇点
	std::vector<std::vector<netNode_index>> _flow_cost_bandwidth(
		netNode_nums + 2, std::vector<netNode_index>(netNode_nums + 2, 0));
	std::vector<std::vector<netNode_index>> _flow_cost_rentcost(
		netNode_nums + 2, std::vector<netNode_index>(netNode_nums + 2, INF));
	std::vector<std::vector<netNode_index>> _flow_G_adj(netNode_nums + 2);

	for (int i = 0; i < netNode_nums; i++)
	{
		_flow_G_adj[i] = Graph_Adj[i];
	}
	_flow_G_adj[netNode_nums] = assign_host_nodes;
	int  assign_length = assign_host_nodes.size();
	for (int i = 0; i < assign_length; i++)
	{
		_flow_G_adj[assign_host_nodes[i]].push_back(netNode_nums);
	}
	for (int i = 0; i < consumeNode_nums; i++)
	{
		_flow_G_adj[netNode_nums + 1].push_back(consumeNodeList[i]);
	}
	for (int i = 0; i < consumeNode_nums; i++)
	{
		_flow_G_adj[consumeNodeList[i]].push_back(netNode_nums + 1);
	}

	for (int i = 0; i < netNode_nums; i++)
	{
		for (int j = 0; j < netNode_nums; j++)
		{
			_flow_cost_bandwidth[i][j] = netNode_MGraph_BandWidth[i][j];
			_flow_cost_rentcost[i][j] = netNode_MGraph_RentCost[i][j];
		}
	}
	for (int i = 0; i < assign_length; i++)
	{
		_flow_cost_bandwidth[netNode_nums][assign_host_nodes[i]] = INF;
		_flow_cost_bandwidth[assign_host_nodes[i]][netNode_nums] = INF;
		_flow_cost_rentcost[netNode_nums][assign_host_nodes[i]] = 0;
		_flow_cost_rentcost[assign_host_nodes[i]][netNode_nums] = 0;
	}
	for (int i = 0; i < consumeNode_nums; i++)
	{
		_flow_cost_bandwidth[netNode_nums + 1][consumeNodeList[i]] = requireBandWidth[i];
		_flow_cost_bandwidth[consumeNodeList[i]][netNode_nums + 1] = requireBandWidth[i];
		_flow_cost_rentcost[netNode_nums + 1][consumeNodeList[i]] = 0;
		_flow_cost_rentcost[consumeNodeList[i]][netNode_nums + 1] = 0;
	}

	// 将消费节点映射到网络节点
	std::vector<netNode_index> req_bandwidth_2_netNode(netNode_nums + 2, 0);
	for (int i = 0; i < consumeNode_nums; i++)
	{
		int idx = consumeNodeList[i];
		req_bandwidth_2_netNode[idx] = requireBandWidth[i];
	}
	// 将网络节点映射到消费节点
	std::vector<consumeNode_index> netNode_2_consumeNode(netNode_nums);
	for (int i = 0; i < consumeNode_nums; i++)
	{
		netNode_2_consumeNode[consumeNodeList[i]] = i;
	}
	// 找出出度带宽最大的满足要求点的集合
	int max_bandwidth_require = 0;
	for (int i = 0; i < consumeNode_nums; i++)
	{
		max_bandwidth_require += requireBandWidth[i];
	}
	req_bandwidth_2_netNode[netNode_nums + 1] = max_bandwidth_require;
	// 断开服务器节点间的通路
	for (int i = 0; i < assign_length; i++)
	{
		for (int j = 0; j < assign_length; j++)
		{
			if (j != i)
			{
				_flow_cost_bandwidth[assign_host_nodes[i]][assign_host_nodes[j]] = 0;
				_flow_cost_bandwidth[assign_host_nodes[j]][assign_host_nodes[i]] = 0;
			}
		}
	}
	int total_cost = 0;
	std::vector<std::vector<int>> link_list2;
	std::vector<int> path_one;
	int adj_count = 0;
	for (int i = 0; i < assign_length; i++)
	{
		adj_count += _flow_G_adj[assign_host_nodes[i]].size();
	}
	std::vector<std::vector<int>> all_path;
	std::vector<int> _total_cost(netNode_nums,0);
	while (req_bandwidth_2_netNode[netNode_nums + 1] > 0)
	{
		int _tmp_cost = 0;
		int _tmp_bw = 0;
		//clock_t start, finish;
		//start = clock();
		auto _tmp_ans = DFS_v(netNode_nums, netNode_nums + 1, _flow_G_adj, _flow_cost_rentcost, _flow_cost_bandwidth);
		//finish = clock();
		//std::cout << "DFS_v:" << (finish - start) << "ms" << std::endl;
		int _tmp_ans_len = _tmp_ans.size();
		if (_tmp_ans_len ==0)
		{
			int count=0;
			for (int i = 0; i < assign_length; i++)
			{
				
				int m = assign_host_nodes[i];
				int node_adj_leng = _flow_G_adj[m].size();
				for (int j = 0; j < node_adj_leng; j++)
				{
					
					int k = _flow_G_adj[m][j];
					if (_flow_cost_bandwidth[m][k] == 0)count++;
				}
				
			}
			
			//std::cout << "现在有"<<count <<"/"<< adj_count <<"条链路带宽为0"<< std::endl;
			if (count == adj_count)break;
		}

		
		//std::cout << _tmp_ans[0].back() << std::endl;

		
		for (int i = 0; i < _tmp_ans_len; i++)
		{
			int _tmpi_length = _tmp_ans[i].size();

			path_one.assign(_tmp_ans[i].begin() + 1, _tmp_ans[i].end() - 3);
			path_one.push_back(netNode_2_consumeNode[_tmp_ans[i][_tmpi_length - 4]]);
			path_one.push_back(_tmp_ans[i][_tmpi_length-2]);
			//放路径和带宽
			all_path.push_back(path_one);
			req_bandwidth_2_netNode[_tmp_ans[i][_tmpi_length-4]]-= _tmp_ans[i][_tmpi_length - 2];
			req_bandwidth_2_netNode[netNode_nums + 1] -= _tmp_ans[i][_tmpi_length - 2];
			total_cost += _tmp_ans[i].back();
			_total_cost[_tmp_ans[i][_tmpi_length - 4]] += _tmp_ans[i].back();
		}
	}
	std::vector<int> cost_v;
	bool Q[NET_NODE_MAXSIZE];
	if (req_bandwidth_2_netNode[netNode_nums + 1] == 0)
	{
		link_list2.clear();
		link_list2 = all_path;
	}
	else
	{
		std::vector<std::vector<int>>remain_path;
		memset(Q, false, sizeof(Q));
		for (int i = 0; i < consumeNode_nums; i++)
		{

			if (req_bandwidth_2_netNode[consumeNodeList[i]]!=0)
			{
				std::vector<int> remain;
				Q[consumeNodeList[i]] = true;
				remain.push_back(consumeNodeList[i]);
				remain.push_back(i);
				remain.push_back(requireBandWidth[i]);
				remain_path.push_back(remain);
				total_cost -= _total_cost[consumeNodeList[i]];
			}
		}
		int all_path_len = all_path.size();
		for (int i = 0; i < all_path_len; i++)
		{
			if (Q[all_path[i][all_path[i].size() - 3]])continue;
			link_list2.push_back(all_path[i]);
		}
		int remain_len = remain_path.size();
		for (int i = 0; i < remain_len; i++)
		{
			link_list2.push_back(remain_path[i]);
		}
	}
	int server_count = 0;
	int link_list2_len = link_list2.size();
	memset(Q, false, sizeof(Q));
	for (int i = 0; i < link_list2_len; i++)
	{
		if (!Q[link_list2[i][0]])
		{
			Q[link_list2[i][0]] = true;
			server_count++;
		}
	}
	total_cost += server_count*serverCost;
	cost_v.push_back(total_cost);
	link_list2.push_back(cost_v);
	//不符合不补了，直接返回INF
	/*if (req_bandwidth_2_netNode[netNode_nums + 1] == 0)
	{
		link_list2.clear();
		link_list2 = all_path;
		memset(Q, false, sizeof(Q));
		int server_count = 0;
		int link_list2_len = link_list2.size();
		for (int i = 0; i < link_list2_len; i++)
		{
			if (!Q[link_list2[i][0]])
			{
				Q[link_list2[i][0]] = true;
				server_count++;
			}
		}

		total_cost += server_count*serverCost;
		cost_v.push_back(total_cost);
		link_list2.push_back(cost_v);
	}
	else
	{
		total_cost =INF;
		cost_v.push_back(total_cost);
		link_list2.push_back(cost_v);
	}*/
	
	return link_list2;
}

std::vector<std::vector<int>> DFS_v(int v0, int tag, std::vector<std::vector<netNode_index>> &G_adj, std::vector<std::vector<netNode_index>> &rc, std::vector<std::vector<netNode_index>> &bw)
{
	int size = G_adj[v0].size();
	std::vector<std::vector<netNode_index>> path_all;
	std::vector<netNode_index> path_one;
	int Q[NET_NODE_MAXSIZE];
	bool vis[NET_NODE_MAXSIZE];
	int stack[NET_NODE_MAXSIZE];
	int top = -1;
	memset(vis, false, sizeof(vis));
	memset(Q, 0, sizeof(Q));
	for (int i = 0; i < consumeNode_nums; i++)
	{
		Q[consumeNodeList[i]] = 1;
	}
	for (int i = 0; i <size; i++)
	{
		top++;
		vis[G_adj[v0][i]] = true;
		stack[top] = G_adj[v0][i];
	}
	vis[v0] = true;
	path_one.push_back(v0);
	int /*count = 0,*/before=top;
	int depth = 0;
	while (top!=-1)
	{
		int out = stack[top];
		/*count = 0;
		for (int i = 0; i < netNode_nums; i++)
		{
			if (vis[i])count++;
		}*/
		if (before == top)depth++;
		else {
			depth = 0;
			before = top;
		}
		
		//if (before == top)count++;
		//else {
		//	count = 0; 
		//	before = top;
		//}
		/*std::cout <<"depth:"<<depth<< std::endl;
		for (int i = 0; i <= top; i++)
		{
			std::cout << stack[i] <<" ";
		}
		std::cout << std::endl;
		std::cout << out<< "出站 "<< std::endl;*/
		top--;
		if (depth == 8)//控制在图中的最多跳数
		{
			depth = 0;
			rc[out][path_one.back()] = INF;
			rc[path_one.back()][out] = INF;
			bw[out][path_one.back()] = 0;
			bw[path_one.back()][out] = 0;
			path_one.clear();
			path_one.push_back(v0);
			continue;
		}
		//std::cout <<"top:"<< top << std::endl;
		//path_one.push_back(out);
		
		//std::cout << std::endl;
		if (out==tag) {
			path_one.push_back(out);
			int len = path_one.size();
			if (len <= 2) {
				path_one.clear();
				path_one.push_back(v0);
				continue;
			}
			/*for (int i = 0; i < path_one.size(); i++)
			{
				std::cout << path_one[i] << "->";
			}
			std::cout << std::endl;*/
			int min = INF;
			for (int i = 1; i < len-1; i++)
			{
				if (min>bw[path_one[i]][path_one[i+1]])
				{
					min = bw[path_one[i]][path_one[i + 1]];
				}
			}
			for (int i = 1; i < len-1; i++)
			{
				bw[path_one[i]][path_one[i + 1]] -= min;
				bw[path_one[i + 1]][path_one[i]] -= min;
			}
			//std::cout <<" bw:"<< min;
			int cost = 0;
			for (int i = 1; i < len-1; i++)
			{
					cost+= min*rc[path_one[i]][path_one[i + 1]];
			}
			//std::cout << " cost:" << cost << std::endl;
			path_one.push_back(min);
			path_one.push_back(cost);
			path_all.push_back(path_one);
			path_one.clear();
			path_one.push_back(v0);
			continue;
		}
		if (!vis[out])
		{
			vis[out] = true;
		}
		
		int min = INF;
		int min_idx;
		int flow = -1;
		int adj_len = G_adj[out].size();
		bool flag = false;
		for (int k = 0; k < adj_len; k++)
		{
			//std::cout << G_adj[out][k] << std::endl;
			if (bw[out][G_adj[out][k]]==0)
				continue;
			
			if (!vis[G_adj[out][k]] && (min>rc[out][G_adj[out][k]]))
			{

				min = rc[out][G_adj[out][k]];
				flow = bw[out][G_adj[out][k]];
			}
		}
		for (int k = 0; k < adj_len; k++)
		{
			if (bw[out][G_adj[out][k]] == 0)
				continue;
			if (!vis[G_adj[out][k]]&&min == rc[out][G_adj[out][k]])
			{
				if (Q[G_adj[out][k]]&&bw[G_adj[out][k]][tag])
				{
					min_idx = G_adj[out][k];
					break;
				}
				if(bw[out][G_adj[out][k]]>=flow)
				{
					min_idx = G_adj[out][k];
					flow = bw[out][G_adj[out][k]];
				}
			}
		}
		//std::cout << "min:" << min << std::endl;
		if (min != INF) {
			path_one.push_back(out);
			top++;
			stack[top] = min_idx;
			//std::cout << min_idx << "进站 " << std::endl;
		}
		else {
			rc[out][path_one.back()] = INF;
			rc[path_one.back()][out] = INF;
			bw[out][path_one.back()] = 0;
			bw[path_one.back()][out] = 0;
			path_one.clear();
			path_one.push_back(v0);
		}
		
	}
	return path_all;
}

std::vector<std::vector<int>> DFS_v_more(int v0, int tag, std::vector<std::vector<netNode_index>> &G_adj, std::vector<std::vector<netNode_index>> &rc, std::vector<std::vector<netNode_index>> &bw)
{
	int size = G_adj[v0].size();
	std::vector<std::vector<netNode_index>> path_all;
	std::vector<netNode_index> path_one;
	int Q[NET_NODE_MAXSIZE];
	bool vis[NET_NODE_MAXSIZE];
	int stack[NET_NODE_MAXSIZE];
	int top = -1;
	memset(vis, false, sizeof(vis));
	memset(Q, 0, sizeof(Q));
	for (int i = 0; i < consumeNode_nums; i++)
	{
		Q[consumeNodeList[i]] = 1;
	}
	for (int i = 0; i <size; i++)
	{
		top++;
		vis[G_adj[v0][i]] = true;
		stack[top] = G_adj[v0][i];
	}
	vis[v0] = true;
	path_one.push_back(v0);
	int count = 0, before = top;
	
	while (top != -1)
	{
		int out = stack[top];
		count = 0;
		for (int i = 0; i < netNode_nums; i++)
		{
			if (vis[i])count++;
		}

		
		//std::cout <<"count:"<<count<< std::endl;
		/*for (int i = 0; i <= top; i++)
		{
		std::cout << stack[i] <<" ";
		}
		std::cout << std::endl;
		std::cout << out<< "出站 "<< std::endl;*/
		top--;
		//std::cout <<"top:"<< top << std::endl;
		//path_one.push_back(out);

		//std::cout << std::endl;
		if (out == tag) {
			path_one.push_back(out);
			int len = path_one.size();
			if (len <= 2) {
				path_one.clear();
				path_one.push_back(v0);
				continue;
			}
			/*for (int i = 0; i < path_one.size(); i++)
			{
			std::cout << path_one[i] << "->";
			}
			std::cout << std::endl;*/
			int min = INF;
			for (int i = 1; i < len - 1; i++)
			{
				if (min>bw[path_one[i]][path_one[i + 1]])
				{
					min = bw[path_one[i]][path_one[i + 1]];
				}
			}
			for (int i = 1; i < len - 1; i++)
			{
				bw[path_one[i]][path_one[i + 1]] -= min;
				bw[path_one[i + 1]][path_one[i]] -= min;
			}
			//std::cout <<" bw:"<< min;
			int cost = 0;
			for (int i = 1; i < len - 1; i++)
			{
				cost += min*rc[path_one[i]][path_one[i + 1]];
			}
			//std::cout << " cost:" << cost << std::endl;
			path_one.push_back(min);
			path_one.push_back(cost);
			path_all.push_back(path_one);
			path_one.clear();
			path_one.push_back(v0);
			continue;
		}
		if (!vis[out])
		{
			vis[out] = true;
		}

		int min = INF;
		int min_idx;
		int flow = -1;
		int adj_len = G_adj[out].size();
		bool flag = false;
		for (int k = 0; k < adj_len; k++)
		{
			//std::cout << G_adj[out][k] << std::endl;
			if (bw[out][G_adj[out][k]] == 0)
				continue;

			if (!vis[G_adj[out][k]] && (min>rc[out][G_adj[out][k]]))
			{

				min = rc[out][G_adj[out][k]];
				flow = bw[out][G_adj[out][k]];
			}
		}
		for (int k = 0; k < adj_len; k++)
		{
			if (bw[out][G_adj[out][k]] == 0)
				continue;
			if (!vis[G_adj[out][k]] && min == rc[out][G_adj[out][k]])
			{
				if (Q[G_adj[out][k]] && bw[G_adj[out][k]][tag])
				{
					min_idx = G_adj[out][k];
					break;
				}
				if (bw[out][G_adj[out][k]] >= flow)
				{
					min_idx = G_adj[out][k];
					flow = bw[out][G_adj[out][k]];
				}
			}
		}
		//std::cout << "min:" << min << std::endl;
		if (min != INF) {
			path_one.push_back(out);
			top++;
			stack[top] = min_idx;
		}
		else {
			int  out_length = G_adj[out].size();
			for (int i = 0; i < out_length; i++)
			{
				rc[out][G_adj[out][i]] = INF;
				rc[G_adj[out][i]][out] = INF;
				bw[out][G_adj[out][i]] = 0;
				bw[G_adj[out][i]][out] = 0;
			}
			path_one.clear();
			path_one.push_back(v0);
		}

	}
	return path_all;
}