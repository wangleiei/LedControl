#ifdef __cplusplus

extern "C" {

#endif
#ifndef __LECONTROL
#define __LECONTROL
#include <stdint.h>

typedef struct LED_CONTROL{
    uint8_t led_canuse;
    uint16_t led_lightms_u16;
    uint16_t led_unlightms_u16;
    int8_t led_rounte_count_16;
    uint8_t led_always_do;
    uint8_t led_busy_sta;
    void (*LIGHT_LED)(void);
    void (*UNLIGHT_LED)(void);
    int templight_32;
    int tempunlight_32;
}LED_CONTROL;
void LedCreate(LED_CONTROL* base,
				void (*LIGHT_LED)(void),
				void (*UNLIGHT_LED)(void)
				);
// led_lightms_u16 灯亮时间长度 单位ms
// led_unlightms_u16 灯灭时间长度 单位ms
// led_rounte_count_16 灯亮灭周期 
// led_always_do 0不循环 1:循环亮灭
void LedControl(LED_CONTROL* base,
    uint16_t led_lightms_u16,
    uint16_t led_unlightms_u16,
    int8_t led_rounte_count_16,
    uint8_t led_always_do);

void LedOff(LED_CONTROL* base);
void LedOn(LED_CONTROL* base);
void LedRun(LED_CONTROL* base,uint16_t interupt_freqms);
int LedIsIdle(LED_CONTROL* base);
#endif

#ifdef __cplusplus
}
#endif