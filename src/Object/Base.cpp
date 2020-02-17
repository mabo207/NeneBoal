#include<M5Stack.h>
#include"Base.h"
#include"GameManager.h"

const int16_t Object::Base::s_lcdExpantion = 32;
// これらのパラメータは後で初期化する。m5が初期化されていないため、width(),height()の向きが逆になる場合がある
int16_t Object::Base::s_coordinateWidth;
int16_t Object::Base::s_coordinateHeight;
// const int16_t Object::Base::s_coordinateWidth = m5.Lcd.width() * Object::Base::s_lcdExpantion;
// const int16_t Object::Base::s_coordinateHeight = m5.Lcd.height() * Object::Base::s_lcdExpantion;

void Object::Base::InitParameter(){
	s_coordinateWidth = m5.Lcd.width() * Object::Base::s_lcdExpantion;
	s_coordinateHeight = m5.Lcd.height() * Object::Base::s_lcdExpantion;
}

void Object::Base::Draw()const{
	// 拡大率を考慮し描画位置を計算して描画する
	Draw(m_x / s_lcdExpantion, m_y / s_lcdExpantion, m_color);
}

void Object::Base::Draw(uint32_t color)const{
	// 拡大率を考慮し描画位置を計算して描画する
	Draw(m_x / s_lcdExpantion, m_y / s_lcdExpantion, color);
}

void Object::Base::BeforeErase()const{
	// 移動前の位置を背景色で塗りつぶす
	Draw((m_x - m_vx) / s_lcdExpantion, (m_y - m_vy) / s_lcdExpantion, GameManager::s_backColor);
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

int16_t Object::Base::GetCoordinateWidth(){
	return s_coordinateWidth;
}

int16_t Object::Base::GetCoordinateHeight(){
	return s_coordinateHeight;
}

Object::Base::Base(int16_t x, int16_t y, int16_t vx, int16_t vy, uint32_t color)
	: m_vx(vx), m_vy(vy), m_x(x), m_y(y), m_color(color)
{}
