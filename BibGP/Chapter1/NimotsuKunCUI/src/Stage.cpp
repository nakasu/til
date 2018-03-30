#include "Stage.h"
#include <string>
#include <iostream>
#include <fstream>
#include "Game.h"

Stage::Stage(const std::string& init_data) {
	//-------------------------
	// �X�e�[�W���C�����̎擾
	//-------------------------
	width_ = init_data.find('\n');
	height_ = 0;
	auto w = width_;
	while (w != -1) {
		data_ += init_data.substr((width_ + 1) * height_, width_);

		// �X�e�[�W�������ꂳ��Ă��Ȃ��ꍇ�G���[
		if ((w - ((width_ + 1) * height_)) != width_) {
			std::cout << "Error!!: Stage data is invalid." << std::endl;
			char tmp;
			std::cin >> tmp;
			exit(EXIT_FAILURE);
		}

		height_++;
		w = init_data.find('\n', (width_ + 1) * height_ + 1);
	}

	//------------
	// �ו�������
	//------------
	auto idx = data_.find(Game::CARGO_CHAR);
	while (idx != -1) {
		cargoes_.emplace_back(idx % width_, idx / width_);
		data_[idx] = Game::SPACE_CHAR;
		idx = data_.find(static_cast<char>(Game::CARGO_CHAR), idx + 1);
	}

	//---------------------
	// �v���C���[�����̍폜
	//---------------------
	data_[data_.find(Game::PLAYER_CHAR)] = Game::SPACE_CHAR;
}

char Stage::getObject(int x, int y) const {
	//---------
	// �͈͊m�F
	//---------
	if (width_ * y + x >= data_.size())
		return '\0';

	//-------------------
	// �ו����ǂ����̊m�F
	//-------------------
	for (const auto& c : cargoes_) {
		if (x == c.X() && y == c.Y()) {
			// �S�[����ɂ���ו����m�F
			if (data_[width_ * y + x] == Game::GOAL_CHAR)
				return Game::CARGO_ON_GOAL_CHAR;
			else
				return Game::CARGO_CHAR;
		}
	}

	return data_[width_ * y + x];
}

bool Stage::moveCargo(int cargo_x, int cargo_y, char direction) {
	//-------------
	// �ړ���̊m�F
	//-------------
	int dst_x;
	int dst_y;
	switch (direction) {
	case Game::MOVE_LEFT:
		dst_x = cargo_x - 1;
		dst_y = cargo_y;
		break;
	case Game::MOVE_RIGHT:
		dst_x = cargo_x + 1;
		dst_y = cargo_y;
		break;
	case Game::MOVE_UP:
		dst_x = cargo_x;
		dst_y = cargo_y - 1;
		break;
	case Game::MOVE_DOWN:
		dst_x = cargo_x;
		dst_y = cargo_y + 1;
		break;
	}
	
	switch (getObject(dst_x, dst_y)) {
	case '\0':
	case Game::WALL_CHAR:
	case Game::CARGO_CHAR:
	case Game::CARGO_ON_GOAL_CHAR:
		return false;
		break;
	}

	//-----------
	// �ו����ړ�
	//-----------
	for (auto& c : cargoes_) {
		if (cargo_x == c.X() && cargo_y == c.Y())
			c.move(dst_x, dst_y);
	}

	return true;
}

bool Stage::isClear() {
	for (const auto& c : cargoes_) {
		if (data_[width_ * c.Y() + c.X()] != Game::GOAL_CHAR)
			return false;
	}
	return true;
}

void Stage::draw(std::string& drawing_area) {
	drawing_area = data_;
	for (auto& c : cargoes_)
		c.draw(*this, drawing_area);
}
