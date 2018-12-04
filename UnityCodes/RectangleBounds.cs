using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RectangleBounds : MonoBehaviour
{

    public void SetRectangleBounds(int valx, int valy, int subWidth, int subHeight)
    {
        collisionBox = instance.AddComponent<BoxCollider2D>();
        collisionBox.size = new Vector3(subWidth, subHeight);
        instance.transform.position = new Vector3(valx,0,0);
        instance.transform.position += new Vector3(0, valy, 0);
        Debug.Log("Instantiated");
    }

    public int GetX
    {
        get
        {
            return (int)instance.transform.position.x;
        }
    }
    public int GetY
    {
        get
        {
            return (int)instance.transform.position.y;
        }
    }
    public int Width
    {
        get
        {
            return (int)collisionBox.bounds.extents.x;
        }
    }
    public int Height
    {
        get
        {
            return (int)collisionBox.bounds.extents.y;
        }

    }

    public GameObject Instance
    {
        set
        {
            Instance = value;
        }
    }

    private GameObject instance;
    private BoxCollider2D collisionBox;

}
