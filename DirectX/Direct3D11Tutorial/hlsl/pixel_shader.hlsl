//--------------------
// ���_�̃f�[�^�^�̐錾
//--------------------
struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float4 color : COLOR0; // �f�B�t���[�Y�F
};

//--------------------------
// �s�N�Z���V�F�[�_��main�֐�
//--------------------------
float4 main(VS_OUTPUT input) : SV_TARGET
{
	return input.color;
}