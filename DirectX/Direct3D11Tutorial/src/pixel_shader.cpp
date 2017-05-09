#include "pixel_shader.h"
#include <fstream>
#include "device.h"

HRESULT PixelShader::initialize(const std::string& file_name, const Device& device) {
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

	//-----------------------
	// ピクセルシェーダの作成
	//-----------------------
	hr = device.getDevice()->CreatePixelShader(
		cso_data, // CSOファイルから読み込んだデータ
		cso_size, // CSOデータのサイズ
		nullptr, // クラスリンクインタフェースへのポインタ（使用しない場合はNULL）
		&pPixelShader // 作成した頂点シェーダの格納先
	);

	delete[] cso_data;
	if (FAILED(hr))
		return hr;

	return S_OK;
}

void PixelShader::finalize() {
	//----------------
	// リソースの解放
	//----------------
	if (pPixelShader)
		pPixelShader->Release();
}