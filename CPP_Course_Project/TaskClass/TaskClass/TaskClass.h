#pragma once

#include <vector>
#include <string>

using namespace std;

class TaskClass
{
public:
	TaskClass(string attributename, string time, int ide, int prior);
	~TaskClass();
	void print();
	void print(int idn);
	void print(string name);

private:
	string attribute;
	string deadline;
	int id;
	int priority;
	void setPriority(int h) { if (h <= 4) priority = h; else { h = 4; priority = h; } };

};
