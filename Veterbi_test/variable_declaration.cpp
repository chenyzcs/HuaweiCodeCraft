#include "variable_declaration.h"

int netLink_nums;						// ������·����
int consumeNode_nums;					// ���ѽڵ�����
int serverCost;							// ����������ɱ�


netNode_index netNode_MGraph_BandWidth[NET_NODE_MAXSIZE][NET_NODE_MAXSIZE];			// ����ڵ���ڽӾ����ʾ==>�߻���������
netNode_index netNode_MGraph_RentCost[NET_NODE_MAXSIZE][NET_NODE_MAXSIZE];			// ����ڵ���ڽӾ����ʾ==>�߻��������
netNode_index netNode_MGraph_BandWidth_Left[NET_NODE_MAXSIZE][NET_NODE_MAXSIZE];	// ����ڵ���ڽӾ����ʾ==>�߻�ʣ�����

std::vector<std::vector<netNode_index>> Graph_Adj(NET_NODE_MAXSIZE);

consumeNode_index consumeNodeList[CONSUME_NODE_MAXSIZE];			// ���ѽڵ�ֱ����
require_bandwidth requireBandWidth[CONSUME_NODE_MAXSIZE];			// ���ѽڵ��������
require_bandwidth requireBandWidth_after_merge[CONSUME_NODE_MAXSIZE];// �ϲ������ѽڵ����