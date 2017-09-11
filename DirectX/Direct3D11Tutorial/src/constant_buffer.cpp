#include "constant_buffer.h"
#include "device.h"

HRESULT ConstantBuffer::initialize(UINT capacity, const Device& device) {
	//------------------
	// 定数バッファの定義
	//------------------
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = capacity; // バッファのサイズ（バイト単位）
	bd.Usage = D3D11_USAGE_DEFAULT; // バッファの使用法（D3D11_USAGE_DEFAULTはGPUによる読み書きができるバッファ）
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // バッファを描画パイプラインにバインドする方法
											 // D3D11_BIND_CONSTANT_BUFFERならば定数バッファとして入力アセンブラにバインドする
	bd.CPUAccessFlags = 0; // CPUアクセスフラグ（CPUアクセスが不必要ならば0）

	//------------------
	// 定数バッファを作成
	//------------------
	HRESULT hr = device.getDevice()->CreateBuffer(&bd, nullptr, &pConstantBuffer);
	if (FAILED(hr))
		return hr;

	return S_OK;
}

void ConstantBuffer::finalize() {
	//----------------
	// リソースの解放
	//----------------
	if (pConstantBuffer)
		pConstantBuffer->Release();
}