#include "Common/HAL/HAL.h"
// #include <windows.h>


void Power_Init() {
    
}
void HAL::Power_GetInfo(Power_Info_t* info)
{
    // SYSTEM_POWER_STATUS sysPower = { 0 };
    // GetSystemPowerStatus(&sysPower);

    // int usage = sysPower.BatteryLifePercent;

    // if (usage > 100)
    // {
    //     usage = 100;
    // }

    info->isCharging = false;
    info->voltage = 3700;
    info->usage = 100;
}

void HAL::Power_SetEventCallback(Power_CallbackFunction_t callback)
{

}
void HAL::Power_Shutdown() {

}