/* dual-button-bricklet
 * Copyright (C) 2013 Olaf Lüke <olaf@tinkerforge.com>
 *
 * config.h: Dual Button Bricklet specific configuration
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

#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>
#include <stdbool.h>

#include "bricklib/drivers/board/sam3s/SAM3S.h"

#include "dual-button.h"

#define BRICKLET_FIRMWARE_VERSION_MAJOR 2
#define BRICKLET_FIRMWARE_VERSION_MINOR 0
#define BRICKLET_FIRMWARE_VERSION_REVISION 0

#define BRICKLET_HARDWARE_VERSION_MAJOR 1
#define BRICKLET_HARDWARE_VERSION_MINOR 0
#define BRICKLET_HARDWARE_VERSION_REVISION 1

#define BRICKLET_DEVICE_IDENTIFIER 230

#define PIN_BUTTON_L (BS->pin1_ad)
#define PIN_LED_L    (BS->pin2_da)
#define PIN_BUTTON_R (BS->pin3_pwm)
#define PIN_LED_R    (BS->pin4_io)

#define LOGGING_LEVEL LOGGING_DEBUG
#define DEBUG_BRICKLET 0

#define BRICKLET_NO_OFFSET
#define INVOCATION_IN_BRICKLET_CODE

typedef struct {
	uint8_t button_r;
	uint8_t button_l;
	uint8_t led_r;
	uint8_t led_l;

	uint16_t button_r_debounce;
	uint16_t button_l_debounce;

	bool state_changed;

	uint32_t tick;
} BrickContext;

#endif
