#pragma once

#include <stdint.h>
#include <Arduino.h> 
#include "driver/pulse_cnt.h"

class Encoder {
  private:
    gpio_num_t first_pin;
    gpio_num_t second_pin;
    
    pcnt_unit_handle_t unit_handle;
    pcnt_channel_handle_t chanA;

    int totalCount = 0;
    
  public:
    Encoder(gpio_num_t first_pin, gpio_num_t second_pin);
    void begin();
    int getCount();
};
