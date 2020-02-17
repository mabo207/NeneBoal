#ifndef DEF_OBJECT_BASE_H
#define DEF_OBJECT_BASE_H

#include<stdint.h>

namespace Object{
	// 全てのオブジェクトはBaseを継承する
	class Base{
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

	protected:
		// コンストラクタ
		Base(int16_t x, int16_t y, int16_t vx, int16_t vy, uint32_t color);
		// デストラクタ
		virtual ~Base() = default;
		// 描画方法を定義する
		virtual void Draw(int16_t x, int16_t y, uint32_t color) const = 0;

		int16_t m_vx, m_vy; // 速度(上位クラスで更新する可能性がある)

	private:
		int16_t m_x, m_y; // 位置(必ずMove()で更新する)
		const uint32_t m_color;
	};
}

#endif