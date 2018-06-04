#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// winmm.lib �������N����
#pragma comment(lib,"winmm")

#include <windows.h>
#include "SceneManager.h"
#include "SoundManager.h"

LRESULT CALLBACK WndProc( HWND hwnd , UINT msg , WPARAM wp , LPARAM lp )
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (msg) {
	case WM_DESTROY:

		Main::SoundManager::destroy();
		Main::SceneManager::destroy();

		KillTimer(hwnd,1);

		PostQuitMessage(0);

		return 0;

	case WM_CREATE:
		Main::SoundManager::create( hwnd );
		Main::SceneManager::create( hwnd );

		SetTimer(hwnd,1,10,NULL);	//���ʂɍ����ɍĕ`�悳����

		return 0;

	case WM_TIMER:	//�ĕ`�悳����
		InvalidateRect( hwnd, NULL, FALSE );	//�w�i���������Ȃ�
		return 0;

	case WM_KEYDOWN:
		if (wp == VK_ESCAPE) PostMessage(hwnd, WM_CLOSE, 0, 0);
		return 0;

	case WM_LBUTTONDOWN:
		if(Main::SoundManager::inst() != 0) {
			Main::SoundManager::inst()->play();
		}
		return 0;

	case WM_RBUTTONDOWN:
		if(Main::SoundManager::inst() != 0) {
			Main::SoundManager::inst()->stop();
		}
		return 0;

	case MM_WOM_DONE:
		if(Main::SoundManager::inst() != 0) {
			Main::SoundManager::inst()->setBuffer();
		}
		return 0;

	case WM_PAINT:
		hdc = BeginPaint( hwnd, &ps );
//		BitBlt(hdc, 0, 0, windowWidth, windowHeight, hdcBMP, 0, 0, SRCCOPY);
//		BitBlt(hdc, 0, 0, windowWidth, windowHeight, gSceneManager->getHDC(), 0, 0, SRCCOPY);
		if(Main::SceneManager::inst() != 0) {
			Main::SceneManager::inst()->draw( hdc );
		}
		EndPaint(hwnd, &ps);
		return 0;
	}

	return DefWindowProc(hwnd , msg , wp , lp);
}


int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hinstPrev, LPSTR lpszCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	TCHAR      szAppName[] = TEXT("Origin");
	HWND       hwnd;
	MSG        msg;
	WNDCLASSEX wc;
	RECT       rc;
	DEVMODE    devMode;

	wc.cbSize        = sizeof(WNDCLASSEX);
	wc.style         = 0;
	wc.lpfnWndProc   = WndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hinst;
	wc.hIcon         = (HICON)LoadImage(NULL, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_SHARED);
	wc.hCursor       = (HCURSOR)LoadImage(NULL, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_SHARED);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = szAppName;
	wc.hIconSm       = (HICON)LoadImage(NULL, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_SHARED);
	
	if (RegisterClassEx(&wc) == 0)
		return 0;

	SetRect(&rc, 0, 0, 800, 640);
	AdjustWindowRectEx(&rc, WS_POPUP, FALSE, WS_EX_TOPMOST);

	hwnd = CreateWindowEx(WS_EX_LEFT, szAppName, szAppName, WS_POPUP, 0, 0, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hinst, NULL);
	if (hwnd == NULL)
		return 0;
	
	devMode.dmSize       = sizeof(DEVMODE);
	devMode.dmFields     = DM_PELSWIDTH | DM_PELSHEIGHT;
	devMode.dmPelsWidth  = 800;
	devMode.dmPelsHeight = 640;

//	ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);

//	ShowWindow(hwnd, nCmdShow);
	ShowWindow(hwnd, SW_MAXIMIZE);
	UpdateWindow(hwnd);
	
	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}
