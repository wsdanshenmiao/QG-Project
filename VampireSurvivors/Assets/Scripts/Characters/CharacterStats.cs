using System.Collections;
using UnityEngine;

public class CharacterStats : MonoBehaviour
{
    // 角色的填表属性
    [SerializeField] private CharacterData_SO TemplateCharacterData;
    [HideInInspector] public CharacterData_SO CharacterData;

    // 角色当前的属性
    [HideInInspector] public float CurrentInvalidTime = 0;
    [HideInInspector] public float CurrentCriticalChange;
    [HideInInspector] public int CurrentArmor;
    [HideInInspector] public int CurrentDamege;
    [HideInInspector] public float CurrentSpeed;

    // 角色状态
    [HideInInspector] public bool IsDeath = false;
    [HideInInspector] public bool CanMove = true;

    // 读取填表属性
    #region Read From CharacterData_SO

    // 最大血量
    public int MaxHP
    {
        get { if (CharacterData) { return CharacterData.MaxHP; } else { return 0; } }
        set { CharacterData.MaxHP = value; }
    }

    // 基础血量
    public int BaseHP
    {
        get { if (CharacterData == null) { return 0; } else { return CharacterData.BaseHP; } }
        set { CharacterData.BaseHP = value; }
    }

    // 速度
    public float BaseSpeed
    {
        get { if (CharacterData == null) { return 0; } else { return CharacterData.BaseSpeed; } }
        set { CharacterData.BaseSpeed = value; }
    }
    // 基础伤害
    public int BaseDamege
    {
        get { if (CharacterData == null) { return 0; } else { return CharacterData.BaseDamage; } }
        set { CharacterData.BaseDamage = value; }
    }

    // 基础护甲
    public int BaseArmor
    {
        get { if (CharacterData) { return CharacterData.BaseArmor; } else { return 0; } }
        set { CharacterData.BaseArmor = value; }
    }

    public int BaseAttackRange
    {
        get { if (CharacterData) { return CharacterData.BaseAttackRange; } else { return 0; } }
        set { CharacterData.BaseAttackRange = value; }
    }

    // 当前血量
    public int CurrentHP
    {
        get { if (CharacterData) { return CharacterData.CurrentHP; } else { return 0; } }
        set { CharacterData.CurrentHP = value; }
    }

    // 无敌帧
    public float InvalidFrame
    {
        get { if (CharacterData) { return CharacterData.InvalidFrame; } else { return 0; } }
        set { CharacterData.InvalidFrame = value; }
    }

    // 暴击率
    public float BaseCriticalChance
    {
        get { if (CharacterData) { return CharacterData.BaseCriticalChance; } else { return 0; } }
        set { CharacterData.BaseCriticalChance = value; }
    }

    // 抗击退系数
    public float ResistKnockFactor
    {
        get { if (CharacterData) { return CharacterData.ResistKnockFactor; } else { return 0; } }
        set { CharacterData.ResistKnockFactor = value; }
    }

    #endregion

    protected virtual void Awake()
    {
        ResetStats();
    }

    /// <summary>
    /// 重设角色当前状态
    /// </summary>
    public virtual void ResetStats()
    {
        CharacterData = Instantiate(TemplateCharacterData);
        CurrentInvalidTime = 0;
        CurrentCriticalChange = BaseCriticalChance;
        CurrentArmor = BaseArmor;
        CurrentDamege = BaseDamege;
        CurrentSpeed = BaseSpeed;
    }

    /// <summary>
    /// 造成伤害的函数，会造成击退
    /// </summary>
    /// <param name="attacker"></param> 攻击者
    /// <param name="defener"></param>  防御者
    static public void TakeDamage(CharacterStats attacker, CharacterStats defener, Bullets bullet)
    {
        if (defener.CurrentInvalidTime > defener.InvalidFrame)
        {
            defener.CurrentInvalidTime = 0;
            int damage = bullet.BulletData.Damage;
            // 伤害浮动
            damage += Random.Range(-damage / 10, damage / 10);
            // 暴击加成
            damage = Random.value < attacker.CurrentCriticalChange ? damage * 2 : damage;
            // 防御扣除伤害
            damage = Mathf.Max(damage - defener.CurrentArmor, 1);
            // 显示伤害
            DamageNumPool.Instance.SpawnDamage(damage, defener.transform.position);
            //  扣除伤害
            defener.CurrentHP -= damage;
            defener.CurrentHP = Mathf.Max(0, defener.CurrentHP);
            // 进行击退
            Rigidbody2D rb = defener.GetComponent<Rigidbody2D>();
            if (rb != null)
            {
                float force = Mathf.Max(0, bullet.BulletData.KnockFactor - defener.CharacterData.ResistKnockFactor);
                defener.StartCoroutine(defener.StopMove(0.2f));
                Knockback(rb, bullet.MoveDir, force);
            }
        }
    }

    /// <summary>
    /// 击退函数
    /// </summary>
    /// <param name="rb"></param>   操作的刚体
    /// <param name="direction"></param>    击退的方向
    /// <param name="force"></param>    击退的系数
    static public void Knockback(Rigidbody2D rb, Vector2 direction, float force)
    {
        rb.AddForce(direction.normalized * force, ForceMode2D.Impulse);
    }

    /// <summary>
    /// 通过协程暂停角色移动
    /// </summary>
    /// <param name="time"></param> 暂停的时间
    /// <returns></returns>
    IEnumerator StopMove(float time)
    {
        CanMove = false;
        yield return new WaitForSeconds(time);
        CanMove = true;
    }
}
