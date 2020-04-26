#ifndef DEF_OBJECT_BOAL_H
#define DEF_OBJECT_BOAL_H

#include "Base.h"
#include "Terrain.h"
#include <vector>

namespace Object
{
	// ボールを表現する
	class Boal : public Base
	{
	public:
		Boal(int16_t x, int16_t y, int16_t vx, int16_t vy);
		~Boal() = default;
		// 速度の更新
		void VelocityUpdate(const std::vector<Terrain> &terrainList);

	protected:
	private:
		void DrawWithShrinkedParameter(int16_t drawX, int16_t drawY, uint32_t color) const;

		const uint16_t m_radius; // ボールの半径
	};
} // namespace Object

#endif