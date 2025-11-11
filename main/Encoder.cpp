#include "hal/pcnt_types.h"
#include "Encoder.h"
#include "arduino.h"
#include "driver/pulse_cnt.h"

Encoder::Encoder(gpio_num_t first_pin, gpio_num_t second_pin)
    : first_pin(first_pin),
      second_pin(second_pin) {}

void Encoder::begin() {
    pcnt_unit_config_t unitConfig = {
        .low_limit  = -32768,
        .high_limit =  32767,
    };
    esp_err_t err = pcnt_new_unit(&unitConfig, &unit_handle);
    if (err != ESP_OK) {
        Serial.printf("PCNT init failed: %d\n", err);
        return;
    }
    
    Serial.printf("Encoder unit handle: %p\n", unit_handle);

    pcnt_chan_config_t channelConfig = {};
    channelConfig.edge_gpio_num = first_pin;
    channelConfig.level_gpio_num = second_pin;
    pcnt_new_channel(unit_handle, &channelConfig, &chanA);

    pcnt_channel_set_edge_action(
        chanA,
        PCNT_CHANNEL_EDGE_ACTION_DECREASE,
        PCNT_CHANNEL_EDGE_ACTION_INCREASE);

    pcnt_channel_set_level_action(
        chanA,
        PCNT_CHANNEL_LEVEL_ACTION_KEEP,
        PCNT_CHANNEL_LEVEL_ACTION_INVERSE);

    pcnt_unit_enable(unit_handle);
    pcnt_unit_clear_count(unit_handle);
    pcnt_unit_start(unit_handle);
}

int Encoder::getCount() {
    int count = 0;
    pcnt_unit_get_count(unit_handle, &count);
    pcnt_unit_clear_count(unit_handle);
    totalCount += count;
    return count;
}
