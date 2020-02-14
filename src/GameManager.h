#ifndef DEF_GAMEMANAGER_H
#define DEF_GAMEMANAGER_H

#include<stdint.h>

// ゲームを管理するクラス
class GameManager{
public:
	GameManager();
	~GameManager() = default;
	void Update();
	void Draw() const;

	static const int32_t s_backColor; // 背景色、他から呼び出すことができるようにpublicに。

private:
	int16_t m_boalX, m_boalY;
};

#endif