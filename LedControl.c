#include "LedControl.h"
void LedOn(LED_CONTROL* base);
void LedControl(LED_CONTROL* base,unsigned short led_lightms_u16,unsigned short led_unlightms_u16,short led_rounte_count_16,unsigned char led_always_do){
	if('n' == base->led_busy_sta){
		base->led_always_do = led_always_do;
		base->led_canuse = 'k';
	    base->led_lightms_u16 = led_lightms_u16;
	    base->led_unlightms_u16 = led_unlightms_u16;
	    base->led_rounte_count_16 = led_rounte_count_16;
		base->templight_32 = led_lightms_u16;
		base->tempunlight_32 = led_unlightms_u16;
		// @DateTime:    2018-07-06 10:19:57
		// @Author wll 为了解决设置完后，状态仍然是忙的问题
		base->led_busy_sta = 'k';
	}
}
void LedOff(LED_CONTROL* base){
	base->led_canuse = 'n';
	base->UNLIGHT_LED();
	base->templight_32 = 0;
	base->tempunlight_32 = 0;
}
static void LedOn(LED_CONTROL* base){
	base->led_canuse = 'n';
	base->LIGHT_LED();
	base->tempunlight_32 = 0;
	base->templight_32 = 0;
}
// void LedDisable(LED_CONTROL* base){
// 	if(base == 0) return;
// 	base->led_canuse = 'n';
// }
// void LedEnable(LED_CONTROL* base){
// 	if(base == 0) return;
// 	base->led_canuse = 'k';
// }
/**********************************************************************************************************
*    函 数 名: LedControl(LED_CONTROL* base,unsigned short led_lightms_u16,unsigned short led_unlightms_u16,short led_rounte_count_16,unsigned char led_always_do);
*    功能说明: 控制led灯亮灭，
*    传    参: base结构体，
               @led_lightms_u16 灯亮时间长度 单位ms
               @led_unlightms_u16 灯灭时间长度 单位ms
               @led_rounte_count_16 灯亮灭周期 
               @led_always_do 'n'不循环 ‘k’:循环亮灭
*    返 回 值: 
*   说    明: 
*********************************************************************************************************/

void LedRun(LED_CONTROL* base,unsigned int interupt_freqms){//放在中断里,interupt_freqms是两次次中断间隔时间
	if('k' == base->led_canuse){
		if((base->led_rounte_count_16>0)||('k' == base->led_always_do)){
			if(base->templight_32>0){
				base->templight_32 = base->templight_32 - interupt_freqms;
				base->LIGHT_LED();
				base->led_busy_sta = 'k';
			}else{
				if(base->tempunlight_32>0){
					base->UNLIGHT_LED();
					base->led_busy_sta = 'k';
					base->tempunlight_32 -= interupt_freqms;
				}
				if((base->tempunlight_32 <= 0)&&(base->templight_32 <= 0)){
					base->tempunlight_32 = base->led_unlightms_u16;
					base->templight_32 = base->led_lightms_u16;
					base->led_rounte_count_16--;
				}
			}
		}else{
			// @DateTime:    2018-07-05 17:28:00
			// @Author wll 计时器时间到达
			base->led_busy_sta = 'n';
			LedOff(base);
		}
	}else{
		base->led_busy_sta = 'n';
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
	if('k' == base->led_busy_sta)
	{
		return 1;
	}	
	else{
		return 0;
	}
}
void LED_CREATE(LED_CONTROL* base,
				void (*LIGHT_LED)(void),
				void (*UNLIGHT_LED)(void)
				){
	base->LIGHT_LED = LIGHT_LED;
	base->UNLIGHT_LED = UNLIGHT_LED;
    base->led_canuse = 'k';
    base->led_lightms_u16 = 0;
    base->led_unlightms_u16 = 0;
    base->led_rounte_count_16 = 0;
	base->tempunlight_32 = 0;
	base->templight_32 = 0;
	base->led_busy_sta = 'n';
	base->led_always_do = 'n';
	
	LedOff(base);
}






