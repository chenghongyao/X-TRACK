#include "Common/HAL/HAL.h"
#include "lvgl/lvgl.h"


static lv_indev_t * encoder_indev;
static void encoder_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    data->enc_diff = 0;
    data->state = LV_INDEV_STATE_REL;
}


void HAL::Encoder_Init()
{
    /*Register a encoder input device*/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_ENCODER;
    indev_drv.read_cb = encoder_read;
    encoder_indev = lv_indev_drv_register(&indev_drv);
}

void HAL::Encoder_Update()
{
}

int32_t HAL::Encoder_GetDiff()
{
    return 0;
}

bool HAL::Encoder_GetIsPush()
{
    return false;
}

void HAL::Encoder_SetEnable(bool en)
{
}