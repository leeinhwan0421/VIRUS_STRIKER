#include "Header.h"

HRESULT Direct3D::InitD3D(HWND hWnd)
{
    wnd = hWnd;

    // Create the D3D object.
    if (NULL == (pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
        return E_FAIL;

    // Set up the structure used to create the D3DDevice. Since we are now
    // using more complex geometry, we will create a device with a zbuffer.
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

    // Create the D3DDevice
    if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &d3dpp, &pd3dDevice)))
    {
        return E_FAIL;
    }

    // Create the vertex buffer.
    if (FAILED(pd3dDevice->CreateVertexBuffer(4 * sizeof(CUSTOMVERTEX),
        0, D3DFVF_CUSTOMVERTEX,
        D3DPOOL_DEFAULT, &pVB, NULL)))
    {
        return E_FAIL;
    }

    if (FAILED(D3DXCreateLine(pd3dDevice, &pLine)))
    {
        return E_FAIL;
    }

    // Turn off culling
    pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

    // Turn off D3D lighting
    pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

    // Turn on the zbuffer
    pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

    pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
    pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
    pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

    // IF DEBUG => Open the Console Window
#if defined (_DEBUG)

    AllocConsole();
    FILE* fp;
    freopen_s(&fp, "CON", "r", stdin);
    freopen_s(&fp, "CON", "w", stdout);
    freopen_s(&fp, "CON", "w", stderr);
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

#endif

    // Set Camera Position
    D3DXVECTOR3 vEyePt(0.0f, 0.0f, -10.0f);
    D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
    D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
    D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
    pd3dDevice->SetTransform(D3DTS_VIEW, &matView);

    D3DXMatrixOrthoLH(&matProj, gameWidth, gameHeight, 0.0f, 1000.0f);
    pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);

    // SceneManager::GetInstance().AddScene(TEXT("GameScene"), new GameScene());
    // SceneManager::GetInstance().ChangeScene(TEXT("GameScene"));

    SceneManager::GetInstance().AddScene(TEXT("IntroScene"), new IntroScene());
    SceneManager::GetInstance().AddScene(TEXT("TitleScene"), new TitleScene());
    SceneManager::GetInstance().AddScene(TEXT("HelpScene"), new HelpScene());

    for (int i = 0; i < 3; ++i)
        SceneManager::GetInstance().AddScene(TEXT("HTPs") + std::to_wstring(i), new HTPs(i));
    
    SceneManager::GetInstance().AddScene(TEXT("GameScene"), new GameScene(0));
    SceneManager::GetInstance().AddScene(TEXT("GameScene_1"), new GameScene(1));
    SceneManager::GetInstance().AddScene(TEXT("EndScene"), new EndScene(0));
    SceneManager::GetInstance().AddScene(TEXT("RankScene"), new RankScene({ 0, TEXT("AAA") }));
    SceneManager::GetInstance().AddScene(TEXT("CreditScene"), new CreditScene());
    SceneManager::GetInstance().ChangeScene(TEXT("IntroScene"));

    return S_OK;
}

VOID Direct3D::Update(float _deltaTime)
{
  //  if (Input::GetInstance().GetKeyState('D'))
  //      destCameraPos.x += 100.0f * _deltaTime;
  //
  //  if (Input::GetInstance().GetKeyState('A'))
  //      destCameraPos.x -= 100.0f * _deltaTime;
  //
  //  if (Input::GetInstance().GetKeyState('Q') == InputState::DOWN)
  //      destCameraScale -= D3DXVECTOR2(0.2f, 0.2f);
  //
  //  if (Input::GetInstance().GetKeyState('E') == InputState::DOWN)
  //      destCameraScale += D3DXVECTOR2(0.2f, 0.2f);

    SceneManager::GetInstance().Update(_deltaTime);
}

VOID Direct3D::FixedUpdate(float _fixedDeltaTime)
{
    cameraPos += (destCameraPos - cameraPos) * 10.0f * _fixedDeltaTime;
    cameraScale += (destCameraScale - cameraScale) * 10.0f * _fixedDeltaTime;
    cameraQuaken += (destCameraQuaken - cameraQuaken) * 10.0f * _fixedDeltaTime;
    SceneManager::GetInstance().FixedUpdate(_fixedDeltaTime);
}

VOID Direct3D::Render()
{
    pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
        D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    if (SUCCEEDED(pd3dDevice->BeginScene()))
    {
        D3DXMATRIX matPos, matScale;
        //D3DXMatrixTranslation(&matPos, -cameraPos.x, -cameraPos.y, 0.0f);
        D3DXMatrixTranslation(&matPos, -960.0f, 540.0f, 0.0f);
        D3DXMatrixScaling(&matScale, cameraScale.x, cameraScale.y, 1.0f);
        matPos *= matScale;
        matPos *= matView;
        pd3dDevice->SetTransform(D3DTS_VIEW, &matPos);
        SceneManager::GetInstance().Render();
        pd3dDevice->SetTransform(D3DTS_VIEW, &matView);
        SceneManager::GetInstance().UiRender();
        pd3dDevice->EndScene();
    }

    pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

VOID Direct3D::CleanUp()
{
    SAFE_RELEASE(pLine);
    SAFE_RELEASE(pVB);
    SAFE_RELEASE(pd3dDevice);
    SAFE_RELEASE(pD3D);
}
