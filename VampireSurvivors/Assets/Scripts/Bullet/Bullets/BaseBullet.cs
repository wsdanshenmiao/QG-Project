using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEditor.PackageManager;
using UnityEngine;

/// <summary>
/// 基础子弹
/// 可调整AngularSpeed来达到追踪效果，为0时不追踪
/// </summary>
public class BaseBullet : Bullets
{
    /// <summary>
    /// 判断碰撞
    /// </summary>
    protected override void CollisionDetection()
    {
        Vector2 dir = (transform.position - m_PrePos).normalized;
        float distance = BulletData.Speed * BulletData.DurationTime;
        RaycastHit2D hitInfo = Physics2D.CircleCast(m_PrePos, BulletData.Radius, dir, distance, layerMask);
        if (hitInfo.collider != null)
        {
            // 判断子弹是否已经穿过物体，防止子弹在射出还未碰到时就判定碰撞
            Vector3 pos = hitInfo.collider.transform.position;
            Vector3 bTot = pos - transform.position;
            if (Mathf.Cos(Vector3.Angle(bTot, MoveDir)) > 0)
                return;

            CharacterStats defener = hitInfo.collider.gameObject.GetComponent<CharacterStats>();
            CharacterStats.TakeDamage(Launcher, defener, this);
            if (--m_Life < 0)
                Release();
        }
    }

    /// <summary>
    /// 销毁子弹
    /// </summary>
    protected override void Release()
    {
        m_BulletPool.Release(this);
    }

    protected override void UpdateBullet()
    {
        m_PrePos = transform.position;

        Transform child = transform.Find("Sprite");
        // 子弹的目标方向
        Vector3 offset = (Target.position - transform.position).normalized;
        // 子弹打中敌人的偏转角，子弹为追踪的时候使用
        float angle = Vector3.Angle(MoveDir, offset);

        // 子弹转弯需要的时间
        float wheelTime = angle / BulletData.AngularSpeed;
        float factor = Time.deltaTime / wheelTime;
        Vector3 dir = Vector3.Lerp(MoveDir, offset, factor).normalized;
        MoveDir = dir == Vector3.zero ? MoveDir : dir;
        // 子精灵旋转
        float childAngle = Vector3.Angle(Vector3.right, MoveDir);
        childAngle = Vector3.right.y < MoveDir.y ? childAngle : -childAngle;
        child.localEulerAngles = new Vector3(0, 0, childAngle);

        transform.position += MoveDir * BulletData.Speed * Time.deltaTime;

    }
}
