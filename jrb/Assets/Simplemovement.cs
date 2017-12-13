using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Simplemovement : MonoBehaviour
{
    public float speed = 5.0f;

    private  float inputX, inputY;
    private Animator anim;
    private SpriteRenderer sprite;
    // Use this for initialization
    void Start()
    {
        sprite = GetComponentInChildren<SpriteRenderer>();
        anim = GetComponentInChildren<Animator>();
    }

    // Update is called once per frame
    void Update()
    {
        inputX = Input.GetAxis("Horizontal");
        inputY = Input.GetAxis("Vertical");

        anim.SetFloat("InputY", inputY);

        if(inputX >= 0.1f)
        {
            anim.SetBool("MovingSideways", true);
            sprite.flipX = false;
        }
        else if(inputX <= -0.1f)
        {
            anim.SetBool("MovingSideways", true);
            sprite.flipX = true;
        }
        else
        {
            anim.SetBool("MovingSideways", false);
        }

        Vector2 movement = new Vector2(inputX, inputY);
        transform.Translate(movement * speed * Time.deltaTime);
    }
}
