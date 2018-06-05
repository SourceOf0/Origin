#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// winmm.lib をリンクする
#pragma comment(lib,"winmm")

#include <windows.h>
#include "HandManager.h"
#include "SceneManager.h"
#include "SoundManager.h"

int gStateSoundThread = 0;
HANDLE gHSoundThread;


DWORD WINAPI SoundThread( LPVOID hWnd )
{
	while( TRUE ) {
		if( gStateSoundThread > 0 ) break;
		Main::SoundManager::inst()->makeWave();
		Sleep( 10 );
	}
	gStateSoundThread = 2;
	ExitThread( TRUE );
}

LRESULT CALLBACK WndProc( HWND hwnd , UINT msg , WPARAM wp , LPARAM lp )
{
	HDC hdc;
	PAINTSTRUCT ps;
	DWORD dwParam;

	switch( msg ) {
	case WM_DESTROY:
		KillTimer( hwnd, 1 );

		Main::SceneManager::destroy();

		if( Main::SoundManager::inst() != 0 ) {
			while( gStateSoundThread < 2 ) {
				Sleep( 100 );
			}
			Main::SoundManager::destroy();
		}

		PostQuitMessage( 0 );

		_CrtDumpMemoryLeaks();
		return 0;

	case WM_CREATE:
		Main::SoundManager::create( hwnd );
		Main::SceneManager::create( hwnd );
		_CrtCheckMemory();

		gHSoundThread = CreateThread( NULL, 0, SoundThread, hwnd, 0, &dwParam );
		
//		SetTimer( hwnd, 1, 10, NULL );	//無駄に高速に再描画させる
		SetTimer( hwnd, 1, 20, NULL );	//無駄に高速に再描画させる
		return 0;

	case WM_TIMER:	//再描画させる
		if( gStateSoundThread > 0 ) return 0;
		Main::SceneManager::inst()->update();
		InvalidateRect( hwnd, NULL, FALSE );	//背景を消去しない
		return 0;

	case WM_KEYDOWN:
		if( wp == VK_ESCAPE ) {
			PostMessage( hwnd, WM_CLOSE, 0, 0 );
		}
		return 0;

	case WM_LBUTTONDOWN:
		if( gStateSoundThread > 0 ) return 0;
		Main::HandManager::inst()->mouseDown();
		return 0;

	case WM_LBUTTONUP:
		if( gStateSoundThread > 0 ) return 0;
		Main::HandManager::inst()->mouseUp();
		return 0;

	case MM_WOM_DONE:
		if( gStateSoundThread > 0 ) return 0;
		Main::SoundManager::inst()->setBuffer();
		Main::SceneManager::inst()->endSetWave();
		return 0;

	case WM_PAINT:
		if( gStateSoundThread > 0 ) return 0;
		hdc = BeginPaint( hwnd, &ps );
		Main::SceneManager::inst()->draw( hdc );
		EndPaint( hwnd, &ps );
		return 0;

	case WM_CLOSE:
		/*
		int messageResult = MessageBox(
			hwnd, TEXT("ウィンドウを閉じます。\nよろしいですか？"), TEXT("確認"),
			MB_OKCANCEL | MB_ICONWARNING
		);
		if(messageResult != IDOK) return 0;
		*/
		gStateSoundThread = 1;
	}

	return DefWindowProc( hwnd , msg , wp , lp );
}


int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hinstPrev, LPSTR lpszCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	Main::SceneManager::setWindowSize();

	int windowWidth  = Main::SceneManager::windowWidth;
	int windowHeight = Main::SceneManager::windowHeight;
	int deviceWidth  = Main::SceneManager::deviceWidth;
	int deviceHeight = Main::SceneManager::deviceHeight;

	TCHAR      szAppName[] = TEXT( "Origin" );
	DWORD      dwExStyle   = WS_EX_LEFT;
	DWORD      dwStyle     = WS_POPUP | WS_CAPTION | WS_SYSMENU;
	HWND       hwnd;
	MSG        msg;
	WNDCLASSEX wc;
	RECT       rc;

	wc.cbSize        = sizeof( WNDCLASSEX );
	wc.style         = 0;
	wc.lpfnWndProc   = WndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hinst;
	wc.hIcon         = (HICON)LoadImage( NULL, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_SHARED );
	wc.hCursor       = (HCURSOR)LoadImage( NULL, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_SHARED );
	wc.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH );
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = szAppName;
	wc.hIconSm       = (HICON)LoadImage( NULL, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_SHARED );
	
	if( RegisterClassEx(&wc) == 0 ) return 0;

	//SetRect( &rc, (deviceWidth - windowWidth)/2, (deviceHeight - windowHeight)/2, (deviceWidth - windowWidth)/2 + windowWidth, (deviceHeight - windowHeight)/2 + windowHeight );
	SetRect( &rc, (1920 - windowWidth)/2, (1200 - windowHeight)/2, (1920 - windowWidth)/2 + windowWidth, (1200 - windowHeight)/2 + windowHeight );
	AdjustWindowRectEx( &rc, dwStyle, FALSE, dwExStyle );

	hwnd = CreateWindowEx( dwExStyle, szAppName, szAppName, dwStyle, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hinst, NULL );
	if( hwnd == NULL ) return 0;

	/*
	{  // フルスクリーンモード
		DEVMODE    devMode;
		devMode.dmSize       = sizeof(DEVMODE);
		devMode.dmFields     = DM_PELSWIDTH | DM_PELSHEIGHT;
		devMode.dmPelsWidth  = deviceWidth;
		devMode.dmPelsHeight = deviceHeight;
		
		ChangeDisplaySettings( &devMode, CDS_FULLSCREEN );
	}
	*/

	ShowWindow( hwnd, nCmdShow );
//	ShowWindow( hwnd, SW_MAXIMIZE ); // ウインドウ最大化
	UpdateWindow( hwnd );
	
	while( GetMessage( &msg, NULL, 0, 0 ) > 0 ) {
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}

	return (int)msg.wParam;
}

