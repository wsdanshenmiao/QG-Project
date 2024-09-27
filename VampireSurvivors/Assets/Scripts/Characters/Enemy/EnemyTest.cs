using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// 生成敌人
/// </summary>
//public class EnemyTest : Singleton<EnemyGeneration>
public class EnemyTest : MonoBehaviour
{
    // 所有怪物的Prefab
    [SerializeField] private EnemyStats[] m_EnemyPrefab;
    // 隔一段时间检测敌人数量
    [SerializeField] private float m_CheckTime = 10;
    // 基础敌人数量
    [SerializeField] private int m_BaseEnemyCount = 50;
    // 每一波增加的敌人数量
    [SerializeField] private int m_IncreaseEnemyNum = 10;

    // 每次生成怪的固定数量
    private int m_PreWaveEnemyNum = 4;

    // 生成下一波怪的时间
    private float m_PreWaveTime;
    private float m_CurrentTime = 0;

    private bool m_EnableGenerate = true;

    private int m_ChunkWidth;
    private int m_ChunkHeight;

    private void Start()
    {
        m_ChunkWidth = GameManager.Instance.MapData.MapWidth / GameManager.Instance.MapData.ChunkWidth;
        m_ChunkHeight = GameManager.Instance.MapData.MapHeight / GameManager.Instance.MapData.ChunkHeight;
    }

    // Update is called once per frame
    void Update()
    {
        StartCoroutine(CheckEnemyCount());
        if (!m_EnableGenerate) return;

        // 每波生成的敌人总数
        int enemyCout = m_BaseEnemyCount + m_IncreaseEnemyNum * GameManager.Instance.CurrentWaveNumber;
        // 生成敌人的次数
        float generateCount = enemyCout / m_PreWaveEnemyNum;
        m_PreWaveTime = GameManager.Instance.WaveTime / generateCount;

        // 间隔特定时间生成怪物
        m_CurrentTime += Time.deltaTime;
        if (m_CurrentTime > m_PreWaveTime)
        {
            GenerateEnemy();
            m_CurrentTime = 0;
        }
    }

    /// <summary>
    /// 根据当前波数生成敌人
    /// </summary>
    private void GenerateEnemy()
    {
        // 随机选择怪物Prefab
        EnemyStats enemyPrefab = m_EnemyPrefab[Random.Range(0, m_EnemyPrefab.Length)];

        // 随机选择一个区块
        MapData_SO mapData = GameManager.Instance.MapData;
        float chunkNumX = Random.Range(0, mapData.ChunkWidth);
        float chunkNumY = Random.Range(0, mapData.ChunkHeight);

        // 在一个区块中生成一堆敌人
        for (int i = 0; i < m_PreWaveEnemyNum; ++i)
        {
            float x = Random.Range(chunkNumX * m_ChunkWidth, m_ChunkWidth * (chunkNumX + 1));
            float y = Random.Range(chunkNumY * m_ChunkHeight, m_ChunkHeight * (chunkNumY + 1));

            EnemyStats enemy = Instantiate(enemyPrefab, new Vector3(x - mapData.MapWidth * 0.5f, y - mapData.MapHeight * 0.5f, 0), Quaternion.identity);
        }
    }

    private IEnumerator CheckEnemyCount()
    {
        yield return new WaitForSeconds(m_CheckTime);

        int totalActiveCout = 0;
        foreach (var enemy in FindObjectsOfType<EnemyStats>())
        {
            totalActiveCout++;
        }
        m_EnableGenerate = totalActiveCout > GameManager.Instance.MaxEnemyCount ? false : true;
    }

    private void OnDrawGizmos()
    {

    }
}