using System.Collections;
using UnityEngine;

public class GhostControl : BaseEnemyControl
{
    private Melt m_Melt;

    protected override void Start()
    {
        base.Start();
        m_Melt = GetComponent<Melt>();
    }

    protected override void Update()
    {
        base.Update();
        if(m_Enemystats.IsDeath){
            m_Rigidbody.velocity = new Vector2(0, 0);
            GetComponent<CircleCollider2D>().enabled = false;
            StartCoroutine(WaitForMelt());
            m_Melt.beginMelt = true;
        }
    }


    protected override void MoveToPlayer()
    {
        if (m_Enemystats.IsDeath) return;
        base.MoveToPlayer();
    }

    IEnumerator WaitForMelt()
    {
        yield return new WaitForSeconds(m_Melt.meltTime);
        m_Enemystats.EnemyPool.Release(m_Enemystats);
    }
}


