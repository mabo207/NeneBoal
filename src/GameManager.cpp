#include <M5Stack.h>
#include "GameManager.h"

const int32_t GameManager::s_backColor = TFT_BLACK;

GameManager::GameManager()
	:m_boal(m5.Lcd.width()/2,m5.Lcd.height()/2,1,1)
{}

void GameManager::Update(){
	// ボールの移動
	m_boal.VelocityUpdate(); // 速度の更新
	m_boal.Move(); // 移動処理
}

void GameManager::Draw()const{
	// オブジェクトを全消去
	m_boal.BeforeErase();
	// 描画処理
	m_boal.Object::Base::Draw();
}
