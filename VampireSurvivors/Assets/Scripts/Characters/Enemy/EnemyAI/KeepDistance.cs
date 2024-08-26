using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class KeepDistance : MonoBehaviour
{
    public Rigidbody2D self;
    public KeepDistanceAIData_SO Data;  // 用于追踪的参数
    private GameObject target;
    private float LockTime = 0.0f;

    void Start()
    {
        FindClosestPlayer();
    }

    void Update()
    {
        float currentDistance = Vector3.Distance(transform.position, target.transform.position);
        // 开润
        if( currentDistance < Data.Distance - Data.radius){
            self.velocity = ( transform.position - target.transform.position).normalized * Data.speed;
        }
        // 追击
        else if( currentDistance > Data.Distance + Data.radius){
            self.velocity = (target.transform.position - transform.position).normalized * Data.speed;
        }
        else{

        }


        if(LockTime >= Data.DurationTime){
            Debug.Log("寻找新目标");
            FindClosestPlayer();
            LockTime = 0.0f;
        }
        LockTime += Time.deltaTime;

    }

    void MoveTowardsPlayer(){
        Wander();
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
            //Debug.Log("找到了玩家");
        }
    }

    void Wander()
    {
        //Vector3 wanderTarget = transform.position + (Vector3)Random.insideUnitCircle * Data.SelfDistance;

        //Vector3 direction = (wanderTarget - transform.position).normalized;
        //self.velocity = direction * Data.speed; // 移动速度
        self.velocity = ((Vector3)Random.insideUnitCircle).normalized * Data.speed;
    }

}
