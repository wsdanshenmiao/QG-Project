using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Chase : MonoBehaviour
{
    public Rigidbody2D self;
    public ChaseAIData_SO Data;  // 用于追踪的参数
    private GameObject target;
    private float LockTime = 0.0f;
    
    void Start()
    {
        FindClosestPlayer();
    }

    
    void Update()
    {
                
        self.velocity = (target.transform.position - transform.position).normalized * Data.speed;
        if(LockTime >= Data.DurationTime){
            Debug.Log("寻找新目标");
            FindClosestPlayer();            
            LockTime = 0.0f;
        }
        LockTime += Time.deltaTime;
    }


    void FindClosestPlayer()
    {
        GameObject[] players = GameObject.FindGameObjectsWithTag("Player");
        target = null;
        float closestDistance = Mathf.Infinity;

        foreach (GameObject player in players)
        {
            float distance = Vector3.Distance(transform.position, player.transform.position);
            if (distance < closestDistance )
            {
                closestDistance = distance;
                target = player;
            }
        }

        if (target != null)
        {
            Debug.Log("找到了玩家");
            // 在这里可以添加敌人朝向玩家移动的逻辑
        }
    }

}
