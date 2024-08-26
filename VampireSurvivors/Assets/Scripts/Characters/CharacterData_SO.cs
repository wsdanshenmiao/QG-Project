using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "New Character Data", menuName = "Character/CharacterData")]

public class CharacterData_SO : ScriptableObject
{
    // 最大血量
    public int MaxHP = 50;
    // 基础血量
    public int BaseHP = 50;
    // 基础速度
    public float BaseSpeed = 10;
    // 基础伤害
    public int BaseDamage = 10;
    // 基础护甲
    public int BaseArmor = 0;
    // 基础攻击速度
    public float BaseAttackSpeed = 1;
    // 当前血量
    public int CurrentHP = 100;
    // 攻击范围
    public int BaseAttackRange = 4;
    // 无敌帧
    public float InvalidFrame = 0.1f;
    // 暴击率
    public float BaseCriticalChance = 0.1f;
    // 抗击退系数
    public float ResistKnockFactor = 0.2f;
}
