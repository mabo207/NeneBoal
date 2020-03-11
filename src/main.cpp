#include "GameManager.h"
#include "Object\Base.h"
#include "m5sensor.h"
#include <M5Stack.h>

static GameManager s_manager;
static unsigned long microsPerReading, microsPrevious;
static const unsigned long fps = 60;

void setup()
{
	M5.begin();
	Wire.begin();
	M5Sensor::Init();
	// m5stack等を初期化した後に初期化すべきものの初期化
	Object::Base::InitParameter();

	microsPerReading = 1000000 / fps;
	microsPrevious = micros();
}

void loop()
{
	// マイコン側の更新
	const unsigned long nowMicros = micros();
	if (nowMicros - microsPrevious >= microsPerReading)
	{
		M5.update();
		M5Sensor::s_sensor.Update();
		// ボタン入力時のジャイロセンサーの初期化
		if (m5.BtnB.isReleased() == 0)
		{
			// ジャイロに不具合を感じたら真ん中のボタンを押せば修正できる
			M5Sensor::Init();
		}

		// プログラムの更新
		s_manager.Update();
		s_manager.Draw();
		microsPrevious = nowMicros;
	}
}
