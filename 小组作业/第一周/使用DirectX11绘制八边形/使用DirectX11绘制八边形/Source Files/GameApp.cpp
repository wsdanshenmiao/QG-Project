#include "GameApp.h"
#include "d3dUtil.h"
#include "DXTrace.h"

using namespace DirectX;

//初始化输入布局描述
const D3D11_INPUT_ELEMENT_DESC GameApp::VertexPosColor::inputLayout[] = {
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

GameApp::GameApp(HINSTANCE hInstance, const std::wstring& windowName, int initWidth, int initHeight)
    : D3DApp(hInstance, windowName, initWidth, initHeight)
{
}

GameApp::~GameApp()
{
}

bool GameApp::Init()
{
    if (!D3DApp::Init()) {
        return false;
    }
    if (!InitEffect()) {
        return false;
    }
    if (!InitResource()) {
        return false;
    }
        
    return true;
}

void GameApp::OnResize()
{
    D3DApp::OnResize();
}

void GameApp::UpdateScene(float dt)
{
}

void GameApp::DrawScene()
{
    assert(m_pd3dImmediateContext);
    assert(m_pSwapChain);
    static float pink[4] = { 255.0f / 255.0f,192.0f / 255.0f, 203.0f / 255.0f };
    m_pd3dImmediateContext->ClearRenderTargetView(m_pRenderTargetView.Get(), reinterpret_cast<const float*>(&pink));
    m_pd3dImmediateContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    m_pd3dImmediateContext->DrawIndexed(18, 0, 0);

    HR(m_pSwapChain->Present(0, 0));
}

//用于创建着色器或特效相关的方法
bool GameApp::InitEffect()
{
    //二进制流读取
    ComPtr<ID3DBlob> blob;

    //读取顶点着色器信息
    HR(D3DReadFileToBlob(L"HLSL Files\\Octagon_VS.cso", blob.GetAddressOf()));
    //创建顶点着色器
    HR(m_pd3dDevice->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), 0, m_pVertexShader.GetAddressOf()));
    //创建顶点输入布局
    HR(m_pd3dDevice->CreateInputLayout(VertexPosColor::inputLayout, ARRAYSIZE(VertexPosColor::inputLayout), blob->GetBufferPointer(), blob->GetBufferSize(), m_pInputLayout.GetAddressOf()));

    //读取像素着色器信息
    HR(D3DReadFileToBlob(L"HLSL Files\\Octagon_PS.cso", blob.GetAddressOf()));
    //创建像素着色器
    HR(m_pd3dDevice->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), 0, m_pPixelShader.GetAddressOf()));

    
    return true;
}

bool GameApp::InitResource()
{
    //设置图形顶点
    GameApp::VertexPosColor vertices[] = {
        {XMFLOAT3(-0.5f,1.0f,0.0f),XMFLOAT4(0.0f,0.0f,0.0f,0.0f)},
        {XMFLOAT3(0.5f,1.0f,0.0f),XMFLOAT4(0.0f,0.0f,0.0f,0.0f)},
        {XMFLOAT3(1.0f,0.5f,0.0f),XMFLOAT4(0.0f,0.0f,0.0f,0.0f)},
        {XMFLOAT3(1.0f,-0.5f,0.0f),XMFLOAT4(0.0f,0.0f,0.0f,0.0f)},
        {XMFLOAT3(0.5f,-1.0f,0.0f),XMFLOAT4(0.0f,0.0f,0.0f,0.0f)},
        {XMFLOAT3(-0.5f,-1.0f,0.0f),XMFLOAT4(0.0f,0.0f,0.0f,0.0f)},
        {XMFLOAT3(-1.0f,-0.5f,0.0f),XMFLOAT4(0.0f,0.0f,0.0f,0.0f)},
        {XMFLOAT3(-1.0f,0.5f,0.0f),XMFLOAT4(0.0f,0.0f,0.0f,0.0f)},
    };

    // 设置顶点缓冲区描述
    D3D11_BUFFER_DESC vbd;
    ZeroMemory(&vbd, sizeof(vbd));
    vbd.ByteWidth = sizeof(vertices);   //字节数
    vbd.Usage = D3D11_USAGE_IMMUTABLE;  //CPU,GPU读写权限
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;   //缓冲区类型
    vbd.CPUAccessFlags = 0; //CPU读写权限

    //创建并填充子资源
    D3D11_SUBRESOURCE_DATA initData;
    ZeroMemory(&initData, sizeof(initData));
    initData.pSysMem = vertices;

    //创建顶点缓冲区
    m_pVertexBuffer = nullptr;
    HR(m_pd3dDevice->CreateBuffer(&vbd, &initData, m_pVertexBuffer.GetAddressOf()));


    //设置顶点索引
    DWORD indices[] = {
        0,1,2,
        0,2,3,
        0,3,4,
        0,4,5,
        0,5,6,
        0,6,7,
    };

    //设置索引缓冲区描述
    D3D11_BUFFER_DESC ibd;
    ZeroMemory(&ibd, sizeof(ibd));
    ibd.ByteWidth = sizeof(indices);
    ibd.Usage = D3D11_USAGE_IMMUTABLE;
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibd.CPUAccessFlags = 0;

    //填充子资源
    initData.pSysMem = indices;

    //创建索引缓冲区
    m_pIndexBuffer = nullptr;
    HR(m_pd3dDevice->CreateBuffer(&ibd, &initData, m_pIndexBuffer.GetAddressOf()));


    // 输入装配阶段的顶点缓冲区设置
    UINT stride = sizeof(VertexPosColor);	// 跨越字节数
    UINT offset = 0;						// 起始偏移量
    m_pd3dImmediateContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);

    //设置顶点输入布局
    m_pd3dImmediateContext->IASetInputLayout(m_pInputLayout.Get());

    // 输入装配阶段的索引缓冲区设置
    m_pd3dImmediateContext->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

    // 将着色器绑定到渲染管线
    m_pd3dImmediateContext->VSSetShader(m_pVertexShader.Get(), nullptr, 0);
    m_pd3dImmediateContext->PSSetShader(m_pPixelShader.Get(), nullptr, 0);

    // 设置图元类型
    m_pd3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


    return true;
}