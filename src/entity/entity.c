//
// Created by vitor on 9/29/26.
//
#include "entity.h"

#include <stdbool.h>
#include <tgmath.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>

#include "../core/input.h"

float depth_scale(float y) {
    float t = (y - 150) / (450 - 150);  // Usar valores de config.h
    if (t < 0) t = 0;
    if (t > 1) t = 1;
    return 0.6f + t * 0.4f;
}

float to_screen_y(Entity *e) {
    return e->y - e->height;
}

void update_entity(Entity *Entity, float gravity) {
    Entity->x += Entity->vel_x;
    Entity->y += Entity->vel_y;

    Entity->vel_height += gravity;
    Entity->height -= Entity->vel_height;

    if (Entity->height <= 0) {
        Entity->height = 0;
        Entity->vel_height = 0;
        Entity->jumping = false;
    }
}

void draw_entity(Entity *Entity, ALLEGRO_COLOR color) {
    float scale = depth_scale(Entity->y);
    float w = Entity->width_base * scale;
    float h = Entity->height_base * scale;
    float screen_y = to_screen_y(Entity);

    al_draw_filled_rectangle(
        Entity->x - w / 2,
        screen_y - h,
        Entity->x + w / 2,
        screen_y,
        color
    );
    // Sombra no chão (ajuda a perceber o pulo)
    al_draw_filled_ellipse(Entity->x, Entity->y, w / 2, 6, al_map_rgba(0, 0, 0, 80));
}

void process_entity(Entity *entity, Input *input) {
    entity->vel_x = 0;
    entity->vel_y = 0;

    if (input->left) entity->vel_x = -entity->speed;
    if (input->right) entity->vel_x = entity->speed;
    if (input->up) entity->vel_y = -entity->speed;
    if (input->down) entity->vel_y = entity->speed;

    // Pulo só dispara na borda de subida da tecla, e só se estiver no chão
    if (input->space_pressed && !entity->jumping) {
        entity->vel_height = -entity->jump_power; // negativo = subindo
        entity->jumping = true;
    }
    input->space_pressed = false;
}

bool check_collision(Entity *a, Entity *b) {
    float a_scale = depth_scale(a->y);
    float b_scale = depth_scale(b->y);
    float a_w = a->width_base * a_scale;
    float a_h = a->height_base * a_scale;
    float b_w = b->width_base * b_scale;
    float b_h = b->height_base * b_scale;

    float a_top = to_screen_y(a) - a_h;
    float a_bottom = to_screen_y(a);
    float b_top = to_screen_y(b) - b_h;
    float b_bottom = to_screen_y(b);

    bool overlap_x = !(a->x + a_w / 2 < b->x - b_w / 2 || a->x - a_w / 2 > b->x + b_w / 2);
    bool overlap_y = !(a_bottom < b_top || a_top > b_bottom);
    // Também exige proximidade de profundidade real (evita golpear quem está longe no eixo Y)
    bool close_depth = fabsf(a->y - b->y) < 40;

    return overlap_x && overlap_y && close_depth;
}

