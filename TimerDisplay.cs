using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TimerDisplay : MonoBehaviour {

    public float timeLeft = 1200.00f; //entspricht 10 minuten
    public bool signalAtHalfTime; // If true, timeForSignal will automaticcaly be set to half of the starting time!
    public float timeForSignal; // after this time, the room lights shortly red as signal
    private bool alreadySignaled = false;
    public GameObject timerDisplay;

    bool gameEnded;

    float timeStep = 1;

	// Use this for initialization
	void Start () {
        if (signalAtHalfTime)
        {
            timeForSignal = timeLeft / 2;
        }
	}
	
	// Update is called once per frame
	void Update () {

        if (!gameEnded)
        {
            timeLeft -= Time.deltaTime * timeStep;

            if (timeLeft < 0 && !gameEnded)
            {
                gameEnded = true;
                GameOver();
            }
            else
            {
                string minutes = Mathf.Floor(timeLeft / 60).ToString("00");
                string seconds = Mathf.Floor(timeLeft % 60).ToString("00");

                timerDisplay.GetComponent<TextMesh>().text = minutes + ":" + seconds;
            }

            if (timeLeft <= timeForSignal && !alreadySignaled)
            {
                alreadySignaled = true;
                GameObject[] lights = GameObject.FindGameObjectsWithTag("Light");
                for (int i = 0; i < lights.Length; i++)
                {
                    if (lights[i].GetComponent<Light>() != null)
                        lights[i].GetComponent<SwitchEmission>().startSignal(Color.red);
                }
            }
        }
	}


    public void GameOver()
    {
        Debug.Log("Game Over!");

        // Update timer:
        timerDisplay.GetComponent<TextMesh>().text = "--:--";

        // All lights to red!
        GameObject[] lights = GameObject.FindGameObjectsWithTag("Light");
        for (int i = 0; i < lights.Length; i++)
        {
            if (lights[i].GetComponent<Light>() != null)
                lights[i].GetComponent<Light>().color = Color.red;
        }
    }

    public void Win()
    {

    }

    public void changeTimerSpeed(float multiplier)
    {
        timeStep *= multiplier;
    }



}
