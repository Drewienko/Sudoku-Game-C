#include "../include/sudoku.h"

bool check_ans_sq(BOARD *sb, char key_value, BUTTON *b)
{
    int start_x = b->board_pos_x / 3 * 3;
    int start_y = b->board_pos_y / 3 * 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            BUTTON *tmp = sb->buttons[start_x + i][start_y + j];
            if (tmp != b && tmp->text[0] == key_value)
                return false;
        }
    }
    return true;
}

bool check_ans_hor(BOARD *sb, char key_value, BUTTON *b)
{
    for (int i = 0; i < 9; i++)
    {
        BUTTON *tmp = sb->buttons[b->board_pos_x][i];
        if (tmp != b && tmp->text[0] == key_value)
            return false;
    }
    return true;
}

bool check_ans_ver(BOARD *sb, char key_value, BUTTON *b)
{
    for (int i = 0; i < 9; i++)
    {
        BUTTON *tmp = sb->buttons[i][b->board_pos_y];
        if (tmp != b && tmp->text[0] == key_value)
            return false;
    }
    return true;
}

bool check_ans(BOARD *sb, char key_value, BUTTON *b)
{
    if (b->text[0] == key_value)
    {
        return false;
    }

    bool result = check_ans_sq(sb, key_value, b);
    result = result && check_ans_ver(sb, key_value, b);
    result = result && check_ans_hor(sb, key_value, b);
    return result;
}

void move_push(move **list, int board_pos_x, int board_pos_y)
{
    move *p;
    p = (struct move *)malloc(sizeof(struct move));
    p->board_pos_x = board_pos_x;
    p->board_pos_y = board_pos_y;
    if (*list == 0)
    {
        *list = p;
        p->next = p;
    }
    else
    {
        p->next = (*list);
        (*list) = p;
    }
}

void move_pop(move **list)
{
    move *p;
    if (*list == 0)
        return;
    if (*list == (*list)->next)
    {
        free(*list);
        *list = NULL;
    }
    else
    {
        p = *list;
        (*list) = (*list)->next;
        free(p);
    }
}

void destroy_move(move **list)
{
    while (*list)
        move_pop(list);
}

char *read_puzzle(int BT_TYPE, int board_nr, char *result_ans)
{
    ALLEGRO_FILE *file;
    const int MAX_PUZZLE_NR = 10000;
    const int MAX_BUFFER = 200;
    char *buffer = (char *)malloc(MAX_BUFFER * sizeof(char));
    char *result = (char *)malloc(82 * sizeof(char));
    switch (BT_TYPE)
    {
    case GAME_BT_EASY:
        file = al_fopen("./puzzles/Easy.json", "r");
        break;
    case GAME_BT_MEDIUM:
        file = al_fopen("./puzzles/Medium.json", "r");
        break;
    case GAME_BT_HARD:
        file = al_fopen("./puzzles/Hard.json", "r");
        break;
    }

    if (file)
    {
        printf("debug file open\n");
        srand(time(NULL));
        int puzzle_nr = board_nr;
        while (puzzle_nr--)
        {
            for (int i = 0; i < 4; i++)
            {
                buffer = al_fgets(file, buffer, MAX_BUFFER * sizeof(char));
            }
        }

        char *tmp = strrchr(buffer, '"');
        tmp -= 81;
        strncpy(result, tmp, 81);
        result[81] = '\0';
        buffer = al_fgets(file, buffer, MAX_BUFFER * sizeof(char));
        tmp = strrchr(buffer, '"');
        tmp -= 81;
        strncpy(result_ans, tmp, 81);
        result_ans[81] = '\0';
    }
    al_fclose(file);
    free(buffer);
    printf("%s\n%s\n", result, result_ans);
    return result;
}

void suggest_next_move(BOARD *sb, move **list)
{
    printf("debug_hint");
    // Szukamy pierwszej pustej komórki na planszy
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            BUTTON *b = sb->buttons[j][i];
            if (b->text[0] == '0')
            {
                b->text[0] = sb->ans[i * 9 + j];
                move_push(list, j, i);
                return;
            }
        }
    }
}

void save_board_state(BOARD *board, move **list, const char *filename)
{
    FILE *file = fopen(filename, "wb");
    if (file == NULL)
    {
        printf("Failed to open file for writing\n");
        return;
    }

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            board->board_[i * 9 + j] = board->buttons[j][i]->text[0];

    fwrite(&board->difficulty, sizeof(int), 1, file);
    fwrite(&board->board_nr, sizeof(int), 1, file);
    fwrite(board->board_, sizeof(char), 82, file);
    fwrite(board->ans, sizeof(char), 82, file);
    struct move *current = 0;
    while ((*list) != NULL)
    {
        fwrite((*list), sizeof(move), 1, file);
        move_push(&current, (*list)->board_pos_x, (*list)->board_pos_y);
        move_pop(list);
    }

    while (current != NULL)
    {
        move_push(list, current->board_pos_x, current->board_pos_y);
        move_pop(&current);
    }

    fclose(file);
}

void load_board_state(BOARD **board, move **list, const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        printf("Failed to open file for reading");
        return;
    }

    fread(&(*board)->difficulty, sizeof(int), 1, file);
    fread(&(*board)->board_nr, sizeof(int), 1, file);
    fread((*board)->board_, sizeof(char), 82, file);
    fread((*board)->ans, sizeof(char), 82, file);

    load_board(*board, (*board)->board_);

    move *temp_stack = NULL;
    move temp;
    while (fread(&temp, sizeof(move), 1, file))
    {
        move_push(&temp_stack, temp.board_pos_x, temp.board_pos_y);
    }

    while (temp_stack != NULL)
    {
        move_push(list, temp_stack->board_pos_x, temp_stack->board_pos_y);
        move_pop(&temp_stack);
    }

    fclose(file);
    return;
}