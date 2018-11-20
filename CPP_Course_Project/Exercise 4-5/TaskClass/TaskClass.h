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

};


struct TaskClassIterator
{
	TaskClassIterator() : prior(0), name(0) {};
	int prior;
	std::string name;
	void operator()(TaskClass *member) { member->print(); };
	void operator()(TaskClass *member, int priority) { if (member->priority == priority) member->print(); };
	void operator()(TaskClass *member, char name[]) { if (member->attribute == name) member->print(); }

};
