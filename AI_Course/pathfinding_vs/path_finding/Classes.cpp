#include "Classes.h"
#include <algorithm>
#include <iostream>

///SearchLevel Functions

float SearchLevel::GetG(const Position& fromPos,const Position & toPos)
{
	float dX = (float)(toPos.first - fromPos.first);
	float dY = (float)(toPos.second - fromPos.second);
	float result = sqrtf(dX*dX + dY * dY);
	return result;
}

float SearchLevel::GetH(const Position& fromPos, const Position &toPos)
{
	float dX = (float)(toPos.first - fromPos.first);
	float dY = (float)(toPos.second - fromPos.second);
	return sqrtf(dX*dX + dY*dY);
}

bool SearchLevel::IsGreen(const uint8_t* pixel)
{
	if (pixel == NULL)
	{
		std::cout << "pixel was null\n";
		return false;
	}
	uint8_t r = pixel[0];
	uint8_t g = pixel[1];
	uint8_t b = pixel[2];

	if (255 == g && r == 0 && b == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool SearchLevel::IsWalkable(int x, int y)
{
	if (x < 0 || y < 0 || x >= 256 / 2 || x >= 256 / 2)
	{
		return false;
	}
	const unsigned char* pixel = GetPixel(x, y, inputData, 256);
	bool isNotWalkable = IsGreen(pixel);
	return !isNotWalkable;
		
}

std::vector<Position> SearchLevel::GetAdjancentNodes(int posX, int posY)
{
	std::vector<Position> result;

	if (IsWalkable(posX + 1, posY)) result.push_back(Position(posX + 1, posY));
	if (IsWalkable(posX - 1, posY))	result.push_back(Position(posX - 1, posY));
	if (IsWalkable(posX, posY + 1)) result.push_back(Position(posX, posY + 1));
	if (IsWalkable(posX, posY - 1)) result.push_back(Position(posX, posY - 1));

	std::cout << "\nNodes found: " << result.size() << "\n";
	return result;
}


///SearchNode Functions


float SearchNode::getDistance()
{
	return F;
}

void SearchNode::resetPrev(SearchNode * prev, float deltaG)
{
	prevNode = prev;
	if (prev == 0)
		G = 0.0f;
	else
	{
		G = deltaG + prev->G;
	}

	F = G + H;
}

bool SearchNode::lesThan(SearchNode * n1, SearchNode * n2)
{
	return n1->getDistance() > n2->getDistance();
}

///Openlist Functions

SearchNode * OpenList::findFromOpenList(const Position &pos)
{
	for (size_t i = 0; i < openList.size(); ++i)
	{
		if (openList[i]->pos == pos)
			return openList[i];
	}
	return NULL;
}

void OpenList::insertToOpenList(SearchNode * n)
{
	openList.push_back(n);
	SortOpenList();
}

void OpenList::SortOpenList()
{
	std::sort(openList.begin(), openList.end(), &SearchNode::lesThan);
}

SearchNode * OpenList::RemoveSmallestFFromOpenList()
{
	SearchNode* result = *(openList.end() - 1);
	openList.pop_back();
	return result;
}

bool OpenList::IsEmpty()
{
	return openList.empty();
}

void OpenList::Clear()
{
	openList.clear();
}

///Closedlist functions

void ClosedList::AddToClosedList(SearchNode * n)
{
	closedList[n->pos] = n;
}

bool ClosedList::IsInClosedList(const Position& pos)
{
	return closedList.find(pos) != closedList.end();
}

void ClosedList::Clear()
{
	closedList.clear();
}
