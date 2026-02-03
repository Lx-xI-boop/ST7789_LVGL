#ifndef __CST816T_H__
#define __CST816T_H__
// #include "stdint.h"


// I2C相关参数
#define CST816T_I2CAddress_7bit 0x15
#define CST816T_I2CAddress_8bit_Read 	(CST816T_I2CAddress_7bit << 1) | 0x01
#define CST816T_I2CAddress_8bit_Write (CST816T_I2CAddress_7bit << 1)

// CST816T的寄存器
// 参考于《CST816T通用版本SDK寄存器说明-v1》
#define CST816T_Register_GestureID			0x01	// 手势码
#define CST816T_Register_FingerNum			0x02	// 手指个数
#define CST816T_Register_XposH					0x03	// X坐标高4位
#define CST816T_Register_XposL					0x04	// X坐标低8位
#define CST816T_Register_YposH					0x05	// Y坐标高4位
#define CST816T_Register_YposL					0x06	// Y坐标低8位
#define CST816T_Register_ChipID					0xA7	// 工程编号
#define CST816T_Register_FwVersion			0xA9	// 软件版本号
#define CST816T_Register_FactoryID 			0xAA	// TP厂家ID
#define CST816T_Register_BPC0H					0xB0	// BPC0值的高8位
#define CST816T_Register_BPC0L					0xB1	// BPC0值的低8位
#define CST816T_Register_BPC1H					0xB2	// BPC1值的高8位
#define CST816T_Register_BPC1L 					0xB3	// BPC1值的低8位
#define CST816T_Register_SleepMode 			0xE5	// 值为0x03时进入休眠状态（无触摸唤醒功能）
#define CST816T_Register_ErrResetCtl 		0xEA	// 复位触摸面积相关
#define CST816T_Register_LongPressTick 	0xEB	// 长按时间门限，默认为100。大约1S
#define CST816T_Register_MotionMask 		0xEC	// 连续运动手势使能
#define CST816T_Register_IrqPluseWidth 	0xED	// 中断低脉冲输出宽度
#define CST816T_Register_NorScanPer 		0xEE	// 正常快速检测周期
#define CST816T_Register_MotionSlAngle 	0xEF	// 手势检测滑动分区角度控制
#define CST816T_Register_LpScanRaw1H 		0xF0	// 低功耗扫描1号通道的基准值的高8位
#define CST816T_Register_LpScanRaw1L 		0xF1	// 低功耗扫描1号通道的基准值的低8位
#define CST816T_Register_LpScanRaw2H 		0xF2	// 低功耗扫描2号通道的基准值的高8位
#define CST816T_Register_LpScanRaw2L 		0xF3	// 低功耗扫描2号通道的基准值的低8位
#define CST816T_Register_LpAutoWakeTime 0xF4	// 低功耗时自动重校正周期
#define CST816T_Register_LpScanTH 			0xF5	// 低功耗扫描唤醒门限。越小越灵敏
#define CST816T_Register_LpScanWin 			0xF6	// 低功耗扫描量程。越大越灵敏，功耗越高
#define CST816T_Register_LpScanFreq 		0xF7	// 低功耗扫描频率。越小越灵敏
#define CST816T_Register_LpScanIdac 		0xF8	// 低功耗扫描电流。越小越灵敏
#define CST816T_Register_AutoSleepTime 	0xF9	// x秒内无触摸时，自动进入低功耗模式
#define CST816T_Register_IrqCtl 				0xFA	// 发出低脉冲的动作
#define CST816T_Register_AutoReset 			0xFB	// x秒内有触摸但无有效手势时，自动复位
#define CST816T_Register_LongPressTime 	0xFC	// 长按x秒后自动复位
#define CST816T_Register_IOCtl 					0xFD	// 主控通过拉低IRQ引脚实现触控的软复位功能
#define CST816T_Register_DisAutoSleep 	0xFE	// 默认为0，使能自动进入低功耗模式


// 功能函数
void CST816T_Init(void);								// 初始化
uint8_t CST816T_GetGestureID(void);		// 获取手势码
uint16_t CST816T_GetXpos(void);				// 获取点击的X坐标
uint16_t CST816T_GetYpos(void);				// 获取点击的Y坐标
uint8_t CST816T_GetChipID(void);				// 获取芯片ID
uint8_t CST816T_GetRegisterData(uint8_t reg);	// 获取单个寄存器数据
uint8_t CST816T_Read_Sensor(uint16_t *x, uint16_t *y);

#endif

