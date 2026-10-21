//
// Created by vitor on 9/27/26.
//


#include "player.h"


void player_init(Player *p) {
    p->entity.x = PLAYER_START_X;
    p->entity.y = PLAYER_START_Y;
    p->entity.hp = ENTITY_DEFAULT_HP;
    p->entity.speed = ENTITY_DEFAULT_SPEED;
    p->entity.jump_power = ENTITY_DEFAULT_JUMP_POWER;
    p->entity.width_base = ENTITY_WIDTH;
    p->entity.height_base = ENTITY_HEIGHT;
    p->entity.jumping = false;
    p->entity.vel_x = 0;
    p->entity.vel_y = 0;
    p->entity.vel_height = 0;
};


void player_update_animation(Player *p) {

    if (p->entity.vel_x != 0) {
        p->direction = (p->entity.vel_x > 0) ? 1 : -1;

        p->frame_counter++;
        if (p->frame_counter >= 5) {
            p->frame_counter = 0;
            p->current_frame = 1 - p->current_frame;
        }
    } else {
        p->current_frame = 0;  // Frame IDLE
        p->frame_counter = 0;
    }

}