#include <Arduino.h>
#include "driver/dac.h"

dac_cw_config_t config {DAC_CHANNEL_1,DAC_CW_SCALE_1,DAC_CW_PHASE_0,256,0};

void setup() {
  // put your setup code here, to run once:
  dac_cw_generator_config(&config); 
  dac_cw_generator_enable(); 

}

void loop() {
  // put your main code here, to run repeatedly:
}