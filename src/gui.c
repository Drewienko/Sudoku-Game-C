#include "../include/gui.h"

void must_init(bool test, const char *description)
{
    if (test)
        return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

void draw_button(BUTTON *b, ALLEGRO_FONT *font, ALLEGRO_COLOR color, float thickness)
{
    if (b->text[0] - '0')
        al_draw_textf(font, al_map_rgb(255, 255, 255), b->x + (b->size_x / 2), b->y + (b->size_y / 10), ALLEGRO_ALIGN_CENTER, b->text, b->board_pos_y + b->board_pos_x);
    al_draw_rectangle(b->x, b->y, b->x + b->size_x, b->y + b->size_y, color, thickness);
}

void draw_main_menu(MAIN_MENU *mm, BUTTON *b, ALLEGRO_FONT *font, ALLEGRO_FONT *font2)
{
    for (int i = 0; i < MAIN_MENU_BT_N; i++)
    {

        BUTTON *b = mm->buttons[i];
        draw_button(b, font2, al_map_rgb(255, 255, 255), 5.0f);
    }
}

void draw_game(BOARD *sb, DONE_MENU *dm, GAME_MENU *mb, BUTTON *b, ALLEGRO_FONT *font, ALLEGRO_FONT *font2, ALLEGRO_FONT *font3)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            BUTTON *b = sb->buttons[i][j];
            draw_button(b, font, al_map_rgb(255, 255, 255), 3.0f);
        }
    }

    for (int i = 0; i < 4; i++)
    {
        int offset = i * (sb->size_x / 3);
        // printf("%d|",offset);
        al_draw_line(sb->x + offset, sb->y, sb->x + offset, sb->y + sb->size_y, al_map_rgb(255, 255, 255), 5.0f);
        al_draw_line(sb->x, sb->y + offset, sb->x + sb->size_x, sb->y + offset, al_map_rgb(255, 255, 255), 5.0f);

        // al_draw_textf(font, al_map_rgb(255, 255, 255), b->x + (b->size_x / 2), b->y + (b->size_y / 10), ALLEGRO_ALIGN_CENTER, b->text, b->board_pos_y + b->board_pos_x);

        //
    }

    for (int i = 0; i < GAME_BT_N; i++)
    {

        BUTTON *b = mb->buttons[i];
        draw_button(b, font2, al_map_rgb(255, 255, 255), 2.0f);
    }

    for (int i = 0; i < GAME_BT_HARD; i++)
    {

        BUTTON *b = mb->buttons[i];
        if (sb->difficulty == b->type && sb->difficulty != GENERATOR_BT_CUSTOM)
            draw_button(b, font2, al_map_rgb(0, 255, 0), 2.0f);
    }

    if (b)
    {
        if (b->type == 0)
        {
            draw_button(b, font, al_map_rgb(255, 0, 0), 5.0f);
        }
    }

    if (sb->b_state == STATE_B_DONE)
    {
        al_draw_filled_rectangle(dm->x, dm->y, dm->x + dm->size_x, dm->y + dm->size_y, al_map_rgb(0, 0, 0));
        al_draw_rectangle(dm->x, dm->y, dm->x + dm->size_x, dm->y + dm->size_y, al_map_rgb(255, 255, 255), 2.0f);
        draw_button(dm->buttons[0], font2, al_map_rgb(255, 255, 255), 3.0f);

        int board_number = sb->board_nr;       // Przykładowy numer planszy
        int difficulty_level = sb->difficulty; // Przykładowy poziom trudności

        char *message[] = {
            "Gratulacje!!!",
            "Ukonczyles planszę:",
            "poziom trudności:",
            "Ukończone plansze zostana zapisane",
            " w pliku \"finished.dat\""};

        char *diff[] = {
            "Łatwa",
            "Średnia",
            "Trudnia",
            "Generowana losowo"};

        char buffer[256];

        snprintf(buffer, sizeof(buffer), "%s %d", message[1], board_number);
        al_draw_text(font2, al_map_rgb(255, 255, 255), dm->x + 10, dm->y + 10 + 40, 0, message[0]);
        al_draw_text(font3, al_map_rgb(255, 255, 255), dm->x + 10, dm->y + 10 + 80, 0, buffer);

        snprintf(buffer, sizeof(buffer), "%s %s", message[2], diff[difficulty_level]);
        al_draw_text(font3, al_map_rgb(255, 255, 255), dm->x + 10, dm->y + 10 + 120, 0, buffer);

        al_draw_text(font3, al_map_rgb(255, 255, 255), dm->x + 10, dm->y + 10 + 160, 0, message[3]);
        al_draw_text(font3, al_map_rgb(255, 255, 255), dm->x + 10, dm->y + 10 + 180, 0, message[4]);
    }
}

void draw_select_menu(BOARD *sb, SELECT_MENU *sm, BUTTON *b, ALLEGRO_FONT *font, ALLEGRO_FONT *font2)
{
    for (int i = 0; i < SELECT_BT_N + SELECT_BT_BOARDS; i++)
    {

        BUTTON *b = sm->buttons[i];
        if (b->type == SELECT_BT_BOARDS)
        {

            draw_button(b, font, al_map_rgb(255, 255, 255), 3.0f);
        }

        else
        {
            draw_button(b, font2, al_map_rgb(255, 255, 255), 4.0f);
        }
    }

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            BUTTON *b = sb->buttons[i][j];
            draw_button(b, font2, al_map_rgb(255, 255, 255), 3.0f);
        }
    }

    for (int i = 0; i < 4; i++)
    {
        int offset = i * (sb->size_x / 3);
        // printf("%d|",offset);
        al_draw_line(sb->x + offset, sb->y, sb->x + offset, sb->y + sb->size_y, al_map_rgb(255, 255, 255), 5.0f);
        al_draw_line(sb->x, sb->y + offset, sb->x + sb->size_x, sb->y + offset, al_map_rgb(255, 255, 255), 5.0f);
    }

    for (int i = 0; i < SELECT_BT_N + SELECT_BT_BOARDS; i++)
    {
        if (sb->difficulty >= GENERATOR_BT_EASY)
        {
            BUTTON *b = sm->buttons[i];
            if (b->type == SELECT_BT_BOARDS)
            {

                if (sm->finished[sb->difficulty][b->board_pos_y - 1])
                {
                    draw_button(b, font, al_map_rgb(0, 255, 0), 3.0f);
                }
            }

            else
            {
                if (sb->difficulty + SELECT_BT_EASY == b->type)
                    draw_button(b, font2, al_map_rgb(0, 255, 0), 4.0f);
            }
        }
    }
}

void draw_generator_menu(BOARD *sb, GENERATOR_MENU *gm, BUTTON *b, ALLEGRO_FONT *font, ALLEGRO_FONT *font2)
{
    for (int i = 0; i < GENERATOR_BT_N; i++)
    {

        BUTTON *b = gm->buttons[i];
        if (b->type == GENERATOR_BT_EMPTY || b->type == GENERATOR_BT_BACKTRACKS)
        {
            draw_button(b, font2, al_map_rgb(0, 0, 0), 5.0f);
            draw_button(gm->buttons[i - 1], font2, al_map_rgb(255, 255, 255), 5.0f);
        }
        else if (b->type == GENERATOR_BT_BOXES)
        {
            draw_button(b, font2, al_map_rgb(0, 0, 0), 5.0f);
        }
        else
        {
            draw_button(b, font2, al_map_rgb(255, 255, 255), 5.0f);
        }
    }

    for (int i = 0; i <= GENERATOR_BT_CUSTOM; i++)
    {
        BUTTON *b = gm->buttons[i];
        if (sb->difficulty == i)
            draw_button(b, font2, al_map_rgb(0, 255, 0), 5.0f);
    }

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            BUTTON *b = sb->buttons[i][j];
            draw_button(b, font2, al_map_rgb(255, 255, 255), 3.0f);
        }
    }

    for (int i = 0; i < 4; i++)
    {
        int offset = i * (sb->size_x / 3);
        // printf("%d|",offset);
        al_draw_line(sb->x + offset, sb->y, sb->x + offset, sb->y + sb->size_y, al_map_rgb(255, 255, 255), 5.0f);
        al_draw_line(sb->x, sb->y + offset, sb->x + sb->size_x, sb->y + offset, al_map_rgb(255, 255, 255), 5.0f);
    }
}
