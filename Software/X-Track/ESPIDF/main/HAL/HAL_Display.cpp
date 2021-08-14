#include "Common/HAL/HAL.h"
#include "HAL_Display.h"

#include "esp_system.h"
#include "esp_heap_caps.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "lvgl/lvgl.h"
#include "lvgl_helpers.h"




static void lv_port_lcd() {
  /* Initialize SPI or I2C bus used by the drivers */
    lvgl_driver_init();

    DMA_ATTR static lv_color_t buf1[DISP_BUF_SIZE]; 

    /* Use double buffered when not working with monochrome displays */
#ifndef CONFIG_LV_TFT_DISPLAY_MONOCHROME
    // DMA_ATTR static lv_color_t buf2[DISP_BUF_SIZE];
    lv_color_t* buf2 = NULL;
#else
    static lv_color_t *buf2 = NULL;
#endif

    static lv_disp_draw_buf_t disp_buf;

    uint32_t size_in_px = DISP_BUF_SIZE;

#if defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_IL3820         \
    || defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_JD79653A    \
    || defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_UC8151D     \
    || defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_SSD1306

    /* Actual size in pixels, not bytes. */
    size_in_px *= 8;
#endif

    /* Initialize the working buffer depending on the selected display.
     * NOTE: buf2 == NULL when using monochrome displays. */
    lv_disp_draw_buf_init(&disp_buf, buf1, buf2, size_in_px);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.flush_cb =  disp_driver_flush;
    // disp_drv.full_refresh = 1;

    /* When using a monochrome display we need to register the callbacks:
     * - rounder_cb
     * - set_px_cb */
#ifdef CONFIG_LV_TFT_DISPLAY_MONOCHROME
    disp_drv.rounder_cb = disp_driver_rounder;
    disp_drv.set_px_cb = disp_driver_set_px;
#endif

    disp_drv.draw_buf = &disp_buf;
    disp_drv.hor_res = LV_HOR_RES_MAX; /*Set the horizontal resolution of the display*/
    disp_drv.ver_res = LV_VER_RES_MAX; /*Set the verizontal resolution of the display*/

    lv_disp_drv_register(&disp_drv);
}

// #define LV_TICK_PERIOD_MS 1
// static void lv_tick_task(void *arg) {
//     (void) arg;
//     lv_tick_inc(LV_TICK_PERIOD_MS);
// }

void HAL::Display_Init() {

    lv_port_lcd();

//    /* Create and start a periodic timer interrupt to call lv_tick_inc */
//     const esp_timer_create_args_t periodic_timer_args = {
//         .callback = &lv_tick_task,
//         .name = "periodic_gui"
//     };
//     esp_timer_handle_t periodic_timer;
//     ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
//     ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, LV_TICK_PERIOD_MS * 1000));
    
}


void HAL::Display_Update() {
    /* Try to take the semaphore, call lvgl related function on success */
    lv_task_handler();
}