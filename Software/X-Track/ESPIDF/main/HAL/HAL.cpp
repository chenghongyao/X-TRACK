#include "Common/HAL/HAL.h"
#include "Arduino.h"
#include "CommonMacro.h"
#include "HAL_Display.h"
#include "lvgl/lvgl.h"


void HAL::HAL_Init()
{
    lv_init();

    Power_Init();
    //Backlight_Init();

    Display_Init();
    Encoder_Init();    
    SD_Init();

    // Clock_Init();
    Buzz_init();
    Audio_Init();
    GPS_Init();



}

void HAL::HAL_Update()
{
    __IntervalExecute(SD_Update(), 500);
    __IntervalExecute(GPS_Update(), 200);
    Power_EventMonitor();

    // TODO: move to interrupt
    Power_Update();
    Encoder_Update();
    Audio_Update();

    Display_Update();
}
