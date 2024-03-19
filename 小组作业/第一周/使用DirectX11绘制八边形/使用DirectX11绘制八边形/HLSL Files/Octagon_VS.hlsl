#include "Octagon.hlsli"

//顶点着色器
VertexOut VS(VertexIn vIn)
{
    VertexOut vOut;
    vOut.posH = float4(vIn.posH, 1.0f); //转换为齐次坐标
    vOut.color = vIn.color;
	return vOut;
}