#ifndef DEF_OBJECT_TERRAIN_H
#define DEF_OBJECT_TERRAIN_H

#include "Base.h"

namespace Object
{
	// Terrainは障害物。全て長方形とする。
	class Terrain : public Base
	{
	public:
		Terrain(int16_t x, int16_t y, uint32_t color, int16_t width, int16_t height); //速度は0なのでvx,vyを引数に持たない
		virtual ~Terrain();
		int16_t GetWidth()const;
		int16_t GetHeight()const;

	protected:
		void DrawWithShrinkedParameter(int16_t drawX, int16_t drawY, uint32_t color) const;

	private:
		int16_t m_width;
		int16_t m_height;
	};
} // namespace Object

#endif