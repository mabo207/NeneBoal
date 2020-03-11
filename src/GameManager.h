#ifndef DEF_GAMEMANAGER_H
#define DEF_GAMEMANAGER_H

#include <stdint.h>
#include "Object\Boal.h"
#include <memory>

// ゲームを管理するクラス
class GameManager
{
public:
	GameManager();
	~GameManager() = default;
	void Init();
	void Update();
	void Draw() const;

	static const int32_t s_backColor; // 背景色、他から呼び出すことができるようにpublicに。

private:
	Object::Boal m_boal;
};

#endif