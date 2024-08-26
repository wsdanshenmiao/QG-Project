using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "New Player Data", menuName = "Character/Player/PlayerData")]

public class PlayerData_SO : ScriptableObject
{
    // 基础生命再生
    public int BaseHpRegen = 1;
    // 基础拾取范围
    public int BasePickupRange = 10;
    // 基础穿透个数
    public int BasePenetrationsNumber = 0;
}
