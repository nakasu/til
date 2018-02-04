#include "Stage.h"
#include <string>
#include "Game.h"

Stage::Stage(const std::string& init_data, size_t width, size_t height) :data_(init_data), width_(width), height_(height) {
	//------------
	// 荷物初期化
	//------------
	auto idx = data_.find(Game::CARGO_CHAR);
	while (idx != -1) {
		cargoes.emplace_back(idx % width_, idx / width_);
		data_[idx] = Game::SPACE_CHAR;
		idx = data_.find(static_cast<char>(Game::CARGO_CHAR), idx + 1);
	}

	data_[data_.find(Game::PLAYER_CHAR)] = Game::SPACE_CHAR;
}

char Stage::getObject(int x, int y) const {
	//---------
	// 範囲確認
	//---------
	if (width_ * y + x >= data_.size())
		return '\0';

	//-------------------
	// 荷物かどうかの確認
	//-------------------
	for (const auto& c : cargoes) {
		if (x == c.X() && y == c.Y()) {
			// ゴール上にある荷物か確認
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
	// 移動先の確認
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
	// 荷物を移動
	//-----------
	for (auto& c : cargoes) {
		if (cargo_x == c.X() && cargo_y == c.Y())
			c.move(dst_x, dst_y);
	}

	return true;
}

bool Stage::isClear() {
	for (const auto& c : cargoes) {
		if (data_[width_ * c.Y() + c.X()] != Game::GOAL_CHAR)
			return false;
	}
	return true;
}

void Stage::draw(std::string& drawing_area) {
	drawing_area = data_;
	for (auto& c : cargoes)
		c.draw(*this, drawing_area);
}