using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class QuadTree : MonoBehaviour
{
    private int maxObjects = 10;
    private int max_levels = 5;

    private int level;
    private List<RectangleBounds> objects;
    private RectangleBounds bounds;
    private QuadTree[] nodes;

    public QuadTree(int pLevel, RectangleBounds pBounds)
    {
        level = pLevel;
        objects = new List<RectangleBounds>();
        bounds = pBounds;
        nodes = new QuadTree[4];
    }

    public void Clear()
    {
        objects.Clear();

        for (int i = 0; i < nodes.Length; i++)
        {
            if (nodes[i] != null)
            {
                nodes[i].Clear();
                nodes[i] = null;
            }
        }
    }

    private void Split()
    {
        int subWidth = (int)bounds.GetComponent<Collider>().bounds.extents.x / 2;
        int subHeight = (int)bounds.GetComponent<Collider>().bounds.extents.y / 2;

        int x = (int)bounds.GetComponent<Transform>().position.x;
        int y = (int)bounds.GetComponent<Transform>().position.y;

        for (int i = 0; i < 3; i++)
        {
            GameObject template = Instantiate(new GameObject());
            template.AddComponent<RectangleBounds>();
            template.GetComponent<RectangleBounds>().Instance = template;
            switch (i)
            {
                case 0:
                    template.GetComponent<RectangleBounds>().SetRectangleBounds(x + subWidth, y, subWidth, subHeight);
                    break;
                case 1:
                    template.GetComponent<RectangleBounds>().SetRectangleBounds(x, y, subWidth, subHeight);
                    break;
                case 2:
                    template.GetComponent<RectangleBounds>().SetRectangleBounds(x, y + subHeight, subWidth, subHeight);
                    break;
                case 3:
                    template.GetComponent<RectangleBounds>().SetRectangleBounds(x + subWidth, y + subHeight, subWidth, subHeight);
                    break;
            }
            nodes[i] = new QuadTree(level + 1, template.GetComponent<RectangleBounds>());

        }


    }

    private int GetIndex(RectangleBounds pRect)
    {
        int index = -1;
        double verticalMidpoint = bounds.GetX + (bounds.Width / 2);
        double horizontalMidpoint = bounds.GetY + (bounds.Height / 2);

        // Object can completely fit within the top quadrants
        bool topQuadrant = (pRect.GetY < horizontalMidpoint && pRect.GetY + pRect.Height < horizontalMidpoint);
        // Object can completely fit within the bottom quadrants
        bool bottomQuadrant = (pRect.GetY > horizontalMidpoint);

        // Object can completely fit within the left quadrants
        if (pRect.GetX < verticalMidpoint && pRect.GetX + pRect.Width < verticalMidpoint)
        {
            if (topQuadrant)
            {
                index = 1;
            }
            else if (bottomQuadrant)
            {
                index = 2;
            }
        }
        // Object can completely fit within the right quadrants
        else if (pRect.GetX > verticalMidpoint)
        {
            if (topQuadrant)
            {
                index = 0;
            }
            else if (bottomQuadrant)
            {
                index = 3;
            }
        }

        return index;
    }

    public void Insert(RectangleBounds pRect)
    {
        if (nodes[0] != null)
        {
            int index = GetIndex(pRect);

            if (index != -1)
            {
                nodes[index].Insert(pRect);
                return;
            }
        }

        objects.Add(pRect);

        if (objects.Count > maxObjects && level < max_levels)
        {
            if (nodes[0] == null) Split();
        }

        int i = 0;
        while (i < objects.Count)
        {
            int index = GetIndex(objects[i]);
            if (index != -1)
            {
                RectangleBounds a = objects[i];
                nodes[index].Insert(a);
                objects.RemoveAt(i);
            }
            else
            {
                i++;
            }
        }
    }

    public List<RectangleBounds> Retrieve(List<RectangleBounds> returnObjects, RectangleBounds pRect)
    {
        int index = GetIndex(pRect);
        if (index != -1 && nodes[0] != null)
        {
            nodes[index].Retrieve(returnObjects, pRect);
        }

        returnObjects.AddRange(objects);
        return returnObjects;
    }


}
