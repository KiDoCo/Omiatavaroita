#include "src/Headers/Quadtree.h"
#include "src/Headers/Shape.h"

QuadTree::QuadTree(int pLevel,Shape shape)
{
	level = pLevel;
	objects = new std::vector<Shape>();
	bounds = &shape;
}

QuadTree::~QuadTree()
{

}

void QuadTree::Clear()
{
	for (int i = 0; i < nodes.size() ; i++)
	{
		if (nodes[i] != nullptr)
		{
			nodes[i]->Clear();
			nodes[i] = nullptr;
		}
	}
}

void QuadTree::Split()
{
	int subWidth = (int)(bounds->GetWidth() / 2);
	int subHeight = (int)(bounds->GetHeight() / 2);
	int x = (int)bounds->GetX();
	int y = (int)bounds->GetY();

	nodes[0] = new QuadTree(level + 1, new Shape(x + subWidth, y, subWidth, subHeight));
	nodes[1] = new QuadTree(level + 1, new Shape(x , y, subWidth, subHeight));
	nodes[2] = new QuadTree(level + 1, new Shape(x , y + subHeight, subWidth, subHeight));
	nodes[3] = new QuadTree(level + 1, new Shape(x + subWidth, y + subHeight, subWidth, subHeight));
}

int QuadTree::getindex(Shape pRect)
{

}