#pragma once
#include <iostream>

class ListNode
{
public:
	ListNode* Prev;
	ListNode* Next;
	ListNode* Rand; // произвольный элемент внутри списка
	std::string Data;

	ListNode(const std::string & data) : Data(data), Prev(nullptr), Next(nullptr), Rand(nullptr) {}
};

class ListRand
{
private:
	ListNode* Head;
	ListNode* Tail;
	int Count;

public:
	void ShowList();
	ListNode* PushBack(const std::string & data, bool setRand = false);
	void SetRand(ListNode* node, const int& idxRand);
	void Clear();

	void Serialize(FILE* file);
	void Deserialize(FILE* file);

	ListRand() : Head(nullptr), Tail(nullptr), Count(0) {}
	~ListRand() { Clear(); };
};