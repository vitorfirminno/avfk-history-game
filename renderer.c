//
// Created by vitor on 9/30/26.
//


#include <stdio.h>

#include "player.h"
#include "allegro5/bitmap.h"
#include "allegro5/allegro_primitives.h"


#define PLAYER_VISUAL_SCALE 2.2f

static ALLEGRO_BITMAP *g_player_frame0 = NULL;
static ALLEGRO_BITMAP *g_player_frame1 = NULL;

void renderer_init() {

    g_player_frame0 = al_load_bitmap("assets/player_frame0.png");
    g_player_frame1 = al_load_bitmap("assets/player_frame1.png");

    if (!g_player_frame0 || !g_player_frame1) {
        fprintf(stderr, "Erro ao carregar sprites!\n");
    }
};

void renderer_load_player_sprites(Player *p) {
    p->frame_idle = g_player_frame0;
    p->frame_walk = g_player_frame1;
}

void draw_player_with_frame(Player *p) {
    if (!p->frame_idle || !p->frame_walk) return;

    // Escolher qual frame desenhar
    ALLEGRO_BITMAP *current_img =
        (p->current_frame == 0) ? p->frame_idle : p->frame_walk;

    float scale = depth_scale(p->entity.y);
    float screen_y = to_screen_y(&p->entity);

    // Tamanho da hitbox (usado para a sombra, que fica presa ao "pé" real do personagem)
    float hit_w = p->entity.width_base * scale;

    // Tamanho visual ampliado do sprite, mantendo a proporção 30:50
    float draw_w = 30 * scale * PLAYER_VISUAL_SCALE;
    float draw_h = 50 * scale * PLAYER_VISUAL_SCALE;

    // Sombra no chão, na mesma posição/tamanho da hitbox (não do sprite ampliado)
    al_draw_filled_ellipse(p->entity.x, p->entity.y, hit_w / 2, 6, al_map_rgba(0, 0, 0, 80));

    // Desenhar com flip se for esquerda, ancorando os pés em screen_y (base da hitbox)
    al_draw_scaled_bitmap(
        current_img,
        0, 0,
        al_get_bitmap_width(current_img),
        al_get_bitmap_height(current_img),
        p->entity.x - (draw_w / 2),
        screen_y - draw_h,
        draw_w,
        draw_h,
        (p->direction == -1) ? ALLEGRO_FLIP_HORIZONTAL : 0
    );
}


