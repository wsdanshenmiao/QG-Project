using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Pool;

public class BasePool<T> : MonoBehaviour where T : Component
{
    protected ObjectPool<T> m_Pool;

    [SerializeField] protected T m_Prefab;
    [SerializeField] protected int m_DefaultSize = 100;
    [SerializeField] protected int m_MaxSize = 1000;
    [SerializeField] protected bool m_CollectionCheck = true;

    public int CountActive => m_Pool.CountActive;
    public int CountInactive => m_Pool.CountInactive;
    public int CountAll => m_Pool.CountAll;

    protected virtual void Awake()
    {
        m_Pool = new ObjectPool<T>(
            CreatePooledItem, 
            OnTakeFormPool, 
            OnReturnedToPool, 
            OnDestroyPoolObject,
            m_CollectionCheck, 
            m_DefaultSize,
            m_MaxSize);
    }

    protected virtual T CreatePooledItem() =>Instantiate(m_Prefab, transform);

    protected virtual void OnTakeFormPool(T obj) => obj.gameObject.SetActive(true);

    protected virtual void OnReturnedToPool(T obj) => obj.gameObject.SetActive(false);

    protected virtual void OnDestroyPoolObject(T obj) => Destroy(obj.gameObject);

    public virtual T Get() => m_Pool.Get();
    public virtual void Release(T item) => m_Pool.Release(item);
    public virtual void Clear() => m_Pool.Clear();
    public virtual void Dispose() => m_Pool.Dispose();

    public void SetPrefab(T prefab) => m_Prefab = prefab;
}
