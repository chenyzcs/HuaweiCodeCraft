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

// ��������
#define INF 0xFFFFFF					// �ڽӾ��������ʾ
#define NET_NODE_MAXSIZE 1000		// �������ڵ����
#define CONSUME_NODE_MAXSIZE 500	// ������ѽڵ����
#define LINK_MAXSIZE 20				// ����ڵ������·����
#define min(a,b) ((a)>(b))?(b):(a)

extern int netNode_nums;			// ����ڵ�����
extern int netLink_nums;			// ������·����
extern int consumeNode_nums;		// ���ѽڵ�����
extern int serverCost;				// ����������ɱ�

extern std::string result;




typedef int netNode_index;		// ����ڵ���
typedef int arc_bandwidth;		// ÿ���ߵĴ���
typedef int arc_rentcost;		// ÿ���ߵ����
typedef int consumeNode_index;	// ���ѽڵ���
typedef int require_bandwidth;	// ���ѽڵ��������


// ����ڵ�����ͼ
extern netNode_index netNode_MGraph_BandWidth[NET_NODE_MAXSIZE][NET_NODE_MAXSIZE];		// ����ڵ���ڽӾ����ʾ==>�߻���������
extern netNode_index netNode_MGraph_RentCost[NET_NODE_MAXSIZE][NET_NODE_MAXSIZE];		// ����ڵ���ڽӾ����ʾ==>�߻��������
extern netNode_index netNode_MGraph_BandWidth_Left[NET_NODE_MAXSIZE][NET_NODE_MAXSIZE];	// ����ڵ���ڽӾ����ʾ==>�߻�ʣ�����

// ͼ�ڽӱ��ʾ
extern std::vector<std::vector<netNode_index>> Graph_Adj;

// ��������
extern int server_Num;				// �����з���������
extern std::vector<std::vector<netNode_index>> netNode_MGraph_BandWidth_Left_vec;		// ����ڵ����·ʣ�����
extern std::vector<consumeNode_index> consumeNodeList_vec;
// ���ѽڵ�
extern consumeNode_index consumeNodeList[CONSUME_NODE_MAXSIZE];			// ���ѽڵ�ֱ����
extern require_bandwidth requireBandWidth[CONSUME_NODE_MAXSIZE];		// ���ѽڵ��������
extern require_bandwidth requireBandWidth_after_merge[CONSUME_NODE_MAXSIZE];

// �ٷ��ӿ�
extern void read_data(char *topo[NET_NODE_MAXSIZE], int line_num);
// ����ڵ��ʼ��==>��ʼ��1000*1000������ڵ�ͼ
extern void Init_netNode(netNode_index (*bw)[NET_NODE_MAXSIZE], netNode_index (*rc)[NET_NODE_MAXSIZE]);		

// ��ʼ��ÿ����·ʣ�����
extern void Init_netNode_bandWidth_left(std::vector<std::vector<netNode_index>> &bdl);

// ���ѽڵ��ʼ��==>��ʼ��500*500�����ѽڵ�ͼ
extern void Init_consumeNode(consumeNode_index *ci, require_bandwidth *cb);
extern void Init_consumeNode_vec(std::vector<consumeNode_index> &cnv);
extern void Init_req_bandwidth_to_netNode(std::vector<netNode_index> &req_bw_2_net);

// ԭʼDijkstra�㷨
extern std::vector<std::vector<int>> Dijkstra_original(netNode_index v0, netNode_index tag, consumeNode_index n, netNode_index(*rc)[NET_NODE_MAXSIZE], netNode_index(*bw)[NET_NODE_MAXSIZE], consumeNode_index *req);
// ��ӡDijkstra·��
extern void print_Dijkstra_ShortPath(const std::vector<std::vector<int>> &vec, int tag, int v);
// �ϲ������ڵ�
extern bool merge_Dijkstra_server(std::vector<consumeNode_index> &cnv, const std::vector<std::vector<int>> &v1, const std::vector<std::vector<int>> &v2, consumeNode_index n1, consumeNode_index n2 ,netNode_index *sever_loc);
// ѡȡ������
extern int select_Point(const std::vector<std::vector<int>> &v1, const std::vector<std::vector<int>> &v2, consumeNode_index n1, consumeNode_index n2);
//
extern void algorithm_Dijkstra(std::vector<consumeNode_index> &cnv);
//
extern std::vector<std::vector<netNode_index>> merge_2_links(std::vector<consumeNode_index> &cnv);
extern std::vector<std::vector<int>> Dijkstra_2_links(netNode_index v0, netNode_index tag, netNode_index(*rc)[NET_NODE_MAXSIZE], std::vector<std::vector<netNode_index>> &bw);
// ԭʼFloyd�㷨
extern void Floyd_original();

// ����������
extern std::string output_ans(std::vector<consumeNode_index> &cnv);
extern std::string output_ans_after_link_merge(std::vector<std::vector<netNode_index>> &v);
extern std::string output_direct_link();

// �����㷨
extern std::vector<std::vector<netNode_index>> out_degree_max();
extern std::vector<std::vector<netNode_index>> merge_host_2_consumme(std::vector<netNode_index> &host_list, std::vector<std::vector<netNode_index>> &netNode_BandWidth_out_degree, std::vector<std::vector<netNode_index>> &netNode_BandWidth_out_degree_tmp, std::vector<netNode_index> &req_bandwidth_2_netNode);
extern void Cij(int i, int j, std::vector<int> &r, int num, std::vector<std::vector<int>> & result);

// ��С��������㷨
extern std::vector<std::vector<int>>  Max_Flow_Min_Cost(std::vector<netNode_index> &assign_host_nodes);
extern std::vector<std::vector<int>> Dijkstra_max_flow_min_cost(netNode_index v0, netNode_index tag, std::vector<std::vector<netNode_index>> &rc, std::vector<std::vector<netNode_index>> &bw);

// GA�㷨
extern int gen(float *min_cost);
extern std::vector<netNode_index> exchange_host_list(float *min_cost);
extern void random_alg();
extern int rand_gen_int(int x, int y);
extern float rand_gen_float();
extern int RWS(float r);

// ���·���Ľ��㷨
extern std::vector<std::vector<int>> dijkstra_priority_queue(netNode_index v0, netNode_index tag, std::vector<std::vector<netNode_index>> &rc, std::vector<std::vector<netNode_index>> &bw);
extern std::vector<std::vector<int>> spfa(int v0, int tag, std::vector<std::vector<netNode_index>> &rc, std::vector<std::vector<netNode_index>> &bw);
extern std::vector<std::vector<int>> spfa_adj(int v0, int tag, std::vector<std::vector<netNode_index>> &G_adj, std::vector<std::vector<netNode_index>> &rc, std::vector<std::vector<netNode_index>> &bw);
extern void end(int v0, int t, std::vector<std::vector<netNode_index>> &rc, std::vector<std::vector<netNode_index>> &bw);


// ����
extern void search();
extern void Cij_search(int i, int j, std::vector<int> &r, int num, std::vector<int> & result, int *min, std::vector<int> &netnodes);

#endif // !VARIABLE_DECLARATION_H
