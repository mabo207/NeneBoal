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
		// y軸並行辺との当たり判定
		if (GetY() >= terrain.GetY() && GetY() <= terrain.GetY() + terrain.GetHeight())
		{
			// 左y軸並行辺との当たり判定
			if (GetX() + m_radius <= terrain.GetX() && GetX() + m_radius + m_vx > terrain.GetX())
			{
				// ボールの右端と左y軸並行辺の交差判定
				m_vx = terrain.GetX() - GetX() - m_radius;
			}
			else if (GetX() - m_radius >= terrain.GetX() && GetX() - m_radius + m_vx < terrain.GetX())
			{
				// ボールの左端と左y軸並行辺の交差判定
				m_vx = terrain.GetX() - GetX() + m_radius;
			}
			//右y軸並行辺との当たり判定
			if (GetX() + m_radius <= terrain.GetX() + terrain.GetWidth() && GetX() + m_radius + m_vx > terrain.GetX() + terrain.GetWidth())
			{
				// ボールの右端と左y軸並行辺の交差判定
				m_vx = terrain.GetX() + terrain.GetWidth() - GetX() - m_radius;
			}
			else if (GetX() - m_radius >= terrain.GetX() + terrain.GetWidth() && GetX() - m_radius + m_vx < terrain.GetX() + terrain.GetWidth())
			{
				// ボールの左端と右y軸並行辺の交差判定
				m_vx = terrain.GetX() + terrain.GetWidth() - GetX() + m_radius;
			}
		}
		// x軸並行辺との当たり判定
		if (GetX() >= terrain.GetX() && GetX() <= terrain.GetX() + terrain.GetWidth())
		{
			// 上x軸並行辺との当たり判定
			if (GetY() + m_radius <= terrain.GetY() && GetY() + m_radius + m_vy > terrain.GetY())
			{
				// ボールの下端と上x軸並行辺の交差判定
				m_vy = terrain.GetY() - GetY() - m_radius;
			}
			else if (GetY() - m_radius >= terrain.GetY() && GetY() - m_radius + m_vy < terrain.GetY())
			{
				// ボールの上端と上x軸並行辺の交差判定
				m_vy = terrain.GetY() - GetY() + m_radius;
			}
			//下x軸並行辺との当たり判定
			if (GetY() + m_radius <= terrain.GetY() + terrain.GetHeight() && GetY() + m_radius + m_vy > terrain.GetY() + terrain.GetHeight())
			{
				// ボールの下端と下x軸並行辺の交差判定
				m_vy = terrain.GetY() + terrain.GetHeight() - GetY() - m_radius;
			}
			else if (GetY() - m_radius >= terrain.GetY() + terrain.GetHeight() && GetY() - m_radius + m_vy < terrain.GetY() + terrain.GetHeight())
			{
				// ボールの上端と下x軸並行辺の交差判定
				m_vy = terrain.GetY() + terrain.GetHeight() - GetY() + m_radius;
			}
		}
		// 壁の外部からの4頂点とボールの当たり判定
		// std::sqrt()は重いので、斜め45度線で当たり判定をごまかして高速化する
		const int16_t diffX = GetX() - terrain.GetX(),
					  diffY = GetY() - terrain.GetY();
		const int16_t sumV = m_vx + m_vy,
					  subV = m_vx - m_vy; // これらの値は除算に用いられるが、0の時は除算の処理に入らないので問題ない
		if (diffX - terrain.GetWidth() > 0 && diffY - terrain.GetHeight() > 0 && -terrain.GetWidth() + diffY - terrain.GetHeight() >= m_radius && diffX - terrain.GetWidth() + diffY - terrain.GetHeight() + sumV < m_radius)
		{
			// 右下の頂点
			// m_vxとm_vyを同じ割合だけ削ると、その場で動かなくなってしまうので、45度線に垂直な方向に押し出す
			m_vx += (m_radius - diffX + terrain.GetWidth() - diffY + terrain.GetHeight() - sumV) / 2;
			m_vy += (m_radius - diffX + terrain.GetWidth() - diffY + terrain.GetHeight() - sumV) / 2;
		}
		else if (diffX - terrain.GetWidth() > 0 && diffY < 0 && diffX - terrain.GetWidth() - diffY >= m_radius && diffX - terrain.GetWidth() - diffY + subV < m_radius)
		{
			// 右上の頂点
			m_vx += (m_radius - diffX + terrain.GetWidth() + diffY - subV) / 2;
			m_vy -= (m_radius - diffX + terrain.GetWidth() + diffY - subV) / 2;
		}
		else if (diffX < 0 && diffY - terrain.GetHeight() > 0 && -diffX + diffY - terrain.GetHeight() >= m_radius && -diffX + diffY - terrain.GetHeight() - subV < m_radius)
		{
			// 左下の頂点
			m_vx -= -(m_radius + diffX - diffY + terrain.GetHeight() + subV) / 2;
			m_vy += -(m_radius + diffX - diffY + terrain.GetHeight() + subV) * m_vy / subV;
		}
		else if (diffX < 0 && diffY < 0 && -diffX - diffY >= m_radius && -diffX - diffY - sumV < m_radius)
		{
			// 左上の頂点
			m_vx -= -(m_radius + diffX + diffY + sumV) / 2;
			m_vy -= -(m_radius + diffX + diffY + sumV) / 2;
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
