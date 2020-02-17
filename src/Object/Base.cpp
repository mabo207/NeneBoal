#include<M5Stack.h>
#include"Base.h"
#include"GameManager.h"

void Object::Base::Draw()const{
	Draw(m_x, m_y, m_color);
}

void Object::Base::Draw(uint32_t color)const{
	Draw(m_x, m_y, color);
}

void Object::Base::BeforeErase()const{
	// 移動前の位置を背景色で塗りつぶす
	Draw(m_x - m_vx, m_y - m_vy, GameManager::s_backColor);
}

void Object::Base::Move(){
	// 速度が決まっているので動かすだけ
	m_x += m_vx;
	m_y += m_vy;
}

int16_t Object::Base::GetX()const{
	return m_x;
}

int16_t Object::Base::GetY() const{
	return m_y;
}

int16_t Object::Base::GetVX() const{
	return m_vx;
}

int16_t Object::Base::GetVY() const{
	return m_vy;
}

Object::Base::Base(int16_t x, int16_t y, int16_t vx, int16_t vy, uint32_t color)
	: m_vx(vx), m_vy(vy), m_x(x), m_y(y), m_color(color)
{}
