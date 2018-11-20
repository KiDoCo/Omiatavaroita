#ifndef QUADTREE

#define QUADTREE

#include <iostream>
#include <vector>
#include <list>
#include "Vector2D.h"

class QuadTree
{
public:
	QuadTree(int pLevel, class Shape shape);
	~QuadTree();
	void Clear();

private:
	int maxObjects = 10;
	int maxLevels = 5;
	int level;
	class Shape *bounds;
	std::vector<class Shape>* objects;
	std::vector<QuadTree*> nodes;
	void Split();
	int getindex(Shape pRect);
};


#endif //Quadtree
