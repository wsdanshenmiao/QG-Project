using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public class CameraControl : MonoBehaviour
{
    private Transform m_Target;

    // Start is called before the first frame update
    void Start()
    {
        m_Target = FindAnyObjectByType<PlayerControl>().transform;
    }

    // ������ƶ���������ƶ�
    void LateUpdate()
    {
        transform.position = new Vector3(m_Target.position.x, m_Target.position.y, transform.position.z);
    }
}
