using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyPool : BasePool<EnemyStats>
{
    public override EnemyStats Get()
    {
        EnemyStats enemy = m_Pool.Get();
        // 重置敌人数据
        enemy.ResetStats();
        return enemy;
    }
}
