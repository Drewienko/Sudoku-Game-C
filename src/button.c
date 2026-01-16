#include "../include/button.h"

BUTTON *init_button(float x, float y, int size_x, int size_y, int type, char *s, int board_pos_x, int board_pos_y)
{
    BUTTON *result = (struct BUTTON *)malloc(sizeof(struct BUTTON));
    result->x = x;
    result->y = y;
    result->size_x = size_x;
    result->size_y = size_y;
    result->board_pos_x = board_pos_x;
    result->board_pos_y = board_pos_y;
    result->type = type;

    result->text = (char *)malloc(100 * sizeof(char));
    strcpy(result->text, s);

    return result;
}

void destroy_button(BUTTON **b)
{
    free((*b)->text);
    free(*b);
    *b = NULL;
}

bool mouse_inside_button(int x, int y, BUTTON *b)
{
    if (x > b->x && x < (b->x + b->size_x))
        if (y > b->y && y < (b->y + b->size_y))
            return true;
    return false;
}