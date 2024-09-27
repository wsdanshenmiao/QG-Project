using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BulletPool : BasePool<Bullets> 
{
    public Bullets CreateBullet(CharacterStats launcher, 
        BulletData_SO bulletData, 
        Transform target, 
        Vector3 mousePos, 
        Vector3 pos, 
        int layerMask)
    {
        Bullets bullet = Get();
        bullet.transform.position = new Vector3(pos.x, pos.y, 0);    // 生成的位置
        bullet.BulletData = bulletData;
        bullet.Target = target;
        bullet.layerMask = layerMask;
        bullet.Launcher = launcher;
        bullet.MoveDir = (mousePos - bullet.transform.position).normalized;

        // 开启子弹自销毁协程
        bullet.StartCoroutine(bullet.AutoRelease());

        return bullet;
    }

    static public void RotateBullet(Bullets bullet)
    {
        // 子弹的初始偏转角
        float randomAngel = Random.Range(-bullet.BulletData.DirOffset, bullet.BulletData.DirOffset);
        float angel = Vector2.Angle(Vector2.right, bullet.MoveDir) + randomAngel;
        angel = Vector2.right.y < bullet.MoveDir.y ? angel : -angel;
        bullet.MoveDir = Quaternion.Euler(0, 0, randomAngel) * bullet.MoveDir;
        bullet.transform.Find("Sprite").localEulerAngles = new Vector3(0, 0, angel);
    }
}
