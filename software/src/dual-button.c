/* dual-button-bricklet
 * Copyright (C) 2013 Olaf Lüke <olaf@tinkerforge.com>
 *
 * dual-button.c: Implementation of Dual Button Bricklet messages
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

#include "dual-button.h"

#include "bricklib/bricklet/bricklet_communication.h"
#include "brickletlib/bricklet_entry.h"

#include "config.h"

void invocation(const ComType com, const uint8_t *data) {
	switch(((MessageHeader*)data)->fid) {
		case FID_SET_LED_STATE: {
			set_led_state(com, (SetLEDState*)data);
			return;
		}

		case FID_GET_LED_STATE: {
			get_led_state(com, (GetLEDState*)data);
			return;
		}

		case FID_GET_BUTTON_STATE: {
			get_button_state(com, (GetButtonState*)data);
			return;
		}

		case FID_SET_SELECTED_LED_STATE: {
			set_selected_led_state(com, (SetSelectedLEDState*)data);
			return;
		}

		default: {
			BA->com_return_error(data, sizeof(MessageHeader), MESSAGE_ERROR_CODE_NOT_SUPPORTED, com);
			return;
		}
	}
}

void set_selected_led_state(const ComType com, const SetSelectedLEDState *data) {
	if(data->state < LED_STATE_AUTO_TOGGLE_ON || data->state > LED_STATE_OFF ||
	   data->led < LED_L || data->led > LED_R) {
		BA->com_return_error(data, sizeof(SetLEDState), MESSAGE_ERROR_CODE_INVALID_PARAMETER, com);
		return;
	}

	if(data->led == LED_L) {
		BC->led_l = data->state;

		if(BC->led_l == LED_STATE_AUTO_TOGGLE_ON || BC->led_l == LED_STATE_ON) {
			PIN_LED_L.pio->PIO_CODR = PIN_LED_L.mask;
		} else {
			PIN_LED_L.pio->PIO_SODR = PIN_LED_L.mask;
		}
	} else {
		BC->led_r = data->state;

		if(BC->led_r == LED_STATE_AUTO_TOGGLE_ON || BC->led_r == LED_STATE_ON) {
			PIN_LED_R.pio->PIO_CODR = PIN_LED_L.mask;
		} else {
			PIN_LED_R.pio->PIO_SODR = PIN_LED_L.mask;
		}
	}

	BA->com_return_setter(com, data);
}

void set_led_state(const ComType com, const SetLEDState *data) {
	if(data->led_r < LED_STATE_AUTO_TOGGLE_ON || data->led_r > LED_STATE_OFF ||
	   data->led_l < LED_STATE_AUTO_TOGGLE_ON || data->led_l > LED_STATE_OFF) {
		BA->com_return_error(data, sizeof(SetLEDState), MESSAGE_ERROR_CODE_INVALID_PARAMETER, com);
		return;
	}

	BC->led_r = data->led_r;
	BC->led_l = data->led_l;

	if(BC->led_r == LED_STATE_AUTO_TOGGLE_ON || BC->led_r == LED_STATE_ON) {
		PIN_LED_R.pio->PIO_CODR = PIN_LED_R.mask;
	} else {
		PIN_LED_R.pio->PIO_SODR = PIN_LED_R.mask;
	}

	if(BC->led_l == LED_STATE_AUTO_TOGGLE_ON || BC->led_l == LED_STATE_ON) {
		PIN_LED_L.pio->PIO_CODR = PIN_LED_L.mask;
	} else {
		PIN_LED_L.pio->PIO_SODR = PIN_LED_L.mask;
	}

	BA->com_return_setter(com, data);
}

void get_led_state(const ComType com, const GetLEDState *data) {
	GetLEDStateReturn glsr;
	glsr.header        = data->header;
	glsr.header.length = sizeof(GetLEDStateReturn);
	glsr.led_r          = BC->led_r;
	glsr.led_l          = BC->led_l;

	BA->send_blocking_with_timeout(&glsr, sizeof(GetLEDStateReturn), com);
}

void get_button_state(const ComType com, const GetButtonState *data) {
	GetButtonStateReturn gbsr;
	gbsr.header        = data->header;
	gbsr.header.length = sizeof(GetButtonStateReturn);
	gbsr.button_r       = BC->button_r;
	gbsr.button_l       = BC->button_l;

	BA->send_blocking_with_timeout(&gbsr, sizeof(GetButtonStateReturn), com);
}

void constructor(void) {
	_Static_assert(sizeof(BrickContext) <= BRICKLET_CONTEXT_MAX_SIZE, "BrickContext too big");

	PIN_BUTTON_R.type = PIO_INPUT;
	PIN_BUTTON_R.attribute = PIO_PULLUP;
    BA->PIO_Configure(&PIN_BUTTON_R, 1);

	PIN_BUTTON_L.type = PIO_INPUT;
	PIN_BUTTON_L.attribute = PIO_PULLUP;
    BA->PIO_Configure(&PIN_BUTTON_L, 1);

    PIN_LED_R.type = PIO_OUTPUT_1;
    PIN_LED_R.attribute = PIO_DEFAULT;
    BA->PIO_Configure(&PIN_LED_R, 1);

    PIN_LED_L.type = PIO_OUTPUT_1;
    PIN_LED_L.attribute = PIO_DEFAULT;
    BA->PIO_Configure(&PIN_LED_L, 1);

	BC->button_r = BUTTON_STATE_RELEASED;
	BC->button_l = BUTTON_STATE_RELEASED;
	BC->led_r    = LED_STATE_AUTO_TOGGLE_OFF;
	BC->led_l    = LED_STATE_AUTO_TOGGLE_OFF;

	BC->button_r_debounce = 0;
	BC->button_l_debounce = 0;
}

void destructor(void) {
	PIN_BUTTON_R.type = PIO_INPUT;
	PIN_BUTTON_R.attribute = PIO_PULLUP;
    BA->PIO_Configure(&PIN_BUTTON_R, 1);

	PIN_BUTTON_L.type = PIO_INPUT;
	PIN_BUTTON_L.attribute = PIO_PULLUP;
    BA->PIO_Configure(&PIN_BUTTON_L, 1);

    PIN_LED_R.type = PIO_INPUT;
    PIN_LED_R.attribute = PIO_PULLUP;
    BA->PIO_Configure(&PIN_LED_R, 1);

    PIN_LED_L.type = PIO_INPUT;
    PIN_LED_L.attribute = PIO_PULLUP;
    BA->PIO_Configure(&PIN_LED_L, 1);
}

void tick(const uint8_t tick_type) {
	if(tick_type & TICK_TASK_TYPE_CALCULATION) {
		if(BC->button_r_debounce == 0) {
			if(PIN_BUTTON_R.pio->PIO_PDSR & PIN_BUTTON_R.mask) {
				if(BC->button_r != BUTTON_STATE_RELEASED) {
					BC->button_r = BUTTON_STATE_RELEASED;
					BC->button_r_debounce = BUTTON_DEBOUNCE_TIME;
					BC->state_changed = true;
				}
			} else {
				if(BC->button_r != BUTTON_STATE_PRESSED) {
					next_led_toggle_state(BUTTON_R);
					BC->button_r = BUTTON_STATE_PRESSED;
					BC->button_r_debounce = BUTTON_DEBOUNCE_TIME;
					BC->state_changed = true;
				}
			}
		} else {
			BC->button_r_debounce--;
		}

		if(BC->button_l_debounce == 0) {
			if(PIN_BUTTON_L.pio->PIO_PDSR & PIN_BUTTON_L.mask) {
				if(BC->button_l != BUTTON_STATE_RELEASED) {
					BC->button_l = BUTTON_STATE_RELEASED;
					BC->button_l_debounce = BUTTON_DEBOUNCE_TIME;
					BC->state_changed = true;
				}
			} else {
				if(BC->button_l != BUTTON_STATE_PRESSED) {
					next_led_toggle_state(BUTTON_L);
					BC->button_l = BUTTON_STATE_PRESSED;
					BC->button_l_debounce = BUTTON_DEBOUNCE_TIME;
					BC->state_changed = true;
				}
			}
		} else {
			BC->button_l_debounce--;
		}
	}

	if(tick_type & TICK_TASK_TYPE_MESSAGE) {
		if(BC->state_changed) {
			send_state_changed_callback();
			BC->state_changed = false;
		}
	}
}

void send_state_changed_callback(void) {
	StateChanged sc;
	BA->com_make_default_header(&sc, BS->uid, sizeof(StateChanged), FID_STATE_CHANGED);
	sc.button_r = BC->button_r;
	sc.button_l = BC->button_l;
	sc.led_r    = BC->led_r;
	sc.led_l    = BC->led_l;

	BA->send_blocking_with_timeout(&sc,
								   sizeof(StateChanged),
								   *BA->com_current);
}

void next_led_toggle_state(const uint8_t button) {
	switch(button) {
		case BUTTON_R: {
			if(BC->led_r == LED_STATE_AUTO_TOGGLE_OFF) {
				PIN_LED_R.pio->PIO_CODR = PIN_LED_R.mask;
				BC->led_r = LED_STATE_AUTO_TOGGLE_ON;
			} else if(BC->led_r == LED_STATE_AUTO_TOGGLE_ON) {
				PIN_LED_R.pio->PIO_SODR = PIN_LED_R.mask;
				BC->led_r = LED_STATE_AUTO_TOGGLE_OFF;
			}
			break;
		}

		case BUTTON_L: {
			if(BC->led_l == LED_STATE_AUTO_TOGGLE_OFF) {
				PIN_LED_L.pio->PIO_CODR = PIN_LED_L.mask;
				BC->led_l = LED_STATE_AUTO_TOGGLE_ON;
			} else if(BC->led_l == LED_STATE_AUTO_TOGGLE_ON) {
				PIN_LED_L.pio->PIO_SODR = PIN_LED_L.mask;
				BC->led_l = LED_STATE_AUTO_TOGGLE_OFF;
			}
			break;
		}
	}
}
