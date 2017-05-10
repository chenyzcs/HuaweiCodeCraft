#include "variable_declaration.h"

int netLink_nums;						// 网络链路数量
int consumeNode_nums;					// 消费节点数量
int serverCost;							// 部署服务器成本


netNode_index netNode_MGraph_BandWidth[NET_NODE_MAXSIZE][NET_NODE_MAXSIZE];			// 网络节点的邻接矩阵表示==>边弧带宽容量
netNode_index netNode_MGraph_RentCost[NET_NODE_MAXSIZE][NET_NODE_MAXSIZE];			// 网络节点的邻接矩阵表示==>边弧带宽租金
netNode_index netNode_MGraph_BandWidth_Left[NET_NODE_MAXSIZE][NET_NODE_MAXSIZE];	// 网络节点的邻接矩阵表示==>边弧剩余带宽

std::vector<std::vector<netNode_index>> Graph_Adj(NET_NODE_MAXSIZE);

consumeNode_index consumeNodeList[CONSUME_NODE_MAXSIZE];			// 消费节点直连点
require_bandwidth requireBandWidth[CONSUME_NODE_MAXSIZE];			// 消费节点带宽需求
require_bandwidth requireBandWidth_after_merge[CONSUME_NODE_MAXSIZE];// 合并后消费节点带宽