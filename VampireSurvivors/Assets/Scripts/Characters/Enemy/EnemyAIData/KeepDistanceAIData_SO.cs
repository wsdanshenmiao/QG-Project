using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "New KeepDistanceAI Data", menuName = "Character/Enemy/AI Data/KeepDistance")]

// 与玩家保持距离的敌人的AI的数据
public class KeepDistanceAIData_SO : BaseAIData_SO
{
    // 与玩家保持的距离，该距离不能太小
    public float Distance;
    // 与自己的距离,保持距离后会随机以自己为中心移动
    public float SelfDistance;
    // 与玩家保持距离的界限
    public float radius;
    // 保持锁定目标不变的持续时间
    public int DurationTime;
    // 移动速度
    public int speed;
}
