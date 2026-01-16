#ifndef SUDOKU_H
#define SUDOKU_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "../include/game.h"

/**
 * @brief Sprawdza poprawność wartości w kwadracie planszy.
 *
 * @param sb Wskaźnik na planszę.
 * @param key_value Wartość do sprawdzenia.
 * @param b Wskaźnik na przycisk.
 * @return true Jeśli wartość jest poprawna.
 * @return false Jeśli wartość nie jest poprawna.
 */
bool check_ans_sq(BOARD *sb, char key_value, BUTTON *b);

/**
 * @brief Sprawdza poprawność wartości w wierszu planszy.
 *
 * @param sb Wskaźnik na planszę.
 * @param key_value Wartość do sprawdzenia.
 * @param b Wskaźnik na przycisk.
 * @return true Jeśli wartość jest poprawna.
 * @return false Jeśli wartość nie jest poprawna.
 */
bool check_ans_hor(BOARD *sb, char key_value, BUTTON *b);

/**
 * @brief Sprawdza poprawność wartości w kolumnie planszy.
 *
 * @param sb Wskaźnik na planszę.
 * @param key_value Wartość do sprawdzenia.
 * @param b Wskaźnik na przycisk.
 * @return true Jeśli wartość jest poprawna.
 * @return false Jeśli wartość nie jest poprawna.
 */
bool check_ans_ver(BOARD *sb, char key_value, BUTTON *b);

/**
 * @brief Sprawdza poprawność wartości na planszy.
 *
 * @param sb Wskaźnik na planszę.
 * @param key_value Wartość do sprawdzenia.
 * @param b Wskaźnik na przycisk.
 * @return true Jeśli wartość jest poprawna.
 * @return false Jeśli wartość nie jest poprawna.
 */
bool check_ans(BOARD *sb, char key_value, BUTTON *b);

/**
 * @brief Struktura reprezentująca ruch w grze.
 */
typedef struct move
{
    int board_pos_x;   /**< Pozycja X na planszy. */
    int board_pos_y;   /**< Pozycja Y na planszy. */
    struct move *next; /**< Wskaźnik na następny ruch. */
} move;

/**
 * @brief Dodaje ruch do listy ruchów.
 *
 * @param list Podwójny wskaźnik na listę ruchów.
 * @param board_pos_x Pozycja X na planszy.
 * @param board_pos_y Pozycja Y na planszy.
 */
void move_push(move **list, int board_pos_x, int board_pos_y);

/**
 * @brief Usuwa ostatni ruch z listy ruchów.
 *
 * @param list Podwójny wskaźnik na listę ruchów.
 */
void move_pop(move **list);

/**
 * @brief Niszczy listę ruchów i zwalnia jej pamięć.
 *
 * @param list Podwójny wskaźnik na listę ruchów.
 */
void destroy_move(move **list);

/**
 * @brief Odczytuje łamigłówkę sudoku.
 *
 * @param BT_TYPE Typ przycisku.
 * @param board_nr Numer planszy.
 * @param result_ans Wynik odpowiedzi.
 * @return char* Ciąg znaków reprezentujący łamigłówkę.
 */
char *read_puzzle(int BT_TYPE, int board_nr, char *result_ans);

/**
 * @brief Sugestia następnego ruchu.
 *
 * @param sb Wskaźnik na planszę.
 * @param list Podwójny wskaźnik na listę ruchów.
 */
void suggest_next_move(BOARD *sb, move **list);

/**
 * @brief Zapisuje stan planszy do pliku.
 *
 * @param board Wskaźnik na planszę.
 * @param list Podwójny wskaźnik na listę ruchów.
 * @param filename Nazwa pliku do zapisu.
 */
void save_board_state(BOARD *board, move **list, const char *filename);

/**
 * @brief Ładuje stan planszy z pliku.
 *
 * @param board Podwójny wskaźnik na planszę.
 * @param list Podwójny wskaźnik na listę ruchów.
 * @param filename Nazwa pliku do odczytu.
 */
void load_board_state(BOARD **board, move **list, const char *filename);

#endif // SUDOKU_H
