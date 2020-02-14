#include <M5Stack.h>
#include "GameManager.h"

static GameManager s_manager;

void setup() {
	M5.begin();
}

void loop() {
	M5.update();
	s_manager.Update();
	s_manager.Draw();
	// 60fpsを維持するための処理
	delay(16);
}