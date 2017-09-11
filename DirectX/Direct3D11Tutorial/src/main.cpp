#include <windows.h>
#include <tchar.h>
#include "window.h"
#include "device.h"
#include "vertex_shader.h"
#include "pixel_shader.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "constant_buffer.h"
#include "trans_matrixes.h"

/**
* 描画（レンダリング）を行う関数
*
* device			描画に使用するデバイス
* vertex_shader		使用する頂点シェーダ
* pixel_shader		使用するピクセルシェーダ
* trans_matrixes	各種座標変換行列（ワールド変換行列等）
* constant_buffer	定数バッファ
*/
void Render(const Device& device, const VertexShader& vertex_shader, const PixelShader& pixel_shader, const TransMatrixes& trans_matrixes, ID3D11Buffer* constant_buffer);

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
	IndexBuffer		index_buffer;
	ConstantBuffer	constant_buffer;
	TransMatrixes	trans_matrixes;

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
		vertex_shader.finalize();
		device.finalize();
		return 0;
	}

	//-------------------------
	// ピクセルシェーダの初期化
	//-------------------------
	if (FAILED(pixel_shader.initialize("./Debug/pixel_shader.cso", device))) {
		pixel_shader.finalize();
		vertex_shader.finalize();
		device.finalize();
		return 0;
	}

	//---------------------
	// 頂点バッファの初期化
	//---------------------
	VertexBuffer::SimpleVertex vertices[] = {
		{ DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f), DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
		{ DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },
		{ DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },
		{ DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },
		{ DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f), DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) },
	};

	if (FAILED(vertex_buffer.initialize(ARRAYSIZE(vertices), vertices, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, device))) {
		vertex_buffer.finalize();
		pixel_shader.finalize();
		vertex_shader.finalize();
		device.finalize();
		return 0;
	}

	//---------------------------
	// インデックスバッファの初期化
	//---------------------------
	WORD indices[] = {
		3,1,0,
		2,1,3, // 1枚目

		0,5,4,
		1,5,0, // 2枚目

		3,4,7,
		0,4,3, // 3枚目

		1,6,5,
		2,6,1, // 4枚目

		2,7,6,
		3,7,2, // 5枚目

		6,4,5,
		7,4,6, // 6枚目
	};

	if (FAILED(index_buffer.initialize(ARRAYSIZE(indices), indices, device))) {
		index_buffer.finalize();
		vertex_buffer.finalize();
		pixel_shader.finalize();
		vertex_shader.finalize();
		device.finalize();
		return 0;
	}

	//--------------------
	// 定数バッファの初期化
	//--------------------
	if (FAILED(constant_buffer.initialize(sizeof(DirectX::XMMATRIX) * 3, device))) {
		constant_buffer.finalize();
		index_buffer.finalize();
		vertex_buffer.finalize();
		pixel_shader.finalize();
		vertex_shader.finalize();
		device.finalize();
		return 0;
	}

	//----------------------
	// 各種座標変換行列の初期化
	//----------------------
	if (FAILED(trans_matrixes.initialize(window))) {
		vertex_shader.finalize();
		pixel_shader.finalize();
		vertex_buffer.finalize();
		index_buffer.finalize();
		constant_buffer.finalize();
		device.finalize();
		return 0;
	}

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
			0, // 受け取るメッセージの最大値（0ならばフィルタリングしない）
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
			Render(device, vertex_shader, pixel_shader, trans_matrixes, constant_buffer.getConstantBuffer());
		}
	}

	//----------
	// 終了処理
	//----------
	vertex_shader.finalize();
	pixel_shader.finalize();
	vertex_buffer.finalize();
	index_buffer.finalize();
	constant_buffer.finalize();
	device.finalize();

	// WM_QUITのwParamを返す
	return msg.wParam;
}

void Render(const Device& device, const VertexShader& vertex_shader, const PixelShader& pixel_shader, const TransMatrixes& trans_matrixes, ID3D11Buffer* constant_buffer) {
	//---------------------------------------
	// 時間経過による座標変換用のパラメータtを更新
	//---------------------------------------
	static float t = 0.0f;
	static ULONGLONG start_time = GetTickCount64(); // GetTickCount64()はシステム起動時からの経過ミリ秒を返す
	ULONGLONG current_time = GetTickCount64();
	t = (current_time - start_time) / 1000.0f;

	//------------------
	// 描画バッファのクリア
	//------------------
	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // クリアする色（RGBA）
	device.getDeviceContext()->ClearRenderTargetView(device.getRenderTargetView(), ClearColor);

	//---------------------
	// ワールド変換行列の更新
	//---------------------
	DirectX::XMMATRIX world_matrix = trans_matrixes.getWorldMatrix();
	world_matrix = DirectX::XMMatrixRotationY(t);

	//-----------------------
	// シェーダへ渡す変数の更新
	//-----------------------
	DirectX::XMMATRIX cb[3];
	cb[0] = DirectX::XMMatrixTranspose(world_matrix); // ワールド変換行列の転置行列
	cb[1] = DirectX::XMMatrixTranspose(trans_matrixes.getViewMatrix()); // ビュー変換行列の転置行列
	cb[2] = DirectX::XMMatrixTranspose(trans_matrixes.getProjectionMatrix()); // プロジェクション変換行列の転置行列
	// 定数バッファを更新
	device.getDeviceContext()->UpdateSubresource(
		constant_buffer, // データのコピー先ポインタ
		0, // サブリソースのインデックス
		nullptr, // コピーするバイト数（定数バッファの場合NULL）
		&cb, // コピー元データのポインタ
		0, // コピー元データの1行のサイズ
		0 // コピー元データの1深度スライスのサイズ
	);

	// 頂点シェーダのセット
	device.getDeviceContext()->VSSetShader(
		vertex_shader.get(), // セットする頂点シェーダ
		nullptr, // シェーダで使用するインタフェース（使用しない場合はNULL）
		0 // 使用するインタフェースの数
	);

	// 頂点シェーダに定数バッファをセット
	device.getDeviceContext()->VSSetConstantBuffers(
		0, // 定数バッファをセットする位置
		1, // セットする定数バッファの数
		&constant_buffer // セットする定数バッファのアドレス
	);

	// ピクセルシェーダのセット
	device.getDeviceContext()->PSSetShader(
		pixel_shader.get(), // セットするピクセルシェーダ
		nullptr, // シェーダで使用するインタフェース（使用しない場合はNULL）
		0 // 使用するインタフェースの数
	);

	//-------------
	//立方体の描画
	//-------------
	device.getDeviceContext()->DrawIndexed(
		36, // 描画するインデックスの数
		0, // インデックスバッファから読み取る最初の場所
		0 // 各インデックス値に加算する値
	);

	// 垂直同期の設定
	device.getSwapChain()->Present(
		0, // n番目の垂直同期の後に表示を同期する（0だと即時表示）
		0 // フレーム出力のオプション
	);
}