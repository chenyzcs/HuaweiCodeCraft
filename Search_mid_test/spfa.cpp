#include "variable_declaration.h"


//int n, ans;
//int cap[Max][Max], pre[Max];
//int cost[Max][Max], dis[Max];
//int que[Max];



std::vector<std::vector<int>> spfa(int v0, int tag, std::vector<std::vector<netNode_index>> &rc, std::vector<std::vector<netNode_index>> &bw) {                  //  源点为0，汇点为n。  

	std::vector<int> dis(netNode_nums+2, INF);
	std::vector<bool> vis(netNode_nums+2, false);
	//std::queue<int> que;
	int que[NET_NODE_MAXSIZE];
	int head = 0;
	int rear = 0;
	std::vector<int> pre(netNode_nums+2, -1);
	std::vector<int> path(netNode_nums+2, -1);

	std::vector<int> _ret;
	std::vector<std::vector<int>> _ans;
	std::vector<int> _tmp_loc;

	dis[v0] = 0;// dis 表示 最小 花费  
	//que.push(v0);
	que[rear] = v0;
	rear++;

	vis[v0] = true;

	while (head==rear) {      //  循环队列。  
		int u = que[head];
		//que.pop();
		head++;
		for (int i = 0; i < netNode_nums+2; i++)
			if (bw[u][i] && dis[i] > dis[u] + rc[u][i]) {    //  存在路径，且权值变小。  
				dis[i] = dis[u] + rc[u][i];
				pre[i] = u;
				//path[i] = i;
				if (!vis[i]) {
					vis[i] = true;
					//que.push(i);
					que[rear] = i;
					rear++;
				}
			}
		vis[u] = false;
	}
	int _tmp_p = tag;
	_ret.push_back(tag);
	while (pre[_tmp_p] != v0 && pre[_tmp_p] != -1)
	{
		_ret.push_back(pre[_tmp_p]);
		_tmp_p = pre[_tmp_p];
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
	dis.push_back(low);
	_ans.push_back(dis);
	_ans.push_back(_ret);

	return _ans;
}

void end(int v0, int t, std::vector<std::vector<netNode_index>> &rc, std::vector<std::vector<netNode_index>> &bw)
{
	/*int i, sum = INF;
	for (i = t; i != v0; i = pre[i])
		sum = min(sum, bw[pre[i]][i]);
	for (i = t; i != v0; i = pre[i]) {
		bw[pre[i]][i] -= sum;
		bw[i][pre[i]] += sum;
		ans += rc[pre[i]][i] * sum;
	}*/
}


std::vector<std::vector<int>> spfa_adj(int v0, int tag, std::vector<std::vector<netNode_index>> &G_adj,std::vector<std::vector<netNode_index>> &rc, std::vector<std::vector<netNode_index>> &bw) {
	std::vector<int> dis(netNode_nums + 2, INF);
	std::vector<bool> vis(netNode_nums + 2, false);
	//std::queue<int> que;
	int que[NET_NODE_MAXSIZE];
	int head = 0;
	int rear = 0;
	std::vector<int> pre(netNode_nums + 2, -1);
	std::vector<int> path(netNode_nums + 2, -1);

	std::vector<int> _ret;
	std::vector<std::vector<int>> _ans;
	std::vector<int> _tmp_loc;

	dis[v0] = 0;// dis 表示 最小 花费  
	que[rear] = v0;
	rear++;
	vis[v0] = true;

	while (head == rear) {      //  循环队列。  
		int u = que[head];
		head++;
		//for (int i = 0; i < netNode_nums + 2; i++)
		for (int j = 0; j < G_adj[u].size(); j++)
		{
			int i = G_adj[u][j];
			if (bw[u][i] && dis[i] > dis[u] + rc[u][i]) {    //  存在路径，且权值变小。  
				dis[i] = dis[u] + rc[u][i];
				pre[i] = u;
				//path[i] = i;
				if (!vis[i]) {
					vis[i] = true;
					//que.push(i);
					que[rear] = i;
					rear++;
				}
			}
		}
		vis[u] = false;
	}
	int _tmp_p = tag;
	_ret.push_back(tag);
	while (pre[_tmp_p] != v0 && pre[_tmp_p] != -1)
	{
		_ret.push_back(pre[_tmp_p]);
		_tmp_p = pre[_tmp_p];
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
	dis.push_back(low);
	_ans.push_back(dis);
	_ans.push_back(_ret);

	return _ans;
}
