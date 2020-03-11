#include "Terrain.h"
#include <M5Stack.h>

Object::Terrain::Terrain(int16_t x, int16_t y, uint32_t color, int16_t width, int16_t height)
	: Base(x, y, 0, 0, color)
	, m_width(width)
	, m_height(height)
{
}

Object::Terrain::~Terrain() {}

int16_t Object::Terrain::GetWidth() const
{
	return m_width;
}

int16_t Object::Terrain::GetHeight() const
{
	return m_height;
}

void Object::Terrain::DrawWithShrinkedParameter(int16_t drawX, int16_t drawY, uint32_t color) const
{
	// 障害物は全て長方形
	m5.Lcd.fillRect(drawX, drawY, m_width >> s_lcdExpantionBit, m_height >> s_lcdExpantionBit, color);
}
