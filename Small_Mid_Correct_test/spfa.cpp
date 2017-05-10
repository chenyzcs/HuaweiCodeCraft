#include "variable_declaration.h"


//int n, ans;
//int cap[Max][Max], pre[Max];
//int cost[Max][Max], dis[Max];
//int que[Max];



std::vector<std::vector<int>> spfa(int v0, int tag, std::vector<std::vector<netNode_index>> &rc, std::vector<std::vector<netNode_index>> &bw) {                  //  源点为0，汇点为n。  

	std::vector<int> dis(netNode_nums+2, INF);
	std::vector<bool> vis(netNode_nums+2, false);
	std::queue<int> que;
	std::vector<int> pre(netNode_nums+2, -1);
	std::vector<int> path(netNode_nums+2, -1);

	std::vector<int> _ret;
	std::vector<std::vector<int>> _ans;
	std::vector<int> _tmp_loc;

	dis[v0] = 0;// dis 表示 最小 花费  
	que.push(v0);
	vis[v0] = true;

	while (!que.empty()) {      //  循环队列。  
		int u = que.front();
		que.pop();
		for (int i = 0; i < netNode_nums+2; i++)
			if (bw[u][i] && dis[i] > dis[u] + rc[u][i]) {    //  存在路径，且权值变小。  
				dis[i] = dis[u] + rc[u][i];
				pre[i] = u;
				//path[i] = i;
				if (!vis[i]) {
					vis[i] = true;
					que.push(i);
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

const int MAXSIZE = 800;
std::vector<std::vector<int>> spfa_adj(int v0, int tag, std::vector<std::vector<netNode_index>> &G_adj,std::vector<std::vector<netNode_index>> &rc, std::vector<std::vector<netNode_index>> &bw) {
	std::vector<int> dis(netNode_nums + 2);
	bool vis[NET_NODE_MAXSIZE];
	int pre[NET_NODE_MAXSIZE];
	//std::vector<int> path(netNode_nums + 2);

	for (int i = 0; i < netNode_nums + 2; i++)
	{
		dis[i] = INF;
	}
	memset(vis, false,sizeof(vis));
	memset(pre, -1, sizeof(pre));
	//std::queue<int> que;
	
	int que[MAXSIZE];
	std::vector<int> _ret;
	std::vector<std::vector<int>> _ans;
	//int head = 200, rear = 200;
	int head = 0, rear = 0;
	dis[v0] = 0;// dis 表示 最小 花费  
	
	que[rear] = v0;
	rear = (rear + 1) % MAXSIZE;
	vis[v0] = true;
	int sum = 0;
	int len = 1;
	while(head!=rear){
	      //  循环队列。  
		
		int u = que[head];
		//sum -= dis[u];
		head = (head + 1) % MAXSIZE;
		len--;
		
		/*if (dis[u] * len > sum) {
			que[rear] = u;
			
			sum += dis[u];

			rear = (rear + 1) % MAXSIZE;
			len++;
			continue;

		}*/
		
		
		int n = G_adj[u].size();
		if (dis[u] >= dis[tag]) continue;
		for (int j = 0; j < n; j++)
		{
			int i = G_adj[u][j];
			
			if (bw[u][i] && dis[i] > dis[u] + rc[u][i]) {    //  存在路径，且权值变小。  
				dis[i] = dis[u] + rc[u][i];
				pre[i] = u;
				
				if (!vis[i]) {
					vis[i] = true;
					//sum += dis[i];
					//if (dis[i] < dis[que[head]]) {
					//	//head--;
					//	head = (head - 1 + MAXSIZE) % MAXSIZE;
					//	len++;
					//	que[head] = i;
					//}
					//else {
						
						que[rear] = i;
						rear = (rear + 1) % MAXSIZE;
/*						len++;
					}	*/			
				}
			}
		}
		if (vis[tag]) break;
		vis[u] = false;
	}
	//int low = INF;
	int _tmp_p = tag;
	_ret.push_back(tag);
	//int k = tag;
	//if (dis[v0] == INF) _ret.push_back(v0);
	//else {
	//	int next;
	//	while (k != v0) {
	//		next = pre[k];
	//		_ret.push_back(next);
	//		//if (bw[k][next] < low) {
	//		//	low = bw[k][next];
	//		//	//cout << min<<"   " << bw[k][next] << endl;
	//		//}
	//		k = next;
	//	}
	//}
	while (pre[_tmp_p] != v0 && pre[_tmp_p] != -1)
	{
		_ret.push_back(pre[_tmp_p]);
		_tmp_p = pre[_tmp_p];
	}
	_ret.push_back(v0);
	int retSize = _ret.size() ;
	for (int i = 0; i < retSize/ 2; i++)
	{
		_ret[i] = _ret[i] ^ _ret[retSize - i - 1];
		_ret[retSize - i - 1] = _ret[retSize - i - 1] ^ _ret[i];
		_ret[i] = _ret[i] ^ _ret[retSize - i - 1];
	}
	int low = INF;
	for (int i = 0; i < retSize; i++)
	{
		if (i + 1<retSize)
		{
			if (bw[_ret[i]][_ret[i + 1]] < low)
				low = bw[_ret[i]][_ret[i + 1]];
		}
	}
	dis.push_back(low);
	_ans.push_back(dis);
	_ans.push_back(_ret);

	return _ans;

	/////////////////////////////

	//std::vector<int> dis(netNode_nums + 2, INF);

	//std::vector<bool> vis(netNode_nums + 2, false);

	//std::queue<int> que;

	//std::vector<int> pre(netNode_nums + 2, -1);

	//std::vector<int> path(netNode_nums + 2, -1);



	//std::vector<int> _ret;

	//std::vector<std::vector<int>> _ans;

	//std::vector<int> _tmp_loc;



	//dis[v0] = 0;// dis ±íÊŸ ×îÐ¡ »š·Ñ  

	//que.push(v0);

	//vis[v0] = true;







	//while (!que.empty()) {      //  Ñ­»·¶ÓÁÐ¡£  

	//	int u = que.front();



	//	que.pop();

	//	//for (int i = 0; i < netNode_nums + 2; i++)

	//	//std::cout << "G_adj[u].size(): " << G_adj[u].size() << std::endl;

	//	for (int j = 0; j < G_adj[u].size(); j++)

	//	{

	//		int i = G_adj[u][j];



	//		if (bw[u][i] != 0 && dis[i] > dis[u] + rc[u][i]) {    //  ŽæÔÚÂ·Ÿ¶£¬ÇÒÈšÖµ±äÐ¡¡£  



	//			dis[i] = dis[u] + rc[u][i];

	//			//std::cout << "dis[i]: " << dis[i] << std::endl;

	//			pre[i] = u;

	//			//path[i] = i;

	//			if (!vis[i]) {

	//				vis[i] = true;

	//				que.push(i);

	//			}

	//		}

	//	}

	//	vis[u] = false;

	//}

	//int _tmp_p = tag;

	//_ret.push_back(tag);

	////std::cout << "tag: " << _tmp_p << std::endl;

	//while (pre[_tmp_p] != v0 && pre[_tmp_p] != -1)

	//{

	//	_ret.push_back(pre[_tmp_p]);

	//	_tmp_p = pre[_tmp_p];

	//}

	//_ret.push_back(v0);

	////std::cout << "v0: " << v0 << std::endl;

	//for (int i = 0; i < _ret.size() / 2; i++)

	//{

	//	_ret[i] = _ret[i] ^ _ret[_ret.size() - i - 1];

	//	_ret[_ret.size() - i - 1] = _ret[_ret.size() - i - 1] ^ _ret[i];

	//	_ret[i] = _ret[i] ^ _ret[_ret.size() - i - 1];

	//}



	//int low = INF;

	//for (int i = 0; i < _ret.size(); i++)

	//{

	//	if (i + 1<_ret.size())

	//	{

	//		if (bw[_ret[i]][_ret[i + 1]] < low)

	//			low = bw[_ret[i]][_ret[i + 1]];

	//	}

	//}

	////std::cout << "low " << low << std::endl; 

	////std::cout << dis[tag] << std::endl;

	//dis.push_back(low);

	//_ans.push_back(dis);

	//_ans.push_back(_ret);



	//return _ans;
}
