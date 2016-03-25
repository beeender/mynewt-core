/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <inttypes.h>
#include "hal/hal_flash_int.h"
#include "mcu/native_bsp.h"
#include "hal/hal_adc_int.h"
#include "bsp/bsp_sysid.h"
#include "mcu/mcu_hal.h"
#include "mcu/mcu_devid.h"

const struct hal_flash *
bsp_flash_dev(uint8_t id)
{
    /*
     * Just one to start with
     */
    if (id != 0) {
        return NULL;
    }
    return &native_flash_dev;
}


/* This is the factory that creates adc devices for the application.
 * Based on the system ID defined, this maps to a creation function for
 * the specific underlying driver */
extern struct hal_adc_device_s *
bsp_get_hal_adc_device(enum SystemDeviceDescriptor sysid) {    
    switch(sysid) {
        case NATIVE_A0:
            return native_adc_random_create(MCU_ADC_CHANNEL_0);
        case NATIVE_A1:
            return native_adc_random_create(MCU_ADC_CHANNEL_1);
        case NATIVE_A2:
            return native_adc_mmm_create(MCU_ADC_CHANNEL_2);
        case NATIVE_A3:
            return native_adc_mmm_create(MCU_ADC_CHANNEL_3);
        case NATIVE_A4:
            return native_adc_mmm_create(MCU_ADC_CHANNEL_4);
        case NATIVE_A5:        
            return native_adc_file_create(MCU_ADC_CHANNEL_5, "foo.txt");
    }
    return NULL;
}
