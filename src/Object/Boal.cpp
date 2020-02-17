#include<M5Stack.h>
#include"Boal.h"
#include"m5sensor.h"

void Object::Boal::VelocityUpdate(){
	const double gravity = 16.0; // 重力加速度
	m_vx += std::sin(M5Sensor::s_sensor.m_postureFilter.getPitchRadians()) * gravity;
	m_vy += std::sin(M5Sensor::s_sensor.m_postureFilter.getRollRadians()) * gravity;
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
