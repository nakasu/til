#pragma once

#include <string>
#include <d3d11.h>

class Device;

class PixelShader {
public:
	// コンストラクタ
	PixelShader() = default;
	PixelShader(const PixelShader&) = default;
	PixelShader(PixelShader&&) = default;

	// デストラクタ
	~PixelShader() = default;

	// 代入演算子
	PixelShader& operator=(const PixelShader&) = default;
	PixelShader& operator=(PixelShader&&) = default;

	/**
	* ピクセルシェーダの初期化関数
	*
	* file_name	コンパイル済シェーダのパス
	* device	シェーダを登録するデバイス
	*/
	HRESULT initialize(const std::string& file_name, const Device& device);

	/**
	* ピクセルシェーダの終了処理
	*/
	void finalize();

	/**
	* ピクセルシェーダの取得
	*/
	ID3D11PixelShader* get() const { return pPixelShader; };

private:
	// メンバ
	ID3D11PixelShader* pPixelShader; // 作成したピクセルシェーダの格納先
};