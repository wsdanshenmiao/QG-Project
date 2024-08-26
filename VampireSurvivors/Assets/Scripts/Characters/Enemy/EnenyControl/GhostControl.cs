public class GhostControl : BaseEnemyControl
{
    protected override void Update()
    {
        base.Update();
        if(m_Enemystats.IsDeath){
            m_Enemystats.EnemyPool.Release(m_Enemystats);
        }
    }


    protected override void MoveToPlayer()
    {
        if (m_Enemystats.IsDeath) return;
        base.MoveToPlayer();
    }
}
