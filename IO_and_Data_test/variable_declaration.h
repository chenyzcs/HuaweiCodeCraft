#ifndef VARIABLE_DECLARATION_H
#define VARIABLE_DECLARATION_H

// 常量定义
#define INF 0xFFFF					// 邻接矩阵无穷表示
#define NET_NODE_MAXSIZE 1000		// 最大网络节点个数
#define CONSUME_NODE_MAXSIZE 500	// 最大消费节点个数
#define LINK_MAXSIZE 20				// 网络节点最大链路个数

extern int netNode_nums;			// 网络节点数量
extern int netLink_nums;			// 网络链路数量
extern int consumeNode_nums;		// 消费节点数量
extern int serverCost;				// 部署服务器成本

typedef int netNode_index;		// 网络节点编号
typedef int arc_bandwidth;		// 每条边的带宽
typedef int arc_rentcost;		// 每条边的租金
typedef int consumeNode_index;	// 消费节点编号
typedef int require_bandwidth;	// 消费节点所需带宽


// 网络节点拓扑图
extern netNode_index netNode_MGraph_BandWidth[NET_NODE_MAXSIZE][NET_NODE_MAXSIZE];		// 网络节点的邻接矩阵表示==>边弧带宽容量
extern netNode_index netNode_MGraph_RentCost[NET_NODE_MAXSIZE][NET_NODE_MAXSIZE];		// 网络节点的邻接矩阵表示==>边弧带宽租金

// 消费节点
extern consumeNode_index consumeNodeList[CONSUME_NODE_MAXSIZE];			// 消费节点直连点
extern require_bandwidth requireBandWidth[CONSUME_NODE_MAXSIZE];		// 消费节点带宽需求

// 网络节点初始化==>初始化1000*1000的网络节点图
extern void Init_netNode(netNode_index (*bw)[NET_NODE_MAXSIZE], 
	netNode_index (*rc)[NET_NODE_MAXSIZE]);		// 

// 消费节点初始化==>初始化500*500的消费节点图
extern void Init_consumeNode(consumeNode_index *ci,
	require_bandwidth *cb);

#endif // !VARIABLE_DECLARATION_H
