using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class IntroHandler : MonoBehaviour {

    public Image ui_Image;

    public Sprite mainMenu;
    public Sprite tutorialScreen;

    public SteamVR_TrackedObject trackedObj;
    SteamVR_Controller.Device controller
    {
        get { return SteamVR_Controller.Input((int)trackedObj.index); }
    }

    void Awake()
    {
        trackedObj = GetComponent<SteamVR_TrackedObject>();
    }

	// Use this for initialization
	void Start () {
        ui_Image.sprite = mainMenu;
	}
	
	// Update is called once per frame
	void Update () {

        //if (controller == null || trackedObj == null)
        //{
        //    Debug.Log("Controller not initilized");
        //    return;
        //}
        //else if (controller.GetPressDown(SteamVR_Controller.ButtonMask.Trigger))
        //{
        //    Next();
        //}
	}

    // Switches to tutorial and then to real game
    void Next()
    {
        if (ui_Image.sprite == mainMenu)
        {
            ui_Image.sprite = tutorialScreen;
        }
        else
        {
            SceneManager.LoadScene("Game");
        }
    }

    public void OnTriggerEnter(Collider col)
    {
        if (col.tag == "StartButton")
        {
            SceneManager.LoadScene("Game");
        }

        if (col.tag == "ControlButton")
        {
            Debug.Log("pressed Button");
            if (ui_Image.sprite == mainMenu)
            {
                ui_Image.sprite = tutorialScreen;
            }
            else
            {
                ui_Image.sprite = mainMenu;
            }
            
        }
    }
}
