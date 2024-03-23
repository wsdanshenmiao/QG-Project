#ifndef GAMEAPP_H
#define GAMEAPP_H

#include "d3dApp.h"
class GameApp : public D3DApp
{
public:
    //C++中对应的输入顶点结构体
    struct VertexPosColor
    {
        DirectX::XMFLOAT3 pos;
        DirectX::XMFLOAT4 color;
        static const D3D11_INPUT_ELEMENT_DESC inputLayout[2];
    };

public:
    GameApp(HINSTANCE hInstance, const std::wstring& windowName, int initWidth, int initHeight);
    ~GameApp();

    bool Init();
    void OnResize();
    void UpdateScene(float dt);
    void DrawScene();

private:
    bool InitEffect();  //用于创建着色器或特效相关的方法
    bool InitResource();    //用于初始化相关资源

private:
    ComPtr<ID3D11VertexShader> m_pVertexShader; //顶点着色器
    ComPtr<ID3D11InputLayout> m_pInputLayout;   //顶点输入布局
    ComPtr<ID3D11PixelShader> m_pPixelShader;   //像素着色器
    
    ComPtr<ID3D11Buffer> m_pVertexBuffer;   //顶点缓冲区
    ComPtr<ID3D11Buffer> m_pIndexBuffer;    //索引缓冲区
};


#endif