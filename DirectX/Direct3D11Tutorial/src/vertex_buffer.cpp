#include "vertex_buffer.h"
#include <Windows.h>
#include <DirectXMath.h>
#include "device.h"

HRESULT VertexBuffer::initialize(UINT capacity, DirectX::XMFLOAT3* vertices, D3D11_PRIMITIVE_TOPOLOGY topology,const Device& device) {
	//--------------------
	// 頂点バッファの定義
	//--------------------
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(DirectX::XMFLOAT3) * capacity; // バッファのサイズ（バイト単位）
	bd.Usage = D3D11_USAGE_DEFAULT; // バッファの使用法（D3D11_USAGE_DEFAULTはGPUによる読み書きができるバッファ）
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER; // バッファを描画パイプラインにバインドする方法
											 // D3D11_BIND_VERTEX_BUFFERならば頂点バッファとして入力アセンブラにバインドする
	bd.CPUAccessFlags = 0; // CPUアクセスフラグ（CPUアクセスが不必要ならば0）
	
	//-------------------
	// 頂点バッファを作成
	//-------------------
	D3D11_SUBRESOURCE_DATA InitData; // 初期化データ
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertices;
	HRESULT hr = device.getDevice()->CreateBuffer(&bd, &InitData, &pVertexBuffer);
	if (FAILED(hr))
		return hr;

	//-------------------
	// 頂点バッファの登録
	//-------------------
	UINT stride = sizeof(DirectX::XMFLOAT3);
	UINT offset = 0;
	device.getDeviceContext()->IASetVertexBuffers(
		0, // バッファをバインドする入力スロット番号
		1, // 配列内の頂点バッファの数
		&pVertexBuffer, // 登録する頂点バッファ配列
		&stride, // 頂点バッファ内の要素のサイズ（頂点バッファごとに指定するので配列のポインタを指定する）
		&offset // 頂点バッファのオフセット（頂点バッファごとに指定するので配列のポインタを指定する）
	);

	//-------------------
	// 頂点群の解釈を定義
	//-------------------
	device.getDeviceContext()->IASetPrimitiveTopology(topology);

	return S_OK;
}

void VertexBuffer::finalize() {
	//----------------
	// リソースの解放
	//----------------
	if (pVertexBuffer)
		pVertexBuffer->Release();
}