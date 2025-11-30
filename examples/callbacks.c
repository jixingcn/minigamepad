#define MG_IMPLEMENTATION
#include "minigamepad.h"

#include <stdio.h>

void gamepad_connection(mg_gamepad* gamepad, mg_bool connected) {
	switch (connected) {
		case MG_FALSE:
            printf("gamepad disconnected (gamepad %p)\n", (void*)gamepad);
			break;
		case MG_TRUE:
            printf("gamepad connected (gamepad %p)\n", (void*)gamepad);
			break;
		default: break;
	}
}

void gamepad_button(mg_gamepad* gamepad, mg_button button, mg_bool pressed) {
	switch (pressed) {
		case MG_FALSE:
			printf("button release (gamepad %p) %i\n", (void*)gamepad, button);
			break;
		case MG_TRUE:
			printf("button press (gamepad %p) %i\n", (void*)gamepad, button);
			break;
		default: break;
	}
}

void gamepad_axis(mg_gamepad* gamepad, mg_axis axis) {
    printf("axis move (gamepad %p) %i\n", (void*)gamepad, axis);
}



int main(void) {
	mg_gamepads gamepads;
	mg_set_gamepad_connected_callback(gamepad_connection);
	mg_set_gamepad_disconnected_callback(gamepad_connection);

	mg_set_gamepad_press_callback(gamepad_button);
	mg_set_gamepad_release_callback(gamepad_button);

	mg_set_gamepad_axis_callback(gamepad_axis);

	mg_gamepads_init(&gamepads);

    while (gamepads.list.head) {
        mg_gamepads_poll(&gamepads);
    }

    mg_gamepads_free(&gamepads);
    return 0;
}
