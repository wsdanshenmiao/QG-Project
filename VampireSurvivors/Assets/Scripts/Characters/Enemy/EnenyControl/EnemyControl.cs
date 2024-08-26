using UnityEngine;
using UnityEngine.UI;

public abstract class BaseEnemyControl : MonoBehaviour
{
    protected EnemyStats m_Enemystats;
    protected Transform m_PlayerTransform;
    protected Animator m_Anim;
    protected Rigidbody2D m_Rigidbody;
    protected Slider m_HPSlider;
    protected Transform m_SpriteTransform;

    // Start is called before the first frame update
    protected virtual void Awake()
    {
        m_PlayerTransform = PlayerControl.Instance.transform;
        m_Enemystats = GetComponent<EnemyStats>();
        m_Anim = GetComponent<Animator>();
        m_Rigidbody = GetComponent<Rigidbody2D>();
        Canvas HpCanvas = GetComponentInChildren<Canvas>();
        m_HPSlider = HpCanvas.GetComponentInChildren<Slider>();
        Transform[] transforms = GetComponentsInChildren<Transform>();
        foreach(var transform in transforms){
            if(transform.name == "Sprite"){
                m_SpriteTransform = transform;
                break;
            }
        }
    }

    protected virtual void Start()
    {
        // 初始化角色状态条
        m_HPSlider.maxValue = m_Enemystats.MaxHP;
        m_HPSlider.value = m_Enemystats.CurrentHP;
    }

    protected virtual void Update()
    {
        m_HPSlider.value = m_Enemystats.CurrentHP;
    }

    protected virtual void FixedUpdate()
    {
        MoveToPlayer();
    }

    protected virtual void MoveToPlayer()
    {
        if (!m_Enemystats.CanMove) return;

        Vector3 moveDir = (m_PlayerTransform.position - transform.position).normalized;
        Vector3 STlocalScale = m_SpriteTransform.localScale;
        if (moveDir.x * STlocalScale.x > 0){
            m_SpriteTransform.localScale = new Vector3(-STlocalScale.x, STlocalScale.y, STlocalScale.z);    
        }

        m_Rigidbody.velocity = moveDir * m_Enemystats.CurrentSpeed;
        // Vector3 position = transform.position + moveDir * m_Enemystats.CurrentSpeed * Time.deltaTime;
        // m_Rigidbody.MovePosition(position);
    }
}
