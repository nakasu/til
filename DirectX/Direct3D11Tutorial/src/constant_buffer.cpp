#include "constant_buffer.h"
#include "device.h"

HRESULT ConstantBuffer::initialize(UINT capacity, const Device& device) {
	//------------------
	// �萔�o�b�t�@�̒�`
	//------------------
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = capacity; // �o�b�t�@�̃T�C�Y�i�o�C�g�P�ʁj
	bd.Usage = D3D11_USAGE_DEFAULT; // �o�b�t�@�̎g�p�@�iD3D11_USAGE_DEFAULT��GPU�ɂ��ǂݏ������ł���o�b�t�@�j
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // �o�b�t�@��`��p�C�v���C���Ƀo�C���h������@
											 // D3D11_BIND_CONSTANT_BUFFER�Ȃ�Β萔�o�b�t�@�Ƃ��ē��̓A�Z���u���Ƀo�C���h����
	bd.CPUAccessFlags = 0; // CPU�A�N�Z�X�t���O�iCPU�A�N�Z�X���s�K�v�Ȃ��0�j

	//------------------
	// �萔�o�b�t�@���쐬
	//------------------
	HRESULT hr = device.getDevice()->CreateBuffer(&bd, nullptr, &pConstantBuffer);
	if (FAILED(hr))
		return hr;

	return S_OK;
}

void ConstantBuffer::finalize() {
	//----------------
	// ���\�[�X�̉��
	//----------------
	if (pConstantBuffer)
		pConstantBuffer->Release();
}