using System;
using System.Collections.Generic;
using System.Net;
using DSM;
using UnityEngine;

public class TestAStar : MonoBehaviour
{
    public enum MapMode { SETBARRIER, SETSTART, SETEND }

    public MapMode Mode = MapMode.SETBARRIER;
    public long MapWidth, MapHeight;
    public GameObject MapPrefab;

    private Map m_Map;
    private List<GameObject> m_MapTiles;
    private Point m_StarPoint;
    private Point m_EndPoint;
    private AStar m_AStar;
    private List<Point> m_PrePath;
    private bool m_IsChange = false;


    // Start is called before the first frame update
    void Start()
    {
        InitMap(MapWidth, MapHeight);
        m_AStar = new AStar();
        m_AStar.InitMap(m_Map);
    }

    // Update is called once per frame
    void Update()
    {
        UpdateMapFactor();
        if(m_IsChange){
            UpdateMap();
            m_IsChange = false;
        }
    }

    private void UpdateMap()
    {
        List<Point> path = m_AStar.AStarAlgorithm(m_StarPoint, m_EndPoint);
        if (path == null) return;
        ClearPath();
        m_PrePath = path;

        Debug.Log("New Path" + path.Count);
        for (int i = 1; i < path.Count - 1; ++i) {
            SetColor(path[i], Color.green);
        }
        SetColor(m_StarPoint, Color.blue);
        SetColor(m_EndPoint, Color.red);
    }

    /// <summary>
    /// 产生新路径后清空地图瓦片的颜色和地图上点的数据
    /// </summary>
    private void ClearPath()
    {
        if(m_PrePath != null){
            Debug.Log("Clear Path");
            foreach(Point point in m_PrePath){
                point.ResetPointState();
                SetColor(point, Color.yellow);
            }
        }
    }

    private void UpdateMapFactor()
    {
        if (!Input.GetMouseButtonDown(0)) return;

        Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
        RaycastHit2D hitInfo = Physics2D.Raycast(ray.origin, ray.direction);
        if (hitInfo.collider == null || hitInfo.collider.tag != "Map") return;

        SpriteRenderer tile = hitInfo.collider.gameObject.GetComponent<SpriteRenderer>();
        Vector3 pos = tile.transform.position;
        bool isBarrier = m_Map.Points[(int)pos.x, (int)pos.y].IsBarrier;
        switch(Mode){
            case MapMode.SETBARRIER:{
                if(isBarrier){
                    tile.color =Color.white;
                    m_Map.Points[(int)pos.x,(int)pos.y].IsBarrier = false;
                }
                else{
                    tile.color = Color.black;
                    m_Map.Points[(int)pos.x, (int)pos.y].IsBarrier = true;
                }
                break;
            }
            case MapMode.SETSTART:{
                if (isBarrier) break;
                m_IsChange = true;
                tile.color = Color.blue;
                SetColor(m_StarPoint, Color.white);
                m_StarPoint.Pos = new Vector2(pos.x,pos.y);
                break;
            }
            case MapMode.SETEND:{
                if(isBarrier) break;
                m_IsChange = true;
                tile.color = Color.red;
                SetColor(m_EndPoint, Color.white);
                m_EndPoint.Pos = new Vector2(pos.x , pos.y);
                break;
            }
        }
    }

    private void InitMap(long width, long height)
    {
        m_Map = new Map();
        m_MapTiles = new List<GameObject>();
        m_StarPoint = new Point(Vector2.zero);
        m_EndPoint = new Point(Vector2.zero);

        m_Map.Width = width;
        m_Map.Height = height;
        m_Map.Points = new Point[m_Map.Width, m_Map.Height];
        for (long i = 0; i < width; ++i) {
            for (long j = 0; j < height; ++j) {
                m_Map.Points[i, j] = new Point(new Vector2(i, j));
                GameObject tile = Instantiate(MapPrefab);
                tile.transform.position = new Vector3(i, j, 0);
                tile.transform.SetParent(transform);
                tile.tag = "Map";
                m_MapTiles.Add(tile);
            }
        }
    }

    private void SetColor(Point point, Color color)
    {
        m_MapTiles.Find(data =>{ return CmpV3AndV2(data.transform.position, point.Pos); })
                    .GetComponent<SpriteRenderer>().color = color;
    }

    private bool CmpV3AndV2(Vector3 vector3, Vector2 vector2)
    {
        return vector3 == new Vector3(vector2.x, vector2.y, 0);
    }

}
