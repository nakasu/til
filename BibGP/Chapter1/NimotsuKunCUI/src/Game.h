#pragma once

#include <memory>
#include "Stage.h"
#include "Player.h"

/**
* �Q�[���S�̂�\���N���X
*/
class Game {
public:
	// �萔
	static constexpr char SPACE_CHAR			= ' '; // �����Ȃ��ꏊ��\������
	static constexpr char WALL_CHAR				= '#'; // �ǂ�\������
	static constexpr char CARGO_CHAR			= 'o'; // �ו���\������
	static constexpr char CARGO_ON_GOAL_CHAR	= 'O'; // �S�[����ɂ���ו���\������
	static constexpr char GOAL_CHAR				= '.'; // �S�[���i�ו���u���ꏊ�j��\������
	static constexpr char PLAYER_CHAR			= 'p'; // �v���C���[��\������
	static constexpr char MOVE_LEFT				= 'a'; // ���ւ̈ړ��R�}���h��\������
	static constexpr char MOVE_RIGHT			= 'd'; // �E�ւ̈ړ��R�}���h��\������
	static constexpr char MOVE_UP				= 'w'; // ��ւ̈ړ��R�}���h��\������
	static constexpr char MOVE_DOWN				= 's'; // ���ւ̈ړ��R�}���h��\������

	// �R���X�g���N�^
	Game();
	Game(const Game&) = delete;
	Game(Game&&) = delete;

	// �f�X�g���N�^
	~Game() = default;

	// ������Z�q
	Game& operator=(const Game&) = delete;
	Game& operator=(Game&&) = delete;

	/**
	* �N���A����
	*/
	bool isClear() { return stage_->isClear(); };

	/**
	* ���[�U����̓��͂��擾
	*/
	void getInput();

	/**
	* �Q�[���̏�Ԃ��X�V
	*/
	void update();

	/**
	* ��ʂɕ`��
	*/
	void draw();

private:
	// �֐�
	/**
	* �X�e�[�W�f�[�^�t�@�C������f�[�^��ǂݍ���
	*
	* file_name		�X�e�[�W�f�[�^�t�@�C����
	* stage_data	�ǂݍ��񂾃X�e�[�W�f�[�^�̕ۑ���
	*/
	void loadStageData(const std::string& file_name, std::string& stage_data);

	// �����o
	std::unique_ptr<Stage>	stage_;
	std::unique_ptr<Player>	player_;
	char	input_;
};