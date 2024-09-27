using System;
using UnityEngine;

public class PlayerControl : Singleton<PlayerControl>
{
    public GameObject Enemys;

    private PlayerStats m_PlayerStats;
    private Animator m_Anim;
    private Rigidbody2D m_Rigidbody;
    private Vector3 m_MoveInput;

    public Bullets[] Bullets;

    protected override void Awake()
    {
        base.Awake();
        m_Anim = GetComponent<Animator>();
        m_Rigidbody = GetComponent<Rigidbody2D>();
        m_PlayerStats = GetComponent<PlayerStats>();
    }

    private void Update()
    {
        Vector3 bulletPos = transform.position;
        bulletPos.x += 2 * transform.localScale.x;
        bulletPos.y += 0.8f;
        if(m_PlayerStats.IsAttack){
            Vector3 mousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
            mousePos.z = 0;
            Bullets bullet = BulletLauncher.Instance.LaunchBullet(
                m_PlayerStats,
                Array.Find<Bullets>(Bullets, data => { return data.BulletData.Type == "BaseBullet"; }).BulletData,
                Enemys.GetComponentInChildren<Transform>(), mousePos, bulletPos, 1 << 6);
            BulletPool.RotateBullet(bullet);
        }
        if(Input.GetMouseButtonDown(1)){
            Bullets bullet = BulletLauncher.Instance.LaunchBullet(
                m_PlayerStats,
                Array.Find<Bullets>(Bullets, data => { return data.BulletData.Type == "FireBallBullet"; }).BulletData,
                transform, transform.position, transform.position, 1 << 6);
            BulletPool.RotateBullet(bullet);
        }
        m_MoveInput.x = Input.GetAxisRaw("Horizontal");
        m_MoveInput.y = Input.GetAxisRaw("Vertical");
        SwitchAnimation();
        AdjustX(m_MoveInput);
    }

    private void FixedUpdate()
    {
        MovePlayer(m_MoveInput.normalized);
    }

    private void MovePlayer(Vector3 moveInput)
    {
        Vector3 position = transform.position;
        if(m_PlayerStats.IsMove){
            position += moveInput * m_PlayerStats.BaseSpeed * Time.deltaTime;
        }
        m_Rigidbody.MovePosition(position);
    }

    private void AdjustX(Vector3 moveInput)
    {
        Vector3 localScale = transform.localScale;
        Vector3 mousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
        if (m_PlayerStats.IsAttack && (mousePos.x * localScale.x < 0)) {
            transform.localScale = new Vector3(-localScale.x, localScale.y, localScale.z);
        }
        else if (moveInput.x * localScale.x < 0) {
            transform.localScale = new Vector3(-localScale.x, localScale.y, localScale.z);
        }
    }

    private void SwitchAnimation()
    {
        m_PlayerStats.IsMove = m_MoveInput.x != 0 || m_MoveInput.y != 0 ? true : false;
        if (Input.GetMouseButton(0)) {
            m_PlayerStats.IsAttack = true;
            m_Anim.SetBool("Attack", true);
            m_Anim.SetBool("Run", false);
        }
        else {
            m_PlayerStats.IsAttack = false;
            m_Anim.SetBool("Run", m_PlayerStats.IsMove);
            m_Anim.SetBool("Attack", false);
        }
    }

    public bool IsDeath()
    {
        return m_PlayerStats.IsDeath;
    }
}
