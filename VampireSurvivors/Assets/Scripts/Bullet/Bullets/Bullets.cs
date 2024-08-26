using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEditor.PackageManager;
using UnityEngine;

/// <summary>
/// 基础子弹
/// 可调整AngularSpeed来达到追踪效果，为0时不追踪
/// </summary>
public abstract class Bullets : MonoBehaviour
{
    public BulletData_SO BulletData;
    // 打击目标的位置
    public Transform Target;
    // 子弹的移动方向
    public Vector3 MoveDir;
    // 打击目标所在的层级
    public int layerMask;
    // 子弹的发射者
    public CharacterStats Launcher;

    protected BulletPool m_BulletPool;

    protected Vector3 m_PrePos;
    // 子弹的剩余穿透次数
    protected int m_Life;

    protected virtual void Start()
    {
        m_BulletPool = GetComponentInParent<BulletPool>();
    }

    protected virtual void OnEnable()
    {
        m_Life = BulletData.PenetrationNum;
    }

    /// <summary>
    /// 更新子弹
    /// </summary>
    protected virtual void FixedUpdate()
    {
        UpdateBullet();
        CollisionDetection();
    }

    protected abstract void UpdateBullet();

    /// <summary>
    /// 自动销毁子弹协程
    /// </summary>
    /// <returns></returns>
    public virtual IEnumerator AutoRelease()
    {
        yield return new WaitForSeconds(BulletData.DurationTime);
        Release();
    }

    /// <summary>
    /// 判断碰撞
    /// </summary>
    protected abstract void CollisionDetection();

    /// <summary>
    /// 销毁子弹
    /// </summary>
    protected abstract void Release();
}
