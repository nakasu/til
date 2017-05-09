#pragma once

#include <Windows.h>

class Window {
public:
	// コンストラクタ
	Window() = default;
	Window(const Window&) = default;
	Window(Window&&) = default;

	// デストラクタ
	~Window() = default;

	// 代入演算子
	Window& operator=(const Window&) = default;
	Window& operator=(Window&&) = default;

	/**
	* ウィンドウの初期化関数
	*
	* hInstance	呼び出し元のインスタンスハンドル
	*/
	HRESULT initialize(HINSTANCE hInstance);

	/**
	* ウィンドウハンドルを取得
	*/
	HWND getWindowHandle() const { return hWnd; };

	/**
	* クライアント領域の幅を取得
	*/
	UINT getWidth() const;

	/**
	* クライアント領域の高さを取得
	*/
	UINT getHeight() const;

private:
	/**
	* ウィンドウプロシージャ
	* ウィンドウへのメッセージを処理するルーチン
	*
	* hWnd		メッセージが発生したウィンドウのハンドル
	* Msg		メッセージ
	* wParam	メッセージの付加情報（メッセージの種類によって変わる）
	* lParam	メッセージの付加情報（メッセージの種類によって変わる）
	*/
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

	// メンバ
	HWND hWnd; // ウィンドウハンドル
};
