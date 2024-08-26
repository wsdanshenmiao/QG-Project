using OfficeOpenXml.Drawing.Chart;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;
using OfficeOpenXml;
using System.Xml.Linq;
using Unity.VisualScripting;
using UnityEditor;
using System;
using System.Text.RegularExpressions;
using UnityEngine.U2D;
using OfficeOpenXml.FormulaParsing.Excel.Functions.Text;
using TMPro;

public class ImportNodeData : MonoBehaviour
{
    public GameObject Node;
    public GameObject Circle;

    private Shader m_Shader;

    private void Awake()
    {
        m_Shader = Shader.Find("Traffic/ChangeColorByWeight");
    }

    // Start is called before the first frame update
    void Start()
    {
        string fileName = Application.dataPath + "/NodeData/node_data.xlsx";
        FileInfo fileInfo = new FileInfo(fileName);

        using (ExcelPackage package = new ExcelPackage(fileInfo))
        {
            ExcelWorksheet worksheet = package.Workbook.Worksheets[1];

            for (int i = 2; i <= 39; ++i)
            {
                double num = (double)worksheet.Cells[i, 1].Value;
                double x = (double)worksheet.Cells[i, 2].Value;
                double y = (double)worksheet.Cells[i, 3].Value;
                string name = worksheet.Cells[i, 4].Value.ToString();
                string nearPoint = worksheet.Cells[i, 5].Value.ToString();

                GameObject gameObject = Instantiate(Circle);
                gameObject.name = num.ToString();

                Vector3 newPos = new Vector3((float)x, (float)y, 0);
                gameObject.transform.position = newPos;
                gameObject.transform.localScale = new Vector3(2, 2, 2);

                switch (Regex.Matches(nearPoint, "¡¢").Count)
                {
                    case 1: gameObject.tag = "TwoPathNode"; break;
                    case 2: gameObject.tag = "ThreePathNode"; break;
                    case 3: gameObject.tag = "FourPathNode"; break;
                }

                Transform transform = gameObject.GetComponentInChildren<Transform>();
                TextMeshProUGUI text = transform.GetComponentInChildren<TextMeshProUGUI>();
                text.text = name;

                gameObject.transform.SetParent(Node.transform);
            }
        }
#if UNITY_EDITOR
        PrefabUtility.SaveAsPrefabAssetAndConnect(Node, "Assets/Prefabs/" + Node.name + ".prefab", InteractionMode.UserAction);
#endif
    }

}
