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
	m5.Lcd.fillScreen(s_backColor);
	m_boal.BeforeErase();
	// 描画処理
	m_boal.Object::Base::Draw();
	if (M5Sensor::s_sensor.m_mpu9250.readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250) != 0x71){
		m5.Lcd.drawString("cannnot find MPU9250", 20, 20);
	}else{
		m5.Lcd.drawString("can find MPU9250", 20, 20);
	}
	m5.Lcd.drawString("ax:", 40, 40);
	m5.Lcd.drawNumber(M5Sensor::s_sensor.m_mpu9250.ax * 100, 100, 40);
	m5.Lcd.drawString("ay:", 40, 60);
	m5.Lcd.drawNumber(M5Sensor::s_sensor.m_mpu9250.ay * 100, 100, 60);
	m5.Lcd.drawString("az:", 40, 80);
	m5.Lcd.drawNumber(M5Sensor::s_sensor.m_mpu9250.az * 100, 100, 80);
	m5.Lcd.drawString("gx:", 40, 100);
	m5.Lcd.drawNumber(M5Sensor::s_sensor.m_mpu9250.gx * 100, 100, 100);
	m5.Lcd.drawString("gy:", 40, 120);
	m5.Lcd.drawNumber(M5Sensor::s_sensor.m_mpu9250.gy * 100, 100, 120);
	m5.Lcd.drawString("gz:", 40, 140);
	m5.Lcd.drawNumber(M5Sensor::s_sensor.m_mpu9250.gz * 100, 100, 140);

	m5.Lcd.drawString("pitch:", 40, 160);
	m5.Lcd.drawNumber(M5Sensor::s_sensor.m_postureFilter.getPitch() * 100, 100, 160);
	m5.Lcd.drawString("roll:", 40, 180);
	m5.Lcd.drawNumber(M5Sensor::s_sensor.m_postureFilter.getRoll() * 100, 100, 180);
	m5.Lcd.drawString("yaw:", 40, 200);
	m5.Lcd.drawNumber(M5Sensor::s_sensor.m_postureFilter.getYaw() * 100, 100, 200);
}
