#pragma once

#include <string>

class Stage;

/**
* �v���C���[��\���N���X
*/
class Player {
public:
	// �R���X�g���N�^
	Player(int x, int y) :x_(x), y_(y) {};
	Player(const Player&) = delete;
	Player(Player&&) = delete;

	// �f�X�g���N�^
	~Player() = default;

	// ������Z�q
	Player& operator=(const Player&) = delete;
	Player& operator=(Player&&) = delete;

	/**
	* �X�V����
	* 
	* input		���[�U����̓���
	* stage		�X�e�[�W�f�[�^
	*/
	void update(char input, Stage& stage);

	/**
	* �`��֐�
	*
	* stage			�X�e�[�W�f�[�^
	* drawing_area	�`���
	*/
	void draw(const Stage& stage, std::string& drawing_area);

private:
	int x_;
	int y_;
};