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

//----------------------
// 頂点シェーダのmain関数
//----------------------
VS_OUTPUT main( float4 pos : POSITION, float3 norm : NORMAL ) /*VS_OUTPUTの方でセマンティクスを付与済のためセマンティクスは不要*/
{
	//----------
	// 座標変換
	//----------
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.pos = mul(pos, world); // ワールド座標系に変換
	output.pos = mul(output.pos, view); // ビュー座標系に変換
	output.pos = mul(output.pos, projection); // プロジェクション座標系に変換
	output.norm = mul(float4(norm, 1), world).xyz; // 法線ベクトルをワールド座標系に変換

	return output;
}