#include "Boal.h"
#include "m5sensor.h"
#include <M5Stack.h>

void Object::Boal::VelocityUpdate(const std::vector<Object::Terrain> &terrainList)
{
	// 加速度を加える
	const double gravity = 16.0; // 重力加速度
	const float sinPitch = std::sin(M5Sensor::s_sensor.m_postureFilter.getPitchRadians());
	const float sinRoll = std::sin(M5Sensor::s_sensor.m_postureFilter.getRollRadians());
	if (sinPitch >= 0.2 || sinPitch <= -0.2)
	{
		// 10度以下の傾きは無視
		m_vx += sinPitch * gravity;
	}
	if (sinRoll >= 0.2 || sinRoll <= -0.2)
	{
		// 10度以下の傾きは無視
		m_vy += sinRoll * gravity;
	}
	// 徐々に減速するようにする(毎フレーム0.95倍する)
	const int16_t multiple = 19, divide = 20;
	m_vx = m_vx * multiple / divide;
	m_vy = m_vy * multiple / divide;
	// 障害物(xy軸に垂直な長方形)との当たり判定
	for (const Terrain &terrain : terrainList)
	{
		// 重くならないよう、簡易な当たり判定にする
		// std::sqrt()は重いので、斜め45度線で当たり判定をごまかして高速化する
		const int16_t afterX = GetX() + m_vx;
		const int16_t afterY = GetY() + m_vy;
		// y軸並行辺との当たり判定
		if (afterY >= terrain.GetY() && afterY <= terrain.GetY() + terrain.GetHeight())
		{
			// ボールの中心がy軸並行辺内に入った場合のみ行う
			if (GetX() < terrain.GetX() && afterX + m_radius > terrain.GetX())
			{
				// 左y軸並行辺を左から右に跨ぐ
				m_vx = terrain.GetX() - GetX() - m_radius;
			}
			else if (GetX() > terrain.GetX() && afterX - m_radius < terrain.GetX())
			{
				// 左y軸並行辺を右から左に跨ぐ
				m_vx = terrain.GetX() - GetX() + m_radius;
			}
			else if (GetX() < terrain.GetX() + terrain.GetWidth() && afterX + m_radius > terrain.GetX() + terrain.GetWidth())
			{
				// 右y軸並行辺を左から右に跨ぐ
				m_vx = terrain.GetX() + terrain.GetWidth() - GetX() - m_radius;
			}
			else if (GetX() > terrain.GetX() + terrain.GetWidth() && afterX - m_radius < terrain.GetX() + terrain.GetWidth())
			{
				// 右y軸並行辺を右から左に跨ぐ
				m_vx = terrain.GetX() + terrain.GetWidth() - GetX() + m_radius;
			}
		}
		// x軸並行辺との当たり判定
		if (afterX >= terrain.GetX() && afterX <= terrain.GetX() + terrain.GetWidth())
		{
			// ボールの中心がx軸並行辺内に入った場合のみ行う
			if (GetY() < terrain.GetY() && afterY + m_radius > terrain.GetY())
			{
				// 上x軸並行辺を上から下に跨ぐ
				m_vy = terrain.GetY() - GetY() - m_radius;
			}
			else if (GetY() > terrain.GetY() && afterY - m_radius < terrain.GetY())
			{
				// 上x軸並行辺を下から上に跨ぐ
				m_vy = terrain.GetY() - GetY() + m_radius;
			}
			else if (GetY() < terrain.GetY() + terrain.GetHeight() && afterY + m_radius > terrain.GetY() + terrain.GetHeight())
			{
				// 下x軸並行辺を上から下に跨ぐ
				m_vy = terrain.GetY() + terrain.GetHeight() - GetY() - m_radius;
			}
			else if (GetY() > terrain.GetY() + terrain.GetHeight() && afterY - m_radius < terrain.GetY() + terrain.GetHeight())
			{
				// 下x軸並行辺を下から上に跨ぐ
				m_vy = terrain.GetY() + terrain.GetHeight() - GetY() + m_radius;
			}
		}
		// 壁の外部からの4頂点とボールの当たり判定
		// 頂点と当たる辺と違う側にあるかどうかが厳密だが、今回は速度が障害物の大きさより小さいことを前提として簡易な当たり判定をする
		// 頂点がboal内に入っているかで判定する
		const auto CalcManhattanDistance = [afterX, afterY](int16_t x, int16_t y) {
			return std::abs(afterX - x) + std::abs(afterY - y);
		};
		if (CalcManhattanDistance(terrain.GetX() + terrain.GetWidth(), terrain.GetY() + terrain.GetHeight()) < m_radius)
		{
			// 右下頂点
			const int16_t manhattanDistance = CalcManhattanDistance(terrain.GetX() + terrain.GetWidth(), terrain.GetY() + terrain.GetHeight()) < m_radius;
			m_vx += (m_radius - manhattanDistance) / 2;
			m_vy += (m_radius - manhattanDistance) / 2;
		}
		else if (CalcManhattanDistance(terrain.GetX() + terrain.GetWidth(), terrain.GetY()) < m_radius)
		{
			// 右上頂点
			const int16_t manhattanDistance = CalcManhattanDistance(terrain.GetX() + terrain.GetWidth(), terrain.GetY());
			m_vx += (m_radius - manhattanDistance) / 2;
			m_vy -= (m_radius - manhattanDistance) / 2;
		}
		else if (CalcManhattanDistance(terrain.GetX(), terrain.GetY() + terrain.GetHeight()) < m_radius)
		{
			// 左下頂点
			const int16_t manhattanDistance = CalcManhattanDistance(terrain.GetX(), terrain.GetY() + terrain.GetHeight());
			m_vx -= (m_radius - manhattanDistance) / 2;
			m_vy += (m_radius - manhattanDistance) / 2;
		}
		else if (CalcManhattanDistance(terrain.GetX(), terrain.GetY()) < m_radius)
		{
			// 左上頂点
			const int16_t manhattanDistance = CalcManhattanDistance(terrain.GetX(), terrain.GetY());
			m_vx -= (m_radius - manhattanDistance) / 2;
			m_vy -= (m_radius - manhattanDistance) / 2;
		}
	}
}

Object::Boal::Boal(int16_t x, int16_t y, int16_t vx, int16_t vy)
	: Base(x, y, vx, vy, TFT_YELLOW)
	, m_radius(4 << s_lcdExpantionBit)
{
}

void Object::Boal::DrawWithShrinkedParameter(int16_t drawX, int16_t drawY, uint32_t color) const
{
	m5.Lcd.fillCircle(drawX, drawY, m_radius >> s_lcdExpantionBit, color);
}
