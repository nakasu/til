//------------------
// 定数バッファの宣言
//------------------
cbuffer ConstantBuffer : register(b0)
{
	matrix world;
	matrix view;
	matrix projection;
	float4 light_dirs[2];
	float4 light_colors[2];
	float4 output_color;
}

//--------------------
// 頂点のデータ型の宣言
//--------------------
struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float3 norm : TEXCOORD0;
};

//-------------------------------
// 光源用ピクセルシェーダのmain関数
//-------------------------------
float4 main(VS_OUTPUT input) : SV_TARGET
{
	return output_color;
	//return float4(1.0f, 0.0f, 0.0f, 1.0f);
}