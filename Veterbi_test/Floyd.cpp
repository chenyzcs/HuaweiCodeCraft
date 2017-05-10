#include "variable_declaration.h"

void Floyd_original()
{
	int v, w, k;
	std::vector<std::vector<netNode_index>> D(netNode_nums, 
		std::vector<netNode_index>(netNode_nums,0));
	std::vector<std::vector<netNode_index>> P(netNode_nums,
		std::vector<netNode_index>(netNode_nums, 0));

	for (v = 0; v < netNode_nums; v++)
	{
		for (w = 0; w < netNode_nums; w++)
		{
			D[v][w] = netNode_MGraph_RentCost[v][w];
			P[v][w] = w;
		}
	}
	for (k = 0; k < netNode_nums; k++)
	{
		for (v = 0; v < netNode_nums; v++)
		{
			for (w = 0; w < netNode_nums; w++)
			{
				if ((D[v][w] > D[v][k] + D[k][w])  /*&&(netNode_MGraph_BandWidth_Left[v][w] >= requireBandWidth[0]) 
					&& (netNode_MGraph_BandWidth_Left[v][k] >= requireBandWidth[0]
						&& (netNode_MGraph_BandWidth_Left[k][w] >= requireBandWidth[0]))*/)
				{
					D[v][w] = D[v][k] + D[k][w];
					P[v][w] = P[v][k];
				}
			}
		}
	}
	for (v = 0; v < netNode_nums; v++)
	{
		for (w = v + 1; w < netNode_nums; w++)
		{
			std::cout << v << "-" << w << ": " << D[v][w] << std::endl;
			k = P[v][w];
			while (k != w)
			{
				std::cout << "==>" << k;
				k = P[k][w];
			}
			std::cout << "==>" << w << std::endl;
		}
	}
	k = P[43][22];
	std::cout << std::endl;
	std::cout << 43;
	while (k != 22)
	{
		std::cout << "==>" << k;
		k = P[k][22];
	}
	std::cout << "==>" << 22 << std::endl;
}