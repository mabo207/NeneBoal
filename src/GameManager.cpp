#include <M5Stack.h>
#include "GameManager.h"

const int32_t GameManager::s_backColor = TFT_BLACK;

GameManager::GameManager()
	:m_boalX(M5.Lcd.width()/2),m_boalY(M5.Lcd.height()/2)
{}

void GameManager::Update(){
	// ボールの移動
	m_boalX += 1;
}

void GameManager::Draw()const{
	// オブジェクトを全消去
	m5.Lcd.fillCircle(m_boalX - 1, m_boalY - 0, 2, s_backColor);
	// 描画処理
	m5.Lcd.fillCircle(m_boalX, m_boalY, 2, TFT_YELLOW);
}
