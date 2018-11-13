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
