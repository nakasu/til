#include "trans_matrixes.h"
#include "window.h"

HRESULT TransMatrixes::initialize(const Window& window) {
	//------------------------------------
	// ���[���h�ϊ��s��̏�����
	//------------------------------------
	world_matrix = DirectX::XMMatrixIdentity(); // �P�ʍs��ŏ�����

	//---------------------
	// �r���[�ϊ��s��̏�����
	//---------------------
	DirectX::XMVECTOR eye = DirectX::XMVectorSet(0.0f, 1.0f, -5.0f, 0.0); // �J�������W
	DirectX::XMVECTOR at = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f); // �œ_���W
	DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f); // �J�����̏����
	view_matrix = DirectX::XMMatrixLookAtLH(eye, at, up); // �r���[�ϊ��s��𐶐��iLH�͍�����W�n�Ő������邱�Ƃ�\���j

	//-----------------------------------------
	// �v���W�F�N�V�����ϊ��s��̏�����
	//
	// �v���W�F�N�V�����ϊ��Ƃ��ē������e���g�p����
	//-----------------------------------------
	projection_matrix = DirectX::XMMatrixPerspectiveFovLH(
		DirectX::XM_PIDIV2, // �r���[�{�����[����Y�����̊p�x�iXM_PIDIV2�̓�/2�j
		window.getAspectRatio(), // �r���[�{�����[���̃A�N�y�N�g��
		0.01f, // �r���[�{�����[���̎�O��Z���W
		100.0f // �r���[�{�����[���̉���Z���W
	);

	return S_OK;
}