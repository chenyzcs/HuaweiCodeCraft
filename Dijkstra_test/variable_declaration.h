#ifndef VARIABLE_DECLARATION_H
#define VARIABLE_DECLARATION_H

#include <vector>
#include <iostream>
#include <algorithm>
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

// ����ڵ��ʼ��==>��ʼ��1000*1000������ڵ�ͼ
extern void Init_netNode(netNode_index (*bw)[NET_NODE_MAXSIZE], netNode_index (*rc)[NET_NODE_MAXSIZE]);		

// ��ʼ��ÿ����·ʣ�����
extern void Init_netNode_bandWidth_left(std::vector<std::vector<netNode_index>> &bdl);

// ���ѽڵ��ʼ��==>��ʼ��500*500�����ѽڵ�ͼ
extern void Init_consumeNode(consumeNode_index *ci, require_bandwidth *cb);
extern void Init_consumeNode_vec(std::vector<consumeNode_index> &cnv);

// ԭʼDijkstra�㷨
extern std::vector<std::vector<int>> Dijkstra_original(netNode_index v0, netNode_index tag, consumeNode_index n, netNode_index(*rc)[NET_NODE_MAXSIZE]);
// ��ӡDijkstra·��
extern void print_Dijkstra_ShortPath(const std::vector<std::vector<int>> &vec, int tag, int v);
// �ϲ������ڵ�
extern bool merge_Dijkstra_server(std::vector<consumeNode_index> &cnv, const std::vector<std::vector<int>> &v1, const std::vector<std::vector<int>> &v2, consumeNode_index n1, consumeNode_index n2 ,netNode_index *sever_loc);
// ѡȡ������
extern int select_Point(const std::vector<std::vector<int>> &v1, const std::vector<std::vector<int>> &v2, consumeNode_index n1, consumeNode_index n2);
//
extern void algorithm_Dijkstra(std::vector<consumeNode_index> &cnv);
// ԭʼFloyd�㷨
extern void Floyd_original();

#endif // !VARIABLE_DECLARATION_H
