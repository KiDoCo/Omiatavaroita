#pragma once

#include <vector>
#include <string>

using namespace std;

class TaskClass
{
public:
	TaskClass(char attributename[], char time[], int ide, int prior);
	TaskClass(int value);
	TaskClass();
	~TaskClass();
	void print();
	void print(int idn);
	void print(string name);

	char attribute[60] = "";
	char deadline[60] = "";
	int id;
	int priority;
	void setPriority(int h) { if (h <= 4) priority = h; else { h = 4; priority = h; } };
	friend bool operator<(const TaskClass &m1, const TaskClass &m2)
	{
		return m1.priority < m2.priority;
	}

};


struct TaskClassIterator
{
	TaskClassIterator() {};
	int* prior = nullptr;
	std::string* name = nullptr;
	void operator()(TaskClass *member)
	{
		if (!prior && !name)
		{
			member->print();
		}

		if(prior && !name)
		{
			if (member->priority == *prior) member->print();
		}

		if(!prior && name)
		{
			if (member->attribute == *name) member->print();
		}
	};
};
