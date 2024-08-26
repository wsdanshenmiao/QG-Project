using System.Collections;
using UnityEngine;

public class SkeletonControl : BaseEnemyControl
{
    private bool m_FinishAppear = false;

    // Update is called once per frame
    protected override void Update()
    {
        base.Update();
        SwitchAnimation();
        if(m_Enemystats.IsDeath){
            m_Rigidbody.velocity = new Vector2(0, 0);
            GetComponent<CircleCollider2D>().enabled = false;
            StartCoroutine(WaitForRelease());
        }
    }

    protected override void MoveToPlayer()
    {
        if (!m_FinishAppear || m_Enemystats.IsDeath) return;
        base.MoveToPlayer();
    }

    protected void SwitchAnimation()
    {
        m_Anim.SetBool("FinishAppear", m_FinishAppear);
        m_Anim.SetBool("Death", m_Enemystats.IsDeath);
    }

    private void FinishAppear()
    {
        m_FinishAppear = true;
    }

    IEnumerator WaitForRelease()
    {
        yield return new WaitForSeconds(1);
        m_Enemystats.EnemyPool.Release(m_Enemystats);
    }
}
