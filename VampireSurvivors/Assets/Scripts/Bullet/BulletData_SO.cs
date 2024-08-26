using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "New Bullet Data", menuName = "Bullet/BulletData")]

// 子弹的数据
public class BulletData_SO : ScriptableObject
{
    // 子弹的种类
    public string Type = "BaseBullet"; 
    // 子弹半径
    public float Radius = 0.1f;
    // 子弹穿透个数
    public int PenetrationNum = 1;
    // 子弹伤害
    public int Damage = 10;
    // 子弹持续时间
    public int DurationTime = 1;
    // 子弹速度
    public int Speed = 100;
    // 子弹角速度,角速度为0时子弹不追踪
    public int AngularSpeed = 0;
    // 子弹方向偏移
    public float DirOffset = 0.1f;
    // 子弹的击退系数
    public float KnockFactor = 0.5f;
}
