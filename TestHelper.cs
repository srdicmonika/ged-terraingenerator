using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TestHelper : MonoBehaviour {

    public bool switchIntoWorkMode;
    public Material transparentMat;
    public Material fixMat;
    public Light directionalLight;


    public GameObject[] roomComponents;

    public void OnValidate()
    {
        if (switchIntoWorkMode)
        {
            for (int i = 0; i < roomComponents.Length; i++)
            {
                roomComponents[i].GetComponent<Renderer>().material = transparentMat;
            }
            directionalLight.enabled = true;
        }
        else
        {
            for (int i = 0; i < roomComponents.Length; i++)
            {
                roomComponents[i].GetComponent<Renderer>().material = fixMat;
            }
            directionalLight.enabled = false;
        }
        
    }

}
