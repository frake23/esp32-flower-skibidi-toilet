#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "dht11.h"
#include "freertos/timers.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"


void app_main()
{
    DHT11_init(GPIO_NUM_21);
    adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);
    esp_adc_cal_characteristics_t adc1_chars;
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_DEFAULT, 0, &adc1_chars);
    adc1_config_width(ADC_WIDTH_BIT_DEFAULT);


    while(1) {
        printf("Temperature is %d \n", DHT11_read().temperature);
        printf("Humidity is %d\n", DHT11_read().humidity);
        int adc_value = adc1_get_raw(ADC1_CHANNEL_0);
        printf("Light %d\n", adc_value);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}