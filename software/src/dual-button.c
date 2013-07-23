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

		default: {
			BA->com_return_error(data, sizeof(MessageHeader), MESSAGE_ERROR_CODE_NOT_SUPPORTED, com);
			return;
		}
	}
}

void set_led_state(const ComType com, const SetLEDState *data) {
	if(data->led1 < LED_STATE_AUTO_TOGGLE_ON || data->led1 > LED_STATE_OFF ||
	   data->led2 < LED_STATE_AUTO_TOGGLE_ON || data->led2 > LED_STATE_OFF) {
		BA->com_return_error(data, sizeof(SetLEDState), MESSAGE_ERROR_CODE_INVALID_PARAMETER, com);
		return;
	}

	BC->led1 = data->led1;
	BC->led2 = data->led2;

	if(BC->led1 == LED_STATE_AUTO_TOGGLE_ON || BC->led1 == LED_STATE_ON) {
		PIN_LED1.pio->PIO_CODR = PIN_LED1.mask;
	} else {
		PIN_LED1.pio->PIO_SODR = PIN_LED1.mask;
	}

	if(BC->led2 == LED_STATE_AUTO_TOGGLE_ON || BC->led2 == LED_STATE_ON) {
		PIN_LED2.pio->PIO_CODR = PIN_LED2.mask;
	} else {
		PIN_LED2.pio->PIO_SODR = PIN_LED2.mask;
	}

	BA->com_return_setter(com, data);
}

void get_led_state(const ComType com, const GetLEDState *data) {
	GetLEDStateReturn glsr;
	glsr.header        = data->header;
	glsr.header.length = sizeof(GetLEDStateReturn);
	glsr.led1          = BC->led1;
	glsr.led2          = BC->led2;

	BA->send_blocking_with_timeout(&glsr, sizeof(GetLEDStateReturn), com);

}

void get_button_state(const ComType com, const GetButtonState *data) {
	GetButtonStateReturn gbsr;
	gbsr.header        = data->header;
	gbsr.header.length = sizeof(GetButtonStateReturn);
	gbsr.button1       = BC->button1;
	gbsr.button2       = BC->button2;

	BA->send_blocking_with_timeout(&gbsr, sizeof(GetButtonStateReturn), com);
}

void constructor(void) {
	PIN_BUTTON1.type = PIO_INPUT;
	PIN_BUTTON1.attribute = PIO_PULLUP;
    BA->PIO_Configure(&PIN_BUTTON1, 1);

	PIN_BUTTON2.type = PIO_INPUT;
	PIN_BUTTON2.attribute = PIO_PULLUP;
    BA->PIO_Configure(&PIN_BUTTON2, 1);

    PIN_LED1.type = PIO_OUTPUT_1;
    PIN_LED1.attribute = PIO_DEFAULT;
    BA->PIO_Configure(&PIN_LED1, 1);

    PIN_LED2.type = PIO_OUTPUT_1;
    PIN_LED2.attribute = PIO_DEFAULT;
    BA->PIO_Configure(&PIN_LED2, 1);

	BC->button1 = BUTTON_STATE_RELEASED;
	BC->button2 = BUTTON_STATE_RELEASED;
	BC->led1    = LED_STATE_AUTO_TOGGLE_OFF;
	BC->led2    = LED_STATE_AUTO_TOGGLE_OFF;

	BC->button1_debounce = 0;
	BC->button2_debounce = 0;
}

void destructor(void) {
	PIN_BUTTON1.type = PIO_INPUT;
	PIN_BUTTON1.attribute = PIO_PULLUP;
    BA->PIO_Configure(&PIN_BUTTON1, 1);

	PIN_BUTTON2.type = PIO_INPUT;
	PIN_BUTTON2.attribute = PIO_PULLUP;
    BA->PIO_Configure(&PIN_BUTTON2, 1);

    PIN_LED1.type = PIO_INPUT;
    PIN_LED1.attribute = PIO_PULLUP;
    BA->PIO_Configure(&PIN_LED1, 1);

    PIN_LED2.type = PIO_INPUT;
    PIN_LED2.attribute = PIO_PULLUP;
    BA->PIO_Configure(&PIN_LED2, 1);
}

void tick(const uint8_t tick_type) {
	if(tick_type & TICK_TASK_TYPE_CALCULATION) {
		if(BC->button1_debounce == 0) {
			if(PIN_BUTTON1.pio->PIO_PDSR & PIN_BUTTON1.mask) {
				if(BC->button1 != BUTTON_STATE_RELEASED) {
					BC->button1 = BUTTON_STATE_RELEASED;
					BC->button1_debounce = BUTTON_DEBOUNCE_TIME;
					BC->state_changed = true;
				}
			} else {
				if(BC->button1 != BUTTON_STATE_PRESSED) {
					BC->button1 = BUTTON_STATE_PRESSED;
					BC->button1_debounce = BUTTON_DEBOUNCE_TIME;
					BC->state_changed = true;
				}
			}
		} else {
			BC->button1_debounce--;
		}

		if(BC->button2_debounce == 0) {
			if(PIN_BUTTON2.pio->PIO_PDSR & PIN_BUTTON2.mask) {
				if(BC->button2 != BUTTON_STATE_RELEASED) {
					BC->button2 = BUTTON_STATE_RELEASED;
					BC->button2_debounce = BUTTON_DEBOUNCE_TIME;
					BC->state_changed = true;
				}
			} else {
				if(BC->button2 != BUTTON_STATE_PRESSED) {
					BC->button2 = BUTTON_STATE_PRESSED;
					BC->button2_debounce = BUTTON_DEBOUNCE_TIME;
					BC->state_changed = true;
				}
			}
		} else {
			BC->button2_debounce--;
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
	sc.button1 = BC->button1;
	sc.button2 = BC->button2;
	sc.led1    = BC->led1;
	sc.led2    = BC->led2;

	BA->send_blocking_with_timeout(&sc,
								   sizeof(StateChanged),
								   *BA->com_current);
}

void next_led_toggle_state(const uint8_t button) {
	switch(button) {
		case 1: {
			if(BC->led1 == LED_STATE_AUTO_TOGGLE_OFF) {
				PIN_LED1.pio->PIO_CODR = PIN_LED1.mask;
				BC->led1 = LED_STATE_AUTO_TOGGLE_ON;
			} else if(BC->led1 == LED_STATE_AUTO_TOGGLE_ON) {
				PIN_LED1.pio->PIO_SODR = PIN_LED1.mask;
				BC->led1 = LED_STATE_AUTO_TOGGLE_OFF;
			}
			break;
		}

		case 2: {
			if(BC->led2 == LED_STATE_AUTO_TOGGLE_OFF) {
				PIN_LED2.pio->PIO_CODR = PIN_LED2.mask;
				BC->led2 = LED_STATE_AUTO_TOGGLE_ON;
			} else if(BC->led2 == LED_STATE_AUTO_TOGGLE_ON) {
				PIN_LED2.pio->PIO_SODR = PIN_LED2.mask;
				BC->led2 = LED_STATE_AUTO_TOGGLE_OFF;
			}
			break;
		}
	}
}
