using System;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class MenuManager : Singleton<MenuManager>
{
    private Button m_StartButton;
    private Button m_QuitButton;

    protected override void Awake()
    {
        base.Awake();

        Button[] buttons = GetComponentsInChildren<Button>();
        m_StartButton = Array.Find<Button>(buttons, data => { return data.name == "Start"; });
        m_QuitButton = Array.Find<Button>(buttons, data => { return data.name == "Quit"; });
    }

    private void Start()
    {
        m_StartButton.onClick.AddListener(StartGame);
        m_QuitButton.onClick.AddListener(QuitGame);
    }

    public void StartGame()
    {
        GameManager.Instance.CurrentWaveNumber = 1;
        GameManager.Instance.BeginGame = true;
        SceneManager.LoadScene(1);
    }

    public void QuitGame()
    {
        Application.Quit();
        Debug.Log("退出游戏");
    }

}
