#include "main.h"
#include "i2c.h"
#include "CST816T.h"

// 初始化
void CST816T_Init(void)
{
	
}	

// 获取手势码
uint8_t CST816T_GetGestureID(void)
{
	uint8_t reData[1] = {0};													// 接收数据
	uint8_t CMD[] = { CST816T_Register_GestureID };	// 命令
	HAL_I2C_Master_Transmit(&hi2c1, CST816T_I2CAddress_8bit_Write, CMD , 1, 1000);
	HAL_I2C_Master_Receive(&hi2c1, CST816T_I2CAddress_8bit_Read, reData , 1, 1000);
	return reData[0];
}

// 获取点击的X坐标
uint16_t CST816T_GetXpos(void)
{
	uint8_t reData[2] = {0};											// 接收数据
	uint8_t CMD[] = { CST816T_Register_XposH };	// 命令
	HAL_I2C_Master_Transmit(&hi2c1, CST816T_I2CAddress_8bit_Write, CMD , 1, 1000);
	HAL_I2C_Master_Receive(&hi2c1, CST816T_I2CAddress_8bit_Read, reData , 2, 1000);
	return ((reData[0] & 0x0F) << 8) | reData[1];
}

// 获取点击的Y坐标
uint16_t CST816T_GetYpos(void)
{
	uint8_t reData[2] = {0};											// 接收数据
	uint8_t CMD[] = { CST816T_Register_YposH };	// 命令
	HAL_I2C_Master_Transmit(&hi2c1, CST816T_I2CAddress_8bit_Write, CMD , 1, 1000);
	HAL_I2C_Master_Receive(&hi2c1, CST816T_I2CAddress_8bit_Read, reData , 2, 1000);
	return ((reData[0] & 0x0F) << 8) | reData[1];
}

// 获取芯片ID
uint8_t CST816T_GetChipID(void)
{
	uint8_t reData[1] = {0};											// 接收数据
	uint8_t CMD[] = { CST816T_Register_ChipID };	// 命令
	HAL_I2C_Master_Transmit(&hi2c1, CST816T_I2CAddress_8bit_Write, CMD , 1, 1000);
	HAL_I2C_Master_Receive(&hi2c1, CST816T_I2CAddress_8bit_Read, reData , 1, 1000);
	return reData[0];
}

// 获取单个寄存器数据
// 多用于测试用，放入寄存器地址获取数据
uint8_t CST816T_GetRegisterData(uint8_t reg)
{
	uint8_t reData[1] = {0};	// 接收数据
	uint8_t CMD[] = { reg };	// 命令
	HAL_I2C_Master_Transmit(&hi2c1, CST816T_I2CAddress_8bit_Write, CMD , 1, 1000);
	HAL_I2C_Master_Receive(&hi2c1, CST816T_I2CAddress_8bit_Read, reData , 1, 1000);
	return reData[0];
}

