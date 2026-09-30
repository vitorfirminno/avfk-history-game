//
// Created by vitor on 9/29/26.
//


#include <allegro5/events.h>
#include <allegro5/keycodes.h>

#include "input.h"


void handle_input(Input *input, ALLEGRO_EVENT *event) {
    switch (event->type) {
        case ALLEGRO_EVENT_KEY_DOWN:
            if (event->keyboard.keycode == ALLEGRO_KEY_LEFT) input->left = true;
            if (event->keyboard.keycode == ALLEGRO_KEY_RIGHT) input->right = true;
            if (event->keyboard.keycode == ALLEGRO_KEY_UP) input->up = true;
            if (event->keyboard.keycode == ALLEGRO_KEY_DOWN) input->down = true;
            if (event->keyboard.keycode == ALLEGRO_KEY_SPACE) {
                if (!input->space) input->space_pressed = true;
                input->space = true;
            }
            break;

        case ALLEGRO_EVENT_KEY_UP:
            if (event->keyboard.keycode == ALLEGRO_KEY_LEFT) input->left = false;
            if (event->keyboard.keycode == ALLEGRO_KEY_RIGHT) input->right = false;
            if (event->keyboard.keycode == ALLEGRO_KEY_UP) input->up = false;
            if (event->keyboard.keycode == ALLEGRO_KEY_DOWN) input->down = false;
            if (event->keyboard.keycode == ALLEGRO_KEY_SPACE) input->space = false;
            break;
    }
}
