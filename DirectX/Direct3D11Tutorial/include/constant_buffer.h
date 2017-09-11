#pragma once

#include <d3d11.h>

class Device;

/**
* �萔�f�[�^���i�[����o�b�t�@
*/
class ConstantBuffer {
public:
	// �R���X�g���N�^
	ConstantBuffer() = default;
	ConstantBuffer(const ConstantBuffer&) = default;
	ConstantBuffer(ConstantBuffer&&) = default;

	// �f�X�g���N�^
	~ConstantBuffer() = default;

	// ������Z�q
	ConstantBuffer& operator=(const ConstantBuffer&) = default;
	ConstantBuffer& operator=(ConstantBuffer&&) = default;

	/**
	* �萔�o�b�t�@�̏������֐�
	*
	* capacity	�萔�o�b�t�@�̗e�ʁi�o�C�g���Ŏw��j
	* device	�萔�o�b�t�@��o�^����f�o�C�X
	*/
	HRESULT initialize(UINT capacity, const Device& device);

	/**
	* �萔�o�b�t�@�̏I������
	*/
	void finalize();

	/**
	* �萔�o�b�t�@���擾
	*/
	ID3D11Buffer* getConstantBuffer() const { return pConstantBuffer; };

private:
	ID3D11Buffer* pConstantBuffer; // �쐬�����萔�o�b�t�@�̊i�[��
};