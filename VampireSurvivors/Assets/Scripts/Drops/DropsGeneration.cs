using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public class DropsGeneration : Singleton<DropsGeneration>
{
    [SerializeField] private BaseDrops[] m_DropsPrefabs;

    public Dictionary<string, DropsPool> DropsPools = new Dictionary<string, DropsPool>();

    private void Start()
    {
        // 初始化不同子弹的对象池
        foreach(BaseDrops drops in m_DropsPrefabs){
            GameObject poolHolder = new GameObject($"Pool:{drops.name}");
            poolHolder.transform.SetParent(transform);

            DropsPool pool = poolHolder.AddComponent<DropsPool>();
            pool.SetPrefab(drops);

            DropsPools.Add(drops.DropsData.DropsID, pool);
        }
    }

    public void SpawnDrops(string dropsID, int dropCount, Vector3 pos)
    {
        DropsPool pool;
        if(DropsPools.TryGetValue(dropsID, out pool)){
            BaseDrops drops = pool.Get();
            drops.DropCount = dropCount;
            drops.transform.position = new Vector3(pos.x + Random.value, pos.y + Random.value, pos.z);
        }
    }
}
