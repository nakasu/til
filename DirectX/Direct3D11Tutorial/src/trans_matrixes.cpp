#include "trans_matrixes.h"
#include "window.h"

HRESULT TransMatrixes::initialize(const Window& window) {
	//------------------------------------
	// ワールド変換行列の初期化
	//------------------------------------
	world_matrix = DirectX::XMMatrixIdentity(); // 単位行列で初期化

	//---------------------
	// ビュー変換行列の初期化
	//---------------------
	DirectX::XMVECTOR eye = DirectX::XMVectorSet(0.0f, 1.0f, -5.0f, 0.0); // カメラ座標
	DirectX::XMVECTOR at = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f); // 焦点座標
	DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f); // カメラの上方向
	view_matrix = DirectX::XMMatrixLookAtLH(eye, at, up); // ビュー変換行列を生成（LHは左手座標系で生成することを表す）

	//-----------------------------------------
	// プロジェクション変換行列の初期化
	//
	// プロジェクション変換として透視投影を使用する
	//-----------------------------------------
	projection_matrix = DirectX::XMMatrixPerspectiveFovLH(
		DirectX::XM_PIDIV2, // ビューボリュームのY方向の角度（XM_PIDIV2はπ/2）
		window.getAspectRatio(), // ビューボリュームのアクペクト比
		0.01f, // ビューボリュームの手前側Z座標
		100.0f // ビューボリュームの奥側Z座標
	);

	return S_OK;
}