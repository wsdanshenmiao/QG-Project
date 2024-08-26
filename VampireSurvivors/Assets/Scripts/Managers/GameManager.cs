using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameManager : DontDestorySingleton<GameManager>
{
    public MapData_SO MapData;

    // 最大波数
    public int MaxWaveNumber = 20;
    // 当前波数
    public int CurrentWaveNumber = 0;
    // 每一波的时间
    public float WaveTime = 60;
    public float CurrentWaveTime;

    // 可同时存在的最大敌人数
    public int MaxEnemyCount = 1000;

    public bool BeginGame = false;

    private void Start()
    {
        CurrentWaveTime = WaveTime;
    }

    private void Update()
    {
        if (BeginGame)
            ManageGame();
    }

    private void ManageGame()
    {
        CurrentWaveTime -= Time.deltaTime;
        if(CurrentWaveTime <= 0){
            CurrentWaveTime = WaveTime;
            ++CurrentWaveNumber;
        }
        if(CurrentWaveNumber > MaxWaveNumber){
            CurrentWaveNumber = 0;
            SceneManager.LoadSceneAsync(0);
        }
    }
}
