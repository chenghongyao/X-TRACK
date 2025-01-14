#include "Common/HAL/HAL.h"
#include "ButtonEvent/ButtonEvent.h"
#include "lvgl/lvgl.h"
#include "Arduino.h"

#define CONFIG_ENCODER_PUSH_PIN 37
#define CONFIG_ENCODER_A_PIN    38
#define CONFIG_ENCODER_B_PIN    39

static ButtonEvent EncoderPush(5000);

static bool EncoderEnable = true;
static volatile int32_t EncoderDiff = 0;
static bool EncoderDiffDisable = false;


static void encoder_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    static bool lastState;
    data->enc_diff = HAL::Encoder_GetDiff();

    bool isPush = HAL::Encoder_GetIsPush();
    
    data->state = isPush ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;

    if(isPush != lastState)
    {
        HAL::Buzz_Tone(isPush ? 500 : 700, 20);
        lastState = isPush;
    }
}

static void lv_port_encoder() {
    /*Register a encoder input device*/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_ENCODER;
    indev_drv.read_cb = encoder_read;
    lv_indev_drv_register(&indev_drv);
}


static void Buzz_Handler(int dir)
{
    static const uint16_t freqStart = 2000;
    static uint16_t freq = freqStart;
    static uint32_t lastRotateTime;

    if(millis() - lastRotateTime > 1000)
    {
        freq = freqStart;
    }
    else
    {
        if(dir > 0)
        {
            freq += 100;
        }

        if(dir < 0)
        {
            freq -= 100;
        }

        freq = constrain(freq, 100, 20 * 1000);
    }

    lastRotateTime = millis();
    HAL::Buzz_Tone(freq, 5);
}


static void Encoder_EventHandler()
{
    if(!EncoderEnable || EncoderDiffDisable)
    {
        return;
    }

    int dir;
    if (digitalRead(CONFIG_ENCODER_A_PIN) == LOW)
    {
        dir = (digitalRead(CONFIG_ENCODER_B_PIN) == LOW ? -1 : +1);
    }
    else 
    {
        dir = (digitalRead(CONFIG_ENCODER_B_PIN) == LOW ? 1 : -1);
    }

    EncoderDiff += dir;
    Buzz_Handler(dir);
}


static void Encoder_PushHandler(ButtonEvent* btn, int event)
{
    if(event == ButtonEvent::EVENT_PRESSED)
    {
        EncoderDiffDisable = true;
    }
    else if(event == ButtonEvent::EVENT_RELEASED)
    {
        EncoderDiffDisable = false;
    }
    else if(event == ButtonEvent::EVENT_LONG_PRESSED)
    {
        HAL::Audio_PlayMusic("Shutdown");
        HAL::Power_Shutdown();
    }
}

void HAL::Encoder_Init()
{
    pinMode(CONFIG_ENCODER_A_PIN, INPUT_PULLUP);
    pinMode(CONFIG_ENCODER_B_PIN, INPUT_PULLUP);
    pinMode(CONFIG_ENCODER_PUSH_PIN, INPUT_PULLUP);

    attachInterrupt(CONFIG_ENCODER_A_PIN, Encoder_EventHandler, CHANGE);

    EncoderPush.EventAttach(Encoder_PushHandler);

    lv_port_encoder();
}

void HAL::Encoder_Update()
{
    EncoderPush.EventMonitor(Encoder_GetIsPush());
}

int32_t HAL::Encoder_GetDiff()
{
    int32_t diff = EncoderDiff;
    EncoderDiff = 0;
    return diff;
}

bool HAL::Encoder_GetIsPush()
{
    if(!EncoderEnable)
    {
        return false;
    }
    
    return (digitalRead(CONFIG_ENCODER_PUSH_PIN) == LOW);
}

void HAL::Encoder_SetEnable(bool en)
{
    EncoderEnable = en;
}
