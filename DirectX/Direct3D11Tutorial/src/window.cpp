#include "window.h"

HRESULT Window::initialize(HINSTANCE hInstance) {
	//---------------------------------------------------
	// ウィンドウクラス（ウィンドウを定義する構造体）の作成
	//---------------------------------------------------
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX); // 構造体のサイズ
	wcex.style = CS_HREDRAW | CS_VREDRAW; // ウィンドウスタイル
										  // CS_HREDRAW	横サイズが変わったときにウィンドウ全体を再描画
										  // CS_VREDRAW 縦サイズが変わったときにウィンドウ全体を再描画
	wcex.lpfnWndProc = WndProc;	// ウィンドウプロシージャへのポインタ
	wcex.cbClsExtra = 0; // 構造体の後ろに割り当てる補足バイト数（通常は0）
	wcex.cbWndExtra = 0; // ウィンドウインスタンス（HWND）の後ろに割り当てる補足バイト数（通常は0）
	wcex.hInstance = hInstance; // このウィンドウが属するインスタンスのハンドル
	wcex.hIcon = static_cast<HICON>(LoadImage(nullptr, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_SHARED)); // アイコンイメージのハンドル
	wcex.hCursor = static_cast<HCURSOR>(LoadImage(nullptr, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_SHARED)); // カーソルイメージのハンドル
	wcex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1); // ウィンドウの背景色
	wcex.lpszMenuName = nullptr; // メニューバークラスの指定（メニューがない場合NULL）
	wcex.lpszClassName = TEXT("TutorialWindowClass"); // ウィンドウクラスを識別するための文字列
	wcex.hIconSm = static_cast<HICON>(LoadImage(nullptr, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_SHARED)); // 小さいアイコンイメージのハンドル

	//------------------------
	// ウィンドウクラスの登録
	//------------------------
	if (!RegisterClassEx(&wcex))
		return E_FAIL;

	//------------------
	// ウィンドウの作成
	//------------------
	RECT rc = { 0, 0, 640, 480 }; // 作成するウィンドウのクライアント領域（実際に描画できる領域）のサイズ
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false); // クライアント領域が指定したサイズになるようにrcを調整する
													   // CreateWindowで指定するのはウィンドウ全体（タイトルバー等を含む）の
													   // サイズなので調整する必要がある

	hWnd = CreateWindow(
		TEXT("TutorialWindowClass"), // 使用するウィンドウクラス名
		TEXT("Direct3D 11 Tutorial 01"), // ウィンドウタイトル（タイトルバーに表示する文字列）
		WS_OVERLAPPEDWINDOW, // ウィンドウスタイル
		CW_USEDEFAULT, // ウィンドウ左上X座標（適当な値で構わないときはCW_USEDEFAULT）
		CW_USEDEFAULT, // ウィンドウ左上Y座標（適当な値で構わないときはCW_USEDEFAULT）
		rc.right - rc.left, // ウィンドウ幅（適当な値で構わないときはCW_USEDEFAULT）
		rc.bottom - rc.top, // ウィンドウ高さ（適当な値で構わないときはCW_USEDEFAULT）
		nullptr, // 親ウィンドウのウィンドウハンドル（親がなければNULL）
		nullptr, // メニューハンドル（メニューがない場合とウィンドウクラスに登録されたものを使うときはNULL）
		hInstance, // ウィンドウクラスを登録したインスタンスハンドル
		nullptr // WM_CREATE時にLPARAMに渡したい値（渡す必要がない場合はNULL）
	);

	if (!hWnd)
		return E_FAIL;

	//-----------------
	// ウィンドウの表示
	//-----------------
	ShowWindow(hWnd, SW_SHOWDEFAULT); // ウィンドウを表示モードにセット
	UpdateWindow(hWnd); // 強制描画を行う（最初の描画までにラグがあるため）

	return S_OK;
}

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	switch (Msg) {
	case WM_DESTROY:
		//--------------------------------------------------------
		// ウィンドウが破棄された（×ボタンが押されたなど）ときの処理
		//--------------------------------------------------------
		PostQuitMessage(0); // メッセージキューにWM_QUITをポスト
							// 引数はwParamパラメータ（通常はこの値がWinMainの戻り値となる）
		break;
	}

	return DefWindowProc(hWnd, Msg, wParam, lParam); // 基本的なウィンドウプロシージャの動作を行わせる
}

UINT Window::getWidth() const {
	RECT rc;
	GetClientRect(hWnd, &rc);
	return rc.right - rc.left;
}

UINT Window::getHeight() const {
	RECT rc;
	GetClientRect(hWnd, &rc);
	return rc.bottom - rc.top;
}