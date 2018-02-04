#include "Cargo.h"
#include "Stage.h"
#include "Game.h"

void Cargo::draw(const Stage& stage, std::string& drawing_area) {
	drawing_area[stage.Width() * y_ + x_] = stage.getObject(x_, y_);
}