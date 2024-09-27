using UnityEngine;

public class EnemyCollisionBullet : Bullets
{
    private Transform m_EnemyTransform;

    protected override void Start()
    {
        m_EnemyTransform = GetComponentInParent<Transform>();
        transform.position = m_EnemyTransform.position;
    }

    protected override void CollisionDetection()
    {
        Vector2 dir = transform.position - m_PrePos;
        float distance = dir.magnitude + 2 * BulletData.Radius;
        dir.Normalize();
        Vector3 starPos = m_PrePos - new Vector3(dir.x, dir.y, 0) * BulletData.Radius;
        RaycastHit2D hitInfo = Physics2D.CircleCast(starPos, BulletData.Radius, dir, distance, layerMask);
        if (hitInfo.collider != null)
        {
            // 判断子弹是否已经穿过物体，防止子弹在射出还未碰到时就判定碰撞
            Vector3 pos = hitInfo.collider.transform.position;
            Vector3 bTot = pos - transform.position;
            if (Mathf.Cos(Vector3.Angle(bTot, MoveDir)) > 0)
                return;

            CharacterStats defener = hitInfo.collider.gameObject.GetComponent<CharacterStats>();
            CharacterStats.TakeDamage(Launcher, defener, this);
        }
    }

    protected override void Release()
    {
    }

    protected override void UpdateBullet()
    {
        m_PrePos = transform.position;
        transform.position = m_EnemyTransform.position;
    }
}
