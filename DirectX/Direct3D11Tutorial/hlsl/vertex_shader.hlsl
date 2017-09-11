//------------------
// �萔�o�b�t�@�̐錾
//------------------
cbuffer ConstantBuffer : register(b0)
{
	matrix world;
	matrix view;
	matrix projection;
}

//--------------------
// ���_�̃f�[�^�^�̐錾
//--------------------
struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float4 color : COLOR0; // �f�B�t���[�Y�F
};

//----------------------
// ���_�V�F�[�_��main�֐�
//----------------------
VS_OUTPUT main( float4 pos : POSITION, float4 color : COLOR ) /*VS_OUTPUT�̕��ŃZ�}���e�B�N�X��t�^�ς̂��߃Z�}���e�B�N�X�͕s�v*/
{
	//----------
	// ���W�ϊ�
	//----------
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.pos = mul(pos, world); // ���[���h���W�ŏ�����
	output.pos = mul(output.pos, view); // �r���[���W�ɕϊ�
	output.pos = mul(output.pos, projection); // �v���W�F�N�V�������W�ɕϊ�
	output.color = color;

	return output;
}