#include <iostream>
#include "Game.h"

int main() {
	Game	game;

	game.draw();

	//ƒƒCƒ“ƒ‹[ƒv
	while (true) {
		if (game.isClear())
			break;
		game.getInput();
		game.update();
		game.draw();
	}

	std::cout << "Congratulation's! you won." << std::endl;

	char tmp;
	std::cin >> tmp;

	return 0;
}