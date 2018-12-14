using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InputManager : MonoBehaviour
{

    int player = 1;
    private CannonFire cannon;
    Vector3 mousePos;
    Vector3 cannonPos;

    private void Start()
    {
        SwitchPlayer();
    }

    void Update()
    {
        Debug.Log(cannon);

        if (cannon.hasFired)
        {
            return;
        }

        if (Input.GetButtonUp("Fire1"))
        {
            cannon.powerUp = false;
            cannon.FireDelegate.Invoke();
            return;
        }

        if (Input.GetButtonDown("Fire1"))
        {
            cannon.powerUp = true;

            return;
        }

        cannon.transform.parent.transform.rotation = Rotation();
    }

    Quaternion Rotation()
    {
        mousePos = Input.mousePosition;
        cannonPos = Camera.main.WorldToScreenPoint(cannon.transform.parent.transform.position);
        mousePos.x = mousePos.x - cannonPos.x;
        mousePos.y = mousePos.y - cannonPos.y;
        float angle = Mathf.Atan2(-mousePos.x, mousePos.y) * Mathf.Rad2Deg;
        return Quaternion.Euler(new Vector3(0, 0, angle));
    }

    public void SwitchPlayer()
    {
        if(cannon != null)
        cannon.hasFired = false;

        if (player == 2)
        {
            cannon = GameObject.Find("Player2").GetComponentInChildren<CannonFire>();
            player--;
            return;
        }

        if (player == 1)
        {
            cannon = GameObject.Find("Player1").GetComponentInChildren<CannonFire>();
            player++;
        }

    }
}
