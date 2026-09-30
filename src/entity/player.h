#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include <allegro5/allegro.h>


#define PLAYER_START_X 300
#define PLAYER_START_Y 300
#define PLAYER_START_LEVEL 1
#define PLAYER_START_SCORE 0

typedef struct {
    Entity entity;
    int level;
    int score;
    int enemies_defeated;

    int current_frame;
    int frame_counter;
    int direction;

    ALLEGRO_BITMAP *frame_idle;     // ← Só REFERÊNCIA
    ALLEGRO_BITMAP *frame_walk;
} Player;

void player_init(Player *p);

void player_update_animation(Player *p);



#endif