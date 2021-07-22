using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DoorMovement : MonoBehaviour {

    // The parts of the door
    public GameObject doorUP;
    public GameObject doorDO;
    public GameObject doorLE;
    public GameObject doorRI;

    private float startZPosition;

    public float startCoolDown; // Amount of seconds to wait before the door starts opening-process

    public float speed; // Speed of moving
    public float howLongMoving; // how long do they separate
    public float differenceMoveBehind; // basically how far do they move to the back
    public float speedMoveBehind; // speed at which they move back

    public float pauseBetweenBehindSeparate;

    private bool isActivated = false; // Bewegt sich nur, wenn aktiviert
    private bool movedBehind = false; // Gibt on, ob sie sich schon vollst. nach hinten bewegt hat oder nicht

	// Use this for initialization
	void Start () {
        startZPosition = doorUP.transform.position.z;
	}
	
	// Update is called once per frame
	void Update () {

        if (isActivated)
        {
            move();
        }
	}

    public void openDoor()
    {
        if (!isActivated)
        {
            StartCoroutine(startingCooldown());
        }
    }

    public void move()
    {
        if (movedBehind)
        {
            // Sie bewegen sich auseinander
            doorUP.transform.position += Vector3.up * Time.deltaTime * speed;
            doorDO.transform.position += Vector3.down * Time.deltaTime * speed;
            doorLE.transform.position += Vector3.back * Time.deltaTime * speed;
            doorRI.transform.position += Vector3.forward * Time.deltaTime * speed;
        }
        else
        {
            // Sich bewegen sich alle kollektiv nach hinten
            doorUP.transform.position += Vector3.right * Time.deltaTime * speedMoveBehind;
            doorDO.transform.position += Vector3.right * Time.deltaTime * speedMoveBehind;
            doorLE.transform.position += Vector3.right * Time.deltaTime * speedMoveBehind;
            doorRI.transform.position += Vector3.right * Time.deltaTime * speedMoveBehind;

            Debug.Log(doorUP.transform.position.z - startZPosition);

            // Wenn Differenz aus Start und momentaner position eine schwelle überschreibtet, geht die Bewegung in separieren über
            if ((doorUP.transform.position.z - startZPosition) >= differenceMoveBehind)
            {
                isActivated = false;
                StartCoroutine(switchToSeparationMovement());
                StartCoroutine(endOpeningTimer());
            }
        }
    }

    IEnumerator startingCooldown()
    {
        yield return new WaitForSeconds(startCoolDown);
        isActivated = true;
    }

    IEnumerator endOpeningTimer()
    {
        yield return new WaitForSeconds(howLongMoving);
        isActivated = false;
    }

    IEnumerator switchToSeparationMovement()
    {
        yield return new WaitForSeconds(pauseBetweenBehindSeparate);
        movedBehind = true;
        isActivated = true;
    }
}
