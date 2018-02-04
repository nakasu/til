#include "Game.h"
#include <iostream>
#include <string>

Game::Game() {
	//---------------
	// ステージ初期化
	//---------------
	std::string init_stage = "########"
							 "# .. p #"
							 "# oo   #"
							 "#      #"
							 "########";
	stage = std::make_unique<Stage>(init_stage, STAGE_WIDTH, STAGE_HEIGHT);

	//-----------------
	// プレイヤー初期化
	//-----------------
	auto player_position = init_stage.find(PLAYER_CHAR);
	player = std::make_unique<Player>(player_position % STAGE_WIDTH, player_position / STAGE_WIDTH);
}

void Game::getInput() {
	std::cin >> input;
}

void Game::update() {
	player->update(input, *stage);
}

void Game::draw() {
	std::string drawing_area;

	stage->draw(drawing_area);
	player->draw(*stage, drawing_area);

	for (auto i = 0; i < STAGE_HEIGHT; i++)
		std::cout << drawing_area.substr(STAGE_WIDTH*i, STAGE_WIDTH) << std::endl;

	std::cout << "a:left d:right w:up s:down. command?" << std::endl;
}