#include "variable_declaration.h"

int netNode_nums;						// ����ڵ�����
int netLink_nums;						// ������·����
int consumeNode_nums;					// ���ѽڵ�����
int serverCost;							// ����������ɱ�

netNode_index netNode_MGraph_BandWidth[NET_NODE_MAXSIZE][NET_NODE_MAXSIZE];		// ����ڵ���ڽӾ����ʾ==>�߻���������
netNode_index netNode_MGraph_RentCost[NET_NODE_MAXSIZE][NET_NODE_MAXSIZE];		// ����ڵ���ڽӾ����ʾ==>�߻��������


consumeNode_index consumeNodeList[CONSUME_NODE_MAXSIZE];			// ���ѽڵ�ֱ����
require_bandwidth requireBandWidth[CONSUME_NODE_MAXSIZE];			// ���ѽڵ��������