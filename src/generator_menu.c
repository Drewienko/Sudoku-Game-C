#include "../include/generator_menu.h"

GENERATOR_MENU *init_generator_menu(float x, float y, int size_x, int size_y)
{
    GENERATOR_MENU *result = (struct GENERATOR_MENU *)malloc(sizeof(struct GENERATOR_MENU));

    result->x = x;
    result->y = y;
    result->size_x = size_x;
    result->size_y = size_y;

    char *menu_str[GENERATOR_BT_N] = {"EASY", "MEDIUM", "HARD", "CUSTOM", "EMPTY", "BOXES", "+", "%d", "-", "GENERATE", "BACKTRACKS", "%d", "PLAY", "BACK"};
    int button_size_x = 150;
    int button_size_y = size_y / 15;
    for (int i = 0; i < GENERATOR_BT_N; i++)
    {

        float button_x = result->x + 320;
        float button_y = result->y + button_size_y * i;
        if (i == GENERATOR_BT_PLUS)
        {
            result->buttons[i] = init_button(button_x, button_y, button_size_x / 4, button_size_y, i, menu_str[i], 0, i);
            i++;
            result->buttons[i] = init_button(button_x + button_size_x / 4, button_y, button_size_x / 2, button_size_y, i, menu_str[i], 0, 40);
            i++;
            result->buttons[i] = init_button(button_x + button_size_x * 3 / 4, button_y, button_size_x / 4, button_size_y, i, menu_str[i], 0, i);
            i++;
            button_y = result->y + button_size_y * i;
        }
        // result->values[i][j] = 0;
        result->buttons[i] = init_button(button_x, button_y, button_size_x, button_size_y, i, menu_str[i], 0, i);
    }
    result->buttons[GENERATOR_BT_BACKTRACKS_ITER]->board_pos_y = 0;

    result->buttons[GENERATOR_BT_PLAY] = init_button(result->x + 490, result->y, 120, button_size_y, GENERATOR_BT_PLAY, menu_str[GENERATOR_BT_PLAY], 1, 0);
    result->buttons[GENERATOR_BT_BACK] = init_button(result->x + 490, result->y + size_y / 15, 120, button_size_y, GENERATOR_BT_BACK, menu_str[GENERATOR_BT_BACK], 1, 1);
    return result;
}

void destroy_generator_menu(GENERATOR_MENU **gm)
{
    for (int i = 0; i < GENERATOR_BT_N; i++)
    {

        destroy_button(&(*gm)->buttons[i]);
    }

    free(*gm);
    *gm = NULL;
}

BUTTON *mouse_inside_generator_menu(int x, int y, GENERATOR_MENU *gm)
{
    if (x > gm->x && x < (gm->x + gm->size_x))
    {
        if (y > gm->y && y < (gm->y + gm->size_y))
        {
            for (int i = 0; i < GENERATOR_BT_N; i++)
            {

                BUTTON *b = gm->buttons[i];
                if (b)
                {
                    if (mouse_inside_button(x, y, b))
                    {
                        printf("%d\n", b->type);
                        return b;
                    }
                }
            }
        }
    }
    return 0;
}