#include "../include/game.h"

BOARD *init_board(float x, float y, int size_x, int size_y, int difficulty)
{
    BOARD *result = (struct BOARD *)malloc(sizeof(struct BOARD));
    result->x = x;
    result->y = y;
    result->size_x = size_x;
    result->size_y = size_y;
    result->difficulty = difficulty;
    result->board_nr = 0;
    result->b_state = STATE_B_EMPTY;

    int button_size_x = size_x / 9;
    int button_size_y = size_y / 9;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            float button_x = result->x + button_size_x * i;
            float button_y = result->y + button_size_y * j;

            result->buttons[i][j] = init_button(button_x, button_y, button_size_x, button_size_y, GAME_BT_BOARD, "0", i, j);
        }
    }

    return result;
}

void destroy_board(BOARD **sb)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            destroy_button(&(*sb)->buttons[i][j]);
        }
    }
    free(*sb);
    *sb = NULL;
}

void load_board(BOARD *sb, char *str_json)
{
    strcpy(sb->board_, str_json);
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            char tmp = str_json[i * 9 + j];
            if (tmp == '.')
                tmp = '0';

            sb->buttons[j][i]->text[0] = tmp;
        }
    }
    sb->b_state = STATE_B_PLAYING;
}

BUTTON *mouse_inside_board(int x, int y, BOARD *sb)
{
    if (x > sb->x && x < (sb->x + sb->size_x))
    {
        if (y > sb->y && y < (sb->y + sb->size_y))
        {
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    BUTTON *b = sb->buttons[i][j];
                    if (mouse_inside_button(x, y, b))
                        return b;
                }
            }
        }
    }
    return 0;
}

void resize_board(int size_x, int size_y, BOARD *sb)
{

    sb->size_x = size_x;
    sb->size_y = size_y;
    int button_size_x = size_x / 9;
    int button_size_y = size_y / 9;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {

            sb->buttons[i][j]->x = sb->x + button_size_x * i;
            sb->buttons[i][j]->y = sb->y + button_size_y * j;
            sb->buttons[i][j]->size_x = button_size_x;
            sb->buttons[i][j]->size_y = button_size_y;
        }
    }
}

int check_board(BOARD *sb)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            BUTTON *b = sb->buttons[j][i];
            if (b->text[0] == '0')
            {
                return STATE_B_PLAYING;
            }
        }
    }
    return STATE_B_DONE;
}

void reset_board(BOARD *sb)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            sb->buttons[j][i]->text[0] = '0';
        }
    }
    sb->b_state = STATE_B_EMPTY;
    sb->board_nr = 0;
    sb->difficulty = -1;
}

GAME_MENU *init_game_menu(float x, float y, int size_x, int size_y)
{
    GAME_MENU *result = (struct GAME_MENU *)malloc(sizeof(struct GAME_MENU));

    result->x = x;
    result->y = y;
    result->size_x = size_x;
    result->size_y = size_y;

    int button_size_x = size_x;
    int button_size_y = size_y / 15;
    char *GAME_MENU_str[7] = {"EASY", "MEDIUM", "HARD", "UNDO", "HINT", "SAVE", "LOAD"};
    for (int i = 0; i < GAME_BT_N; i++)
    {

        float button_x = result->x;
        float button_y = result->y + button_size_y * i;
        // result->values[i][j] = 0;
        result->buttons[i] = init_button(button_x, button_y, button_size_x, button_size_y, i, GAME_MENU_str[i], 0, i);
    }

    return result;
}

BUTTON *mouse_inside_game_menu(int x, int y, GAME_MENU *sb)
{
    if (x > sb->x && x < (sb->x + sb->size_x))
    {
        if (y > sb->y && y < (sb->y + sb->size_y))
        {
            for (int i = 0; i < GAME_BT_N; i++)
            {

                BUTTON *b = sb->buttons[i];
                if (mouse_inside_button(x, y, b))
                    return b;
            }
        }
    }
    return 0;
}

void destroy_game_menu(GAME_MENU **mb)
{
    for (int i = 0; i < GAME_BT_N; i++)
    {

        destroy_button(&(*mb)->buttons[i]);
    }
    free(*mb);
    *mb = NULL;
}

DONE_MENU *init_done_menu(float x, float y, int size_x, int size_y)
{
    DONE_MENU *result = (struct DONE_MENU *)malloc(sizeof(struct DONE_MENU));

    result->x = x;
    result->y = y;
    result->size_x = size_x;
    result->size_y = size_y;

    int button_size_x = 150;
    int button_size_y = 30;

    result->buttons[DONE_BT_MAIN_MENU] = init_button(x + 75, y + 255, button_size_x, button_size_y, DONE_BT_MAIN_MENU, "MAIN MENU", 0, 0);
    return result;
}

void destroy_done_menu(DONE_MENU **dm)
{
    for (int i = 0; i < DONE_BT_N; i++)
    {

        destroy_button(&(*dm)->buttons[i]);
    }
    free(*dm);
    *dm = NULL;
}

BUTTON *mouse_inside_done_menu(int x, int y, DONE_MENU *sb)
{

    if (x > sb->x && x < (sb->x + sb->size_x))
    {

        if (y > sb->y && y < (sb->y + sb->size_y))
        {
            for (int i = 0; i < DONE_BT_N; i++)
            {

                BUTTON *b = sb->buttons[i];
                if (mouse_inside_button(x, y, b))
                {
                    return b;
                }
            }
        }
    }
    return 0;
}
