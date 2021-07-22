using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LightDeveloper : MonoBehaviour {

    // Sinn hierhinter ist es, dass man nicht mehr in der Szene die Lichter ausmachen muss vor Spielstart
    // Also editieren kann, während die Lichter an sind

    //private Light[] lights;
    public GameObject[] lightObjects;

	// Use this for initialization
	void Start () {
		//lightObjects = GameObject.FindGameObjectsWithTag("Light");
        for (int i = 0; i < lightObjects.Length; i++)
        {
            if (lightObjects[i].GetComponent<Light>() != null)
            {
                lightObjects[i].GetComponent<Light>().enabled = false;
                //lights[i].enabled = false;
            }
        }
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
