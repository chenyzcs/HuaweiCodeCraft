#include "variable_declaration.h"

int netNode_nums = 10;						// 网络节点数量
int netLink_nums = 10;						// 网络链路数量
int consumeNode_nums = 10;					// 消费节点数量
int serverCost = 10;						// 部署服务器成

netNode_index netNode_MGraph_BandWidth[NET_NODE_MAXSIZE][NET_NODE_MAXSIZE];		// 网络节点的邻接矩阵表示==>边弧带宽容量
netNode_index netNode_MGraph_RentCost[NET_NODE_MAXSIZE][NET_NODE_MAXSIZE];		// 网络节点的邻接矩阵表示==>边弧带宽租金

consumeNode_index consumeNodeList[CONSUME_NODE_MAXSIZE];			// 消费节点直连点
require_bandwidth requireBandWidth[CONSUME_NODE_MAXSIZE];		// 消费节点带宽需求