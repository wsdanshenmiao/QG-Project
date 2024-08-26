using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "New Enemy Data", menuName = "Character/Enemy/Enemy Data")]

// 敌人数据
public class EnemyData_SO : ScriptableObject
{
    // 敌人ID
    public string EnemyID = null;
    // 敌人外观
    public string Appearance = null;
    // 每波提升血量
    public int IncreaseHP = 5;
    // 每波提升伤害
    public int IncreaseDamage = 1;
    // 掉落经验数
    public int DropExperience = 10;
    // 掉落金币数
    public int DropGold = 5;
    // 掉落道具的几率
    public float PropChance = 0.05f;
    // 死亡后发生的事件
    public List<string> DeathIncident = null;
    //怪物AI种类
    public BaseAIData_SO EnemyAiData = null;
}
