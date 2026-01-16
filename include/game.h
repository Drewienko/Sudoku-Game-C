#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include "../include/button.h"

/**
 * @brief Enum reprezentujący stan planszy.
 */
enum STATE_BOARD
{
    STATE_B_EMPTY = 0, /**< Plansza jest pusta. */
    STATE_B_PLAYING,   /**< Gra jest w toku. */
    STATE_B_DONE       /**< Gra jest zakończona. */
};

/**
 * @brief Struktura reprezentująca planszę gry.
 */
typedef struct BOARD
{
    int difficulty;        /**< Poziom trudności planszy. */
    int board_nr;          /**< Identyfikator planszy. */
    float x;               /**< Pozycja X planszy. */
    float y;               /**< Pozycja Y planszy. */
    int size_x;            /**< Szerokość planszy. */
    int size_y;            /**< Wysokość planszy. */
    BUTTON *buttons[9][9]; /**< Dwuwymiarowa tablica przycisków na planszy. */
    char board_[82];       /**< Aktualny stan planszy. */
    char ans[82];          /**< Rozwiązanie planszy. */
    int b_state;           /**< Stan planszy. */
} BOARD;

/**
 * @brief Inicjalizuje planszę gry.
 *
 * @param x Pozycja X planszy.
 * @param y Pozycja Y planszy.
 * @param size_x Szerokość planszy.
 * @param size_y Wysokość planszy.
 * @param difficulty Poziom trudności planszy.
 * @return BOARD* Wskaźnik na zainicjalizowaną planszę.
 */
BOARD *init_board(float x, float y, int size_x, int size_y, int difficulty);

/**
 * @brief Niszczy planszę gry i zwalnia jej pamięć.
 *
 * @param sb Podwójny wskaźnik na planszę do zniszczenia.
 */
void destroy_board(BOARD **sb);

/**
 * @brief Ładuje planszę gry z ciągu CSV.
 *
 * @param sb Wskaźnik na planszę.
 * @param str_csv Ciąg CSV zawierający dane planszy.
 */
void load_board(BOARD *sb, char *str_csv);

/**
 * @brief Sprawdza, czy myszka znajduje się wewnątrz planszy.
 *
 * @param x Pozycja X myszki.
 * @param y Pozycja Y myszki.
 * @param b Wskaźnik na planszę.
 * @return BUTTON* Wskaźnik na przycisk, jeśli myszka jest wewnątrz, NULL w przeciwnym razie.
 */
BUTTON *mouse_inside_board(int x, int y, BOARD *b);

/**
 * @brief Zmienia rozmiar planszy gry.
 *
 * @param size_x Nowa szerokość planszy.
 * @param size_y Nowa wysokość planszy.
 * @param sb Wskaźnik na planszę.
 */
void resize_board(int size_x, int size_y, BOARD *sb);

/**
 * @brief Sprawdza aktualny stan planszy.
 *
 * @param sb Wskaźnik na planszę.
 * @return int Kod statusu wskazujący stan planszy.
 */
int check_board(BOARD *sb);

/**
 * @brief Resetuje planszę gry do jej początkowego stanu.
 *
 * @param sb Wskaźnik na planszę.
 */
void reset_board(BOARD *sb);

/**
 * @brief Enum reprezentujący typy przycisków gry.
 */
enum GAME_BT_TYPE
{
    GAME_BT_BOARD = -1, /**< Przycisk planszy gry. */
    GAME_BT_EASY = 0,   /**< Przycisk dla łatwego poziomu trudności. */
    GAME_BT_MEDIUM,     /**< Przycisk dla średniego poziomu trudności. */
    GAME_BT_HARD,       /**< Przycisk dla trudnego poziomu trudności. */
    GAME_BT_UNDO,       /**< Przycisk cofania akcji. */
    GAME_BT_HINT,       /**< Przycisk podpowiedzi. */
    GAME_BT_SAVE,       /**< Przycisk zapisu gry. */
    GAME_BT_LOAD,       /**< Przycisk wczytania gry. */
    GAME_BT_N           /**< Liczba przycisków gry. */
};

/**
 * @brief Struktura reprezentująca menu gry.
 */
typedef struct GAME_MENU
{
    float x;                    /**< Pozycja X menu. */
    float y;                    /**< Pozycja Y menu. */
    int size_x;                 /**< Szerokość menu. */
    int size_y;                 /**< Wysokość menu. */
    BUTTON *buttons[GAME_BT_N]; /**< Tablica przycisków w menu. */
} GAME_MENU;

/**
 * @brief Inicjalizuje menu gry.
 *
 * @param x Pozycja X menu.
 * @param y Pozycja Y menu.
 * @param size_x Szerokość menu.
 * @param size_y Wysokość menu.
 * @return GAME_MENU* Wskaźnik na zainicjalizowane menu.
 */
GAME_MENU *init_game_menu(float x, float y, int size_x, int size_y);

/**
 * @brief Niszczy menu gry i zwalnia jego pamięć.
 *
 * @param mb Podwójny wskaźnik na menu do zniszczenia.
 */
void destroy_game_menu(GAME_MENU **mb);

/**
 * @brief Sprawdza, czy myszka znajduje się wewnątrz menu gry.
 *
 * @param x Pozycja X myszki.
 * @param y Pozycja Y myszki.
 * @param sb Wskaźnik na menu.
 * @return BUTTON* Wskaźnik na przycisk, jeśli myszka jest wewnątrz, NULL w przeciwnym razie.
 */
BUTTON *mouse_inside_game_menu(int x, int y, GAME_MENU *sb);

/**
 * @brief Enum reprezentujący typy przycisków menu zakończenia gry.
 */
enum DONE_BT_TYPE
{
    DONE_BT_MAIN_MENU = 0, /**< Przycisk powrotu do głównego menu. */
    DONE_BT_N              /**< Liczba przycisków menu zakończenia gry. */
};

/**
 * @brief Struktura reprezentująca menu zakończenia gry.
 */
typedef struct DONE_MENU
{
    float x;                    /**< Pozycja X menu. */
    float y;                    /**< Pozycja Y menu. */
    int size_x;                 /**< Szerokość menu. */
    int size_y;                 /**< Wysokość menu. */
    BUTTON *buttons[DONE_BT_N]; /**< Tablica przycisków w menu. */
} DONE_MENU;

/**
 * @brief Inicjalizuje menu zakończenia gry.
 *
 * @param x Pozycja X menu.
 * @param y Pozycja Y menu.
 * @param size_x Szerokość menu.
 * @param size_y Wysokość menu.
 * @return DONE_MENU* Wskaźnik na zainicjalizowane menu.
 */
DONE_MENU *init_done_menu(float x, float y, int size_x, int size_y);

/**
 * @brief Niszczy menu zakończenia gry i zwalnia jego pamięć.
 *
 * @param dm Podwójny wskaźnik na menu do zniszczenia.
 */
void destroy_done_menu(DONE_MENU **dm);

/**
 * @brief Sprawdza, czy myszka znajduje się wewnątrz menu zakończenia gry.
 *
 * @param x Pozycja X myszki.
 * @param y Pozycja Y myszki.
 * @param sb Wskaźnik na menu.
 * @return BUTTON* Wskaźnik na przycisk, jeśli myszka jest wewnątrz, NULL w przeciwnym razie.
 */
BUTTON *mouse_inside_done_menu(int x, int y, DONE_MENU *sb);

#endif // GAME_H
