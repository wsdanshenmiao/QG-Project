using UnityEngine;

public class PlayerStats : CharacterStats
{
    [SerializeField] private PlayerData_SO TemplatePlayerData;
    [HideInInspector] public PlayerData_SO PlayerData;

    // 玩家经验
    [HideInInspector] public long Experience = 0;
    // 玩家经验槽最大容量
    public long MaxExperience = 100;
    // 玩家等级
    [HideInInspector] public int Level = 0;
    // 金币数量
    [HideInInspector] public int Gold = 0;
    // 杀敌数
    [HideInInspector] public int KillNum = 0;
    // 总杀敌数
    [HideInInspector] public int TotalKillNum = 0;

    // 玩家状态
    public bool IsMove = false;
    public bool IsAttack = false;

    #region Read From PlayerData_SO

    // 基础生命再生
    public int BaseHpRegen
    {
        get { if (PlayerData) { return PlayerData.BaseHpRegen; } else { return 0; } }
        set { PlayerData.BaseHpRegen = value; }
    }

    // 基础拾取范围
    public int BasePickupRange
    {
        get { if (PlayerData) { return PlayerData.BasePickupRange; } else { return 0; } }
        set { PlayerData.BasePickupRange = value; }
    }

    // 基础穿透个数
    public int BasePenetrationsNumber
    {
        get { if (PlayerData) { return PlayerData.BasePenetrationsNumber; } else { return 0; } }
        set { PlayerData.BasePenetrationsNumber = value; }
    }


    #endregion

    protected override void Awake()
    {
        ResetStats();
    }

    protected void Update()
    {
        CurrentInvalidTime += Time.deltaTime;
        if(Experience > MaxExperience){
            MaxExperience <<= 2;
            Experience = 0;
            ++Level;
        }
    }

    public override void ResetStats()
    {
        base.ResetStats();
        PlayerData = Instantiate(TemplatePlayerData);
        MaxHP = BaseHP;
        CurrentHP = MaxHP;
        Experience = 0;
        Level = 0;
        Gold = 0;
        KillNum = 0;
        TotalKillNum = 0;
    }

}
