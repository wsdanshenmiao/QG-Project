using System.Collections;
using System.Collections.Generic;
using System.Net;
using UnityEngine;
using UnityEngine.Networking;
using System.IO;

public class NavigationPath : Singleton<NavigationPath>
{
    /// <summary>
    /// 接收到的导航路径上的节点，按顺序
    /// </summary>
    [System.Serializable]
    private struct PathNode
    {
        public Vector3[] PathNodes;
    }

    //private string m_FilePath = Application.dataPath + "/Macroscopic/Scripts/TestData/PathNodes.json";
    private string m_Address = "http://8.138.121.2:8080/get_user_path";

    private GameObject m_Path;
    private LineRenderer m_PathLR;

    // 是否发送请求
    private bool m_IsRequest = false;
    // 是否初始化
    private bool m_IsInit = false;
    // 是否渲染
    private bool m_RenderPath = true;

    // Start is called before the first frame update
    void Start()
    {
        m_Path = new GameObject();
        m_Path.AddComponent<LineRenderer>();
        StartCoroutine(RequestForInitPath());
    }

    // Update is called once per frame
    void Update()
    {
        if (!m_IsInit)
            return;

        if (!m_IsRequest)
            StartCoroutine(RequestForRenderPath());

        m_PathLR.enabled = m_RenderPath;
    }

    void InitPath(Vector3[] nodes)
    {
        if (nodes != null)
        {
            bool init = true;
            foreach (Vector3 node in nodes)
            {
                if (node == null || node.x == float.NaN || node.y == float.NaN || node.z == float.NaN)
                {
                    init = false;
                    break;
                }
            }
            if (init)
            {
                m_PathLR = m_Path.GetComponent<LineRenderer>();
                m_PathLR.positionCount = nodes.Length;
                m_PathLR.SetPositions(nodes);
                m_PathLR.startWidth = 1;
                m_PathLR.endWidth = 1;
                m_PathLR.alignment = LineAlignment.TransformZ;
                m_PathLR.useWorldSpace = true;
                m_PathLR.sortingLayerName = "NavigationPath";
                m_PathLR.material = new Material(Shader.Find("Traffic/ChangeColorByWeight"));
                m_PathLR.numCornerVertices = 5;

                m_Path.transform.SetParent(transform);

                m_IsInit = true;
            }
        }
    }

    IEnumerator RequestForInitPath()
    {
        UnityWebRequest request = UnityWebRequest.Get(m_Address);

        yield return request.SendWebRequest();

        if (request.result == UnityWebRequest.Result.ConnectionError || request.result == UnityWebRequest.Result.ProtocolError)
        {
            Debug.LogError("错误: " + request.error);
        }
        else
        {
            // 请求成功，进行导航路径初始化
            string json = request.downloadHandler.text;
            PathNode pathNode = JsonUtility.FromJson<PathNode>(json);
            InitPath(pathNode.PathNodes);
        }
    }

    IEnumerator RequestForRenderPath()
    {
        UnityWebRequest request = UnityWebRequest.Get(m_Address);

        m_IsRequest = true;

        yield return request.SendWebRequest();

        if (request.result == UnityWebRequest.Result.ConnectionError || request.result == UnityWebRequest.Result.ProtocolError)
        {
            Debug.LogError("错误: " + request.error);
        }
        else
        {
            string json = request.downloadHandler.text;
            PathNode pathNode = JsonUtility.FromJson<PathNode>(json);

            if (pathNode.PathNodes != null)
                m_RenderPath = (pathNode.PathNodes[0].x == 0 &&
                                pathNode.PathNodes[0].y == 0 &&
                                pathNode.PathNodes[0].z == 0) ? false : true;
            if (m_RenderPath)
                InitPath(pathNode.PathNodes);
            m_IsRequest = false;
        }
    }

    private PathNode ReadFormJson(string filePath)
    {
        string json = File.ReadAllText(filePath);
        return JsonUtility.FromJson<PathNode>(json);
    }
}
