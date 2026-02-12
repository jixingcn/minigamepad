#define MG_IMPLEMENTATION
#include "minigamepad.h"

#include <stdio.h>

void gamepad_connection(mg_gamepad* gamepad, mg_bool connected, void* userdata) {
	switch (connected) {
		case MG_FALSE:
            printf("gamepad disconnected (gamepad %p) (userdata %p)\n", (void*)gamepad, userdata);
			break;
		case MG_TRUE:
            printf("gamepad connected (gamepad %p) (userdata %p)\n", (void*)gamepad, userdata);
			break;
		default: break;
	}
}

void gamepad_button(mg_gamepad* gamepad, mg_button button, mg_bool pressed, void* userdata) {
	switch (pressed) {
		case MG_FALSE:
			printf("button release (gamepad %p) %i (userdata %p)\n", (void*)gamepad, button, userdata);
			break;
		case MG_TRUE:
			printf("button press (gamepad %p) %i (userdata %p)\n", (void*)gamepad, button, userdata);
			break;
		default: break;
	}
}

void gamepad_axis(mg_gamepad* gamepad, mg_axis axis, void* userdata) {
    printf("axis move (gamepad %p) %i (userdata %p)\n", (void*)gamepad, axis, userdata);
}



int main(void) {
	mg_gamepads gamepads;
	mg_gamepads_init(&gamepads);

    mg_set_gamepad_connected_callback(&gamepads, gamepad_connection, NULL);
	mg_set_gamepad_disconnected_callback(&gamepads, gamepad_connection, NULL);

	mg_set_gamepad_press_callback(&gamepads, gamepad_button, NULL);
	mg_set_gamepad_release_callback(&gamepads, gamepad_button, NULL);

	mg_set_gamepad_axis_callback(&gamepads, gamepad_axis, NULL);

    while (gamepads.list.head) {
        mg_gamepads_poll(&gamepads);
    }

    mg_gamepads_free(&gamepads);
    return 0;
}
