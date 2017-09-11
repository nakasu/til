#pragma once

#include <d3d11.h>

class Device;

/**
* 定数データを格納するバッファ
*/
class ConstantBuffer {
public:
	// コンストラクタ
	ConstantBuffer() = default;
	ConstantBuffer(const ConstantBuffer&) = default;
	ConstantBuffer(ConstantBuffer&&) = default;

	// デストラクタ
	~ConstantBuffer() = default;

	// 代入演算子
	ConstantBuffer& operator=(const ConstantBuffer&) = default;
	ConstantBuffer& operator=(ConstantBuffer&&) = default;

	/**
	* 定数バッファの初期化関数
	*
	* capacity	定数バッファの容量（バイト数で指定）
	* device	定数バッファを登録するデバイス
	*/
	HRESULT initialize(UINT capacity, const Device& device);

	/**
	* 定数バッファの終了処理
	*/
	void finalize();

	/**
	* 定数バッファを取得
	*/
	ID3D11Buffer* getConstantBuffer() const { return pConstantBuffer; };

private:
	ID3D11Buffer* pConstantBuffer; // 作成した定数バッファの格納先
};