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

//----------------------
// ���_�V�F�[�_��main�֐�
//----------------------
VS_OUTPUT main( float4 pos : POSITION, float3 norm : NORMAL ) /*VS_OUTPUT�̕��ŃZ�}���e�B�N�X��t�^�ς̂��߃Z�}���e�B�N�X�͕s�v*/
{
	//----------
	// ���W�ϊ�
	//----------
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.pos = mul(pos, world); // ���[���h���W�n�ɕϊ�
	output.pos = mul(output.pos, view); // �r���[���W�n�ɕϊ�
	output.pos = mul(output.pos, projection); // �v���W�F�N�V�������W�n�ɕϊ�
	output.norm = mul(float4(norm, 1), world).xyz; // �@���x�N�g�������[���h���W�n�ɕϊ�

	return output;
}