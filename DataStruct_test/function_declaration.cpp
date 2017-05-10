#include "variable_declaration.h"

// 网络节点拓扑初始化
void Init_netNode(netNode_index (*bw)[NET_NODE_MAXSIZE],
	netNode_index (*rc)[NET_NODE_MAXSIZE])
{
	for (int i = 0; i < NET_NODE_MAXSIZE; i++)
	{
		for (int j = 0; j < NET_NODE_MAXSIZE; j++)
		{
			bw[i][j] = INF;
			rc[i][j] = INF;
		}
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