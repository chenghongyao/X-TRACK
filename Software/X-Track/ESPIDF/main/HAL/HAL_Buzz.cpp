#include "Common/HAL/HAL.h"
#include "Arduino.h"

#define CONFIG_BUZZ_PIN 33
#define CONFIG_BUZZ_LEDC_CHANNEL 0

// use 13 bit precission for LEDC timer
#define LEDC_TIMER_BIT 13

// use 2000 Hz as a LEDC base frequency
#define LEDC_BASE_FREQ 2000

static bool IsEnable = true;

typedef enum {Off = 0, On = !Off} _Switch_Type;

static uint8_t tone_State = Off;
static uint8_t tone_Pin;
static uint32_t tone_StopTimePoint;

void tone(uint8_t Pin, uint32_t freq, uint32_t Time_ms);
void tone(uint8_t Pin, uint32_t freq);
void noTone(uint8_t Pin);

/**
  * @brief  在Pin上生成指定频率 (50%占空比的方波)
  * @param  pin: 产生音调的 Pin
  * @param  freq: 频率(Hz)
  * @param  Time_ms: 音调的持续时间 (以毫秒为单位)
  * @retval 无
  */
void tone(uint8_t Pin, uint32_t freq, uint32_t Time_ms)
{
    if(freq == 0 || freq > 500000 || Time_ms == 0)
    {
        noTone(Pin);
        return;
    }
    tone(Pin, freq);
    tone_StopTimePoint = millis() + Time_ms;
    tone_State = Off;
}

/**
  * @brief  在Pin上生成指定频率 (50%占空比的方波)
  * @param  pin: 产生音调的引脚编号
  * @param  freq: 频率(Hz)
  * @retval 无
  */
void tone(uint8_t Pin, uint32_t freq)
{
    if(freq == 0 || freq > 500000)
    {
        noTone(Pin);
        return;
    }
    tone_Pin = Pin;
    tone_State = On;

    ledcWriteTone(Pin, 500000 / freq);
}

/**
  * @brief  关闭声音
  * @param  Pin: 产生音调的引脚编号
  * @retval 无
  */
void noTone(uint8_t Pin)
{
    ledcWrite(Pin, 0);
    tone_State = Off;
}



static void Buzz_InterrputUpdate(void *arg) {
    (void) arg;
    if(millis() > tone_StopTimePoint && !tone_State)
    {
        noTone(tone_Pin);
    }
}




void HAL::Buzz_init()
{
    ledcSetup(CONFIG_BUZZ_LEDC_CHANNEL, LEDC_BASE_FREQ, LEDC_TIMER_BIT);
    ledcWrite(CONFIG_BUZZ_LEDC_CHANNEL, 0);

    ledcAttachPin(CONFIG_BUZZ_PIN,CONFIG_BUZZ_LEDC_CHANNEL);

    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &Buzz_InterrputUpdate,
        .name = "buzz_interrputUpdate"
    };
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, 1000));
}

void HAL::Buzz_SetEnable(bool en)
{
    IsEnable = en;
}

void HAL::Buzz_Tone(uint32_t freq, int32_t duration)
{
    if(!IsEnable)
        return;

    if(duration >= 0)
    {
        tone(CONFIG_BUZZ_LEDC_CHANNEL, freq, duration);
    }
    else
    {
        tone(CONFIG_BUZZ_LEDC_CHANNEL, 0);
    }
}























