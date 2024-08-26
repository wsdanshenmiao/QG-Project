using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;
using UnityEngine.SceneManagement;


public class ScenesManager2D : DontDestorySingleton<ScenesManager2D>
{
    [DllImport("__Internal")]
    private static extern void SendMessageToParent(bool status, int num);

    [SerializeField] private bool m_EnableSwitch = false;
    private RaycastHit2D m_HitInfo;

    public string UserID;

    protected override void Awake()
    {
        base.Awake();
        UserID = null;
    }

    // Update is called once per frame
    void Update()
    {
        if (m_EnableSwitch)
            SwitchMicScenes();
    }

    private void SwitchMicScenes()
    {
        Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
        m_HitInfo = Physics2D.Raycast(ray.origin, ray.direction);

        if (Input.GetMouseButtonDown(0) && m_HitInfo.collider)
        {
            if (m_HitInfo.collider.CompareTag("ThreePathNode"))
            {
                SendMessageToParent(true, int.Parse(m_HitInfo.collider.name));
                SceneManager.LoadSceneAsync(1);
            }
            else if (m_HitInfo.collider.CompareTag("FourPathNode"))
            {
                SendMessageToParent(true, int.Parse(m_HitInfo.collider.name));
                SceneManager.LoadSceneAsync(2);
            }
        }
    }

    public void GetUserID(string userID)
    {
        UserID = userID;
        if (userID.Length == 0)
            return;
        if (userID[0] == '0')
            m_EnableSwitch = true;
        else
            m_EnableSwitch = false;
    }

}
