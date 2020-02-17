#include<M5Stack.h>
#include"Boal.h"
#include"m5sensor.h"

void Object::Boal::VelocityUpdate(){
	// 加速度を加える
	const double gravity = 16.0; // 重力加速度
	const float sinPitch = std::sin(M5Sensor::s_sensor.m_postureFilter.getPitchRadians());
	const float sinRoll = std::sin(M5Sensor::s_sensor.m_postureFilter.getRollRadians());
	if(sinPitch>=0.2 || sinPitch<=-0.2){
		// 10度以下の傾きは無視
		m_vx += sinPitch * gravity;
	}
	if(sinRoll>=0.2 || sinRoll<=-0.2){
		// 10度以下の傾きは無視
		m_vy += sinRoll * gravity;
	}
	// 徐々に減速するようにする(毎フレーム0.95倍する)
	const int16_t multiple = 19, divide = 20;
	m_vx = m_vx * multiple / divide;
	m_vy = m_vy * multiple / divide;
	// 場外に行かないようにする
	if(GetX()+GetVX()<0){
		m_vx = -GetX();
	}else if(GetX()+GetVX()>GetCoordinateWidth()){
		m_vx = GetCoordinateWidth() - GetX();
	}
	if (GetY() + GetVY() < 0){
		m_vy = -GetY();
	}else if (GetY() + GetVY() > GetCoordinateHeight()){
		m_vy = GetCoordinateHeight() - GetY();
	}
}

Object::Boal::Boal(int16_t x, int16_t y, int16_t vx, int16_t vy)
	:Base(x,y,vx,vy,TFT_YELLOW)
	,m_radius(4*s_lcdExpantion)
{}

void Object::Boal::Draw(int16_t drawX, int16_t drawY, uint32_t color)const{
	m5.Lcd.fillCircle(drawX, drawY, m_radius / s_lcdExpantion, color);
}
