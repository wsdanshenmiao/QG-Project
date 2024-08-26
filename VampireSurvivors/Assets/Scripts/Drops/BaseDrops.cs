using UnityEngine;

public abstract class BaseDrops : MonoBehaviour
{
    public DropsData_SO DropsData;
    public int DropCount = 1;

    protected DropsPool m_DropsPool;

    protected virtual void Awake()
    {
        m_DropsPool = GetComponentInParent<DropsPool>();
    }

    protected abstract void MoveToPlayer();

    protected abstract void OnTriggerEnter2D(Collider2D collision);
}
