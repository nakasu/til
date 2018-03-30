#pragma once

#include <memory>
#include "Stage.h"
#include "Player.h"

/**
* ゲーム全体を表すクラス
*/
class Game {
public:
	// 定数
	static constexpr char SPACE_CHAR			= ' '; // 何もない場所を表す文字
	static constexpr char WALL_CHAR				= '#'; // 壁を表す文字
	static constexpr char CARGO_CHAR			= 'o'; // 荷物を表す文字
	static constexpr char CARGO_ON_GOAL_CHAR	= 'O'; // ゴール上にある荷物を表す文字
	static constexpr char GOAL_CHAR				= '.'; // ゴール（荷物を置く場所）を表す文字
	static constexpr char PLAYER_CHAR			= 'p'; // プレイヤーを表す文字
	static constexpr char MOVE_LEFT				= 'a'; // 左への移動コマンドを表す文字
	static constexpr char MOVE_RIGHT			= 'd'; // 右への移動コマンドを表す文字
	static constexpr char MOVE_UP				= 'w'; // 上への移動コマンドを表す文字
	static constexpr char MOVE_DOWN				= 's'; // 下への移動コマンドを表す文字

	// コンストラクタ
	Game();
	Game(const Game&) = delete;
	Game(Game&&) = delete;

	// デストラクタ
	~Game() = default;

	// 代入演算子
	Game& operator=(const Game&) = delete;
	Game& operator=(Game&&) = delete;

	/**
	* クリア判定
	*/
	bool isClear() { return stage_->isClear(); };

	/**
	* ユーザからの入力を取得
	*/
	void getInput();

	/**
	* ゲームの状態を更新
	*/
	void update();

	/**
	* 画面に描画
	*/
	void draw();

private:
	// 関数
	/**
	* ステージデータファイルからデータを読み込む
	*
	* file_name		ステージデータファイル名
	* stage_data	読み込んだステージデータの保存先
	*/
	void loadStageData(const std::string& file_name, std::string& stage_data);

	// メンバ
	std::unique_ptr<Stage>	stage_;
	std::unique_ptr<Player>	player_;
	char	input_;
};