#pragma once

#include <d3d11.h>
#include <DirectXMath.h>

class Window;

/**
* �e����W�ϊ��s����i�[����N���X
*/
class TransMatrixes {
public:
	// �R���X�g���N�^
	TransMatrixes() = default;
	TransMatrixes(const TransMatrixes&) = default;
	TransMatrixes(TransMatrixes&&) = default;

	// �f�X�g���N�^
	~TransMatrixes() = default;

	// ������Z�q
	TransMatrixes& operator=(const TransMatrixes&) = default;
	TransMatrixes& operator=(TransMatrixes&&) = default;

	/**
	* �e����W�ϊ��s��̏������֐�
	*/
	HRESULT initialize(const Window& window);

	/**
	* ���[���h�ϊ��s����擾
	*/
	DirectX::XMMATRIX getWorldMatrix() const { return world_matrix; };

	/**
	* �r���[�ϊ��s����擾
	*/
	DirectX::XMMATRIX getViewMatrix() const { return view_matrix; };

	/**
	* �v���W�F�N�V�����ϊ��s����擾
	*/
	DirectX::XMMATRIX getProjectionMatrix() const { return projection_matrix; };

private:
	DirectX::XMMATRIX world_matrix; // ���[���h�ϊ��s��
	DirectX::XMMATRIX view_matrix; // �r���[�ϊ��s��
	DirectX::XMMATRIX projection_matrix; // �v���W�F�N�V�����ϊ��s��
};