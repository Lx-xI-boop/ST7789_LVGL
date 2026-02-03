#include "main.h"
#include "i2c.h"
#include "CST816T.h"

// 初始化
void CST816T_Init(void)
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_RESET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_SET);
	HAL_Delay(50);
}	

uint8_t CST816T_Read_Sensor(uint16_t *x, uint16_t *y) 
{
    uint8_t buf[6];
    // 从 0x01 寄存器开始，连续读取 6 个字节
    // 0x01:Gesture, 0x02:FingerNum, 0x03:XH, 0x04:XL, 0x05:YH, 0x06:YL
    if (HAL_I2C_Mem_Read(&hi2c1, CST816T_I2CAddress_8bit_Read, 0x01, 
                         I2C_MEMADD_SIZE_8BIT, buf, 6, 100) == HAL_OK) 
    {
        uint8_t fingerNum = buf[1] & 0x0F;
        if (fingerNum == 0) return 0; // 没人摸，直接返回

        *x = ((uint16_t)(buf[2] & 0x0F) << 8) | buf[3];
        *y = ((uint16_t)(buf[4] & 0x0F) << 8) | buf[5];
        return 1; // 读取成功且有触摸
    }
    return 0;
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

