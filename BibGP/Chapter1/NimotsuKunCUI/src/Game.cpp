#include "Game.h"
#include <iostream>
#include <fstream>
#include <string>

Game::Game() {
	std::string init_stage_data;

	//-----------------------
	// �X�e�[�W�f�[�^�ǂݍ���
	//-----------------------
	loadStageData("stageData.txt", init_stage_data);

	//---------------
	// �X�e�[�W������
	//---------------
	stage_ = std::make_unique<Stage>(init_stage_data);

	//-----------------
	// �v���C���[������
	//-----------------
	auto player_position = init_stage_data.find(PLAYER_CHAR);
	player_ = std::make_unique<Player>(player_position % (stage_->Width() + 1), player_position / (stage_->Width() + 1));
}

void Game::getInput() {
	std::cin >> input_;
}

void Game::update() {
	player_->update(input_, *stage_);
}

void Game::draw() {
	std::string drawing_area;

	stage_->draw(drawing_area);
	player_->draw(*stage_, drawing_area);

	for (unsigned int i = 0; i < stage_->Height(); i++)
		std::cout << drawing_area.substr(stage_->Width() * i, stage_->Width()) << std::endl;

	std::cout << "a:left d:right w:up s:down. command?" << std::endl;
}

void Game::loadStageData(const std::string& file_name, std::string& stage_data) {
	//--------------------------------
	// �X�e�[�W�f�[�^�t�@�C���̓ǂݍ���
	//--------------------------------
	std::ifstream fin(file_name);

	if (fin.fail()) {
		std::cout << "Error!!: Can't read " << file_name << "." << std::endl;
		char tmp;
		std::cin >> tmp;
		exit(EXIT_FAILURE);
	}

	fin.seekg(0, std::ios::end);
	auto file_size = static_cast<size_t>(fin.tellg());
	fin.seekg(0, std::ios::beg);
	auto buf = std::make_unique<char[]>(file_size);
	fin.read(buf.get(), file_size);

	stage_data = buf.get();
}