#pragma once

#include <Windows.h>
#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")

class Window;

class Device {
public:
	// コンストラクタ
	Device() = default;
	Device(const Device&) = default;
	Device(Device&&) = default;

	// デストラクタ
	~Device() = default;

	// 代入演算子
	Device& operator=(const Device&) = default;
	Device& operator=(Device&&) = default;

	/**
	* デバイスの初期化関数
	*
	* window	描画対象のウィンドウクラス（バッファサイズを決めるのに必要）
	*/
	HRESULT initialize(const Window& window);

	/**
	* デバイスの終了処理
	*/
	void finalize();

	/**
	* デバイスコンテキストの取得
	*/
	ID3D11DeviceContext* getDeviceContext() const { return pImmediateContext; };

	/**
	* レンダリングターゲットビューの取得
	*/
	ID3D11RenderTargetView* getRenderTargetView() const { return pRenderTargetView; };

	/**
	* スワップチェインの取得
	*/
	IDXGISwapChain* getSwapChain() const { return pSwapChain; };

private:
	// メンバ
	ID3D11Device*			pd3dDevice; // 作成したデバイス（バッファやテクスチャの設定を行うもの）の格納先
	ID3D11DeviceContext*	pImmediateContext; // 作成したデバイスコンテキスト（描画を行うもの）の格納先
											   // 即時コンテキスト（詰まれたコマンドが即時実行される）（c.f. 遅延コンテキスト）
	IDXGISwapChain*			pSwapChain; // 作成したスワップチェインの格納先
	ID3D11RenderTargetView*	pRenderTargetView; // 作成したレンダリングターゲットビュー格納先
};