#include "io_cpp_ver.h"

void dataParser_cpp_ver(std::string str)
{
	char *_tmpStr = std::strtok((char*)str.c_str(), " ");
	int _ans;
	while (_tmpStr)
	{
		_ans = std::stoi(_tmpStr++);
		std::cout << _ans << " ";
		_tmpStr = std::strtok(nullptr, " ");
	}
}

void readFile_cpp_ver(const std::string &fileName)
{
	std::ifstream in(fileName);
	std::string line;

	int spaceLine = 0;

	while (std::getline(in,line))
	{
		switch (spaceLine)
		{
		case 0: {
			dataParser_cpp_ver(line);
			std::cout << std::endl;
			break;
		}
		case 1: {
			dataParser_cpp_ver(line);
			std::cout << std::endl;
			break;
		}
		case 2: {
			dataParser_cpp_ver(line);
			std::cout << std::endl;
			break;
		}
		case 3: {
			dataParser_cpp_ver(line);
			std::cout << std::endl;
			break;
		}
		default:
			break;
		}
		if (line == "")
			spaceLine++;
	}
	in.close();
}