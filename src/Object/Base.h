#ifndef DEF_OBJECT_BASE_H
#define DEF_OBJECT_BASE_H

#include <stdint.h>

namespace Object
{
	// 全てのオブジェクトはBaseを継承する
	class Base
	{
	public:
		// 現在位置に描画
		void Draw() const;
		void Draw(uint32_t color) const; // 色を指定できる
		// 移動前のオブジェクトを消す
		void BeforeErase() const;
		// 決められた速度を元にオブジェクトを動かす
		void Move();
		// getter
		int16_t GetX() const;
		int16_t GetY() const;
		int16_t GetVX() const;
		int16_t GetVY() const;
		uint32_t GetColor() const;

		// 静的変数
		static void InitParameter();
		static int16_t GetCoordinateWidth();	// 外部からの変更を防ぐためのgetter
		static int16_t GetCoordinateHeight();   // 外部からの変更を防ぐためのgetter
		static const uint8_t s_lcdExpantionBit; // s_lcdExpantionが何bitのシフトに当たるのか

	protected:
		// コンストラクタ
		Base(int16_t x, int16_t y, int16_t vx, int16_t vy, uint32_t color);
		// デストラクタ
		virtual ~Base() = default;
		// 描画方法を定義する(拡大処理済み)
		virtual void DrawWithShrinkedParameter(int16_t drawX, int16_t drawY, uint32_t color) const = 0;

		int16_t m_vx, m_vy; // 速度(上位クラスで更新する可能性がある)

	private:
		int16_t m_x, m_y; // 位置(必ずMove()で更新する)
		const uint32_t m_color;

		// 静的変数
		static int16_t s_coordinateWidth;  // 拡大率を考慮した座標系の横幅
		static int16_t s_coordinateHeight; // 拡大率を考慮した座標系の縦幅
	};
} // namespace Object

#endif