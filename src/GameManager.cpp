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
	// m5.Lcd.fillRect(40, 120, 160, 100, s_backColor);
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
	// m5.Lcd.drawString("X:", 40, 120);
	// m5.Lcd.drawNumber(m_boal.GetX(), 100, 120);
	// m5.Lcd.drawString("Y:", 40, 140);
	// m5.Lcd.drawNumber(m_boal.GetY(), 100, 140);
	// m5.Lcd.drawString("pitch:", 40, 160);
	// m5.Lcd.drawNumber(M5Sensor::s_sensor.m_postureFilter.getPitch() * 100, 100, 160);
	// m5.Lcd.drawString("roll:", 40, 180);
	// m5.Lcd.drawNumber(M5Sensor::s_sensor.m_postureFilter.getRoll() * 100, 100, 180);
	// m5.Lcd.drawString("yaw:", 40, 200);
	// m5.Lcd.drawNumber(M5Sensor::s_sensor.m_postureFilter.getYaw() * 100, 100, 200);
}
