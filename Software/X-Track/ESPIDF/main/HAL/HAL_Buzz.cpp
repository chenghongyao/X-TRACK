#include "Common/HAL/HAL.h"
#include "Arduino.h"

#define CONFIG_BUZZ_PIN 33
#define CONFIG_BUZZ_LEDC_CHANNEL 0


// use 13 bit precission for LEDC timer
#define LEDC_TIMER_BIT 13

// use 5000 Hz as a LEDC base frequency
#define LEDC_BASE_FREQ 5000


static bool IsEnable = true;

void HAL::Buzz_init()
{
    // pinMode(CONFIG_BUZZ_PIN, OUTPUT);
    ledcSetup(CONFIG_BUZZ_LEDC_CHANNEL, LEDC_BASE_FREQ, LEDC_TIMER_BIT);
    ledcWrite(CONFIG_BUZZ_LEDC_CHANNEL, 0);

    ledcAttachPin(CONFIG_BUZZ_PIN,CONFIG_BUZZ_LEDC_CHANNEL);

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
        // TODO: tone pwm
        duration = 8191*duration/100;
        ledcWriteTone(CONFIG_BUZZ_LEDC_CHANNEL, freq);
        ledcWrite(CONFIG_BUZZ_LEDC_CHANNEL, duration);
    }
    else
    {
        ledcWrite(CONFIG_BUZZ_LEDC_CHANNEL, 0);
    }
}
