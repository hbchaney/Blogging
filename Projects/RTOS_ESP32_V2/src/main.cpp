#include "esp_log.h"
#include "driver/gpio.h"


extern "C" 
{
    void app_main() {
        static const char* TAG = "MAIN"; 
        ESP_LOGD(TAG,"Hello World!");

        gpio_pad_select_gpio(GPIO_NUM_15);
        ESP_ERROR_CHECK(gpio_set_direction(GPIO_NUM_15,GPIO_MODE_OUTPUT));  
        ESP_ERROR_CHECK(gpio_set_level(GPIO_NUM_15,1)); 
        
    }
}

