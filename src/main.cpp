#include <M5Stack.h>
#include "GameManager.h"
#include "m5sensor.h"
#include "Object\Base.h"

static GameManager s_manager;
static unsigned long microsPerReading, microsPrevious;
static const unsigned long fps = 60;

void setup() {
	M5.begin();
	Wire.begin();
	M5Sensor::Init();
	// m5stack等を初期化した後に初期化すべきものの初期化
	Object::Base::InitParameter();

	microsPerReading = 1000000 / fps;
	microsPrevious = micros();
}

void loop() {
	// マイコン側の更新
	const unsigned long nowMicros = micros();
	if (nowMicros - microsPrevious >= microsPerReading){
		M5.update();
		M5Sensor::s_sensor.Update();
		// プログラムの更新
		s_manager.Update();
		s_manager.Draw();
		microsPrevious = nowMicros;
	}
}
