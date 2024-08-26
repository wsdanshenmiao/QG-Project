using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "New Map Size", menuName = "Map Size")]

public class MapData_SO : ScriptableObject
{
    // 地图的宽度
    public int MapWidth = 120;
    // 地图的高度
    public int MapHeight = 80;
    // 宽度上分成小区快的个数
    public int ChunkWidth = 3;
    // 高度上分成小区快的个数
    public int ChunkHeight = 2;
}
