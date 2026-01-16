#include "../include/main_menu.h"

MAIN_MENU *init_main_menu(float x, float y, int size_x, int size_y)
{
    MAIN_MENU *result = (struct MAIN_MENU *)malloc(sizeof(struct MAIN_MENU));

    result->x = x;
    result->y = y;
    result->size_x = size_x;
    result->size_y = size_y;

    int button_size_x = size_x;
    int button_size_y = size_y / 15;
    char *menu_str[MAIN_MENU_BT_N] = {"CHOOSE", "GENERATE", "EXIT"};
    for (int i = 0; i < MAIN_MENU_BT_N; i++)
    {

        float button_x = result->x;
        float button_y = result->y + button_size_y * i;
        // result->values[i][j] = 0;
        result->buttons[i] = init_button(button_x, button_y, button_size_x, button_size_y, i, menu_str[i], 0, i);
    }

    return result;
}

void destroy_main_menu(MAIN_MENU **mm)
{
    for (int i = 0; i < MAIN_MENU_BT_N; i++)
    {

        destroy_button(&(*mm)->buttons[i]);
    }
    free(*mm);
    *mm = NULL;
}

BUTTON *mouse_inside_main_menu(int x, int y, MAIN_MENU *mm)
{
    if (x > mm->x && x < (mm->x + mm->size_x))
    {
        if (y > mm->y && y < (mm->y + mm->size_y))
        {
            for (int i = 0; i < MAIN_MENU_BT_N; i++)
            {

                BUTTON *b = mm->buttons[i];
                if (mouse_inside_button(x, y, b))
                    return b;
            }
        }
    }
    return 0;
}