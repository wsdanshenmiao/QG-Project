using UnityEngine;

public class Experience : BaseDrops
{
    protected virtual void Update()
    {
        MoveToPlayer();
    }

    protected override void MoveToPlayer()
    {
        // 不进行归一化，掉落物越远速度越快
        Vector3 moveDir = PlayerControl.Instance.transform.position - transform.position;
        moveDir = moveDir.magnitude < DropsData.MoveSpeed ? moveDir.normalized * DropsData.MoveSpeed : moveDir;
        transform.position += Time.deltaTime * moveDir;
    }

    protected override void OnTriggerEnter2D(Collider2D collision){
        if(collision.tag == "Player"){
            PlayerStats player = collision.gameObject.GetComponent<PlayerStats>();
            player.Experience += DropCount;
            m_DropsPool.Release(this);
        }
    }

}
