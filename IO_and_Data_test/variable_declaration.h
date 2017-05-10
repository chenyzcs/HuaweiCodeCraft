#ifndef VARIABLE_DECLARATION_H
#define VARIABLE_DECLARATION_H

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

// ���ѽڵ�
extern consumeNode_index consumeNodeList[CONSUME_NODE_MAXSIZE];			// ���ѽڵ�ֱ����
extern require_bandwidth requireBandWidth[CONSUME_NODE_MAXSIZE];		// ���ѽڵ��������

// ����ڵ��ʼ��==>��ʼ��1000*1000������ڵ�ͼ
extern void Init_netNode(netNode_index (*bw)[NET_NODE_MAXSIZE], 
	netNode_index (*rc)[NET_NODE_MAXSIZE]);		// 

// ���ѽڵ��ʼ��==>��ʼ��500*500�����ѽڵ�ͼ
extern void Init_consumeNode(consumeNode_index *ci,
	require_bandwidth *cb);

#endif // !VARIABLE_DECLARATION_H
