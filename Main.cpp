#include "Header.h"

LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
    case WM_KEYDOWN:
        Input::GetInstance().IfKeyPressed = true;
        Input::GetInstance().SetKeyState(wParam, InputState::DOWN);
        return 0;
    case WM_KEYUP:
        Input::GetInstance().IfKeyPressed = false;
        Input::GetInstance().SetKeyState(wParam, InputState::UP);
        return 0;
    case WM_DESTROY:
        PostQuitMessage( 0 );
        return 0;
    }
    return DefWindowProc( hWnd, msg, wParam, lParam );
}

INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
    UNREFERENCED_PARAMETER( hInst );

    WNDCLASSEX wc =
    {
        sizeof( WNDCLASSEX ), CS_CLASSDC, MsgProc, 0L, 0L,
        GetModuleHandle( NULL ), NULL, NULL, NULL, NULL,
        Direct3D::GetInstance().nameOfWindowClass.c_str(), NULL
    };
    RegisterClassEx( &wc );

    // Create the application's window
    HWND hWnd = CreateWindow( Direct3D::GetInstance().nameOfWindowClass.c_str(), Direct3D::GetInstance().nameOfWindow.c_str(),
        WS_POPUP, 0, 0, Direct3D::GetInstance().wndWidth, Direct3D::GetInstance().wndHeight,
                              NULL, NULL, wc.hInstance, NULL );

    // Initialize Direct3D
    if( SUCCEEDED( Direct3D::GetInstance().InitD3D( hWnd ) ) )
    {
        // Render가 호출 된 이후에 Window를 보이는 상태로 바꾸어 줍니다.
        if (!IsWindowVisible(hWnd))
        {
            ShowWindow(hWnd, SW_SHOWDEFAULT);
            UpdateWindow(hWnd);
        }

        // Enter the message loop
        MSG msg;
        ZeroMemory( &msg, sizeof( msg ) );
        while( msg.message != WM_QUIT )
        {
            if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
            {
                TranslateMessage( &msg );
                DispatchMessage( &msg );
            }
            else
            {
                static DWORD prevTime = timeGetTime();
                if (SceneManager::GetInstance().IsResetDeltaTime())
                    prevTime = timeGetTime();

                DWORD curTime = timeGetTime();
                float deltaTime = (curTime - prevTime) / 1000.0f;
                static float fixedUpdateTime = 1.0f / 50.0f;
                static float fixedDeltaTime = 0.0f;
                fixedDeltaTime += deltaTime;
                if (fixedDeltaTime >= 2.0f) fixedDeltaTime = 2.0f;
                while (fixedDeltaTime > fixedUpdateTime)
                {
                    fixedDeltaTime -= fixedUpdateTime;
                    Direct3D::GetInstance().FixedUpdate(fixedUpdateTime);
                }
                static int fps = 0;
                static float fpsDeltaTime = 0.0f;
                ++fps;
                fpsDeltaTime += deltaTime;
                if (fpsDeltaTime > 1.0f)
                {
                    Direct3D::GetInstance().fps = fps;
                    wprintf(TEXT("%d\n"), fps);
                    fps = 0;
                    fpsDeltaTime = 0.0f;
                }
                Direct3D::GetInstance().Update(deltaTime);
                Direct3D::GetInstance().Render();
                Input::GetInstance().KeyUpdate();
                prevTime = curTime;
            }
        }
    }
    Direct3D::GetInstance().CleanUp();
    UnregisterClass( Direct3D::GetInstance().nameOfWindowClass.c_str(), wc.hInstance );
    return 0;
}



