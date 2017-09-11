#include "index_buffer.h"
#include "device.h"

HRESULT IndexBuffer::initialize(UINT capacity, WORD* indices, const Device& device) {
	//--------------------------
	// �C���f�b�N�X�o�b�t�@�̒�`
	//--------------------------
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(WORD) * capacity; // �o�b�t�@�̃T�C�Y�i�o�C�g�P�ʁj
	bd.Usage = D3D11_USAGE_DEFAULT; // �o�b�t�@�̎g�p�@�iD3D11_USAGE_DEFAULT��GPU�ɂ��ǂݏ������ł���o�b�t�@�j
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER; // �o�b�t�@��`��p�C�v���C���Ƀo�C���h������@
											 // D3D11_BIND_INDEX_BUFFER�Ȃ�΃C���f�b�N�X�o�b�t�@�Ƃ��ē��̓A�Z���u���Ƀo�C���h����
	bd.CPUAccessFlags = 0; // CPU�A�N�Z�X�t���O�iCPU�A�N�Z�X���s�K�v�Ȃ��0�j

	//-------------------------
	// �C���f�b�N�X�o�b�t�@���쐬
	//-------------------------
	D3D11_SUBRESOURCE_DATA InitData; // �������f�[�^
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = indices;
	HRESULT hr = device.getDevice()->CreateBuffer(&bd, &InitData, &pIndexBuffer);
	if (FAILED(hr))
		return hr;

	//-------------------------
	// �C���f�b�N�X�o�b�t�@�̓o�^
	//-------------------------
	device.getDeviceContext()->IASetIndexBuffer(
		pIndexBuffer, // �o�^����C���f�b�N�X�o�b�t�@
		DXGI_FORMAT_R16_UINT, // �C���f�b�N�X�o�b�t�@���̃f�[�^�t�H�[�}�b�g
		0 // �C���f�b�N�X�o�b�t�@�̃I�t�Z�b�g
	);

	return S_OK;
}

void IndexBuffer::finalize() {
	//---------------
	// ���\�[�X�̉��
	//---------------
	if (pIndexBuffer)
		pIndexBuffer->Release();
}