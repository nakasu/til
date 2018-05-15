#include "device.h"
#include <d3d11.h>
#include "window.h"

HRESULT Device::initialize(const Window& window) {
	HRESULT hr = S_OK; // 初期化結果を格納する

	UINT createDeviceFlags = 0; // D3D11_CREATE_DEVICE_FLAG（デバイスの作成で使用するパラメータ）
#ifdef _DEBUG
	// デバッグモードのときにデバッグ情報を付加したデバイスを作成するようにする
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	//-----------------------------
	// 使用するドライバの種類を指定
	//-----------------------------
	D3D_DRIVER_TYPE driverTypes[] = {
		D3D_DRIVER_TYPE_HARDWARE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	//---------------------------------
	// 使用するDirectXの機能レベルを指定
	//---------------------------------
	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	//--------------------------------------------------------------------
	// 作成するスワップチェイン（描画バッファと書込バッファの切り替え）の定義
	//--------------------------------------------------------------------
	DXGI_SWAP_CHAIN_DESC sd; // スワップチェイン定義構造体
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferDesc.Width = window.getWidth(); // バッファの幅
	sd.BufferDesc.Height = window.getHeight(); // バッファの高さ
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // バッファの各ピクセルのフォーマット（型情報）
	sd.BufferDesc.RefreshRate.Numerator = 60; // リフレッシュレートの分母
	sd.BufferDesc.RefreshRate.Denominator = 1; // リフレッシュレートの分子
	sd.SampleDesc.Count = 1; // アンチエイリアス（マルチサンプリング）に用いるピクセル数（アンチエイリアスを使わない場合は1）
	sd.SampleDesc.Quality = 0; // アンチエイリアス（マルチサンプリング）の品質レベル（アンチエイリアスを使わない場合は0）
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // バッファの使用目的
													  // DXGI_USAGE_RENDER_TARGET_OUTPUT 出力レンダーターゲットとして使用する
	sd.BufferCount = 1; // バッファの枚数
	sd.OutputWindow = window.getWindowHandle(); // 出力するウィンドウのハンドル
	sd.Windowed = true; // 出力がウィンドウモードかフルスクリーンモードか（ウィンドウハンドルモードならばTRUE）

	//------------------------------------
	// デバイスとスワップチェインを作成する
	//------------------------------------
	D3D_FEATURE_LEVEL		featureLevel; // 動作する機能レベル

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++) {
		// ドライバタイプを優先度が高いものから見ていく（デバイスとスワップチェインの作成が成功したら完了）
		D3D_DRIVER_TYPE driverType = driverTypes[driverTypeIndex];
		
		hr = D3D11CreateDeviceAndSwapChain(
			nullptr, // 使用するDXGIアダプタ（デフォルトのものを使用する場合はNULL）
			driverType, // ドライバタイプ
			nullptr, // ドライバタイプがD3D_DRIVER_TYPE_SOFTWAREのときに使用するソフトウェアラスタライザを指定する
					 // ドライバタイプがD3D_DRIVER_TYPE_SOFTWARE以外のときはNULL
			createDeviceFlags, // デバイス作成フラグ
			featureLevels, // 使用する機能レベルを列挙した配列
			numFeatureLevels, // 機能レベルの列挙数
			D3D11_SDK_VERSION, // DirectX SDKのバージョン
			&sd, // 作成するスワップチェインの定義構造体
			&pSwapChain, // 作成したスワップチェインの格納先
			&pd3dDevice, // 作成したデバイスの格納先
			&featureLevel, // 実際に動作する機能レベル
			&pImmediateContext // 作成したデバイスコンテキストの格納先
		);

		// 指定したドライバタイプでデバイスの作成ができた場合はループを抜ける
		if (SUCCEEDED(hr))
			break;
	}

	if (FAILED(hr))
		return hr;

	//----------------------------------------------------------------
	// レンダリングターゲット（レンダリング結果を格納するバッファ）の作成
	//----------------------------------------------------------------
	ID3D11Texture2D* pBackBuffer; // レンダリングターゲット

	// スワップチェインからバッファを取得する
	hr = pSwapChain->GetBuffer(
		0, // バッファのインデックス
		__uuidof(ID3D11Texture2D), // バッファの操作に使用するインタフェースの種類（バッファの型）
								   // 型を直接は指定できないためシステムで定義済のGUIDを用いる
		reinterpret_cast<LPVOID*>(&pBackBuffer)
	);
	if (FAILED(hr))
		return hr;

	//--------------------------------------------------------------------------------------
	// 作成したレンダリングターゲットをデバイスに登録してレンダリングターゲットビューを作成
	//
	// レンダリングターゲットビューはスワップチェインがもつレンダリングターゲット（バッファ）と
	// デバイスがもつ描画パイプラインを結びつける役割を持つ 
	//--------------------------------------------------------------------------------------
	hr = pd3dDevice->CreateRenderTargetView(
		pBackBuffer, // 登録するレンダリングターゲット
		nullptr, // レンダリングターゲットビューの設定構造体
				 // NULLにするとミップマップレベル0ですべてのサブリソースにアクセスできるビューが作成される
		&pRenderTargetView
	);
	pBackBuffer->Release(); // レンダリングターゲットを登録したので開放
	if (FAILED(hr))
		return hr;

	//--------------------------------------------------------
	// 深度ステンシルバッファ（Zバッファ+ステンシルバッファ）の作成
	//--------------------------------------------------------
	ID3D11Texture2D* pDepthStencil; // 深度ステンシルバッファ

	D3D11_TEXTURE2D_DESC descDepth; // 深度ステンシルバッファ定義構造体
	ZeroMemory(&descDepth, sizeof(descDepth));
	descDepth.Width = window.getWidth(); // バッファの幅
	descDepth.Height = window.getHeight(); // バッファの高さ
	descDepth.MipLevels = 1; // バッファ内のミップマップレベルの最大数（ミップマップの枚数）
							 // 0にすると1*1までミップマップを作成
							 // 深度ステンシルバッファではミップマップは必要ないのでレベル1
	descDepth.ArraySize = 1; // バッファの枚数
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; // バッファの各ピクセルのフォーマット（型情報）
													  // DXGI_FORMAT_D24_UNORM_S8_UINT 深度チャンネルに24bit，ステンシルチャンネルに8bitの32bitの符号なし整数フォーマット
	descDepth.SampleDesc.Count = 1; // アンチエイリアス（マルチサンプリング）に用いるピクセル数（アンチエイリアスを使わない場合は1）
	descDepth.SampleDesc.Quality = 0; // アンチエイリアス（マルチサンプリング）の品質レベル（アンチエイリアスを使わない場合は0）
	descDepth.Usage = D3D11_USAGE_DEFAULT; // バッファの読み書き方法の指定
										   // D3D11_USAGE_DEFAULT GPUによる読み書きが可能
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL; // バッファをパイプラインにバインドする方法
													// D3D11_BIND_DEPTH_STENCIL 出力結合ステージに深度ステンシルターゲットとしてバインド
	descDepth.CPUAccessFlags = 0; // 許可するCPUアクセスの種類を指定するフラグ（CPUアクセスが不要な場合は0）
	descDepth.MiscFlags = 0; // 一般的でない細かなオプションを指定するフラグ（使用しない場合は0）

	hr = pd3dDevice->CreateTexture2D(
		&descDepth, // 登録する深度ステンシルバッファ
		nullptr, // サブリソース配列へのポインタ（サブリソースを使用しない場合はNULL）
		&pDepthStencil // 作成した深度ステンシルバッファの格納先
	);
	if (FAILED(hr))
		return hr;

	//--------------------------------------------------------------------------------------
	// 作成した深度ステンシルバッファをデバイスに登録して深度ステンシルビューを作成
	//
	// 深度ステンシルビューはバッファと描画パイプラインを結びつける役割を持つ 
	//--------------------------------------------------------------------------------------
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV; // 深度ステンシルビュー定義構造体
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format; // ビューの各ピクセルのフォーマット（型情報）
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D; // ビューに用いるリソースのタイプ
	descDSV.Texture2D.MipSlice = 0; // 最初に使用するミップマップレベルのインデックス（ミップマップを使用しないので0）

	hr = pd3dDevice->CreateDepthStencilView(
		pDepthStencil, // 深度ステンシルビューに使用するバッファへのポインタ
		&descDSV, // 作成する深度ステンシルビューの定義
		&pDepthStencilView // 作成した深度ステンシルビューの格納先
	);
	if (FAILED(hr))
		return hr;

	//-----------------------------------------------------------------------
	// レンダリングターゲットビューと深度ステンシルビューをデバイスコンテキストに登録
	//-----------------------------------------------------------------------
	pImmediateContext->OMSetRenderTargets(
		1, // 登録するレンダリングターゲットビュー数
		&pRenderTargetView, // 登録するレンダリングターゲットビュー
		pDepthStencilView // 登録する深度ステンシルビュー
	);

	//--------------------
	// ビューポートの設定
	//--------------------
	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0; // ビューポートの左側のX座標
	vp.TopLeftY = 0; // ビューポートの上側のY座標
	vp.Width = static_cast<FLOAT>(window.getWidth()); // ビューポートの幅
	vp.Height = static_cast<FLOAT>(window.getHeight()); // ビューポートの高さ
	vp.MinDepth = 0.0f; // ビューポートの最小深度
	vp.MaxDepth = 1.0f; // ビューポートの最大深度

	pImmediateContext->RSSetViewports(
		1, // 登録するビューポート数
		&vp // 登録するビューポート
	);

	return S_OK;
}

void Device::finalize() {
	// デバイスコンテキストのリセット（登録した情報を消す）
	if (pImmediateContext)
		pImmediateContext->ClearState();

	//----------------
	// リソースの開放
	//----------------
	if (pDepthStencilView)
		pDepthStencilView->Release();
	if (pRenderTargetView)
		pRenderTargetView->Release();
	if (pSwapChain)
		pSwapChain->Release();
	if (pImmediateContext)
		pImmediateContext->Release();
	if (pd3dDevice)
		pd3dDevice->Release();
}
