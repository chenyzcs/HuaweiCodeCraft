#include "variable_declaration.h"

struct EDGE
{
	int cost, cap, v;
	int next, re;
}edge[INF], edge2[INF], edge3[INF];
int head[NET_NODE_MAXSIZE], head2[NET_NODE_MAXSIZE];
long long int e, e2;
//int ans, cost, src, des, n;

int vis[NET_NODE_MAXSIZE];

int cost = 0 , tag;
int ans;
int flow;

void edge_init()
{
	memset(head, -1, sizeof(head));
	memset(head2, -1, sizeof(head2));
	 e = 0;
	 e2 = 0;
	ans = cost = 0;
}

void add_edges(int u, int v, int cap, int cost)
{
	edge[e].v = v;
	edge[e].cap = cap;
	edge[e].cost = cost;
	edge[e].re = e + 1;
	edge[e].next = head[u];
	head[u] = e++;
	edge[e].v = u;
	edge[e].cap = 0;
	edge[e].cost = -cost;
	edge[e].re = e - 1;
	edge[e].next = head[v];
	head[v] = e++;
	//////
	edge2[e2].v = v;
	edge2[e2].cap = cap;
	edge2[e2].cost = cost;
	edge2[e2].re = e2 + 1;
	edge2[e2].next = head2[u];
	head2[u] = e2++;
	edge2[e2].v = u;
	edge2[e2].cap = 0;
	edge2[e2].cost = -cost;
	edge2[e2].re = e2 - 1;
	edge2[e2].next = head2[v];
	head2[v] = e2++;
	//std::cout << e << std::endl;
}
//void add_edges2(int u, int v, int cap, int cost)
//{
//
//}

int aug(int v0, int f, std::vector<std::vector<netNode_index>> &G_adj, std::vector<std::vector<netNode_index>> &rc, std::vector<std::vector<netNode_index>> &bw)
{
	if (v0 == tag)
	{
		ans += cost * f;
		flow += f;
		return f;
	}
	vis[v0] = 1;
	int tmp = f;
	for (int i = head[v0]; i != -1; i = edge[i].next)
		if (edge[i].cap && !edge[i].cost && !vis[edge[i].v])
		{
			int delta = aug(edge[i].v, tmp < edge[i].cap ? tmp : edge[i].cap, G_adj, rc, bw);
			edge[i].cap -= delta;
			edge[edge[i].re].cap += delta;
			tmp -= delta;
			if (!tmp) return f;
		}
	return f - tmp;
}

bool modlabel(std::vector<std::vector<netNode_index>> &G_adj, std::vector<std::vector<netNode_index>> &rc, std::vector<std::vector<netNode_index>> &bw)
{
	int delta = INF;
	for (int u = 0; u < netNode_nums+2; u++)
		if (vis[u])
			for (int i = head[u]; i != -1; i = edge[i].next)
				if (edge[i].cap && !vis[edge[i].v] && edge[i].cost < delta) delta = edge[i].cost;
	if (delta == INF) return false;
	for (int u = 0; u < netNode_nums + 2; u++)
		if (vis[u])
			for (int i = head[u]; i != -1; i = edge[i].next)
				edge[i].cost -= delta, edge[edge[i].re].cost += delta;
	cost += delta;
	return true;
}

void dfs()
{
	bool visit[NET_NODE_MAXSIZE];
	memset(visit, false, sizeof(visit));
	visit[netNode_nums] = true;
	int pre[NET_NODE_MAXSIZE];
	
	/*pre[netNode_nums] = -1;
	std::queue<int> que;*/
	

	std::vector<int> link;
	std::vector<int> stack;
	

	bool tag_flag = false;
	std::vector<int> stack_rev;
	std::vector<int> bw;
	//while (stack.size())
	//{
	//	
	//	int top = stack.back();
	//	stack.pop_back();
	//	stack_rev.push_back(top);
	//	
	//	//stack.pop_back();
	//	int min_flow = INF;
	//	

	//	for (int i = head2[top]; i != -1; i = edge2[i].next)
	//	{
	//		if (edge2[i].cap>0)
	//		{
	//			if (edge2[i].cap < min_flow)
	//			{
	//				min_flow = edge2[i].cap;
	//			}
	//			if (edge2[i].v == netNode_nums + 1)
	//			{
	//				tag_flag = true;
	//			}
	//			link.push_back(edge2[i].v);
	//			stack.push_back(edge2[i].v);
	//			break;
	//		}
	//	}
	//	if (tag_flag)
	//	{
	//		while (stack_rev.size() - 1)
	//		{
	//			int end = stack_rev.back();
	//			stack_rev.pop_back();
	//			int pre = stack_rev.back();
	//			for (int i = head[pre]; i != -1; i = edge2[i].next)
	//				if (edge2[i].v==end)
	//				{
	//					edge2[i].cap -= min_flow;
	//				}
	//		}
	//		tag_flag = false;
	//	}
	//}

	std::vector<std::vector<int>> all_path;
	int min_flow = INF;
	std::vector<int> server_arr;
	bool Q[NET_NODE_MAXSIZE];
	memset(Q, false, sizeof(Q));
	visit[netNode_nums] = true;
	for (int i = head2[netNode_nums]; i!=-1; i=edge2[i].next)
	{
		if (!Q[edge2[i].v])
		{
			server_arr.push_back(edge2[i].v);
			Q[edge2[i].v] = true;
			pre[edge2[i].v] = -1;
		}
	}
	int idx = 0;
	int server_count = server_arr.size();
	stack.push_back(server_arr[idx]);
	while (stack.size())
	{
		int u = stack.back();
		visit[u] = true;
		stack.pop_back();
		
		if (u==netNode_nums+1)
		{

			int next = pre[u];
			while (next!=-1)
			{
				int k = head2[next];
				while (k % 2 != 0)
				{
					k = edge2[k].next;
				}
				for (; k!=-1; )
				{
					if (edge2[k].v==u)
					{
						edge2[k].cap -= min_flow;
						//break;
					}
					k = edge2[k].next;
					if (k==-1)
					{
						break;
					}
					while (k%2!=0)
					{
						k = edge2[k].next;
					}
				}
				u = next;
				next = pre[next];
			}
			stack.push_back(server_arr[idx]);
			bw.push_back(min_flow);
			min_flow = INF;
			all_path.push_back(link);
			link.clear();
			std::cout << "--------------new----------------" << std::endl;
			memset(visit, false, sizeof(visit));
			visit[netNode_nums] = true;
			continue;
		}
		link.push_back(u);
		

		int i = head2[u];
		std::cout << "-------------------" << std::endl;
		int count = 0;
		while (i!=-1) {
			if (i%2==0)
			{
				std::cout << u << "->" << edge2[i].v << " cap:" << edge2[i].cap << " visited:" << visit[edge2[i].v] << std::endl;
				if (!Q[edge2[i].v]&&!visit[edge2[i].v] && edge2[i].cap > 0)
				{
					if (min_flow > edge2[i].cap)
					{
						min_flow = edge2[i].cap;
					}
					pre[edge2[i].v] = u;
					stack.push_back(edge2[i].v);
					count++;
					break;
				}
				i = edge2[i].next;			
			}
			else
			{
				std::cout << u << "->" << edge2[i].v << " cap:" << edge2[i].cap << " visited:" << visit[edge2[i].v] << std::endl;
				i = edge2[i].next; 
			}
			
		}
		if (count) { 
			count = 0;
			continue; 
		}
		if (pre[u] == -1) {
			idx++;
			if (idx==server_count)
			{
				break;
			}
			stack.push_back(server_arr[idx]);
			memset(visit, false, sizeof(visit));
			visit[netNode_nums] = true;
			link.clear();
		}
		else
		{
			//memset(visit, false, sizeof(visit));
			visit[u] = true;
			visit[netNode_nums] = true;
			link.pop_back();
			link.pop_back();
			stack.push_back(pre[u]);
		}
		
	}

	/*for (int u = 0; u < netNode_nums + 2; u++)
	{
		link.push_back(u);
		for (int i = head2[u]; i != -1; i = edge2[i].next)
		{
			if (edge2[i].cap && !visit[edge2[i].v])
			{
				link.push_back(edge2[i].v);
				visit[edge2[i].v] = true;
			}
		}
		if (visit[netNode_nums+1])
		{
			visit[netNode_nums + 1] = false;
		}
	}*/



}

int costflow(std::vector<std::vector<netNode_index>> &G_adj, std::vector<std::vector<netNode_index>> &rc, std::vector<std::vector<netNode_index>> &bw, int max_flow)
{
	
	edge_init();
	int len = 0;
	for (int i = 0; i < G_adj.size(); i++)
	{
		len += G_adj[i].size();
	}
	//std::cout << len << std::endl;
	for (int i = 0; i < G_adj.size(); i++)
	{
		for (int j = 0; j < G_adj[i].size(); j++)
		{
			add_edges(i, G_adj[i][j], bw[i][G_adj[i][j]], rc[i][G_adj[i][j]]);
			//add_edges(G_adj[i][j], i, bw[G_adj[i][j]][i], rc[G_adj[i][j]][i]);
		}
	}
	//std::cout << e << std::endl;
	tag = netNode_nums + 1;
	do
	{
		do
		{
			memset(vis, 0, sizeof(vis));
		} while (aug(netNode_nums, INF,G_adj, rc, bw));
	} while (modlabel(G_adj, rc, bw));
	//std::cout << ans << std::endl;

	for (int u = 0; u < netNode_nums + 2; u++)
	{
		for (int i = head[u]; i != -1; i = edge[i].next)
		{
			//edge3[i].cost = edge2[i].cost;// - edge[i].cost;
			edge2[i].cap =  edge[i].cap-edge2[i].cap ;
			//edge2[edge2[i].re].cost = edge2[edge2[i].re].cost;// -edge[edge[i].re].cost;
			edge2[edge2[i].re].cap =   edge[edge[i].re].cap-edge2[edge2[i].re].cap;
		}
	}
	dfs();
		
	if (flow < max_flow)
	{
		std::cout << "INF" << std::endl;
		return INF;
	}
	else
	{
		return ans;
	}
}