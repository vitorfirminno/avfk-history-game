//
// Created by vitor on 9/29/26.
//

#ifndef AVFK_HISTORY_GAME_INPUT_H
#define AVFK_HISTORY_GAME_INPUT_H

#include <allegro5/allegro.h>


typedef struct {
    bool left, right, up, down, space;
    bool space_pressed; // borda de subida, evita pulo contínuo
} Input;

void handle_input(Input *input, ALLEGRO_EVENT *event);


#endif //AVFK_HISTORY_GAME_INPUT_H
