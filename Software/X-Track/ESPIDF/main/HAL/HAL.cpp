#include "Common/HAL/HAL.h"
#include "HAL_Display.h"
#include "lvgl/lvgl.h"


void HAL::HAL_Init()
{
    lv_init();

    Display_Init();
    Encoder_Init();
    SD_Init();

    Buzz_init();
    Audio_Init();
    GPS_Init();
}

void HAL::HAL_Update()
{
    IMU_Update();
    MAG_Update();
    Audio_Update();

    Display_Update();

}
