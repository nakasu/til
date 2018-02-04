#pragma once

#include <string>

class Stage;

/**
* プレイヤーを表すクラス
*/
class Player {
public:
	// コンストラクタ
	Player(int x, int y) :x_(x), y_(y) {};
	Player(const Player&) = delete;
	Player(Player&&) = delete;

	// デストラクタ
	~Player() = default;

	// 代入演算子
	Player& operator=(const Player&) = delete;
	Player& operator=(Player&&) = delete;

	/**
	* 更新処理
	* 
	* input		ユーザからの入力
	* stage		ステージデータ
	*/
	void update(char input, Stage& stage);

	/**
	* 描画関数
	*
	* stage			ステージデータ
	* drawing_area	描画先
	*/
	void draw(const Stage& stage, std::string& drawing_area);

private:
	int x_;
	int y_;
};