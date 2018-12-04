using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CollisionManager : MonoBehaviour
{
    QuadTree quad;
    List<RectangleBounds> allObjects;
    List<RectangleBounds> collidingObjects;
    // Use this for initialization

    void Start()
    {
        GameObject a = Instantiate(new GameObject());
        a.AddComponent<RectangleBounds>();
        a.GetComponent<RectangleBounds>().SetRectangleBounds(0, 0, 600, 600);

        quad = Instantiate<QuadTree>(new QuadTree(0, a.GetComponent<RectangleBounds>()));
        quad.name = "QuadTree";
        for(int i = 0; i < 100; i++)
        {
            GameObject b = Instantiate(new GameObject());
            b.AddComponent<RectangleBounds>();
            b.GetComponent<RectangleBounds>().Instance = b;
            b.GetComponent<RectangleBounds>().SetRectangleBounds(i, i, 600 / i, 600 / i);
            allObjects[i] = b.GetComponent<RectangleBounds>();

               
        }
    }

    // Update is called once per frame
    void Update()
    {
        quad.Clear();
        for (int i = 0; i < allObjects.Count; i++)
        {
            quad.Insert(allObjects[i]);
        }

        List<RectangleBounds> returnObjects = new List<RectangleBounds>();
        for (int i = 0; i < allObjects.Count; i++)
        {
            returnObjects.Clear();
            quad.Retrieve(returnObjects,collidingObjects[i] );

            for (int x = 0; x < returnObjects.Count; x++)
            {
                //logic here
            }
        }
    }
}
