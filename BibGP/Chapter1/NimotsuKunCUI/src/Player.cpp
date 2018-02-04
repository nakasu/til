#include "Player.h"
#include "Stage.h"
#include "Game.h"

void Player::update(char input, Stage& stage) {
	auto previous_x = x_;
	auto previous_y = y_;

	//----------
	// ˆÚ“®ˆ—
	//----------
	switch (input) {
	case Game::MOVE_LEFT:
		if (x_ > 0)
			--x_;
		break;
	case Game::MOVE_RIGHT:
		if (x_ < static_cast<int>(stage.Width()) - 1)
			++x_;
		break;
	case Game::MOVE_UP:
		if (y_ > 0)
			--y_;
		break;
	case Game::MOVE_DOWN:
		if (y_ < static_cast<int>(stage.Height()) - 1)
			++y_;
		break;
	}

	//-----------
	// “–‚½‚è”»’è
	//-----------
	switch (stage.getObject(x_, y_)) {
	case Game::WALL_CHAR:
		x_ = previous_x;
		y_ = previous_y;
		break;
	case Game::CARGO_CHAR:
	case Game::CARGO_ON_GOAL_CHAR:
		if (!stage.moveCargo(x_, y_, input)) {
			x_ = previous_x;
			y_ = previous_y;
		}
		break;
	}
}

void Player::draw(const Stage& stage, std::string& drawing_area) {
	drawing_area[stage.Width()*y_ + x_] = Game::PLAYER_CHAR;
}