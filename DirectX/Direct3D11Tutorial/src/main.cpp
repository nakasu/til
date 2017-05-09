#include <windows.h>
#include <tchar.h>
#include "window.h"
#include "device.h"
#include "vertex_shader.h"
#include "pixel_shader.h"
#include "vertex_buffer.h"

/**
* 描画（レンダリング）を行う関数
*
* device		描画に使用するデバイス
* vertex_shader	使用する頂点シェーダ
* pixel_shader	使用するピクセルシェーダ
*/
void Render(const Device& device, const VertexShader& vertex_shader, const PixelShader& pixel_shader);

/**
* hInstance		インスタンスハンドル（プログラムを識別するためのハンドル）
* hPrevInstance	同一アプリケーションの別インスタンスを識別するためのインスタンスハンドル
*				WIN16APIとの互換性のための引数（WIN32APIでは使用しないため常にNULL）
* lpCmdLine		コマンドライン引数
* nCmdShow		ウィンドウの表示方法（サイズやアクティブかどうかなど）を指定する定数
*/
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
	Window			window;
	Device			device;
	VertexShader	vertex_shader;
	PixelShader		pixel_shader;
	VertexBuffer	vertex_buffer;

	//-------------------
	// ウィンドウの初期化
	//-------------------
	if (FAILED(window.initialize(hInstance)))
		return 0; // メッセージループに入る前に終了する際は0を返す

	//-----------------
	// デバイスの初期化
	//-----------------
	if (FAILED(device.initialize(window))) {
		device.finalize();
		return 0;
	}

	//---------------------
	// 頂点シェーダの初期化
	//---------------------
	if (FAILED(vertex_shader.initialize("./Debug/vertex_shader.cso", device))) {
		device.finalize();
		return 0;
	}

	//-------------------------
	// ピクセルシェーダの初期化
	//-------------------------
	if (FAILED(pixel_shader.initialize("./Debug/pixel_shader.cso", device)))
		return 0;

	//---------------------
	// 頂点バッファの初期化
	//---------------------
	DirectX::XMFLOAT3 vertices[] = {
		DirectX::XMFLOAT3(0.0f, 0.5f, 0.5f),
		DirectX::XMFLOAT3(0.5f, -0.5f, 0.5f),
		DirectX::XMFLOAT3(-0.5f, -0.5f, 0.5f)
	};

	if (FAILED(vertex_buffer.initialize(3, vertices, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, device)))
		return 0;

	//------------------
	// メッセージループ
	//------------------
	MSG msg = { 0 };

	//----------------------------------------------------
	// GetMessage
	// 
	// GetMessageでメッセージキューからメッセージを受け取る
	// GetMessageはWM_QUITを受け取った場合のみFALSEを返す
	// GetMessageはメッセージが来るまで制御を返さない
	// メッセージがないときも処理をするにはPeekMessageを使う
	//----------------------------------------------------

	//while (
	//	GetMessage(
	//		&msg, // メッセージの格納先
	//		nullptr, // メッセージを受け取るウィンドウのハンドル（アプリケーションで表示している全てのウィンドウから受け取る場合はNULL）
	//		0, // 受け取るメッセージの最小値（0ならばフィルタリングしない）
	//		0 // 受け取るメッセージの最大値（0ならばフィルタリングしない）
	//	)
	//) {
	//	// ウィンドウプロシージャにメッセージを渡す
	//	DispatchMessage(&msg);
	//}

	//------------------------
	// PeekMessage
	//
	// PeekMessageではメッセージキューにメッセージがある場合はメッセージを受け取り，
	// メッセージが空の場合はそのまま制御を返す
	//-------------------------

	//PeekMessageはWM_QUITもそのまま受け取るのでループ条件を変える
	while (WM_QUIT != msg.message) {
		if (PeekMessage(
			&msg, // メッセージの格納先
			nullptr, // メッセージを受け取るウィンドウのハンドル（アプリケーションで表示している全てのウィンドウから受け取る場合はNULL）
			0, // 受け取るメッセージの最小値（0ならばフィルタリングしない）
			0, // 受け取るメッセージの最大値（０ならばフィルタリングしない）
			PM_REMOVE // 受け取ったメッセージをキューから削除するか（もう一度メッセージを受け取りたい場合のみ削除しない）
		)
			) {
			// キーボードメッセージ（キーボードが押されたという情報）から文字メッセージ（押された文字の情報）に変換する
			// 次のループで文字メッセージが受け取れる
			TranslateMessage(&msg);

			// ウィンドウプロシージャにメッセージを渡す
			DispatchMessage(&msg);
		}
		else {
			// レンダリングを行う
			Render(device, vertex_shader, pixel_shader);
		}
	}

	//----------
	// 終了処理
	//----------
	vertex_shader.finalize();
	pixel_shader.finalize();
	vertex_buffer.finalize();
	device.finalize();

	// WM_QUITのwParamを返す
	return msg.wParam;
}

void Render(const Device& device, const VertexShader& vertex_shader, const PixelShader& pixel_shader) {
	//------------------
	// 描画バッファのクリア
	//------------------
	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // クリアする色（RGBA）
	device.getDeviceContext()->ClearRenderTargetView(device.getRenderTargetView(), ClearColor);

	// 頂点シェーダのセット
	device.getDeviceContext()->VSSetShader(
		vertex_shader.get(), // セットする頂点シェーダ
		nullptr, // シェーダで使用するインタフェース（使用しない場合はNULL）
		0 // 使用するインタフェースの数
	);

	// ピクセルシェーダのセット
	device.getDeviceContext()->PSSetShader(
		pixel_shader.get(), // セットするピクセルシェーダ
		nullptr, // シェーダで使用するインタフェース（使用しない場合はNULL）
		0 // 使用するインタフェースの数
	);

	// 三角形の描画
	device.getDeviceContext()->Draw(3, 0);

	// 垂直同期の設定
	device.getSwapChain()->Present(
		0, // n番目の垂直同期の後に表示を同期する（0だと即時表示）
		0 // フレーム出力のオプション
	);
}