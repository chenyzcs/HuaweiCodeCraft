#include "variable_declaration.h"

void Veterbi()
{
	
	std::vector<int> path(netNode_nums, -1);
	std::vector<int> dis(netNode_nums, INF);
	std::vector<bool> isMark(netNode_nums, false);
	std::vector<int> preLayer;

	int v0 = 0;
	int tag = 1;
	isMark[v0] = true;
	preLayer.push_back(v0);

	int max = INF;
	int k;

	while (!isMark[tag])
	{
		for (int i = 0; i < netNode_nums; i++)
		{
			k = max;
			std::vector<int> _tmp_layer;
			for (int j = 0; j < preLayer.size(); j++)
			{
				if (i == preLayer[j])
					continue;
				if (!isMark[i])
				{

				}
			}
		}
	}
}

