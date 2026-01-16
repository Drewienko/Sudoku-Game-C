#include "../include/select_menu.h"

SELECT_MENU *init_select_menu(float x, float y, int size_x, int size_y)
{
    SELECT_MENU *result = (struct SELECT_MENU *)malloc(sizeof(struct SELECT_MENU));

    result->x = x;
    result->y = y;
    result->size_x = size_x;
    result->size_y = size_y;

    read_finished("finished.dat", &result);

    int button_size_x = 120;
    int button_size_y = size_y / 15;
    char *menu_str[SELECT_BT_N + 1] = {"-10", "-100", "-1000", "+10", "+100", "+1000", "EASY", "MEDIUM", "HARD", "RANDOM", "START", "BOARD %d"};

    for (int i = 0; i < SELECT_BT_N; i++)
    {

        float button_x = result->x + 480;
        float button_y = result->y + button_size_y * i;
        // result->values[i][j] = 0;
        result->buttons[i] = init_button(button_x, button_y, button_size_x, button_size_y, i, menu_str[i], 1, i);
    }

    button_size_y = size_y / SELECT_BT_BOARDS;
    button_size_x = 90;
    for (int i = 0; i < SELECT_BT_BOARDS; i++)
    {

        float button_x = result->x + 345;
        float button_y = result->y + button_size_y * i;
        // result->values[i][j] = 0;
        result->buttons[SELECT_BT_N + i] = init_button(button_x, button_y, button_size_x, button_size_y, SELECT_BT_BOARDS, menu_str[SELECT_BT_N], 0, i + 1);
    }

    return result;
}

void destroy_select_menu(SELECT_MENU **sm)
{
    save_finished("finished.dat", sm);

    for (int i = 0; i < SELECT_BT_N + SELECT_BT_BOARDS; i++)
    {

        destroy_button(&(*sm)->buttons[i]);
    }

    free(*sm);
    *sm = NULL;
}

BUTTON *mouse_inside_select_menu(int x, int y, SELECT_MENU *sm)
{
    if (x > sm->x && x < (sm->x + sm->size_x))
    {
        if (y > sm->y && y < (sm->y + sm->size_y))
        {
            for (int i = 0; i < SELECT_BT_N + SELECT_BT_BOARDS; i++)
            {

                BUTTON *b = sm->buttons[i];
                if (mouse_inside_button(x, y, b))
                    return b;
            }
        }
    }
    return 0;
}

void update_board_bt(int x, SELECT_MENU *sm)
{

    if ((sm->buttons[23]->board_pos_y + x) > 10000)
        return;
    else if ((sm->buttons[SELECT_BT_N]->board_pos_y + x) < 1)
        return;

    for (int i = SELECT_BT_N; i < SELECT_BT_N + SELECT_BT_BOARDS; i++)
    {
        BUTTON *b = sm->buttons[i];
        b->board_pos_y += x;
    }
}

void save_finished(const char *filename, SELECT_MENU **sm)
{
    FILE *file = fopen(filename, "wb");
    if (file == NULL)
    {
        printf("Failed to open file for writing");
        return;
    }

    size_t elements_written = fwrite((*sm)->finished, sizeof(bool), 3 * 10000, file);
    if (elements_written != 3 * 10000)
    {
        printf("Failed to write all elements to file");
    }
    fclose(file);
}

void read_finished(const char *filename, SELECT_MENU **sm)
{

    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        printf("Failed to open file for reading");
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 10000; j++)
                (*sm)->finished[i][j] = false;
        return;
    }

    size_t elements_read = fread((*sm)->finished, sizeof(bool), 3 * 10000, file);
    if (elements_read != 3 * 10000)
    {
        printf("Failed to read all elements from file");
    }

    fclose(file);
}