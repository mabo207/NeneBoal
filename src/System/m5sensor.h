#ifndef DEF_M5SENSOR_H
#define DEF_M5SENSOR_H

#include "utility\MPU9250.h" // ジャイロセンサー
#include <MadgwickAHRS.h>

namespace System
{
	// m5stackに内蔵or接続されているセンサーを管理する
	// 1つのm5stackに一定数しか存在しないので、static変数で管理しプログラム全体で利用できるようにする
	class M5Sensor
	{
	public:
		M5Sensor();
		~M5Sensor();
		void Update();

		MPU9250 m_mpu9250;		  // ジャイロセンサー
		Madgwick m_postureFilter; // mpu9250を用いた姿勢情報を格納

		// 静的変数
		static void Init();
		static M5Sensor s_sensor; // センサー群は1つのm5stackにつき1つだけ
	};
} // namespace System

#endif