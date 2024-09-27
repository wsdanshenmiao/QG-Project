using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using DSM;

public class AStar : MonoBehaviour
{
    private List<Point> m_OpenList = new List<Point>();
    private List<Point> m_CloseList = new List<Point>();
    private Map m_Map;

    /// <summary>
    /// A*算法主体
    /// </summary>
    /// <param name="start"></param> 起点
    /// <param name="end"></param>  终点
    /// <returns></returns> 从起点到终点的路径
    public List<Point> AStarAlgorithm(Point start, Point end)
    {
        if (start == null || end == null) return null;
        m_OpenList.Add(start);   // 将起点加入集合Open
        while (m_OpenList.Count > 0) {
            // 选取优先级最高的点
            Point point = FindHighestPriority();

            if (point == end) {
                return TracePath(point);
            }
            else {
                m_OpenList.Remove(point);
                m_CloseList.Add(point);
                TraverseNearPoint(point, start, end);
            }
        }

        return null;
    }

    /// <summary>
    /// 遍历四周的点
    /// </summary>
    private void TraverseNearPoint(Point point, Point start, Point end)
    {
        for (int i = (int)point.Pos.x - 1; i <= (int)point.Pos.x + 1; ++i) {
            for (int j = (int)point.Pos.y - 1; j <= (int)point.Pos.y + 1; ++j) {
                // 超出地图界限
                if (i < 0 || i >= m_Map.Width || j < 0 || j >= m_Map.Height) continue;

                // 该点为障碍或是再集合Close中
                Point currentPoint = m_Map.Points[i, j];
                if (currentPoint.IsBarrier || m_CloseList.Find(data => { return data == currentPoint; }) != null) {
                    continue;
                }

                // 该点不再集合Open中
                if (m_OpenList.Find(data => { return data == currentPoint; }) == null) {
                    currentPoint.Parent = point;
                    CalculatePriority(currentPoint, start, end);
                    m_OpenList.Add(currentPoint);
                }
            }
        }
    }

    /// <summary>
    /// 计算权重
    /// </summary>
    /// <param name="currentPoint"></param> 计算的点
    /// <param name="start"></param>    起点
    /// <param name="end"></param>  终点
    private void CalculatePriority(Point currentPoint, Point start, Point end)
    {
        // 点到起点的距离
        currentPoint.GCost = Vector2.Distance(currentPoint.Pos, start.Pos);

        // 点到终点的距离
        Heuristic(currentPoint, end);

        // 综合优先级
        currentPoint.FCost = currentPoint.GCost + currentPoint.HCost;
    }

    private void Heuristic(Point point, Point end)
    {
        // 欧几里得距离
        point.HCost = Vector2.Distance(point.Pos, end.Pos);
        // 曼哈顿距离
        // point.HCost = Mathf.Abs(point.Pos.x - end.Pos.x) + 
        //     Mathf.Abs(point.Pos.y - end.Pos.y);
    }

    /// <summary>
    /// 从终点回溯到起点
    /// </summary>
    /// <returns></returns> 返回起点到终点的路径
    private List<Point> TracePath(Point end)
    {
        if (end == null) return null;

        Point point = end;
        List<Point> path = new();
        for (path.Add(point); point.Parent != null; point = point.Parent, path.Add(point)) ;
        path.Reverse();

        return path.Count == 0 ? null : path;
    }

    /// <summary>
    /// 查找集合Open中优先级最高的点
    /// </summary>
    /// <returns></returns> 优先级最高的点
    private Point FindHighestPriority()
    {
        // 排序集合Open
        m_OpenList.Sort((a, b) => { return (int)(a.FCost - b.FCost); });
        // 返回优先级最高的点，即FCost最小
        return m_OpenList.First();
    }

    public void InitMap(Map map)
    {
        m_Map = map;
    }
}
