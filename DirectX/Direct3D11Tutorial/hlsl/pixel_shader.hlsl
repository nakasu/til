//--------------------
// 頂点のデータ型の宣言
//--------------------
struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float4 color : COLOR0; // ディフューズ色
};

//--------------------------
// ピクセルシェーダのmain関数
//--------------------------
float4 main(VS_OUTPUT input) : SV_TARGET
{
	return input.color;
}