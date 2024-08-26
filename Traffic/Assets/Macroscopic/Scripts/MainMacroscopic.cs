using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;   // 用于文件调用
using UnityEngine.Networking;
using UnityEngine.SceneManagement;
using System.Threading;

public class MainMacroscopic : DontDestorySingleton<MainMacroscopic>
{
    private bool isPutSucceed = false;  // 标志需求是否成功
    //string[] json;

    int quantity = 10;  // 车的数量
    //string json;     // 用来临时存储json文件
    string GetServeUrl = "http://8.138.121.2:8080/get_path"; // 使用你的公网IP
    string PutServeUrl = "http://8.138.121.2:8080/put_car?car_num=10";

    public Sprite CarSprite;
    public Material SphereMaterial;
    public Vector3 sphereScale = new Vector3(3f, 3f, 3f); // 设置球体缩放大小

    //public float testSpeed = 1f;
    //public Vector3[] testPath ={
    //new Vector3(4f,4f,-3f),new Vector3(4f,16f,-3f),new Vector3(16f,14f,-3f)
    //};



    car[] cars;

    void Start()
    {
        StartCoroutine(SendPutRequest());    // 向服务器发送车辆的数量

        //StartCoroutine(CheckRequestStatus());
        //InvokeRepeating("Check",0.0f,1.0f);



        //string[] filePath = new string[quantity];
        //filePath[0] = Application.dataPath + "/Macroscopic/Scripts/cars_data2.json"; // JSON文件路径
        //filePath[1] = Application.dataPath + "/Macroscopic/Scripts/cars_data3.json"; // JSON文件路径

        //json = new string[quantity];

        // 初始化各个车辆
        cars = new car[quantity];
        for (int i = 0; i < quantity; i++)
        {
            cars[i] = new car();
            cars[i].initialSphere(SphereMaterial, sphereScale, CarSprite);
            //cars[i].TestRefresh(filePath[i]);
            //cars[i].sphereObject.transform.position = cars[i].fromAI.path[0];

            // 设为子类
            cars[i].sphereObject.transform.SetParent(transform, false);

        }


    }

    void FixedUpdate()
    {
        if (ScenesManager2D.Instance.UserID == null)
            return;
        else if (ScenesManager2D.Instance.UserID[0] != '0')
            return;

        //Thread blockingThread = new Thread(Check);
        //blockingThread.Start();
        if (!isPutSucceed)
        {
            ;
        }
        else
        {
            //Debug.Log("启动！！！！！！！！！！！！！！！！！！！！！！");
            //foreach (var car in cars)
            for (int i = 0; i < quantity; i++)
            {
                if (cars[i].isMoving == true)
                {
                    cars[i].Move();
                }
                else
                {
                    //StartCoroutine(GetRequestToServer(() => cars[i].json, newValue => cars[i].json = newValue));
                    int index = i; // 使用局部变量来保存 i 的值
                    StartCoroutine(GetRequestToServer((value) => cars[index].json = value,
                    (value) => cars[index].getNewPathSucceed = value));
                    //Debug.Log(cars[i].json);
                    if (cars[index].getNewPathSucceed)
                    {
                        cars[index].refresh();
                    }

                }
            }
        }


        RenderCar();
    }



    private void RenderCar()
    {
        bool render = FindObjectOfType<ScenesManager2D>() != null;
        MeshRenderer[] childMeshRenderer = GetComponentsInChildren<MeshRenderer>();
        foreach (var child in childMeshRenderer)
        {
            child.enabled = render;
        }
    }

    public IEnumerator GetRequestToServer(System.Action<string> setString = null, System.Action<bool> setBool = null)
    //public IEnumerator GetRequestToServer(System.Func<string> getValue, System.Action<string> setValue = null)
    {

        using (UnityWebRequest webRequest = UnityWebRequest.Get(GetServeUrl))
        {
            // 请求超时时间设置，这里设置为 10 秒
            //webRequest.timeout = 10;

            // 发送请求并等待响应
            yield return webRequest.SendWebRequest();
            if (webRequest.result == UnityWebRequest.Result.ConnectionError || webRequest.result == UnityWebRequest.Result.ProtocolError)
            {
                //Debug.LogError("错误: " + webRequest.error);
                Debug.Log("错误: ");
            }
            else
            {
                // 请求成功，处理响应数据
                //Debug.Log("回复: " + webRequest.downloadHandler.text);
                // 使用 JsonUtility 在这里解析 JSON
                string temp = webRequest.downloadHandler.text;
                setString(temp);
                setBool(true);

            }

        }
    }

    class car
    {
        public transmitData fromAI;     // 从AI组中获取到的信息
        public GameObject sphereObject;   // 表示车辆的一个物体
        public int currentWaypointIndex = 1; // 引用索引
        public bool isMoving = false;          // 标志是否在移动
        public bool getNewPathSucceed = false;
        public string json;   // 用来保存json数据
        //public bool GetSucceed = false;

        //public car(){
        //this.initialSphere(SphereMaterial,sphereScale);
        //}

        public void initialSphere(Material SphereMaterial, Vector3 sphereScale, Sprite sprite)
        {
            // 创建球体对象
            sphereObject = new GameObject();
            sphereObject.transform.position = new Vector3(-10f, -10f, 0);

            // 获取球体的渲染器组件
            SpriteRenderer rend = sphereObject.AddComponent<SpriteRenderer>();
            // 应用材质到球体
            rend.material = SphereMaterial;
            rend.sortingLayerName = "Car";
            rend.sprite = sprite;

            // 设置球体的缩放
            sphereObject.transform.localScale = sphereScale;
        }




        public void Move()
        {
            // 检查是否还有目标点
            if (currentWaypointIndex < fromAI.path.Length)
            {

                float distance = Vector3.Distance(sphereObject.transform.position, fromAI.path[currentWaypointIndex]);
                float duration = distance / fromAI.speed;
                sphereObject.transform.position = Vector3.Lerp(sphereObject.transform.position, fromAI.path[currentWaypointIndex], Time.deltaTime / duration);

                // 检查是否接近当前目标点，如果接近则切换到下一个目标点
                if (Vector3.Distance(sphereObject.transform.position, fromAI.path[currentWaypointIndex]) < 0.0001f)
                {
                    currentWaypointIndex++;
                }
            }
            else
            {
                // 如果已经到达路径末尾，可以执行额外的逻辑或者停止移动
                Debug.Log("已经到达路径末尾");
                isMoving = false;
                // 这里可以根据需要重置
            }
        }

        // 测试使用的更新函数
        public void TestRefresh(string path)
        {

            //string path = Application.dataPath + "/Macroscopic/Scripts/TestData/cars_data2.json"; // JSON文件路径
            if (File.Exists(path))
            {
                string json = File.ReadAllText(path);
                this.fromAI = JsonUtility.FromJson<transmitData>(json);
                Debug.Log("路径点1:" + fromAI.path[0] + "路径点2:" + fromAI.path[1] + "速度为:" + fromAI.speed);
            }
            else
            {
                Debug.LogError("Json没找到: " + path);
            }

        }

        public void refresh()
        {

            fromAI = JsonUtility.FromJson<transmitData>(json);      // 获得新的速度和路径
            sphereObject.transform.position = fromAI.path[0];       // 设置为起点位置
            currentWaypointIndex = 1;
            isMoving = true;
            getNewPathSucceed = false;
        }

    }

    // 从AI组拿到的数据
    struct transmitData
    {
        public float speed;
        public Vector3[] path;
    }

    // 向服务器发送车辆数量
    IEnumerator SendPutRequest()
    {
        UnityWebRequest www = UnityWebRequest.Put(PutServeUrl, "");
        www.downloadHandler = new DownloadHandlerBuffer();
        www.SetRequestHeader("Content-Type", "application/json");

        yield return www.SendWebRequest();

        if (www.result != UnityWebRequest.Result.Success)
        {
            Debug.LogError("请求失败: " + www.error);
        }
        else
        {
            Debug.Log("请求成功，回复： " + www.downloadHandler.text);

            // 检查服务器返回的文本是否为 "succeed"
            //if (www.downloadHandler.text == "["put succeed"]")
            //{
            isPutSucceed = true;
            Debug.Log("收到 'put succeed'，继续执行");
            //}
            //else
            //{
            //Debug.Log("未收到 'succeed'，暂停执行");
            //}
        }

    }

    IEnumerator CheckRequestStatus()
    {
        while (!isPutSucceed)
        {
            Debug.Log("等待回复.ing");
            yield return null; // 每帧检查一次
        }

        // 在这里继续执行后续代码
        Debug.Log("继续执行后续代码");
    }

    void Check()
    {
        while (!isPutSucceed)
        {
            Debug.Log("等待回复.ing");

            // 阻塞线程1秒
            Thread.Sleep(1000);
        }
    }

}
