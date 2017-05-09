#include <windows.h>
#include <tchar.h>
#include "window.h"

/**
* hInstance		インスタンスハンドル（プログラムを識別するためのハンドル）
* hPrevInstance	同一アプリケーションの別インスタンスを識別するためのインスタンスハンドル
*				WIN16APIとの互換性のための引数（WIN32APIでは使用しないため常にNULL）
* lpCmdLine		コマンドライン引数
* nCmdShow		ウィンドウの表示方法（サイズやアクティブかどうかなど）を指定する定数
*/
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
	Window window;

	if (FAILED(window.initialize(hInstance, nCmdShow)))
		return 0; // メッセージループに入る前に終了する際は0を返す

	//------------------
	// メッセージループ
	//------------------
	MSG msg = { 0 };

	// GetMessageでメッセージキューからメッセージを受け取る
	// GetMessageはWM_QUITを受け取った場合のみFALSEを返す
	// GetMessageはメッセージが来るまで制御を返さない
	// メッセージがないときも処理をするにはPeekMessageを使う
	while (
		GetMessage(
			&msg, // メッセージの格納先
			nullptr, // メッセージを受け取るウィンドウのハンドル（アプリケーションで表示している全てのウィンドウから受け取る場合はNULL）
			0, // 受け取るメッセージの最小値（0ならばフィルタリングしない）
			0 // 受け取るメッセージの最大値（0ならばフィルタリングしない）
		)
	) {
		// ウィンドウプロシージャにメッセージを渡す
		DispatchMessage(&msg);
	}

	// システムにWM_QUITのwParamを返す
	return msg.wParam;
}