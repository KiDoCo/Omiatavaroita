using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine;

public delegate void CannonActionDelegate();

public class CannonFire : MonoBehaviour
{
    public CannonActionDelegate FireDelegate;

    public CannonActionDelegate PowerDelegate;
    private InputManager manager;
    GameObject[] temp;
    private GameObject clone;
    public GameObject bullet;
    public GameObject launchpos;
    public GameObject explosion;
    public Slider slid;
    public bool hasFired;
    public bool powerUp;
    private float bulletRadius = 2.0f;
    private float accDec = 0.5f;
    private const float Constacc = 100.0f;
    private float acc;
    private float gravityModifier = 30.0f;
    private const float powerMultiplier = 2.0f;
    private const float reactionTime = 600.0f;
    private float velocityX;
    private float velocityY;
    private bool increase;

    private void Start()
    {
        FireDelegate += Fire;
        PowerDelegate += Power;
        manager = FindObjectOfType<InputManager>();
        temp = FindObjectsOfType<GameObject>();
    }

    //if I have time , I will implement wind resistance

    public void Power()
    {
        if (clone) return;
        acc = PingPongDingDong(acc, Constacc * 0.5f, 3.0f * Constacc);
        float x = Mathf.Clamp(Mathf.Abs(Camera.main.ScreenToWorldPoint(Input.mousePosition).x - launchpos.transform.position.x), -20, 20);
        float y = Mathf.Clamp(Mathf.Abs(Camera.main.ScreenToWorldPoint(Input.mousePosition).y - launchpos.transform.position.y), -20, 20);
        velocityX = x * acc * Time.deltaTime * powerMultiplier;
        velocityY = y * acc * Time.deltaTime * powerMultiplier; //cannon rotation * acceleration *  time
        slid.maxValue = 3 * Constacc;
        slid.value = acc;
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
                    if (temp[i].name == manager.enemy) Destroy(temp[i]);

                    GameObject tempa = Instantiate(explosion, clone.transform.position, Quaternion.identity);
                    Destroy(clone);
                    clone = null;
                    Destroy(tempa, 2.0f);
                    return;
                }
            }

            Vector2 delta = Direction() * Time.deltaTime;
            Vector2 direction = Mathf.Clamp(-transform.GetComponentInParent<Transform>().rotation.z, -1, 1) <= 0 ? Vector2.left : Vector2.right;
            clone.GetComponent<Rigidbody2D>().position =
                clone.GetComponent<Rigidbody2D>().position +
                new Vector2(direction.x * delta.x, Vector2.up.y * delta.y);
        }
        else
        {
            velocityX = 0;
            velocityY = 0;
            acc = 0;
            slid.value = acc;
            manager.SwitchPlayer();
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

    private float PingPongDingDong(float val, float min, float max)
    {
        if (val <= min)
        {
            increase = true;
        }

        if (val >= max)
        {
            increase = false;
        }

        if (increase)
        {
            val += Time.deltaTime * reactionTime;
        }
        else
        {
            val -= Time.deltaTime * reactionTime;
        }

        return val;
    }
}
