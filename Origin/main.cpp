#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// winmm.lib をリンクする
#pragma comment(lib,"winmm")

#include <windows.h>
#include "common.h"
#include "HandManager.h"
#include "SceneManager.h"
#include "SoundManager.h"

enum ThreadStateID {
	THREAD_INIT,
	THREAD_IDLE,
	THREAD_EXIT,

	THREAD_NONE,
};

ThreadStateID gStateSoundThread = THREAD_INIT;
HANDLE gHSoundThread;


DWORD WINAPI SoundThread( LPVOID hWnd )
{
	while( gStateSoundThread == THREAD_IDLE ) {
		Main::SoundManager::inst()->makeWave();
		Sleep( 10 );
	}
	ExitThread( 0 );
}

LRESULT CALLBACK WndProc( HWND hwnd , UINT msg , WPARAM wp , LPARAM lp )
{
	HDC hdc;
	PAINTSTRUCT ps;
	DWORD id;

	switch( msg ) {
	case WM_DESTROY:
		KillTimer( hwnd, 1 );

		Main::SceneManager::destroy();

		if( gStateSoundThread > THREAD_INIT ) {
			DWORD result;
			while( TRUE ) {
				GetExitCodeThread( gHSoundThread, &result );
				if( result != STILL_ACTIVE ) {
					CloseHandle( gHSoundThread );
					Main::SoundManager::destroy();
					break;
				}
				Sleep( 10 );
			}
		}

		PostQuitMessage( 0 );

		_CrtDumpMemoryLeaks();
		return 0;

	case WM_CREATE:
		Main::SoundManager::create( hwnd );
		Main::SceneManager::create( hwnd );
		_CrtCheckMemory();

		gStateSoundThread = THREAD_IDLE;
		gHSoundThread = CreateThread( NULL, 0, SoundThread, hwnd, 0, &id );
		
//		SetTimer( hwnd, 1, 1, NULL );	//無駄に高速に再描画させる
		SetTimer( hwnd, 1, 20, NULL );	//無駄に高速に再描画させる
		return 0;

	case WM_TIMER:	//再描画させる
		if( gStateSoundThread != THREAD_IDLE ) return 0;
		Main::SceneManager::inst()->update();
		InvalidateRect( hwnd, NULL, FALSE );	//背景を消去しない
		return 0;

	case WM_SIZE:
		Main::SceneManager::setWindowSize( hwnd );
		InvalidateRect( hwnd, NULL, TRUE );	//背景を消去する
		return 0;

	case WM_KEYDOWN:
		if( wp == VK_ESCAPE ) {
			PostMessage( hwnd, WM_CLOSE, 0, 0 );
		}
		return 0;

	case WM_LBUTTONDOWN:
		if( gStateSoundThread != THREAD_IDLE ) return 0;
		Main::HandManager::inst()->mouseDown();
		return 0;

	case WM_LBUTTONUP:
		if( gStateSoundThread != THREAD_IDLE ) return 0;
		Main::HandManager::inst()->mouseUp();
		return 0;

	case MM_WOM_DONE:
		if( gStateSoundThread != THREAD_IDLE ) return 0;
		Main::SoundManager::inst()->setBuffer();
		Main::SceneManager::inst()->endSetWave();
		return 0;

	case WM_PAINT:
		if( gStateSoundThread != THREAD_IDLE ) return 0;
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
		gStateSoundThread = THREAD_EXIT;
		DestroyWindow( hwnd );
	}

	return DefWindowProc( hwnd , msg , wp , lp );
}


int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hinstPrev, LPSTR lpszCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	const int VIEW_WIDTH  = Main::SceneManager::VIEW_WIDTH;
	const int VIEW_HEIGHT = Main::SceneManager::VIEW_HEIGHT;

	TCHAR      szAppName[] = TEXT( "Origin" );
	DWORD      dwExStyle   = WS_EX_LEFT;
	DWORD      dwStyle     = WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
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

	SetRect( &rc, 0, 0, VIEW_WIDTH, VIEW_HEIGHT );
	AdjustWindowRectEx( &rc, dwStyle, FALSE, dwExStyle );

	hwnd = CreateWindowEx( dwExStyle, szAppName, szAppName, dwStyle, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hinst, NULL );
	if( hwnd == NULL ) return 0;

	{
		HDC hdc = GetDC( hwnd );
		const int deviceWidth  = GetDeviceCaps( hdc, HORZRES );
		const int deviceHeight = GetDeviceCaps( hdc, VERTRES );
		const int windowWidth  = rc.right - rc.left;
		const int windowHeight = rc.bottom - rc.top;

		MoveWindow( hwnd, (deviceWidth - windowWidth)/2, (deviceHeight - windowHeight)/2, windowWidth, windowHeight, FALSE );

		ReleaseDC( hwnd, hdc );
	}

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
	UpdateWindow( hwnd );
	
	while( GetMessage( &msg, NULL, 0, 0 ) > 0 ) {
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}

	return (int)msg.wParam;
}

