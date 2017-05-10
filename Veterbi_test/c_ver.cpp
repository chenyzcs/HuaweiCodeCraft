#include "io_c_ver.h"

int netNode_nums;						// 网络节点数量

void readFile_c_ver(const char * fileName)
{
	FILE *fp = fopen(fileName, "r");
	char buf[50];
	int spaceLine = 0;
	std::vector<int> _tmp;
	
	while (fgets(buf, 19, fp))
	{
		//fgets(buf, 19, fp);
		if (buf[0] != '\n')
		{
			switch (spaceLine)
			{
			case 0: {
				_tmp = dataPraser_c_ver(buf);
				netNode_nums = _tmp[0];
				netLink_nums = _tmp[1];
				consumeNode_nums = _tmp[2];
				//std::vector<std::vector<netNode_index>> Graph_Adj(netNode_nums);
				//printf("\n");
				break;
			}
			case 1: {
				_tmp = dataPraser_c_ver(buf);
				serverCost = _tmp[0];
				//printf("\n");
				break;
			}
			case 2: {
				_tmp = dataPraser_c_ver(buf);
				netNode_MGraph_BandWidth[_tmp[0]][_tmp[1]] = _tmp[2];
				netNode_MGraph_BandWidth[_tmp[1]][_tmp[0]] = _tmp[2];
				netNode_MGraph_RentCost[_tmp[0]][_tmp[1]] = _tmp[3];
				netNode_MGraph_RentCost[_tmp[1]][_tmp[0]] = _tmp[3];
				netNode_MGraph_BandWidth_Left[_tmp[0]][_tmp[1]] = _tmp[2];
				netNode_MGraph_BandWidth_Left[_tmp[1]][_tmp[0]] = _tmp[2];
				Graph_Adj[_tmp[0]].push_back(_tmp[1]);
				Graph_Adj[_tmp[1]].push_back(_tmp[0]);
				//printf("\n");
				break;
			}
			case 3: {
				_tmp = dataPraser_c_ver(buf);
				consumeNodeList[_tmp[0]] = _tmp[1];
				requireBandWidth[_tmp[0]] = _tmp[2];
				requireBandWidth_after_merge[_tmp[0]] = _tmp[2];
				//printf("\n");
				break;
			}
			default:
				break;
			}
		}
		else
		{
			spaceLine++;
			//printf("\n");
		}
	}
}
//std::vector<std::vector<netNode_index>> netNode_MGraph_BandWidth_Left_v(
//	netNode_nums, std::vector<netNode_index>(netNode_nums, 0));



void read_data(char *topo[NET_NODE_MAXSIZE], int line_num)
{
	
	int spaceLine = 0;
	std::vector<int> _tmp;

	for(int i=0;i<line_num;i++)
	{
		if (topo[i][0] != '\n')
		{
			switch (spaceLine)
			{
			case 0: {
				_tmp = dataPraser_c_ver(topo[i]);
				netNode_nums = _tmp[0];
				netLink_nums = _tmp[1];
				consumeNode_nums = _tmp[2];
				break;
			}
			case 1: {
				_tmp = dataPraser_c_ver(topo[i]);
				serverCost = _tmp[0];
				break;
			}
			case 2: {
				_tmp = dataPraser_c_ver(topo[i]);
				netNode_MGraph_BandWidth[_tmp[0]][_tmp[1]] = _tmp[2];
				netNode_MGraph_BandWidth[_tmp[1]][_tmp[0]] = _tmp[2];
				netNode_MGraph_RentCost[_tmp[0]][_tmp[1]] = _tmp[3];
				netNode_MGraph_RentCost[_tmp[1]][_tmp[0]] = _tmp[3];
				netNode_MGraph_BandWidth_Left[_tmp[0]][_tmp[1]] = _tmp[2];
				netNode_MGraph_BandWidth_Left[_tmp[1]][_tmp[0]] = _tmp[2];
				break;
			}
			case 3: {
				_tmp = dataPraser_c_ver(topo[i]);
				consumeNodeList[_tmp[0]] = _tmp[1];
				requireBandWidth[_tmp[0]] = _tmp[2];
				requireBandWidth_after_merge[_tmp[0]] = _tmp[2];
				break;
			}
			default:
				break;
			}
		}
		else
		{
			spaceLine++;
		}
	}
}

std::vector<int> dataPraser_c_ver(char *buf)
{

	char *_res = strtok(buf, " ");
	const char *_ans;
	//int _ret[4];
	std::vector<int> _ret;
	int i = 0;
	while (_res)
	{
		if (_res != "\n" && _res != "\0")
		{
			_ans = (const char *)(_res);
			_ret.push_back(atoi(_ans));
		}
		_res = strtok(NULL, " ");
	}
	return _ret;
}