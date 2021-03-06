
#include "stdafx.h"
#include <iostream>
#include <conio.h>

using namespace std;

struct NODE
{
	int index;
	int value;
	NODE *next;

	NODE(int id = 0,int val = 0)
	{
		index = id;
		value = val;
		next = nullptr;
	}
};

int linkLength = 0;
void CreateNode(NODE *item);
void printList(NODE *head);
void addToTheEnd(NODE *head, NODE *item);
void remove(NODE **first, int toRemove);

int main()
{
	NODE *n1 = new NODE(0,0);
	char input = ' ';

	NODE *head = n1;

	linkLength++;
	while (input != 'q')
	{
	cout << "ADD node : a" << "\n" << "remove node : r" << "\n" << "print list : p" << "\n";

	cin >> input;
		if (input == 'a')
		{
			NODE *temp = new NODE();
			CreateNode(temp);
			addToTheEnd(head, temp);
			linkLength++;
		}

		if (input == 'r')
		{
			int val = 0;
			cout << "Give the node ID which is to be removed " << "\n";
			cin >> val;

			remove(&head, val);
		}

		if (input == 'p')
		{
			printList(head);
		}
	}

	return 1;
}



void CreateNode(NODE *item)
{
	int temp;
	int id;
	cout << "Enter Initial value for " << linkLength << " node " << "\n";
	cin >> temp;

	cout << "Enter ID for value " << "\n";
	cin >> id;

	item->index = id;
	item->value = temp;
	item->next = nullptr;
}

void printList(NODE *head)
{
	NODE *n;
	cout << "Printing the list" << "\n";

	for (n = head; n != 0; n = n->next)
	{
		cout << n->value << " ";
	}
	cout << "\n";
}

void addToTheEnd(NODE *head, NODE *item)
{
	NODE *n = head;

	while (n->next != 0)
	{
		n = n->next;
	}

	n->next = item;
}

void remove(NODE **first, int toRemove)
{
	NODE *temp, *prev;

	temp = *first;

	prev = new NODE(0, 0);

	while (temp != 0)
	{
		if (temp->index == toRemove)
		{
			if (temp == *first)
			{
				*first = temp->next;
				temp = 0;
			}
			else
			{
				prev->next = temp->next;
				temp = 0;
			}
			cout << "Removed Node" << "\n";
		}
		else
		{
			prev = temp;
			temp = temp->next;
		}
	}

}



