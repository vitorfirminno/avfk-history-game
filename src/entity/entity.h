//
// Created by vitor on 9/29/26.
//

#ifndef AVFK_HISTORY_GAME_ENTITY_H
#define AVFK_HISTORY_GAME_ENTITY_H
#define ENTITY_WIDTH 30
#define ENTITY_HEIGHT 50
#define ENTITY_DEFAULT_HP 100
#define ENTITY_DEFAULT_SPEED 4.0f
#define ENTITY_DEFAULT_JUMP_POWER 10.0f


#include <allegro5/color.h>

#include "../core/input.h"


typedef struct {
    float x, y;
    float height;
    float vel_x, vel_y, vel_height;
    float speed;
    bool jumping;
    float jump_power;
    int hp;
    float width_base, height_base;
} Entity;



void update_entity(Entity *entity, float gravity);
void draw_entity(Entity *entity, ALLEGRO_COLOR color);
void process_entity(Entity *entity, Input *input);
bool check_collision(Entity * entity, Entity * enemy);
float depth_scale(float y);
float to_screen_y(Entity *e);
#endif //AVFK_HISTORY_GAME_ENTITY_H