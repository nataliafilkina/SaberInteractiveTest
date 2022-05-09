#include <iostream>
#include <fstream>
#include "List.h"

int main()
{
	ListRand inputList;
	ListRand outputList;
	FILE* file;
	const char* path = "input.dat";

	inputList.PushBack("AAA AA A", true);
	inputList.PushBack("BBB BB BB");
	inputList.PushBack("CCCC", true);
	inputList.PushBack("DD");
	inputList.PushBack("EEEEE", true);
	inputList.PushBack("FFFF");

	std::cout << "InputList" << std::endl;
	inputList.ShowList();

	if (file = fopen(path, "wb"))
	{
		inputList.Serialize(file);
		fclose(file);
	}
	else
		std::cout << "The file " << path << " was not opened" << std::endl;

	if (file = fopen(path, "rb"))
	{
		outputList.Deserialize(file);
		std::cout << std::endl << "OutputList " << std::endl;
		outputList.ShowList();
		fclose(file);
	}
	else
		std::cout << "The file " << path << " was not opened" << std::endl;
	return 0;
}