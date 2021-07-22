using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SwitchEmission : MonoBehaviour {

    public Material materialWithEmission;

    public Material signalMaterial;
    public float signalFrequence;
    public int howManySignals;
    private Material initialMat;

	// Use this for initialization
	void Start () {
        initialMat = this.gameObject.GetComponent<Renderer>().material;
	}
	
	// Update is called once per frame
	void Update () {
		
	}


    public void SwitchEmissionOn()
    {
        materialWithEmission.EnableKeyword("_Emission");
    }

    public void SwitchEmissionOff()
    {
        materialWithEmission.DisableKeyword("_Emission");
    }

    public void startSignal(Color color)
    {
        StartCoroutine(lightSignal(color));
    }

    IEnumerator lightSignal(Color color)
    {
        for(int i = 0; i < howManySignals; i++) {
            this.gameObject.GetComponent<Light>().color = color;
            yield return new WaitForSeconds(signalFrequence);
            this.gameObject.GetComponent<Light>().color = Color.white;
            yield return new WaitForSeconds(signalFrequence);
        }
    }
}
