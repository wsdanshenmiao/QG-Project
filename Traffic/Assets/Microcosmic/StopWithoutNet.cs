/*
using UnityEngine;
using Dreamteck.Splines;
using System.Collections;

public class StopWithoutNet : MonoBehaviour
{
    public SplineComputer splineComputer;
    public SplineFollower follower;
    public float WaitTime = 2;
    public float StopTime = 2;

    void Start()
    {
        follower.follow = false;
        StartCoroutine(FollowSplineWithPause());
    }

    IEnumerator FollowSplineWithPause()
    {
        // 开始跟随样条曲线
        follower.follow = true;

        // 等待到达某个关键点
        yield return new WaitForSeconds(WaitTime);

        // 停顿 2 秒钟
        follower.follow = false;
        yield return new WaitForSeconds(StopTime);

        // 继续跟随样条曲线
        follower.follow = true;
    }
}
*/