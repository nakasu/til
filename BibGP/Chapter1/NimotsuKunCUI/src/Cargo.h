#pragma once

#include <string>

class Stage;

/**
* 移動させる荷物を表すクラス
*/
class Cargo {
public:
	// コンストラクタ
	Cargo(int x, int y) :x_(x), y_(y) {};
	Cargo(const Cargo&) = default;
	Cargo(Cargo&&) = delete;

	// デストラクタ
	~Cargo() = default;

	// 代入演算子
	Cargo& operator=(const Cargo&) = delete;
	Cargo& operator=(Cargo&&) = delete;

	int X() const { return x_; };
	int Y() const { return y_; };

	/**
	* 荷物を移動
	*
	* dst_x		移動先のX座標
	* dst_y		移動先のY座標
	*/
	void move(int dst_x, int dst_y) { x_ = dst_x; y_ = dst_y; };

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