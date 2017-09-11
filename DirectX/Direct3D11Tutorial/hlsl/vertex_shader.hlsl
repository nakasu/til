//------------------
// 定数バッファの宣言
//------------------
cbuffer ConstantBuffer : register(b0)
{
	matrix world;
	matrix view;
	matrix projection;
}

//--------------------
// 頂点のデータ型の宣言
//--------------------
struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float4 color : COLOR0; // ディフューズ色
};

//----------------------
// 頂点シェーダのmain関数
//----------------------
VS_OUTPUT main( float4 pos : POSITION, float4 color : COLOR ) /*VS_OUTPUTの方でセマンティクスを付与済のためセマンティクスは不要*/
{
	//----------
	// 座標変換
	//----------
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.pos = mul(pos, world); // ワールド座標で初期化
	output.pos = mul(output.pos, view); // ビュー座標に変換
	output.pos = mul(output.pos, projection); // プロジェクション座標に変換
	output.color = color;

	return output;
}