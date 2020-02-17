#include<M5Stack.h>
#include"Boal.h"
#include"m5sensor.h"

void Object::Boal::VelocityUpdate(){
	const double gravity = 7.0; // 重力加速度
	m_vx += std::sin(M5Sensor::s_sensor.m_postureFilter.getPitchRadians()) * gravity;
	m_vy += std::sin(M5Sensor::s_sensor.m_postureFilter.getRollRadians()) * gravity;
	// 場外に行かないようにする
	if(GetX()+GetVX()<0){
		m_vx = -GetX();
	}else if(GetX()+GetVX()>m5.Lcd.width()){
		m_vx = m5.Lcd.width() - GetX();
	}
	if (GetY() + GetVY() < 0){
		m_vy = -GetY();
	}else if (GetY() + GetVY() > m5.Lcd.height()){
		m_vy = m5.Lcd.height() - GetY();
	}
}

Object::Boal::Boal(int16_t x, int16_t y, int16_t vx, int16_t vy)
	:Base(x,y,vx,vy,TFT_YELLOW)
	,m_radius(4)
{}

void Object::Boal::Draw(int16_t x, int16_t y, uint32_t color)const{
	m5.Lcd.fillCircle(x, y, m_radius, color);
}
