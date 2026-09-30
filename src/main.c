#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <entity/player.h>
#include <entity/entity.h>
#include <graphics/renderer.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FPS 60

#define DEPTH_TOP 150      // "fundo" do cenário (mais longe)
#define DEPTH_BOTTOM 450   // "frente" do cenário (mais perto)



void process_enemy(Entity *enemy, Entity *player) {
    float dx = player->x - enemy->x;
    float dy = player->y - enemy->y;
    float dist2 = dx * dx + dy * dy;

    if (dist2 > 40 * 40 && dist2 < 220 * 220) {
        enemy->vel_x = (dx > 0) ? enemy->speed : -enemy->speed;
        enemy->vel_y = (dy > 0) ? enemy->speed * 0.7f : -enemy->speed * 0.7f;
    } else {
        enemy->vel_x = 0;
        enemy->vel_y = 0;
    }

    // Pulo raro e só se estiver no chão
    if (!enemy->jumping && rand() % 240 == 0) {
        enemy->vel_height = -enemy->jump_power;
        enemy->jumping = true;
    }
}

void(* get_value(void))(Entity *, ALLEGRO_COLOR) {
    return draw_entity;
}



int main() {

    if (!al_init()) {
        fprintf(stderr, "Falha ao inicializar Allegro\n");
        return -1;
    }
    if (!al_init_primitives_addon()) {
        fprintf(stderr, "Falha ao inicializar primitivas\n");
        return -1;
    }
    if (!al_init_image_addon()) {
        fprintf(stderr, "Falha ao inicializar addon de imagem\n");
        return -1;
    }
    if (!al_install_keyboard()) {
        fprintf(stderr, "Falha ao instalar teclado\n");
        return -1;
    }

    ALLEGRO_DISPLAY *display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!display) {
        fprintf(stderr, "Falha ao criar display\n");
        return -1;
    }

    renderer_init();

    al_set_window_title(display, "Beat 'em Up - Street of Rage Style");

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());

    al_start_timer(timer);

    Player player;
    player_init(&player);

    renderer_load_player_sprites(&player);

    Entity enemy = {
        .x = 500, .y = 300, .height = 0,
        .vel_x = 0, .vel_y = 0, .vel_height = 0,
        .speed = 2.5f, .jumping = false, .jump_power = 9,
        .hp = 80, .width_base = 30, .height_base = 50
    };

    Input input = {false, false, false, false, false, false};
    float gravity = 0.6f;
    bool running = true;
    bool redraw = false;

    printf("Controles:\n");
    printf("  LEFT/RIGHT  - Mover esquerda/direita\n");
    printf("  UP/DOWN     - Mover para frente/tras (profundidade)\n");
    printf("  SPACE       - Pular\n");
    printf("  ESC         - Sair\n\n");

    while (running) {
        ALLEGRO_EVENT event;
        while (al_get_next_event(queue, &event)) {
            switch (event.type) {
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    running = false;
                    break;

                case ALLEGRO_EVENT_KEY_DOWN:
                    if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) running = false;
                    handle_input(&input, &event);
                    break;

                case ALLEGRO_EVENT_KEY_UP:
                    handle_input(&input, &event);
                    break;

                case ALLEGRO_EVENT_TIMER:
                    redraw = true;
                    break;
            }
        }

        if (redraw) {
            process_entity(&player.entity, &input);
            process_enemy(&enemy, &player.entity);

            player_update_animation(&player);

            update_entity(&player.entity, gravity);
            update_entity(&enemy, gravity);

            if (check_collision(&player.entity, &enemy)) {
                enemy.hp -= 1;
                enemy.vel_x = (enemy.x > player.entity.x) ? 3 : -3;
            }

            al_clear_to_color(al_map_rgb(50, 50, 80));

            // "Cenário" - piso com linhas de profundidade
            al_draw_filled_rectangle(0, DEPTH_TOP - 20, SCREEN_WIDTH, DEPTH_BOTTOM + 60,
                                      al_map_rgb(80, 80, 100));
            for (int i = DEPTH_TOP; i <= DEPTH_BOTTOM; i += 30) {
                al_draw_line(0, i, SCREEN_WIDTH, i, al_map_rgb(100, 100, 120), 1);
            }

            // Desenhar quem está mais "atrás" primeiro
            if (enemy.y < player.entity.y) {
                draw_entity(&enemy, al_map_rgb(255, 0, 0));
                draw_player_with_frame(&player);
            } else {
                draw_player_with_frame(&player);
                draw_entity(&enemy, al_map_rgb(255, 0, 0));
            }

            al_flip_display();
            redraw = false;
        }
    }

    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_display(display);

    return 0;
}
