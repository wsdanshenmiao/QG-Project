using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class BulletLauncher : Singleton<BulletLauncher>
{
    [SerializeField] private Bullets[] m_BulletPrefab;

    public Dictionary<string, BulletPool> BulletPools = new Dictionary<string, BulletPool>();

    private void Start()
    {
        // 初始化不同子弹的对象池
        foreach(Bullets bullet in m_BulletPrefab){
            GameObject poolHolder = new GameObject($"Pool:{bullet.name}");
            poolHolder.transform.SetParent(transform);

            BulletPool pool = poolHolder.AddComponent<BulletPool>();
            pool.SetPrefab(bullet);

            BulletPools.Add(bullet.BulletData.Type, pool);
        }
    }

    public void LaunchBullet(CharacterStats launcher, BulletData_SO bulletData, Transform target, Vector3 mousePos, Vector3 pos, int layerMask)
    {        
        BulletPool bulletPool;
        if (BulletPools.TryGetValue(bulletData.Type, out bulletPool)){
            bulletPool.CreateBullet(launcher, bulletData, target, mousePos, pos, layerMask);
        }
    }

}
