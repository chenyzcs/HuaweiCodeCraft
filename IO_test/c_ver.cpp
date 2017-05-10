#include "io_c_ver.h"

void readFile_c_ver(const char * fileName)
{
	FILE *fp = fopen(fileName, "r");
	char buf[50];
	int spaceLine = 0;
	
	while (fgets(buf, 19, fp))
	{
		//fgets(buf, 19, fp);
		if (buf[0] != '\n')
		{
			switch (spaceLine)
			{
			case 0: {
				dataPraser_c_ver(buf);
				printf("\n");
				break;
			}
			case 1: {
				dataPraser_c_ver(buf);
				printf("\n");
				break;
			}
			case 2: {
				dataPraser_c_ver(buf);
				printf("\n");
				break;
			}
			case 3: {
				dataPraser_c_ver(buf);
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

void dataPraser_c_ver(char *buf)
{
	
	char *_res = strtok(buf, " ");
	const char *_ans;
	while (_res)
	{
		if (_res != "\n" && _res != "\0")
		{
			_ans = (const char *)(_res);
			printf("%d ", atoi(_ans));
		}
		
		_res = strtok(NULL, " ");
	}
}