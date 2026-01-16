#include "../include/generator.h"

void generate_sudoku(Sudoku *sudoku, int holes)
{
    int attempts = 0;
    bool success = false;

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            sudoku->board[i][j] = 0;
        }
    }

    while (!success && attempts < MAX_ATTEMPTS)
    {
        attempts++;
        fill_diagonal_boxes(sudoku->board);
        fill_remaining(sudoku->board, 0, 3);
        remove_numbers(sudoku->board, holes);

        if (has_unique_solution(sudoku->board))
        {
            success = true;
        }
        else
        {
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    sudoku->board[i][j] = 0;
                }
            }
        }
    }

    if (attempts == MAX_ATTEMPTS)
    {
        printf("Failed to generate a puzzle with unique solution in %d attempts.\n", MAX_ATTEMPTS);
        exit(EXIT_FAILURE);
    }
}

void fill_diagonal_boxes(int board[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i += 3)
    {
        fill_box(board, i, i);
    }
}

void fill_box(int board[SIZE][SIZE], int row, int col)
{
    int num;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            do
            {
                num = random_number();
            } while (!is_valid(board, row + i, col + j, num));
            board[row + i][col + j] = num;
        }
    }
}

int random_number()
{
    return rand() % SIZE + 1;
}

bool is_valid(int board[SIZE][SIZE], int row, int col, int num)
{
    for (int x = 0; x < SIZE; x++)
    {
        if (board[row][x] == num || board[x][col] == num)
        {
            return false;
        }
    }
    int start_row = row - row % 3;
    int start_col = col - col % 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i + start_row][j + start_col] == num)
            {
                return false;
            }
        }
    }
    return true;
}

bool solve_sudoku(Sudoku *sudoku, int depth)
{
    printf("%d\n", depth);
    if (depth > MAX_RECURSION_DEPTH)
    {
        return false;
    }

    int row = -1;
    int col = -1;
    bool is_empty = true;
    for (int i = 0; i < SIZE && is_empty; i++)
    {
        for (int j = 0; j < SIZE && is_empty; j++)
        {
            if (sudoku->board[i][j] == 0)
            {
                row = i;
                col = j;
                is_empty = false;
            }
        }
    }
    if (is_empty)
    {
        return true;
    }
    for (int num = 1; num <= SIZE; num++)
    {
        if (is_valid(sudoku->board, row, col, num))
        {
            sudoku->board[row][col] = num;
            if (solve_sudoku(sudoku, depth + 1))
            {
                return true;
            }
            sudoku->board[row][col] = 0;
            sudoku->backtracks++;
        }
    }
    return false;
}

bool count_solutions(int board[SIZE][SIZE], int *count)
{
    int row = -1;
    int col = -1;
    bool is_empty = true;
    for (int i = 0; i < SIZE && is_empty; i++)
    {
        for (int j = 0; j < SIZE && is_empty; j++)
        {
            if (board[i][j] == 0)
            {
                row = i;
                col = j;
                is_empty = false;
            }
        }
    }
    if (is_empty)
    {
        (*count)++;
        return (*count > 1);
    }
    for (int num = 1; num <= SIZE; num++)
    {
        if (is_valid(board, row, col, num))
        {
            board[row][col] = num;
            if (count_solutions(board, count))
            {
                board[row][col] = 0;
                return true;
            }
            board[row][col] = 0;
        }
    }
    return false;
}

bool has_unique_solution(int board[SIZE][SIZE])
{
    int count = 0;
    int board_copy[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board_copy[i][j] = board[i][j];
        }
    }
    count_solutions(board_copy, &count);
    return count == 1;
}

bool fill_remaining(int board[SIZE][SIZE], int i, int j)
{
    if (j >= SIZE)
    {
        i = i + 1;
        j = 0;
    }
    if (i >= SIZE)
    {
        return true;
    }
    if (i < 3)
    {
        if (j < 3)
        {
            j = 3;
        }
    }
    else if (i < SIZE - 3)
    {
        if (j == (i / 3) * 3)
        {
            j = j + 3;
        }
    }
    else
    {
        if (j == SIZE - 3)
        {
            i = i + 1;
            j = 0;
            if (i >= SIZE)
            {
                return true;
            }
        }
    }
    for (int num = 1; num <= SIZE; num++)
    {
        if (is_valid(board, i, j, num))
        {
            board[i][j] = num;
            if (fill_remaining(board, i, j + 1))
            {
                return true;
            }
            board[i][j] = 0;
        }
    }
    return false;
}

void remove_numbers(int board[SIZE][SIZE], int holes)
{
    int count = holes;
    while (count != 0)
    {
        int cell_id = rand() % (SIZE * SIZE);
        int i = cell_id / SIZE;
        int j = cell_id % SIZE;
        if (board[i][j] != 0)
        {
            int temp = board[i][j];
            board[i][j] = 0;
            if (!has_unique_solution(board))
            {
                board[i][j] = temp;
            }
            else
            {
                count--;
            }
        }
    }
}

void debug_print_board(int board[SIZE][SIZE])
{
    for (int r = 0; r < SIZE; r++)
    {
        for (int d = 0; d < SIZE; d++)
        {
            printf("%d ", board[r][d]);
        }
        printf("\n");
    }
    printf("\n");
}

char *sudoku_to_json_str(Sudoku *sudoku)
{
    char *result = (char *)malloc(82 * sizeof(char));
    for (int r = 0; r < SIZE; r++)
    {
        for (int d = 0; d < SIZE; d++)
        {
            if (sudoku->board[r][d] == 0)
                result[r * SIZE + d] = '.';
            else
                result[r * SIZE + d] = sudoku->board[r][d] + '0';
        }
    }
    result[81] = '\0';
    return result;
}

int load_random_board(BOARD *sb, int holes)
{
    Sudoku tmp;
    generate_sudoku(&tmp, holes);

    char *sudoku_str = sudoku_to_json_str(&tmp);
    load_board(sb, sudoku_str);
    free(sudoku_str);

    tmp.backtracks = 0;
    solve_sudoku(&tmp, 0);

    char *solution_str = sudoku_to_json_str(&tmp);
    strcpy(sb->ans, solution_str);
    free(solution_str);

    return tmp.backtracks;
}