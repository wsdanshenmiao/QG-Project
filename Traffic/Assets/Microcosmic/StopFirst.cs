/*
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Dreamteck.Splines;

public class StopFirst : MonoBehaviour
{
    public SplineFollower follower; // 引用SplineFollower组件
    public double pausePoint = 0.122f; // 停顿点（0到1之间的值，表示样条路径的进度）
    public float pauseDuration = 2.0f; // 停顿时间（秒）

    private bool isPaused = false;
    private double resumePosition;
    private float pauseTimer;

    void Start()
    {
        if (follower == null)
        {
            follower = GetComponent<SplineFollower>();
        }
    }

    void Update()
    {
        if (isPaused)
        {
            // 如果处于停顿状态，暂停移动
            follower.follow = false;
            pauseTimer -= Time.deltaTime;
            if (pauseTimer <= 0)
            {
                // 停顿时间结束，恢复移动
                isPaused = false;
                follower.follow = true;
                follower.SetPercent(resumePosition);
            }
        }
        else
        {
            // 检查是否到达停顿点
            double progress = follower.result.percent;
            if (Mathf.Approximately((float)progress, (float)pausePoint))
            {
                isPaused = true;
                pauseTimer = pauseDuration;
                resumePosition = progress;
                Debug.Log("到达停顿点");
            }
        }
    }
}
*/