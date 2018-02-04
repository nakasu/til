#pragma once

#include <string>

class Stage;

/**
* �ړ�������ו���\���N���X
*/
class Cargo {
public:
	// �R���X�g���N�^
	Cargo(int x, int y) :x_(x), y_(y) {};
	Cargo(const Cargo&) = default;
	Cargo(Cargo&&) = delete;

	// �f�X�g���N�^
	~Cargo() = default;

	// ������Z�q
	Cargo& operator=(const Cargo&) = delete;
	Cargo& operator=(Cargo&&) = delete;

	int X() const { return x_; };
	int Y() const { return y_; };

	/**
	* �ו����ړ�
	*
	* dst_x		�ړ����X���W
	* dst_y		�ړ����Y���W
	*/
	void move(int dst_x, int dst_y) { x_ = dst_x; y_ = dst_y; };

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