#include "m5sensor.h"
#include <M5Stack.h>

M5Sensor M5Sensor::s_sensor = M5Sensor();

M5Sensor::M5Sensor()
{
	// ジャイロセンサーの初期化
	m_mpu9250.initMPU9250();
	m_mpu9250.calibrateMPU9250(m_mpu9250.gyroBias, m_mpu9250.accelBias);
	// 姿勢情報の初期化
	m_postureFilter.begin(60);
}

M5Sensor::~M5Sensor() {}

void M5Sensor::Update()
{
	// ジャイロセンサーから姿勢情報を計算するためのデータを取得
	if (!(m_mpu9250.readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01))
	{
		//return;
	}
	m_mpu9250.readAccelData(m_mpu9250.accelCount); // 加速度の生データーを取得する
	m_mpu9250.getAres();						   // スケール値を取得する
	// x/y/z軸の加速度値を計算する
	m_mpu9250.ax = (float)m_mpu9250.accelCount[0] * m_mpu9250.aRes - m_mpu9250.accelBias[0];
	m_mpu9250.ay = (float)m_mpu9250.accelCount[1] * m_mpu9250.aRes - m_mpu9250.accelBias[1];
	m_mpu9250.az = (float)m_mpu9250.accelCount[2] * m_mpu9250.aRes - m_mpu9250.accelBias[2];
	m_mpu9250.readGyroData(m_mpu9250.gyroCount); // ジャイロの生データーを取得する
	m_mpu9250.getGres();						 // スケール値を取得する
	// x/y/z軸のジャイロ値を計算する
	m_mpu9250.gx = (float)m_mpu9250.gyroCount[0] * m_mpu9250.gRes;
	m_mpu9250.gy = (float)m_mpu9250.gyroCount[1] * m_mpu9250.gRes;
	m_mpu9250.gz = (float)m_mpu9250.gyroCount[2] * m_mpu9250.gRes;
	// 姿勢情報を更新
	m_postureFilter.updateIMU(m_mpu9250.gx, m_mpu9250.gy, m_mpu9250.gz, m_mpu9250.ax, m_mpu9250.ay, m_mpu9250.az);
}

void M5Sensor::Init()
{
	s_sensor = M5Sensor();
}
