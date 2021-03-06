
#include "TaskClass.h"
#include <iostream>
#include <fstream>
#include <algorithm>
void TaskValue();
void Sort();
bool IsNumeric(const std::string& input)
{
	return std::all_of(input.begin(), input.end(), ::isdigit);
}

auto lambdaiterator = [=](vector<TaskClass*> list, TaskClassIterator &itr)
{
	for_each(list.begin(), list.end(), [=](TaskClass  *a) 
	{
		if (!itr.prior && !itr.name)
		{
			a->print();
		}

		if (itr.prior && !itr.name)
		{
			if (a->priority == *itr.prior) a->print();
		}

		if (!itr.prior && itr.name)
		{
			if (a->attribute == *itr.name) a->print();
		}
	});
};

vector<TaskClass*> classlist;
void SaveToFile(vector<TaskClass*> list);
void LoadFromFile(vector<TaskClass*> &list);

int main()
{
	char input = ' ';
	LoadFromFile(classlist);
	system("pause");
	while (input != 'q')
	{
		system("cls");
		cout << "Enter a to add task " << endl;
		cout << "Enter s to list all task" << endl;
		cout << "Enter d to print specific task" << endl;

		input = getchar();

		if (input == 'a')
		{
			TaskValue();
		}

		if (input == 's')
		{
			TaskClassIterator itr;

			lambdaiterator(classlist, itr);
			system("pause");
		}

		if (input == 'd')
		{
			std::string id;
			cout << "Give task name or priority" << "\n";
			try
			{
				std::cin.ignore();
				std::getline(std::cin, id);
				TaskClassIterator itr;
				if (!IsNumeric(id))
				{
					itr.name = &id;
				}
				else
				{
					int a = std::stoi(id);
					itr.prior = &a;
				}
				lambdaiterator(classlist, itr);

			}
			catch (exception &e)
			{
				std::cout << e.what() << std::endl;
				std::runtime_error("Failed to read input" );

			}
			system("pause");

		}

		if (input == 'b')
		{
			Sort();
		}
	}

	SaveToFile(classlist);
	return 0;
}

void TaskValue()
{
	char name[60];
	char date[60];
	int identity = 0;
	int priority = 0;
	try
	{
		cout << "Enter name of the task " << "\n";
		cin >> name;
		cout << "Enter the due date " << "\n";
		cin >> date;
		cout << "Enter id for the task (number) " << "\n";
		cin >> identity;
		cout << "Enter priority for the task" << "\n";
		cin >> priority;
		TaskClass *temp = new TaskClass(name, date, identity, priority);
		classlist.push_back(temp);

	}
	catch (const std::exception& e)
	{
		cout << e.what();
		system("pause");
	}

}

void Sort()
{
	std::sort(classlist.begin(), classlist.end(), [=](TaskClass *val1, TaskClass *val2) 
	{
		return (*val1) < (*val2);
	});

}

//TaskClass implementations

#pragma region Cons/Decons

TaskClass::TaskClass()
{

}

TaskClass::TaskClass(char attributename[], char time[], int ide = 0, int prior = 0)
{
	strcpy_s(attribute, attributename);
	strcpy_s(deadline, time);
	id = ide;
	priority = prior;
}

TaskClass::TaskClass(int value)
{
	id = value;
}

TaskClass::~TaskClass()
{
	cout << "Deconstructed" << "\n";
}


#pragma endregion

#pragma region prints

void TaskClass::print()
{
	cout << "Task name : " << attribute << endl;
	cout << "Deadline date : " << deadline << endl;
	cout << "priority (0-4) : " << priority << endl;
}

void TaskClass::print(int idn)
{
	if (id == idn)
	{
		if (attribute != "")
			cout << attribute << "\n " << deadline << "\n " << priority << std::endl;
		else
			print(idn);
	}
}

void TaskClass::print(string name)
{
	if (attribute == name)
	{
		cout << attribute << "\n " << deadline << "\n " << priority << std::endl;
	}
}

#pragma endregion

void SaveToFile(vector<TaskClass*> list)
{
	std::ofstream myFile("container.dat", std::ios::binary | std::ios::out | std::ios::app);

	for (vector<TaskClass*>::iterator it = list.begin(); it != list.end(); ++it)
	{
		if (myFile)
		{
			myFile.write((char*)(*it), sizeof(TaskClass));
		}
	}

	myFile.close();
}

void LoadFromFile(vector<TaskClass*> &list)
{
	std::ifstream myFile("container.dat", std::ios::binary | std::ios::in);

	if (myFile)
	{
		while (myFile.peek() != EOF)
		{
			TaskClass *task = new TaskClass;
			myFile.read((char*)task, sizeof(TaskClass));
			task->print();
			list.push_back(task);
		}
	}
	myFile.close();
	remove("container.dat");
}

