#include <M5Stack.h>
#include "GameManager.h"
#include "m5sensor.h"

const int32_t GameManager::s_backColor = TFT_BLACK;

GameManager::GameManager()
	:m_boal(m5.Lcd.width()/2,m5.Lcd.height()/2,0,0)
{}

void GameManager::Update(){
	// ボールの移動
	m_boal.VelocityUpdate(); // 速度の更新
	m_boal.Move(); // 移動処理
}

void GameManager::Draw()const{
	// オブジェクトを全消去
	m5.Lcd.fillRect(40, 160, 120, 60, s_backColor);
	m_boal.BeforeErase();
	// 描画処理
	m_boal.Object::Base::Draw();
	m5.Lcd.drawString("pitch:", 40, 160);
	m5.Lcd.drawNumber(M5Sensor::s_sensor.m_postureFilter.getPitch() * 100, 100, 160);
	m5.Lcd.drawString("roll:", 40, 180);
	m5.Lcd.drawNumber(M5Sensor::s_sensor.m_postureFilter.getRoll() * 100, 100, 180);
	m5.Lcd.drawString("yaw:", 40, 200);
	m5.Lcd.drawNumber(M5Sensor::s_sensor.m_postureFilter.getYaw() * 100, 100, 200);
}
