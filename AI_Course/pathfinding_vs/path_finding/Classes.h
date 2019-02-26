#include <vector>
#include <map>
#include <glut/glut.h>

#pragma once
static int WIDTH = 2 * (512 + 4);

static int HEIGHT = 2 * (256 + 2);



namespace
{

	uint8_t* GetPixel(int x, int y, uint8_t* data, int width)
	{
		return &data[3 * (y*width + x)];
	}

    const uint8_t* GetPixel(int x, int y, const uint8_t* data, int width)
	{
		return &data[3 * (y*width + x)];
	}


	void SetPixel(int x, int y, uint8_t* data, int width, uint8_t r, uint8_t b, uint8_t g)
	{
		uint8_t* pixel = GetPixel(x, y, data, width);
		pixel[0] = b;
		pixel[1] = g;
		pixel[2] = r;
	}
}


template<class T>
struct vec2
{
	T x = 0;
	T y = 0;
};

typedef std::pair<int, int> Position;

class SearchNode;



class SearchLevel
{

public:
	SearchLevel(const uint8_t *inputdata) : inputData(inputdata) {};

	//Start node
	float GetG(const Position& fromPos, const Position& toPos);

	//end node
	float GetH(const Position& fromPos, const Position &toPos);
	bool IsWalkable(int x, int y);
	std::vector<Position> GetAdjancentNodes(int posX, int posY);
	bool IsGreen(const uint8_t* pixel);
	const uint8_t* inputData;

};

class OpenList
{
public:
	SearchNode * findFromOpenList(const Position &pos);
	void insertToOpenList(SearchNode* n);
	void SortOpenList();
	SearchNode* RemoveSmallestFFromOpenList();
	bool IsEmpty();
	void Clear();

private:
	typedef std::vector<SearchNode*> OpenListType;
	OpenListType openList;
};

class ClosedList
{
public:
	ClosedList() {};
	void AddToClosedList(SearchNode* n);
	bool IsInClosedList(const Position &pos);
	void Clear();

private:
	typedef std::map<Position, SearchNode*> ClosedListType;
	ClosedListType closedList;
};

class SearchNode
{
public:
	SearchNode* prevNode;
	Position pos;
	float G;
	float H;
	float F;


	SearchNode(const Position &curPos, float h, float deltaG, SearchNode* prev) :
		prevNode(0), pos(curPos), G(0), H(h)
	{
		resetPrev(prev, deltaG);
	};

	float getDistance();
	void resetPrev(SearchNode* prev, float deltaG);
	static bool lesThan(SearchNode* n1, SearchNode* n2);
};


