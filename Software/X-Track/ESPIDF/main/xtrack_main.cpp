#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "App.h"
#include "Common/HAL/HAL.h"
#include "Arduino.h"

extern "C" void app_main(void)
{
    initArduino();
    HAL::HAL_Init();
    App_Init();
    HAL::Power_SetEventCallback(App_Uninit);
    
    while (1) {
        /* Delay 1 tick (assumes FreeRTOS tick is 10ms */
        vTaskDelay(pdMS_TO_TICKS(10));
        HAL::HAL_Update();
    }

}

