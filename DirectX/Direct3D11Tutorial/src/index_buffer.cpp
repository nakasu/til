#include "index_buffer.h"
#include "device.h"

HRESULT IndexBuffer::initialize(UINT capacity, WORD* indices, const Device& device) {
	//--------------------------
	// インデックスバッファの定義
	//--------------------------
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(WORD) * capacity; // バッファのサイズ（バイト単位）
	bd.Usage = D3D11_USAGE_DEFAULT; // バッファの使用法（D3D11_USAGE_DEFAULTはGPUによる読み書きができるバッファ）
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER; // バッファを描画パイプラインにバインドする方法
											 // D3D11_BIND_INDEX_BUFFERならばインデックスバッファとして入力アセンブラにバインドする
	bd.CPUAccessFlags = 0; // CPUアクセスフラグ（CPUアクセスが不必要ならば0）

	//-------------------------
	// インデックスバッファを作成
	//-------------------------
	D3D11_SUBRESOURCE_DATA InitData; // 初期化データ
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = indices;
	HRESULT hr = device.getDevice()->CreateBuffer(&bd, &InitData, &pIndexBuffer);
	if (FAILED(hr))
		return hr;

	//-------------------------
	// インデックスバッファの登録
	//-------------------------
	device.getDeviceContext()->IASetIndexBuffer(
		pIndexBuffer, // 登録するインデックスバッファ
		DXGI_FORMAT_R16_UINT, // インデックスバッファ内のデータフォーマット
		0 // インデックスバッファのオフセット
	);

	return S_OK;
}

void IndexBuffer::finalize() {
	//---------------
	// リソースの解放
	//---------------
	if (pIndexBuffer)
		pIndexBuffer->Release();
}