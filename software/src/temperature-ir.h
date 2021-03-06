/* temperature-ir-bricklet
 * Copyright (C) 2010-2012 Olaf Lüke <olaf@tinkerforge.com>
 *
 * temperature-ir.h: Implementation of Temperature-IR Bricklet messages
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef TEMPERATURE_IR_H
#define TEMPERATURE_IR_H

#include <stdint.h>
#include "bricklib/com/com_common.h"

#define I2C_ADDRESS 0x5A // Factory default
#define I2C_INTERNAL_ADDRESS_BYTES 1
#define I2C_DATA_LENGTH 3

#define I2C_INTERNAL_ADDRESS_PWM         0x22
#define I2C_INTERNAL_ADDRESS_EMISSIVITY  0x24

#define I2C_INTERNAL_ADDRESS_TA          0x6
#define I2C_INTERNAL_ADDRESS_TOBJ1       0x7
#define I2C_INTERNAL_ADDRESS_TOBJ2       0x8

#define IR_TEMP_SET_EMISSIVITY_START     0
#define IR_TEMP_SET_EMISSIVITY_END       1
#define IR_TEMP_SET_EMISSIVITY_NONE      2

#define IR_TEMP_CRC_POLYNOM         (0x1070U << 3)  // = X^8+X^2+X^1+X^0

#define PWM_EXTENDED                (1 << 0)
#define PWM_ENABLED                 (1 << 1)
#define PWM_PUSHPULL                (1 << 2)
#define PWM_THERMAL_RELAY           (1 << 3)
#define PWM_REPETITION(v)           ((v) << 4)
#define PWM_PERIOD(v)               ((v) << 9)

#define FID_GET_AMBIENT_TEMPERATURE 1
#define FID_GET_OBJECT_TEMPERATURE 2
#define FID_SET_EMISSIVITY 3
#define FID_GET_EMISSIVITY 4
#define FID_SET_AMBIENT_TEMPERATURE_CALLBACK_PERIOD 5
#define FID_GET_AMBIENT_TEMPERATURE_CALLBACK_PERIOD 6
#define FID_SET_OBJECT_TEMPERATURE_CALLBACK_PERIOD 7
#define FID_GET_OBJECT_TEMPERATURE_CALLBACK_PERIOD 8
#define FID_SET_AMBIENT_TEMPERATURE_CALLBACK_THRESHOLD 9
#define FID_GET_AMBIENT_TEMPERATURE_CALLBACK_THRESHOLD 10
#define FID_SET_OBJECT_TEMPERATURE_CALLBACK_THRESHOLD 11
#define FID_GET_OBJECT_TEMPERATURE_CALLBACK_THRESHOLD 12
#define FID_SET_DEBOUNCE_PERIOD 13
#define FID_GET_DEBOUNCE_PERIOD 14
#define FID_AMBIENT_TEMPERATURE 15
#define FID_OBJECT_TEMPERATURE 16
#define FID_AMBIENT_TEMPERATURE_REACHED 17
#define FID_OBJECT_TEMPERATURE_REACHED 18

#define FID_LAST 18

typedef struct {
	int16_t data;
	uint8_t crc;
} Temperature;

typedef struct {
	int16_t data;
	uint8_t crc;
} Emissivity;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) StandardMessage;

typedef struct {
	MessageHeader header;
	uint16_t emissivity;
} __attribute__((__packed__)) SetEmissivity;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetEmissivity;

typedef struct {
	MessageHeader header;
	uint16_t emissivity;
} __attribute__((__packed__)) GetEmissivityReturn;

void set_emissivity(const ComType com, const SetEmissivity *data);
void get_emissivity(const ComType com, const GetEmissivity *data);

void invocation(const ComType com, const uint8_t *data);
void constructor(void);
void destructor(void);
void tick(uint8_t tick_type);

void ir_temp_set_emissivity_correction(const uint16_t value, const uint8_t part);
void ir_temp_get_emissivity_correction(void);
uint8_t ir_temp_calculate_pec(const uint8_t *data, const uint8_t length);
int16_t ir_temp_to_celsius(const int16_t temp);
void ir_temp_to_pwm(void);
void ir_temp_to_i2c(void);
void ir_temp_callback_set_emissivity(Async *a);
void ir_temp_callback_get_emissivity(Async *a);
void ir_temp_callback_value(Async *a);
void ir_temp_write(const uint8_t internal_address, const uint16_t value);
bool ir_temp_next_value(void);
#endif
