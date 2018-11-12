#ifndef __LECONTROL
#define __LECONTROL
#include <stdint.h>

typedef struct LED_CONTROL{
    unsigned char led_canuse;
    unsigned short led_lightms_u16;
    unsigned short led_unlightms_u16;
    short led_rounte_count_16;
    unsigned char led_always_do;
    unsigned char led_busy_sta;
    void (*LIGHT_LED)(void);
    void (*UNLIGHT_LED)(void);
    int templight_32;
    int tempunlight_32;
}LED_CONTROL;
void LED_CREATE(LED_CONTROL* base,
				void (*LIGHT_LED)(void),
				void (*UNLIGHT_LED)(void)
				);
void LedControl(LED_CONTROL* base,unsigned short led_lightms_u16,unsigned short led_unlightms_u16,short led_rounte_count_16,unsigned char led_always_do);
void LedOff(LED_CONTROL* base);
void LedRun(LED_CONTROL* base,unsigned int interupt_freqms);//放在中断里,interupt_freqms是两次次中断间隔时间
int LedIsIdle(LED_CONTROL* base);
#endif



