#include "variable_declaration.h"

int netNode_nums = 10;						// ����ڵ�����
int netLink_nums = 10;						// ������·����
int consumeNode_nums = 10;					// ���ѽڵ�����
int serverCost = 10;						// �����������

netNode_index netNode_MGraph_BandWidth[NET_NODE_MAXSIZE][NET_NODE_MAXSIZE];		// ����ڵ���ڽӾ����ʾ==>�߻���������
netNode_index netNode_MGraph_RentCost[NET_NODE_MAXSIZE][NET_NODE_MAXSIZE];		// ����ڵ���ڽӾ����ʾ==>�߻��������

consumeNode_index consumeNodeList[CONSUME_NODE_MAXSIZE];			// ���ѽڵ�ֱ����
require_bandwidth requireBandWidth[CONSUME_NODE_MAXSIZE];		// ���ѽڵ��������