using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class VibrationController : MonoBehaviour {

    public float pauseBetweenVibr;
    public float[] vibrationSequenz;

    public GameObject loadingBar;
    Vector3 startSizeLoadingBar;
    public float additor;
    public float multiplier;

    public bool resetted;
    int coroutinesActive = 0;
    

	// Use this for initialization
	void Start () {
        startSizeLoadingBar.x = loadingBar.transform.localScale.x;
        startSizeLoadingBar.y = loadingBar.transform.localScale.y;
        startSizeLoadingBar.z = loadingBar.transform.localScale.z;
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    //public void OnTriggerStay(Collider col)
    //{

    //    if (col.tag == "Controller")
    //    {
    //        Debug.Log("should change bar");
    //        loadingBar.transform.localScale += new Vector3((loadingBar.transform.localScale.x + additor), startSizeLoadingBar.y, startSizeLoadingBar.z);
    //        //loadingBar.transform.localScale.Scale(new Vector3(1, 1, multiplier));
    //    }
    //}

    public void OnTriggerExit(Collider col)
    {
        ResetLoadingBar();
    }

    IEnumerator ChangeLoadingBarCor()
    {
        coroutinesActive++;
        if (coroutinesActive > 1)
        {
            coroutinesActive--;
            yield break;
        }
        while(!resetted){
            loadingBar.transform.localScale += new Vector3((additor), 0, 0);
            yield return new WaitForSeconds(0.2f);
        }
        coroutinesActive--;
 
        
    }

    public void ChangeLoadingBar()
    {
        resetted = false;
        StartCoroutine(ChangeLoadingBarCor());
    }

    public void ResetLoadingBar()
    {
        loadingBar.transform.localScale = startSizeLoadingBar;
        resetted = true;
        //coroutinesActive = 0;
    }
}
