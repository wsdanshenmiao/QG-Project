using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyStats : CharacterStats
{
    [SerializeField] private EnemyData_SO TemplateEnemyData;

    // 敌人的掉落物
    public BaseDrops[] EnemyDrops;

    [HideInInspector] public EnemyData_SO EnemyData;
    [HideInInspector] public EnemyPool EnemyPool;

    #region Read From EnemyData_SO

    // 敌人ID
    public string EnemyID
    {
        get { if (EnemyData == null) { return null; } else { return EnemyData.EnemyID; } }
        set { EnemyData.EnemyID = value; }
    }

    // 敌人外观
    public string Appearance
    {
        get { if (EnemyData == null) { return null; } else { return EnemyData.Appearance; } }
        set { EnemyData.Appearance = value; }
    }


    // 每波提升血量
    public int IncreaseHP
    {
        get { if (EnemyData == null) { return 0; } else { return EnemyData.IncreaseHP; } }
        set { EnemyData.IncreaseHP = value; }
    }

    // 每波提升伤害
    public int IncreaseDamege
    {
        get { if (EnemyData == null) { return 0; } else { return EnemyData.IncreaseDamage; } }
        set { EnemyData.IncreaseDamage = value; }
    }

    // 掉落经验数
    public int DropExperience
    {
        get { if (EnemyData == null) { return 0; } else { return EnemyData.DropExperience; } }
        set { EnemyData.DropExperience = value; }
    }

    // 掉落金币数
    public int DropGold
    {
        get { if (EnemyData == null) { return 0; } else { return EnemyData.DropGold; } }
        set { EnemyData.DropGold = value; }
    }

    // 掉落道具的几率
    public float PropChance
    {
        get { if (EnemyData == null) { return 0; } else { return EnemyData.PropChance; } }
        set { EnemyData.PropChance = value; }
    }

    // 死亡后发生的事件
    public List<string> DeathIncident
    {
        get { if (EnemyData == null) { return null; } else { return EnemyData.DeathIncident; } }
        set { EnemyData.DeathIncident = value; }
    }


    //怪物AI种类
    public BaseAIData_SO EnemyAiData
    {
        get { if (EnemyData == null) { return null; } else { return EnemyData.EnemyAiData; } }
        set { EnemyData.EnemyAiData = value; }
    }


    #endregion

    protected override void Awake()
    {
        ResetStats();
        EnemyPool = EnemyGeneration.Instance.EnemyPools.GetValueOrDefault(EnemyData.EnemyID);
    }

    public override void ResetStats()
    {
        base.ResetStats();
        EnemyData = Instantiate(TemplateEnemyData);
        MaxHP = BaseHP + IncreaseHP * GameManager.Instance.CurrentWaveNumber;
        CurrentHP = MaxHP;
        CurrentDamege = BaseDamege + IncreaseDamege * GameManager.Instance.CurrentWaveNumber;
        CurrentSpeed = BaseSpeed + Random.Range(-BaseSpeed / 20, BaseSpeed / 20);
    }

    private void Update()
    {
        CurrentInvalidTime += Time.deltaTime;
        if(CharacterData.CurrentHP <= 0 && !IsDeath){
            IsDeath = true;
            foreach(var drops in EnemyDrops){
                DropsGeneration.Instance.SpawnDrops(drops.DropsData.DropsID, EnemyData.DropExperience, transform.position);
            }
        }
    }

}
