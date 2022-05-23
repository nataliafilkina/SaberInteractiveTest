#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "List.h"

void ListRand::Serialize(FILE* file)
{
	std::unordered_map<ListNode*, int> map;
	int i = 1;

	fprintf(file, "%d\n", Count);

	for (ListNode* node = Head; node; node = node->Next, ++i)
	{
		fprintf(file, "%s\n", node->Data.c_str());
		map[node] = i;
	}

	for (ListNode* node = Head; node; node = node->Next)
		if (node->Rand)
			fprintf(file, "%d ", map[node->Rand]);
		else
			fprintf(file, "%d ", 0);
}

void ListRand::Deserialize(FILE* file)
{
	char buf[256];
	std::string data;
	fseek(file, 0, SEEK_SET);
	std::unordered_map<int, ListNode*> map;

	int numLines = 0;
	fscanf_s(file, "%d\n", &numLines);

	for (int i = 1; i <= numLines; ++i)
	{
		if (fgets(buf, sizeof(buf), file))
		{
			data = buf;
			data.pop_back();
			ListNode* newNode = PushBack(data, false);
			map[i] = newNode;
		}
	}

	int idx;
	for (ListNode* node = Head; node; node = node->Next)
	{
		fscanf_s(file, "%d", &idx);
		node->Rand = map[idx];
	}
}

void ListRand::ShowList()
{
	if (!Head)
		std::cout << "List is empty" << std::endl;
	else
		for (ListNode* node = Head; node; node = node->Next)
		{
			std::cout << node->Data << " rand: " << (node->Rand ? node->Rand->Data : "null") << std::endl;
		}
}

ListNode* ListRand::PushBack(const std::string& data, bool setRand)
{
	ListNode* newNode = new ListNode(data);

	if (!Head)
	{
		Head = Tail = newNode;
	}
	else
	{
		newNode->Prev = Tail;
		Tail->Next = newNode;
		Tail = newNode;
	}

	if (setRand)
	{
		srand(time(NULL));
		int idx = rand() % (Count + 1);
		SetRand(newNode, idx);
	}
	else
		newNode->Rand = nullptr;

	Count++;
	return newNode;
}

void ListRand::SetRand(ListNode* node, const int & idxRand)
{
	if (idxRand <= Count)
	{
		ListNode* randNode = nullptr;
		if (idxRand)
		{
			if (idxRand <= Count / 2)
			{
				randNode = Head;
				for (int i = 1; i != idxRand; ++i)
					randNode = randNode->Next;
			}
			else
			{
				randNode = Tail;
				for (int i = Count; i != idxRand; --i)
					randNode = randNode->Prev;
			}
		}
		node->Rand = randNode;
	}
	else
		std::cout << "SetRand: error\n";
}

void ListRand::Clear()
{
	if (Head)
	{
		ListNode* nodeNext = Head;
		for (ListNode* node = Head; nodeNext; node = nodeNext)
		{
			node->Next ? nodeNext = node->Next : nodeNext = nullptr;
			delete node;
		}

		Head = Tail = nullptr;
		Count = 0;
	}
}
