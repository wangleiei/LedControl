#ifdef __cplusplus

extern "C" {

#endif
#include "LedControl.h"

/**********************************************************************************************************
*    函 数 名: LedControl(LED_CONTROL* base,uint16_t led_lightms_u16,uint16_t led_unlightms_u16,int8_t led_rounte_count_16,uint8_t led_always_do);
*    功能说明: 控制led灯亮灭，
*    传    参: base结构体，
               @led_lightms_u16 灯亮时间长度 单位ms
               @led_unlightms_u16 灯灭时间长度 单位ms
               @led_rounte_count_16 灯亮灭周期 
               @led_always_do 0不循环 1:循环亮灭
*    返 回 值: 
*   说    明: 
*********************************************************************************************************/

void LedControl(LED_CONTROL* base,
	uint16_t led_lightms_u16,
	uint16_t led_unlightms_u16,
	int8_t led_rounte_count_16,
	uint8_t led_always_do){
	if(0 == base->led_busy_sta){
		base->led_always_do = led_always_do;
		base->led_canuse = 1;
	    base->led_lightms_u16 = led_lightms_u16;
	    base->led_unlightms_u16 = led_unlightms_u16;
	    base->led_rounte_count_16 = led_rounte_count_16;
		base->templight_32 = led_lightms_u16;
		base->tempunlight_32 = led_unlightms_u16;
		base->led_busy_sta = 1;
	}
}
void LedOff(LED_CONTROL* base){
	base->led_canuse = 0;
	base->UNLIGHT_LED();
	base->templight_32 = 0;
	base->tempunlight_32 = 0;
}
void LedOn(LED_CONTROL* base){
	base->led_canuse = 0;
	base->LIGHT_LED();
	base->tempunlight_32 = 0;
	base->templight_32 = 0;
}

void LedRun(LED_CONTROL* base,uint16_t interupt_freqms){
	if(1 == base->led_canuse){
		if((base->led_rounte_count_16>0)||(1 == base->led_always_do)){
			if(base->templight_32>0){
				base->templight_32 = base->templight_32 - interupt_freqms;
				base->LIGHT_LED();
				base->led_busy_sta = 1;
			}else{
				if(base->tempunlight_32>0){
					base->UNLIGHT_LED();
					base->led_busy_sta = 1;
					base->tempunlight_32 -= interupt_freqms;
				}
				if((base->tempunlight_32 <= 0)&&(base->templight_32 <= 0)){
					base->tempunlight_32 = base->led_unlightms_u16;
					base->templight_32 = base->led_lightms_u16;
					base->led_rounte_count_16--;
				}
			}
		}else{
			
			
			base->led_busy_sta = 0;
			LedOff(base);
		}
	}else{
		base->led_busy_sta = 0;
		LedOff(base);
	}
}
/**********************************************************************************************************
*	函 数 名: int LedIsIdle(LED_CONTROL* base)
*	功能说明:查看led灯有没有完成功能
*	传    参: 
*	返 回 值: 0:空闲 ，1：忙
*   说    明: 警告，若led设置成永远亮灭返回忙
*********************************************************************************************************/

int LedIsIdle(LED_CONTROL* base)
{
	if(1 == base->led_busy_sta)
	{
		return 1;
	}	
	else{
		return 0;
	}
}
void LedCreate(LED_CONTROL* base,
				void (*LIGHT_LED)(void),
				void (*UNLIGHT_LED)(void)
				){
	base->LIGHT_LED = LIGHT_LED;
	base->UNLIGHT_LED = UNLIGHT_LED;
    base->led_canuse = 1;
    base->led_lightms_u16 = 0;
    base->led_unlightms_u16 = 0;
    base->led_rounte_count_16 = 0;
	base->tempunlight_32 = 0;
	base->templight_32 = 0;
	base->led_busy_sta = 0;
	base->led_always_do = 0;
}

#ifdef __cplusplus
}
#endif