#pragma once

#include <d3d11.h>
#include <DirectXMath.h>

class Device;

/**
* ���_�f�[�^�̃C���f�b�N�X�l���i�[����o�b�t�@
*/
class IndexBuffer {
public:
	// �R���X�g���N�^
	IndexBuffer() = default;
	IndexBuffer(const IndexBuffer&) = default;
	IndexBuffer(IndexBuffer&&) = default;

	// �f�X�g���N�^
	~IndexBuffer() = default;

	// ������Z�q
	IndexBuffer& operator=(const IndexBuffer&) = default;
	IndexBuffer& operator=(IndexBuffer&&) = default;

	/**
	* �C���f�b�N�X�o�b�t�@�̏������֐�
	*
	* capacity	�C���f�b�N�X�o�b�t�@�̗e�ʁiWORD�^�̌��Ŏw��j
	* indices	�C���f�b�N�X�o�b�t�@�Ɋi�[����f�[�^
	* device	�C���f�b�N�X�o�b�t�@��o�^����f�o�C�X
	*/
	HRESULT initialize(UINT capacity, WORD* indices, const Device& device);

	/**
	* �C���f�b�N�X�o�b�t�@�̏I������
	*/
	void finalize();

private:
	ID3D11Buffer* pIndexBuffer; // �쐬�����C���f�b�N�X�o�b�t�@�̊i�[��
};