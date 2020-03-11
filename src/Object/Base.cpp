#include "Base.h"
#include "GameManager.h"
#include <M5Stack.h>

const uint8_t Object::Base::s_lcdExpantionBit = 5;
// これらのパラメータは後で初期化する。m5が初期化されていないため、width(),height()の向きが逆になる場合がある
int16_t Object::Base::s_coordinateWidth;
int16_t Object::Base::s_coordinateHeight;

void Object::Base::InitParameter()
{
	s_coordinateWidth = m5.Lcd.width() << Object::Base::s_lcdExpantionBit;
	s_coordinateHeight = m5.Lcd.height() << Object::Base::s_lcdExpantionBit;
}

void Object::Base::Draw() const
{
	// 拡大率を考慮し描画位置を計算して描画する
	DrawWithShrinkedParameter(m_x >> s_lcdExpantionBit, m_y >> s_lcdExpantionBit, m_color);
}

void Object::Base::Draw(uint32_t color) const
{
	// 拡大率を考慮し描画位置を計算して描画する
	DrawWithShrinkedParameter(m_x >> s_lcdExpantionBit, m_y >> s_lcdExpantionBit, color);
}

void Object::Base::BeforeErase() const
{
	if (m_vx != 0 || m_vy != 0)
	{
		// 移動前の位置を背景色で塗りつぶす
		DrawWithShrinkedParameter((m_x - m_vx) >> s_lcdExpantionBit, (m_y - m_vy) >> s_lcdExpantionBit, GameManager::s_backColor);
	}
}

void Object::Base::Move()
{
	// 速度が決まっているので動かすだけ
	m_x += m_vx;
	m_y += m_vy;
}

int16_t Object::Base::GetX() const
{
	return m_x;
}

int16_t Object::Base::GetY() const
{
	return m_y;
}

int16_t Object::Base::GetVX() const
{
	return m_vx;
}

int16_t Object::Base::GetVY() const
{
	return m_vy;
}

int16_t Object::Base::GetCoordinateWidth()
{
	return s_coordinateWidth;
}

int16_t Object::Base::GetCoordinateHeight()
{
	return s_coordinateHeight;
}

Object::Base::Base(int16_t x, int16_t y, int16_t vx, int16_t vy, uint32_t color)
	: m_vx(vx)
	, m_vy(vy)
	, m_x(x)
	, m_y(y)
	, m_color(color)
{
}
