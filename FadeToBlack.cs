using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FadeToBlack : MonoBehaviour {

    
    public GameObject plane;
    Color black = Color.black;
    float alpha = 0;

    public void Start()
    {
        //plane.GetComponent<Renderer>().material.color = new Color(0, 0, 0, 0);
        plane.GetComponent<Renderer>().enabled = false;
    }

    public void OnTriggerEnter(Collider col)
    {
        
        //fadeIntoBlack = true;
        Debug.Log("Should fade to black");
        //StartCoroutine(FadeIntoBlack());
        plane.GetComponent<Renderer>().enabled = true;
    }
    public void OnTriggerExit(Collider col){
        //fadeIntoBlack = false;
        //StartCoroutine(FadeToScene());
        plane.GetComponent<Renderer>().enabled = false;
    }

    IEnumerator FadeIntoBlack()
    {
        for (alpha = 0; alpha < 1; alpha += 0.1f)
        {
            Debug.Log("Start fading");
            plane.GetComponent<Renderer>().material.color = new Color(0, 0, 0, alpha);
            yield return new WaitForSeconds(0.5f);
        }
         
    }

    IEnumerator FadeToScene()
    {
        for (alpha = 1; alpha > 0; alpha -= 0.1f)
        {
            plane.GetComponent<Renderer>().material.color = new Color(0, 0, 0, 0);
            yield return new WaitForSeconds(0.5f);
        }

    }
}
