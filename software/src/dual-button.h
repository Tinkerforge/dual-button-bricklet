/* dual-button-bricklet
 * Copyright (C) 2013 Olaf Lüke <olaf@tinkerforge.com>
 *
 * dual-button.h: Implementation of Dual Button Bricklet messages
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

#ifndef DUAL_BUTTON_H
#define DUAL_BUTTON_H

#include <stdint.h>
#include "bricklib/com/com_common.h"

#define BUTTON_L 0
#define BUTTON_R 1

#define BUTTON_STATE_PRESSED 0
#define BUTTON_STATE_RELEASED 1

#define BUTTON_DEBOUNCE_TIME 25 // in ms

#define LED_STATE_AUTO_TOGGLE_ON 0
#define LED_STATE_AUTO_TOGGLE_OFF 1
#define LED_STATE_ON 2
#define LED_STATE_OFF 3

#define FID_SET_LED_STATE 1
#define FID_GET_LED_STATE 2
#define FID_GET_BUTTON_STATE 3
#define FID_STATE_CHANGED 4

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) StandardMessage;

typedef struct {
	MessageHeader header;
	uint8_t led_l;
	uint8_t led_r;
} __attribute__((__packed__)) SetLEDState;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetLEDState;

typedef struct {
	MessageHeader header;
	uint8_t led_l;
	uint8_t led_r;
} __attribute__((__packed__)) GetLEDStateReturn;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetButtonState;

typedef struct {
	MessageHeader header;
	uint8_t button_l;
	uint8_t button_r;
} __attribute__((__packed__)) GetButtonStateReturn;

typedef struct {
	MessageHeader header;
	uint8_t button_l;
	uint8_t button_r;
	uint8_t led_l;
	uint8_t led_r;
} __attribute__((__packed__)) StateChanged;

void set_led_state(const ComType com, const SetLEDState *data);
void get_led_state(const ComType com, const GetLEDState *data);
void get_button_state(const ComType com, const GetButtonState *data);

void next_led_toggle_state(const uint8_t button);
void send_state_changed_callback(void);

void invocation(const ComType com, const uint8_t *data);
void constructor(void);
void destructor(void);
void tick(const uint8_t tick_type);

#endif
