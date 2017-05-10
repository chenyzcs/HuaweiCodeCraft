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
//#include <hash_map>

// ��������
#define INF 0xFFFF					// �ڽӾ��������ʾ
#define NET_NODE_MAXSIZE 1000		// �������ڵ����
#define CONSUME_NODE_MAXSIZE 500	// ������ѽڵ����
#define LINK_MAXSIZE 20				// ����ڵ������·����

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

// �����㷨
extern std::vector<std::vector<netNode_index>> out_degree_max();
extern std::vector<std::vector<netNode_index>> merge_host_2_consumme(std::vector<netNode_index> &host_list, std::vector<std::vector<netNode_index>> &netNode_BandWidth_out_degree, std::vector<std::vector<netNode_index>> &netNode_BandWidth_out_degree_tmp, std::vector<netNode_index> &req_bandwidth_2_netNode);
extern void Cij(int i, int j, std::vector<int> &r, int num, std::vector<std::vector<int>> & result);

#endif // !VARIABLE_DECLARATION_H