#ifndef VARIABLE_DECLARATION_H
#define VARIABLE_DECLARATION_H

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <numeric>
#include <math.h>
#include <time.h>
#include <queue>
//#include <limits>
#include <functional>
#include <fstream>
//#include <hash_map>

// 常量定义
#define INF 0xFFFFFF					// 邻接矩阵无穷表示
#define NET_NODE_MAXSIZE 1000		// 最大网络节点个数
#define CONSUME_NODE_MAXSIZE 500	// 最大消费节点个数
#define LINK_MAXSIZE 20				// 网络节点最大链路个数
#define min(a,b) ((a)>(b))?(b):(a)

extern int netNode_nums;			// 网络节点数量
extern int netLink_nums;			// 网络链路数量
extern int consumeNode_nums;		// 消费节点数量
extern int serverCost;				// 部署服务器成本

extern std::string result;




typedef int netNode_index;		// 网络节点编号
typedef int arc_bandwidth;		// 每条边的带宽
typedef int arc_rentcost;		// 每条边的租金
typedef int consumeNode_index;	// 消费节点编号
typedef int require_bandwidth;	// 消费节点所需带宽


// 网络节点拓扑图
extern netNode_index netNode_MGraph_BandWidth[NET_NODE_MAXSIZE][NET_NODE_MAXSIZE];		// 网络节点的邻接矩阵表示==>边弧带宽容量
extern netNode_index netNode_MGraph_RentCost[NET_NODE_MAXSIZE][NET_NODE_MAXSIZE];		// 网络节点的邻接矩阵表示==>边弧带宽租金
extern netNode_index netNode_MGraph_BandWidth_Left[NET_NODE_MAXSIZE][NET_NODE_MAXSIZE];	// 网络节点的邻接矩阵表示==>边弧剩余带宽

// 图邻接表表示
extern std::vector<std::vector<netNode_index>> Graph_Adj;

// 更新拓扑
extern int server_Num;				// 拓扑中服务器个数
extern std::vector<std::vector<netNode_index>> netNode_MGraph_BandWidth_Left_vec;		// 网络节点各链路剩余带宽
extern std::vector<consumeNode_index> consumeNodeList_vec;
// 消费节点
extern consumeNode_index consumeNodeList[CONSUME_NODE_MAXSIZE];			// 消费节点直连点
extern require_bandwidth requireBandWidth[CONSUME_NODE_MAXSIZE];		// 消费节点带宽需求
extern require_bandwidth requireBandWidth_after_merge[CONSUME_NODE_MAXSIZE];

// 官方接口
extern void read_data(char *topo[NET_NODE_MAXSIZE], int line_num);
// 网络节点初始化==>初始化1000*1000的网络节点图
extern void Init_netNode(netNode_index (*bw)[NET_NODE_MAXSIZE], netNode_index (*rc)[NET_NODE_MAXSIZE]);		

// 初始化每条链路剩余带宽
extern void Init_netNode_bandWidth_left(std::vector<std::vector<netNode_index>> &bdl);

// 消费节点初始化==>初始化500*500的消费节点图
extern void Init_consumeNode(consumeNode_index *ci, require_bandwidth *cb);
extern void Init_consumeNode_vec(std::vector<consumeNode_index> &cnv);
extern void Init_req_bandwidth_to_netNode(std::vector<netNode_index> &req_bw_2_net);

// 原始Dijkstra算法
extern std::vector<std::vector<int>> Dijkstra_original(netNode_index v0, netNode_index tag, consumeNode_index n, netNode_index(*rc)[NET_NODE_MAXSIZE], netNode_index(*bw)[NET_NODE_MAXSIZE], consumeNode_index *req);
// 打印Dijkstra路径
extern void print_Dijkstra_ShortPath(const std::vector<std::vector<int>> &vec, int tag, int v);
// 合并相连节点
extern bool merge_Dijkstra_server(std::vector<consumeNode_index> &cnv, const std::vector<std::vector<int>> &v1, const std::vector<std::vector<int>> &v2, consumeNode_index n1, consumeNode_index n2 ,netNode_index *sever_loc);
// 选取公共点
extern int select_Point(const std::vector<std::vector<int>> &v1, const std::vector<std::vector<int>> &v2, consumeNode_index n1, consumeNode_index n2);
//
extern void algorithm_Dijkstra(std::vector<consumeNode_index> &cnv);
//
extern std::vector<std::vector<netNode_index>> merge_2_links(std::vector<consumeNode_index> &cnv);
extern std::vector<std::vector<int>> Dijkstra_2_links(netNode_index v0, netNode_index tag, netNode_index(*rc)[NET_NODE_MAXSIZE], std::vector<std::vector<netNode_index>> &bw);
// 原始Floyd算法
extern void Floyd_original();

// 输出结果函数
extern std::string output_ans(std::vector<consumeNode_index> &cnv);
extern std::string output_ans_after_link_merge(std::vector<std::vector<netNode_index>> &v);
extern std::string output_direct_link();

// 出度算法
extern std::vector<std::vector<netNode_index>> out_degree_max();
extern std::vector<std::vector<netNode_index>> merge_host_2_consumme(std::vector<netNode_index> &host_list, std::vector<std::vector<netNode_index>> &netNode_BandWidth_out_degree, std::vector<std::vector<netNode_index>> &netNode_BandWidth_out_degree_tmp, std::vector<netNode_index> &req_bandwidth_2_netNode);
extern void Cij(int i, int j, std::vector<int> &r, int num, std::vector<std::vector<int>> & result);

// 最小费最大流算法
extern std::vector<std::vector<int>>  Max_Flow_Min_Cost(std::vector<netNode_index> &assign_host_nodes);
extern std::vector<std::vector<int>> Dijkstra_max_flow_min_cost(netNode_index v0, netNode_index tag, std::vector<std::vector<netNode_index>> &rc, std::vector<std::vector<netNode_index>> &bw);

// GA算法
extern int gen(float *min_cost);
extern std::vector<netNode_index> exchange_host_list(float *min_cost);
extern void random_alg();
extern int rand_gen_int(int x, int y);
extern float rand_gen_float();
extern int RWS(float r);

// 最短路径改进算法
extern std::vector<std::vector<int>> dijkstra_priority_queue(netNode_index v0, netNode_index tag, std::vector<std::vector<netNode_index>> &rc, std::vector<std::vector<netNode_index>> &bw);
extern std::vector<std::vector<int>> spfa(int v0, int tag, std::vector<std::vector<netNode_index>> &rc, std::vector<std::vector<netNode_index>> &bw);
extern std::vector<std::vector<int>> spfa_adj(int v0, int tag, std::vector<std::vector<netNode_index>> &G_adj, std::vector<std::vector<netNode_index>> &rc, std::vector<std::vector<netNode_index>> &bw);
extern void end(int v0, int t, std::vector<std::vector<netNode_index>> &rc, std::vector<std::vector<netNode_index>> &bw);


// 搜索
extern void search();
extern void Cij_search(int i, int j, std::vector<int> &r, int num, std::vector<int> & result, int *min, std::vector<int> &netnodes);

#endif // !VARIABLE_DECLARATION_H
