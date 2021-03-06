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

//--------------------------
// ピクセルシェーダのmain関数
//--------------------------
float4 main(VS_OUTPUT input) : SV_TARGET
{
	float4 final_color = 0.0f;

	for (int i = 0; i < 2; ++i) {
		final_color += saturate(dot((float3)light_dirs[i], input.norm) * light_colors[i]);
	}
	final_color.a = 1.0f;

	return final_color;
}