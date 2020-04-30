#include "GameManager.h"
#include "m5sensor.h"
#include <M5Stack.h>

const int32_t GameManager::s_backColor = TFT_BLACK;

GameManager::GameManager()
	: m_boal(Object::Base::s_coordinateWidth / 2, Object::Base::s_coordinateHeight / 2, 0, 0)
	, m_terrainList{Object::Terrain(0, 0, TFT_WHITE, 150, 7680),
					Object::Terrain(0, 0, TFT_WHITE, 10240, 150),
					Object::Terrain(10090, 0, TFT_WHITE, 150, 7680),
					Object::Terrain(0, 7530, TFT_WHITE, 10240, 150),
					Object::Terrain(2000, 2680, TFT_WHITE, 150, 5000),
					Object::Terrain(0, 4000, TFT_WHITE, 1500, 150),
					Object::Terrain(7000, 1000, TFT_WHITE, 3240, 150)}
{
}

void GameManager::Update()
{
	// ボールの移動
	m_boal.VelocityUpdate(m_terrainList); // 速度の更新
	m_boal.Move();						  // 移動処理
}

void GameManager::Draw() const
{
	// オブジェクトを全消去
	m_boal.BeforeErase();
	for (const Object::Terrain &terrain : m_terrainList)
	{
		terrain.BeforeErase();
	}

	// 描画処理
	for (const Object::Terrain &terrain : m_terrainList)
	{
		terrain.Draw();
	}
	m_boal.Object::Base::Draw();
}
