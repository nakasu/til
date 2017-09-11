#pragma once

#include <string>
#include <d3d11.h>
#include <DirectXMath.h>

class Device;

class VertexShader {
public:
	// コンストラクタ
	VertexShader() = default;
	VertexShader(const VertexShader&) = default;
	VertexShader(VertexShader&&) = default;

	// デストラクタ
	~VertexShader() = default;

	// 代入演算子
	VertexShader& operator=(const VertexShader&) = default;
	VertexShader& operator=(VertexShader&&) = default;

	/**
	* 頂点シェーダの初期化関数
	*
	* file_name	コンパイル済シェーダのパス
	* device	シェーダを登録するデバイス
	*/
	HRESULT initialize(const std::string& file_name, const Device& device);

	/**
	* 頂点シェーダの終了処理
	*/
	void finalize();

	/**
	* 頂点シェーダの取得
	*/
	ID3D11VertexShader* get() const { return pVertexShader; };

private:
	// メンバ
	ID3D11VertexShader* pVertexShader; // 作成した頂点シェーダの格納先
	ID3D11InputLayout* pVertexLayout; // 作成した入力レイアウトの格納先
};