using UnityEngine;
using UnityEngine.Networking;
using System.Collections;


// GetRequestFromUnity
public class WebTest : MonoBehaviour
{
    string serverUrl = "http://139.159.156.117:8080/get_position"; // 使用你的公网IP

    void Start()
    {
        StartCoroutine(GetRequestToServer());
    }

    IEnumerator GetRequestToServer()
    {
        using (UnityWebRequest webRequest = UnityWebRequest.Get(serverUrl))
        {
            // 请求超时时间设置，这里设置为 10 秒
            webRequest.timeout = 10;

            // 发送请求并等待响应
            yield return webRequest.SendWebRequest();

            if (webRequest.result == UnityWebRequest.Result.ConnectionError || webRequest.result == UnityWebRequest.Result.ProtocolError)
            {
                Debug.LogError("Error: " + webRequest.error);
            }
            else
            {
                // 请求成功，处理响应数据
                Debug.Log("Received: " + webRequest.downloadHandler.text);
                // 如果响应是 JSON 格式，可以在这里解析 JSON
                // 例如，使用 JsonUtility 
                string json = webRequest.downloadHandler.text;
                Debug.Log($"!!!!!!!!!!!!!!!!!!!!Received JSON: {json}!!!!!!!!!!!!!!");

            }
        }
    }
}
