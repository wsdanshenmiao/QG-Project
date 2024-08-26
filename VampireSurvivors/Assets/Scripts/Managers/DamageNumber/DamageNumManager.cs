using UnityEngine;

public class DamageNumPool : BasePool<DamageNum>
{
    private static DamageNumPool m_Instance;
    public static DamageNumPool Instance => m_Instance;

    protected override void Awake()
    {
        if (m_Instance != null){
            Destroy(gameObject);
        }
        else{
            m_Instance = (DamageNumPool)this;
            base.Awake();
        }
    }

    protected void OnDestroy()
    {
        if (m_Instance == this)
            m_Instance = null;
    }

    public void SpawnDamage(int damage, Vector3 pos)
    {
        DamageNum damageNum = Get();
        damageNum.SetText(damage);
        damageNum.transform.position = pos;
        StartCoroutine(damageNum.AutoRelease());
        damageNum.gameObject.SetActive(true);
    }
}
