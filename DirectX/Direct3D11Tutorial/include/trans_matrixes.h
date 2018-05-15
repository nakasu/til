#pragma once

#include <d3d11.h>
#include <DirectXMath.h>

class Window;

/**
* 各種座標変換行列を格納するクラス
*/
class TransMatrixes {
public:
	// コンストラクタ
	TransMatrixes() = default;
	TransMatrixes(const TransMatrixes&) = default;
	TransMatrixes(TransMatrixes&&) = default;

	// デストラクタ
	~TransMatrixes() = default;

	// 代入演算子
	TransMatrixes& operator=(const TransMatrixes&) = default;
	TransMatrixes& operator=(TransMatrixes&&) = default;

	/**
	* 各種座標変換行列の初期化関数
	*/
	HRESULT initialize(const Window& window);

	/**
	* ワールド変換行列1を取得
	*/
	DirectX::XMMATRIX getWorldMatrix1() const { return world_matrix1; };

	/**
	* ワールド変換行列2を取得
	*/
	DirectX::XMMATRIX getWorldMatrix2() const { return world_matrix2; };

	/**
	* ビュー変換行列を取得
	*/
	DirectX::XMMATRIX getViewMatrix() const { return view_matrix; };

	/**
	* プロジェクション変換行列を取得
	*/
	DirectX::XMMATRIX getProjectionMatrix() const { return projection_matrix; };

private:
	DirectX::XMMATRIX world_matrix1; // ワールド変換行列1
	DirectX::XMMATRIX world_matrix2; // ワールド変換行列2
	DirectX::XMMATRIX view_matrix; // ビュー変換行列
	DirectX::XMMATRIX projection_matrix; // プロジェクション変換行列
};