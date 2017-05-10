#include "io_c_ver.h"
#include "variable_declaration.h"



void readFile_c_ver(const char * fileName)
{
	FILE *fp = fopen(fileName, "r");
	char buf[50];
	int spaceLine = 0;
	int *_tmp;
	
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
				printf("\n");
				break;
			}
			case 1: {
				_tmp = dataPraser_c_ver(buf);
				serverCost = _tmp[0];
				printf("\n");
				break;
			}
			case 2: {
				_tmp = dataPraser_c_ver(buf);
				netNode_MGraph_BandWidth[_tmp[0]][_tmp[1]] = _tmp[2];
				netNode_MGraph_RentCost[_tmp[0]][_tmp[1]] = _tmp[3];
				printf("\n");
				break;
			}
			case 3: {
				_tmp = dataPraser_c_ver(buf);
				consumeNodeList[_tmp[0]] = _tmp[1];
				requireBandWidth[_tmp[0]] = _tmp[2];
				printf("\n");
				break;
			}
			default:
				break;
			}
		}
		else
		{
			spaceLine++;
			printf("\n");
		}
	}
}

int * dataPraser_c_ver(char *buf)
{
	
	char *_res = strtok(buf, " ");
	const char *_ans;
	int _ret[4];
	int i = 0;
	while (_res)
	{
		if (_res != "\n" && _res != "\0")
		{
			_ans = (const char *)(_res);
			_ret[i++] = (atoi(_ans));
			printf("%d ", atoi(_ans));
		}
		_res = strtok(NULL, " ");
	}
	return _ret;
}