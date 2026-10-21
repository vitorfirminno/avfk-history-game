//
// Created by vitor on 9/30/26.
//

#ifndef AVFK_HISTORY_GAME_RENDERER_H
#define AVFK_HISTORY_GAME_RENDERER_H
#include "player.h"


void renderer_init();
void renderer_load_player_sprites(Player *p);

void draw_player(Player *p);
void draw_player_with_frame(Player *p);



#endif //AVFK_HISTORY_GAME_RENDERER_H
