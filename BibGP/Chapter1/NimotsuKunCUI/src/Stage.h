#pragma once

#include <string>
#include <vector>
#include "Cargo.h"

/**
* ステージを表すクラス
*/
class Stage {
public:
	// コンストラクタ
	/**
	* init_data	文字列で表した初期ステージ構成
	*/
	Stage(const std::string& init_data);
	
	Stage(const Stage&) = delete;
	Stage(Stage&&) = delete;

	// デストラクタ
	~Stage() = default;

	// 代入演算子
	Stage& operator=(const Stage&) = delete;
	Stage& operator=(Stage&&) = delete;

	size_t Width() const { return width_; };
	size_t Height() const { return height_; };

	/**
	* 指定した座標にあるオブジェクトを取得
	*
	* 不正な座標を指定した場合は'\0'を返す
	*
	* x		X座標
	* y		Y座標
	*/
	char getObject(int x, int y) const;

	/**
	* 荷物を移動する
	*
	* 移動が成功したかどうかを返す
	*
	* cargo_x	移動したい荷物のX座標
	* cargo_y	移動したい荷物のY座標
	* direction	移動したい方向
	*/
	bool moveCargo(int cargo_x, int cargo_y, char direction);

	/**
	* クリア判定
	*/
	bool isClear();

	/**
	* 描画関数
	*
	* drawing_area	描画先
	*/
	void draw(std::string& drawing_area);

private:
	std::string data_; // ステージ構成
	size_t width_; // ステージ幅
	size_t height_; // ステージ高
	std::vector<Cargo> cargoes_; // ステージ中の荷物
};