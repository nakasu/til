#pragma once

#include <string>
#include <vector>
#include "Cargo.h"

/**
* �X�e�[�W��\���N���X
*/
class Stage {
public:
	// �R���X�g���N�^
	/**
	* init_data	������ŕ\���������X�e�[�W�\��
	*/
	Stage(const std::string& init_data);
	
	Stage(const Stage&) = delete;
	Stage(Stage&&) = delete;

	// �f�X�g���N�^
	~Stage() = default;

	// ������Z�q
	Stage& operator=(const Stage&) = delete;
	Stage& operator=(Stage&&) = delete;

	size_t Width() const { return width_; };
	size_t Height() const { return height_; };

	/**
	* �w�肵�����W�ɂ���I�u�W�F�N�g���擾
	*
	* �s���ȍ��W���w�肵���ꍇ��'\0'��Ԃ�
	*
	* x		X���W
	* y		Y���W
	*/
	char getObject(int x, int y) const;

	/**
	* �ו����ړ�����
	*
	* �ړ��������������ǂ�����Ԃ�
	*
	* cargo_x	�ړ��������ו���X���W
	* cargo_y	�ړ��������ו���Y���W
	* direction	�ړ�����������
	*/
	bool moveCargo(int cargo_x, int cargo_y, char direction);

	/**
	* �N���A����
	*/
	bool isClear();

	/**
	* �`��֐�
	*
	* drawing_area	�`���
	*/
	void draw(std::string& drawing_area);

private:
	std::string data_; // �X�e�[�W�\��
	size_t width_; // �X�e�[�W��
	size_t height_; // �X�e�[�W��
	std::vector<Cargo> cargoes_; // �X�e�[�W���̉ו�
};