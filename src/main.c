#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include "../include/gui.h"
#include "../include/sudoku.h"

enum GameState
{
    STATE_MAIN_MENU,
    STATE_SELECT_MENU,
    STATE_GENERATOR_MENU,
    STATE_GAME
};

int main()
{
    srand(time(0));
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    must_init(queue, "queue");

    ALLEGRO_DISPLAY *disp = al_create_display(640, 480);
    must_init(disp, "display");

    must_init(al_init_font_addon(), "font addon");
    must_init(al_init_ttf_addon(), "ttf addon");
    ALLEGRO_FONT *font = al_load_font("./fonts/calibri.ttf", 45, 0);
    must_init(font, "font");
    ALLEGRO_FONT *font2 = al_load_font("./fonts/calibri.ttf", 25, 0);
    must_init(font2, "font2");
    ALLEGRO_FONT *font3 = al_load_font("./fonts/calibri.ttf", 15, 0);
    must_init(font3, "font3");

    must_init(al_install_mouse(), "mouse");

    must_init(al_init_primitives_addon(), "primitives");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());

    BOARD *sb = init_board(15.0, 15.0, 300, 300, -1);
    must_init(sb, "sudoku board");

    GAME_MENU *mb = init_game_menu(495.0, 15.0, 120, 450);
    must_init(mb, "menu board");

    MAIN_MENU *mm = init_main_menu(245.0, 15.0, 120, 450);
    must_init(mm, "main_menu board");

    SELECT_MENU *sm = init_select_menu(15.0, 15.0, 580, 450);
    must_init(sm, "select_menu board");

    GENERATOR_MENU *gm = init_generator_menu(15.0, 15.0, 580, 450);
    must_init(gm, "generator_menu board");

    DONE_MENU *dm = init_done_menu(120.0, 90.0, 300, 300);
    must_init(dm, "generator_menu board");

    bool done = false;
    bool redraw = true;
    bool focused = true;
    BUTTON *focused_button = NULL;
    move *move_list = 0;
    int key_value = 0;
    ALLEGRO_EVENT event;
    int state = STATE_MAIN_MENU;
    int select_offset = 0;

    int x = 0, y = 0;
    al_start_timer(timer);

    bool running = true;
    while (running)
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:

            redraw = true;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            if (focused && !key_value)
                switch (event.keyboard.keycode)
                {
                case ALLEGRO_KEY_1:
                case ALLEGRO_KEY_PAD_1:
                    key_value = 1;
                    break;
                case ALLEGRO_KEY_2:
                case ALLEGRO_KEY_PAD_2:
                    key_value = 2;
                    break;
                case ALLEGRO_KEY_3:
                case ALLEGRO_KEY_PAD_3:
                    key_value = 3;
                    break;
                case ALLEGRO_KEY_4:
                case ALLEGRO_KEY_PAD_4:
                    key_value = 4;
                    break;
                case ALLEGRO_KEY_5:
                case ALLEGRO_KEY_PAD_5:
                    key_value = 5;
                    break;
                case ALLEGRO_KEY_6:
                case ALLEGRO_KEY_PAD_6:
                    key_value = 6;
                    break;
                case ALLEGRO_KEY_7:
                case ALLEGRO_KEY_PAD_7:
                    key_value = 7;
                    break;
                case ALLEGRO_KEY_8:
                case ALLEGRO_KEY_PAD_8:
                    key_value = 8;
                    break;
                case ALLEGRO_KEY_9:
                case ALLEGRO_KEY_PAD_9:
                    key_value = 9;
                    break;
                case ALLEGRO_KEY_BACKSPACE:
                    if (move_list)
                    {
                        sb->buttons[move_list->board_pos_x][move_list->board_pos_y]->text[0] = '0';
                        move_pop(&move_list);
                    }
                }
            break;
        case ALLEGRO_EVENT_MOUSE_AXES:

            break;

        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            x = event.mouse.x;
            y = event.mouse.y;
            focused = false;
            redraw = true;
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }

        if (done)
            break;

        if (redraw && al_is_event_queue_empty(queue))
        {
            if (state == STATE_MAIN_MENU)
            {
                al_clear_to_color(al_map_rgb(0, 0, 0));
                draw_main_menu(mm, focused_button, font, font2);
            }
            else if (state == STATE_GAME)
            {
                al_clear_to_color(al_map_rgb(0, 0, 0));
                // char digit[2] = {'0', '\0'};
                draw_game(sb, dm, mb, focused_button, font, font2, font3);
            }
            else if (state == STATE_SELECT_MENU)
            {
                al_clear_to_color(al_map_rgb(0, 0, 0));
                // char digit[2] = {'0', '\0'};
                draw_select_menu(sb, sm, focused_button, font3, font2);
            }
            else if (state == STATE_GENERATOR_MENU)
            {
                al_clear_to_color(al_map_rgb(0, 0, 0));
                // char digit[2] = {'0', '\0'};
                draw_generator_menu(sb, gm, focused_button, font, font2);
            }

            al_flip_display();
            redraw = false;
        }

        if (!focused)
        {
            printf("debug find\n");
            if (state == STATE_MAIN_MENU)
            {
                focused_button = mouse_inside_main_menu(x, y, mm);
                if (focused_button)
                    switch (focused_button->type)
                    {
                    case MAIN_MENU_BT_START:
                        state = STATE_SELECT_MENU;
                        break;
                    case MAIN_MENU_BT_GENERATE:
                        state = STATE_GENERATOR_MENU;
                        break;
                    case MAIN_MENU_BT_EXIT:
                        running = false;
                        break;
                    }
                focused_button = 0;
            }
            else if (state == STATE_GENERATOR_MENU)
            {
                focused_button = mouse_inside_generator_menu(x, y, gm);
                if (focused_button)
                    switch (focused_button->type)
                    {
                    case GENERATOR_BT_EASY:
                        sb->difficulty = GENERATOR_BT_EASY;
                        break;
                    case GENERATOR_BT_MEDIUM:
                        sb->difficulty = GENERATOR_BT_MEDIUM;
                        break;
                    case GENERATOR_BT_HARD:
                        sb->difficulty = GENERATOR_BT_HARD;
                        break;
                    case GENERATOR_BT_CUSTOM:
                        sb->difficulty = GENERATOR_BT_CUSTOM;
                        break;
                    case GENERATOR_BT_PLUS:
                        gm->buttons[GENERATOR_BT_ITER]->board_pos_y++;
                        break;
                    case GENERATOR_BT_MINUS:
                        gm->buttons[GENERATOR_BT_ITER]->board_pos_y--;
                        break;
                    case GENERATOR_BT_PLAY:
                        if (sb->b_state == STATE_B_PLAYING)
                        {
                            sb->board_nr = 0;
                            state = STATE_GAME;
                            resize_board(450, 450, sb);
                        }
                        break;
                    case GENERATOR_BT_BACK:
                        state = STATE_MAIN_MENU;
                        reset_board(sb);
                        resize_board(300, 300, sb);
                        break;
                    case GENERATOR_BT_GENERATE:
                        switch (sb->difficulty)
                        {
                        case GENERATOR_BT_EASY:
                            gm->buttons[GENERATOR_BT_BACKTRACKS_ITER]->board_pos_y =
                                load_random_board(sb, 30);
                            break;
                        case GENERATOR_BT_MEDIUM:
                            gm->buttons[GENERATOR_BT_BACKTRACKS_ITER]->board_pos_y =
                                load_random_board(sb, 45);
                            break;
                        case GENERATOR_BT_HARD:
                            gm->buttons[GENERATOR_BT_BACKTRACKS_ITER]->board_pos_y =
                                load_random_board(sb, 50);
                            break;
                        case GENERATOR_BT_CUSTOM:
                            gm->buttons[GENERATOR_BT_BACKTRACKS_ITER]->board_pos_y =
                                load_random_board(sb, gm->buttons[GENERATOR_BT_ITER]->board_pos_y);
                            break;
                        }
                        break;
                    default:
                        break;
                    }
                focused_button = 0;
            }
            else if (state == STATE_GAME)
            {
                if (sb->b_state == STATE_B_PLAYING)
                {
                    focused_button = mouse_inside_board(x, y, sb);
                    if (!focused_button)
                    {
                        focused_button = mouse_inside_game_menu(x, y, mb);
                        if (focused_button)
                        {
                            switch (focused_button->type)
                            {
                            case GAME_BT_EASY:
                                break;
                            case GAME_BT_MEDIUM:
                                break;
                            case GAME_BT_HARD:
                                break;
                            case GAME_BT_UNDO:
                                if (move_list)
                                {
                                    sb->buttons[move_list->board_pos_x][move_list->board_pos_y]->text[0] = '0';
                                    move_pop(&move_list);
                                }
                                break;
                            case GAME_BT_HINT:
                                suggest_next_move(sb, &move_list);
                                sb->b_state = check_board(sb);
                                redraw = true;
                                break;
                            case GAME_BT_SAVE:
                                save_board_state(sb, &move_list, "save.dat");
                                break;
                            case GAME_BT_LOAD:
                                load_board_state(&sb, &move_list, "save.dat");
                                break;
                            }
                            focused_button = 0;
                        }
                    }
                }
                else if (sb->b_state == STATE_B_DONE)
                {
                    focused_button = mouse_inside_done_menu(x, y, dm);

                    if (focused_button)
                    {

                        if (focused_button->type == DONE_BT_MAIN_MENU)
                        {
                            if (sb->board_nr)
                                sm->finished[sb->difficulty][sb->board_nr - 1] = true;
                            printf("%d\n", focused_button->board_pos_y);
                            save_finished("finished.dat", &sm);
                            state = STATE_MAIN_MENU;
                            reset_board(sb);
                            resize_board(300, 300, sb);
                        }
                        focused_button = 0;
                    }
                }
            }
            else if (state = STATE_SELECT_MENU)
            {
                focused_button = mouse_inside_select_menu(x, y, sm);
                if (focused_button)
                {
                    switch (focused_button->type)
                    {
                    case SELECT_BT_PREV10:
                        update_board_bt(-10, sm);
                        break;
                    case SELECT_BT_PREV100:
                        update_board_bt(-100, sm);
                        break;
                    case SELECT_BT_PREV1000:
                        update_board_bt(-1000, sm);
                        break;
                    case SELECT_BT_NEXT10:
                        update_board_bt(10, sm);
                        break;
                    case SELECT_BT_NEXT100:
                        update_board_bt(100, sm);
                        break;
                    case SELECT_BT_NEXT1000:
                        update_board_bt(1000, sm);
                        break;
                    case SELECT_BT_EASY:
                        sb->difficulty = GAME_BT_EASY;
                        break;
                    case SELECT_BT_MEDIUM:
                        sb->difficulty = GAME_BT_MEDIUM;
                        break;
                    case SELECT_BT_HARD:
                        sb->difficulty = GAME_BT_HARD;
                        break;
                    case SELECT_BT_RANDOM:
                        int random = rand() % 10000 + 1;
                        if (sb->difficulty >= 0)
                        {
                            load_board(sb, read_puzzle(sb->difficulty, random, sb->ans));
                            sb->board_nr = random;
                            printf("%d", sb->board_nr);
                        }
                        break;
                    case SELECT_BT_BOARDS:
                        if (sb->difficulty >= 0)
                        {
                            load_board(sb, read_puzzle(sb->difficulty, focused_button->board_pos_y, sb->ans));
                            sb->board_nr = focused_button->board_pos_y;
                        }
                        // sm->finished[sb->difficulty][focused_button->board_pos_y] = true;
                        break;
                    case SELECT_BT_START:
                        if (sb->board_nr)
                        {
                            state = STATE_GAME;
                            resize_board(450, 450, sb);
                        }

                        break;
                    }
                    focused_button = 0;
                }
            }

            focused = true;
        }

        if (focused && key_value)
        {
            printf("debug key\n");
            BUTTON *b = focused_button;
            if (b)
            {
                if (check_ans(sb, key_value + '0', b) && b->text[0] == '0')
                {
                    move_push(&move_list, b->board_pos_x, b->board_pos_y);
                    printf("move: %d %d\n", move_list->board_pos_x, move_list->board_pos_y);
                    b->text[0] = key_value + '0';
                    sb->b_state = check_board(sb);
                }
            }
            key_value = 0;
        }
    }

    destroy_move(&move_list);
    destroy_board(&sb);
    destroy_game_menu(&mb);
    destroy_main_menu(&mm);
    destroy_select_menu(&sm);
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}
