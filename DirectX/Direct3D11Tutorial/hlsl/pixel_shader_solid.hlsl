//------------------
// �萔�o�b�t�@�̐錾
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
// ���_�̃f�[�^�^�̐錾
//--------------------
struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float3 norm : TEXCOORD0;
};

//-------------------------------
// �����p�s�N�Z���V�F�[�_��main�֐�
//-------------------------------
float4 main(VS_OUTPUT input) : SV_TARGET
{
	return output_color;
	//return float4(1.0f, 0.0f, 0.0f, 1.0f);
}