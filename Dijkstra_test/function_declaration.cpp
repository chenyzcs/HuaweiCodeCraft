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