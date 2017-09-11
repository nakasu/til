#pragma once

#include <d3d11.h>
#include <DirectXMath.h>

class Device;

/**
* 頂点データのインデックス値を格納するバッファ
*/
class IndexBuffer {
public:
	// コンストラクタ
	IndexBuffer() = default;
	IndexBuffer(const IndexBuffer&) = default;
	IndexBuffer(IndexBuffer&&) = default;

	// デストラクタ
	~IndexBuffer() = default;

	// 代入演算子
	IndexBuffer& operator=(const IndexBuffer&) = default;
	IndexBuffer& operator=(IndexBuffer&&) = default;

	/**
	* インデックスバッファの初期化関数
	*
	* capacity	インデックスバッファの容量（WORD型の個数で指定）
	* indices	インデックスバッファに格納するデータ
	* device	インデックスバッファを登録するデバイス
	*/
	HRESULT initialize(UINT capacity, WORD* indices, const Device& device);

	/**
	* インデックスバッファの終了処理
	*/
	void finalize();

private:
	ID3D11Buffer* pIndexBuffer; // 作成したインデックスバッファの格納先
};