using System.Collections;
using Unity.VisualScripting;
using UnityEngine;

/// <summary>
/// 围绕发射者旋转的火球子弹
/// pos需为发射者本身
/// MoveDir无效
/// PenetrationNum无效
/// DurationTime无效，子弹发出后不自动销毁
/// Speed无效
/// AngularSpeed为旋转角速度
/// DirOffset无效
/// </summary> 
public class FireBallBullet : Bullets
{
    public float GrowSpeed = 2f;

    private Transform m_SpriteTrans;
    private Vector3 m_TargetScale;
    private  Vector3 m_Scale;
    private bool m_Disappear = false;

    protected override void OnEnable()
    {
        base.OnEnable();
        m_Scale = transform.localScale;
        m_TargetScale = transform.localScale;
        transform.localScale = Vector3.zero;
        m_Disappear = false;
    }

    protected override void Start()
    {
        base.Start();
        Transform[] transforms = GetComponentsInChildren<Transform>();
        foreach(Transform trans in transforms){
            if(trans.name == "Sprite"){
                m_SpriteTrans = trans;
                break;
            }
        }
    }

    /// <summary>
    /// 围绕中心旋转
    /// </summary>
    protected override void UpdateBullet()
    {
        m_PrePos = m_SpriteTrans.position;

        transform.rotation *= Quaternion.Euler(0, 0, BulletData.AngularSpeed * Time.deltaTime);
        transform.position = Target.position;
        transform.localScale = Vector3.MoveTowards(transform.localScale, m_TargetScale, GrowSpeed * Time.deltaTime);
        
        m_TargetScale = m_Disappear ? Vector3.zero : m_TargetScale;
        if (transform.localScale == Vector3.zero){
            transform.localScale = m_Scale;
            m_BulletPool.Release(this);
        }
    }

    /// <summary>
    /// 自动销毁火球
    /// </summary>
    /// <returns></returns>
    public override IEnumerator AutoRelease()
    {
        float disappearTime = m_TargetScale.x == 0 ? transform.localScale.x : m_TargetScale.x / GrowSpeed;
        yield return new WaitForSeconds(BulletData.DurationTime - disappearTime);
        Release();
    }

    /// <summary>
    /// 子弹的碰撞检测
    /// </summary>
    protected override void CollisionDetection()
    {
        Vector2 dir = (m_SpriteTrans.position - m_PrePos).normalized;
        float distance = Vector2.Distance(m_SpriteTrans.position, transform.position);
        RaycastHit2D hitInfo = Physics2D.CircleCast(m_PrePos, BulletData.Radius, dir, distance, layerMask);
        if(hitInfo.collider != null){
            // 判断子弹是否已经穿过物体，防止子弹在射出还未碰到时就判定碰撞
            Vector3 pos = hitInfo.collider.transform.position;
            Vector3 bTot = pos - m_SpriteTrans.position;
            if (Mathf.Cos(Vector3.Angle(bTot, dir)) > 0) 
                return;

            CharacterStats defener = hitInfo.collider.gameObject.GetComponent<CharacterStats>();
            CharacterStats.TakeDamage(Launcher, defener, this);
        }
    }

    protected override void Release()
    {
        m_Disappear = true;
    }

    // protected void OnTriggerStay2D(Collider2D collision)
    // {
    //     if(layerMask >> collision.gameObject.layer == 1){
    //         CharacterStats defener = collision.gameObject.GetComponent<CharacterStats>();
    //         CharacterStats.TakeDamege(Launcher, defener, this);
    //     }
    // }

}
