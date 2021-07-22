using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HighlightObject : MonoBehaviour {

    public Material highlightMaterial;
    public Material StartMaterial;
    public bool highlighted;

    float timer = 1800;
    public float resetInterval = 1800;

	// Use this for initialization
	void Start () {
        StartMaterial = this.GetComponentInChildren<Renderer>().material;
	}
	
	// Update is called once per frame
	void Update () {

        timer -= Time.deltaTime;

        if (timer <= 0)
        {
            timer = resetInterval;
            resetMaterial();
        }

	}

    public void Highlight()
    {
        if (!highlighted)
        {
            highlighted = true;
            StartCoroutine(HighlightObj());
        }
    }


    IEnumerator HighlightObj()
    {
       // highlighted = true;
        Renderer tmpRend = this.GetComponentInChildren<Renderer>();
        if (tmpRend)
        {
            Material tmpMat = tmpRend.material;
            this.GetComponentInChildren<Renderer>().material = highlightMaterial;
            yield return new WaitForSeconds(0.2f);

            this.GetComponentInChildren<Renderer>().material = tmpMat;
        }

        highlighted = false;
    }

    public void resetMaterial()
    {
        this.GetComponentInChildren<Renderer>().material = StartMaterial;
    }
}
