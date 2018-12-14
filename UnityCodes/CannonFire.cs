using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine;

public delegate void CannonActionDelegate();

public class CannonFire : MonoBehaviour
{
    public CannonActionDelegate FireDelegate;

    public CannonActionDelegate PowerDelegate;
    GameObject[] temp;
    public GameObject bullet;
    public Slider slid;
    public GameObject launchpos;
    GameObject clone;

    public bool hasFired;
    public bool powerUp;
    private float bulletRadius = 2.0f;
    private float accDec = 0.5f;
    private const float Constacc = 18.0f;
    private float acc;
    private float gravityModifier = 4.0f;
    private float velocityX;
    private float velocityY;

    private void Start()
    {
        FireDelegate += Fire;
        PowerDelegate += Power;

        temp = FindObjectsOfType<GameObject>();
    }

    //if I have time , I will implement wind resistance

    public void Power()
    {
        if (clone) return;
        acc = Mathf.PingPong(Time.time * Constacc * 2, 3 * Constacc);
        velocityX = Input.mousePosition.x * acc  * Time.deltaTime;
        velocityY = Input.mousePosition.y * acc * Mathf.Pow(9.81f,2.0f) * Time.deltaTime;
        slid.value = acc;
        Debug.Log("Power called");
    }

    void Fire()
    {
        clone = Instantiate(bullet, launchpos.transform.position, Quaternion.identity);
        clone.transform.parent = null;
        hasFired = true;
        Debug.Log("Fire called");
        Destroy(clone, 5.0f);
    }

    void PlaySound()
    {

    }

    private void Update()
    {
        Debug.Log(transform.GetChild(0).name);
        if (powerUp)
            Power();
    }

    private void FixedUpdate()
    {
        if (!hasFired) return;

        if (clone != null)
        {
            for (int i = 0; i < temp.Length; i++)
            {
                if (temp[i].GetComponent<Collider2D>() != null && clone.GetComponent<Collider2D>().bounds.Intersects(temp[i].GetComponent<Collider2D>().bounds))
                {
                    Debug.Log("destroyed");
                    Destroy(clone);
                    clone = null;
                    return;

                }
            }

            Vector2 delta = Direction() * Time.deltaTime;
            Vector2 direction = Mathf.Clamp(-transform.GetComponentInParent<Transform>().rotation.z, -1, 1) <= 0 ? Vector2.left : Vector2.right;
            clone.GetComponent<Rigidbody2D>().position =
                clone.GetComponent<Rigidbody2D>().position +
                new Vector2(direction.x * delta.x, Vector2.up.y * delta.y);
            Debug.Log(delta.y);
        }
        else
        {
            velocityX = 0;
            velocityY = 0;
            acc = 0;
            slid.value = acc;
            FindObjectOfType<InputManager>().SwitchPlayer();
        }
    }

    Vector2 Direction()
    {
        acc -= accDec * Time.deltaTime;

        if (acc >= 0)
            velocityX += acc * Time.deltaTime;

        velocityY -= gravityModifier * 9.81f * Time.deltaTime;

        return new Vector2(velocityX, velocityY);
    }
}
