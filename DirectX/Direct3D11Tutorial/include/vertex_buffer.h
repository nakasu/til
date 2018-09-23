#pragma once

#include <d3d11.h>
#include <DirectXMath.h>

class Device;

/**
* 頂点データを格納するバッファ
*/
class VertexBuffer {
public:
	/**
	* 1つの頂点データを表す構造体
	*/
	struct SimpleVertex {
		DirectX::XMFLOAT3 pos; // 座標
		DirectX::XMFLOAT3 normal; // 法線
		//DirectX::XMFLOAT4 color; // 色
	};

	// コンストラクタ
	VertexBuffer() = default;
	VertexBuffer(const VertexBuffer&) = default;
	VertexBuffer(VertexBuffer&&) = default;

	// デストラクタ
	~VertexBuffer() = default;

	// 代入演算子
	VertexBuffer& operator=(const VertexBuffer&) = default;
	VertexBuffer& operator=(VertexBuffer&&) = default;

	/**
	* 頂点バッファの初期化関数
	*
	* capacity	頂点バッファの容量（登録する頂点の個数で指定）
	* vertices	頂点バッファに格納するデータ
	* topology	頂点バッファ内のデータの解釈方法
	* device	頂点バッファを登録するデバイス
	*/
	HRESULT initialize(UINT capacity, SimpleVertex* vertices, D3D11_PRIMITIVE_TOPOLOGY topology, const Device& device);

	/**
	* 頂点バッファの終了処理
	*/
	void finalize();

private:
	ID3D11Buffer* pVertexBuffer; // 作成した頂点バッファの格納先
};