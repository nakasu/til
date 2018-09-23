#include "vertex_shader.h"
#include <fstream>
#include "device.h"

HRESULT VertexShader::initialize(const std::string& file_name, const Device& device) {
	HRESULT hr = S_OK; // 初期化結果を格納する

	//-----------------------------
	// シェーダプログラムの読み込み
	//-----------------------------
	std::ifstream fin(file_name, std::ios::in | std::ios::binary);
	if (!fin) {
		MessageBox(nullptr, TEXT("The CSO file not found."), TEXT("ERROR"), MB_OK);
		return E_FAIL;
	}

	// ファイルサイズの取得
	fin.seekg(0, std::ios::end);
	SIZE_T cso_size = static_cast<SIZE_T>(fin.tellg());
	fin.seekg(0, std::ios::beg);

	// コンパイル済シェーダ（CSO）ファイルの読み込み
	char* cso_data = new char[cso_size];
	fin.read(cso_data, cso_size);

	//--------------------
	// 頂点シェーダの作成
	//--------------------
	hr = device.getDevice()->CreateVertexShader(
		cso_data, // CSOファイルから読み込んだデータ
		cso_size, // CSOデータのサイズ
		nullptr, // クラスリンクインタフェースへのポインタ（使用しない場合はNULL）
		&pVertexShader // 作成した頂点シェーダの格納先
	);
	if (FAILED(hr)) {
		delete[] cso_data;
		return hr;
	}

	//-----------------------------------------------------------
	// 入力レイアウト（シェーダに入力される頂点データの情報）の定義
	//-----------------------------------------------------------
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{
			"POSITION", // 入力レイアウトの識別子（セマンティクス）
			0, // 入力レイアウトのインデックス（1つしかなければ0）
			DXGI_FORMAT_R32G32B32_FLOAT, // 入力情報のフォーマット（型情報）
			0, // 入力アセンブラを識別する整数値
			0, // 要素間のオフセット（バイト単位）
			D3D11_INPUT_PER_VERTEX_DATA, // 入力データクラスの情報（D3D11_INPUT_PER_VERTEX_DATAならば頂点単位のデータ）
			0 // 要素ごとに描画するインスタンス数（頂点単位のデータならば0）
		},
		{
			"NORMAL", // 入力レイアウトの識別子（セマンティクス）
			0, // 入力レイアウトのインデックス（1つしかなければ0）
			DXGI_FORMAT_R32G32B32_FLOAT, // 入力情報のフォーマット（型情報）
			0, // 入力アセンブラを識別する整数値
			12, // 要素間のオフセット（バイト単位）
				// 法線情報の前に座標情報（POSITION）として4バイトのfloat型が3つあるためオフセットは12
			D3D11_INPUT_PER_VERTEX_DATA, // 入力データクラスの情報（D3D11_INPUT_PER_VERTEX_DATAならば頂点単位のデータ）
			0 // 要素ごとに描画するインスタンス数（頂点単位のデータならば0）
		}
	};
	UINT numElements = ARRAYSIZE(layout);

	//---------------------
	// 入力レイアウトの作成
	//---------------------
	hr = device.getDevice()->CreateInputLayout(
		layout, // 作成する入力レイアウトの定義
		numElements, // 定義した入力レイアウト数
		cso_data, // CSOデータ
		cso_size, // CSOデータのサイズ
		&pVertexLayout // 作成した入力レイアウトの格納先
	);

	delete[] cso_data;
	if (FAILED(hr))
		return hr;

	//----------------------
	// 入力レイアウトの登録
	//----------------------
	device.getDeviceContext()->IASetInputLayout(pVertexLayout);

	return S_OK;
}

void VertexShader::finalize() {
	//----------------
	// リソースの解放
	//----------------
	if (pVertexShader)
		pVertexShader->Release();

	if (pVertexLayout)
		pVertexLayout->Release();
}