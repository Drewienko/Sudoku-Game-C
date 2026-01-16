#ifndef SELECT_MENU_H
#define SELECT_MENU_H

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
 * @brief Enum reprezentujący typy przycisków w menu wyboru.
 */
enum SELECT_BT_TYPE
{
    SELECT_BT_PREV10 = 0, /**< Przycisk do przejścia o 10 plansz wstecz. */
    SELECT_BT_PREV100,    /**< Przycisk do przejścia o 100 plansz wstecz. */
    SELECT_BT_PREV1000,   /**< Przycisk do przejścia o 1000 plansz wstecz. */
    SELECT_BT_NEXT10,     /**< Przycisk do przejścia o 10 plansz naprzód. */
    SELECT_BT_NEXT100,    /**< Przycisk do przejścia o 100 plansz naprzód. */
    SELECT_BT_NEXT1000,   /**< Przycisk do przejścia o 1000 plansz naprzód. */
    SELECT_BT_EASY,       /**< Przycisk wyboru łatwego poziomu trudności. */
    SELECT_BT_MEDIUM,     /**< Przycisk wyboru średniego poziomu trudności. */
    SELECT_BT_HARD,       /**< Przycisk wyboru trudnego poziomu trudności. */
    SELECT_BT_RANDOM,     /**< Przycisk wyboru losowej planszy. */
    SELECT_BT_START,      /**< Przycisk rozpoczęcia gry. */
    SELECT_BT_N,          /**< Liczba przycisków w menu wyboru. */
    SELECT_BT_BOARDS = 20 /**< Przycisk wyboru plansz. */
};

/**
 * @brief Struktura reprezentująca menu wyboru.
 */
typedef struct SELECT_MENU
{
    float x;                                         /**< Pozycja X menu. */
    float y;                                         /**< Pozycja Y menu. */
    int size_x;                                      /**< Szerokość menu. */
    int size_y;                                      /**< Wysokość menu. */
    BUTTON *buttons[SELECT_BT_N + SELECT_BT_BOARDS]; /**< Tablica przycisków w menu. */
    bool finished[3][10000];                         /**< Tablica ukończonych plansz dla różnych poziomów trudności. */
    // int values[9][9];
} SELECT_MENU;

/**
 * @brief Inicjalizuje menu wyboru.
 *
 * @param x Pozycja X menu.
 * @param y Pozycja Y menu.
 * @param size_x Szerokość menu.
 * @param size_y Wysokość menu.
 * @return SELECT_MENU* Wskaźnik na zainicjalizowane menu.
 */
SELECT_MENU *init_select_menu(float x, float y, int size_x, int size_y);

/**
 * @brief Niszczy menu wyboru i zwalnia jego pamięć.
 *
 * @param mm Podwójny wskaźnik na menu do zniszczenia.
 */
void destroy_select_menu(SELECT_MENU **mm);

/**
 * @brief Sprawdza, czy myszka znajduje się wewnątrz menu wyboru.
 *
 * @param x Pozycja X myszki.
 * @param y Pozycja Y myszki.
 * @param mm Wskaźnik na menu.
 * @return BUTTON* Wskaźnik na przycisk, jeśli myszka jest wewnątrz, NULL w przeciwnym razie.
 */
BUTTON *mouse_inside_select_menu(int x, int y, SELECT_MENU *mm);

/**
 * @brief Aktualizuje przyciski plansz w menu wyboru.
 *
 * @param x Indeks planszy.
 * @param sm Wskaźnik na menu wyboru.
 */
void update_board_bt(int x, SELECT_MENU *sm);

/**
 * @brief Odczytuje ukończone plansze z pliku.
 *
 * @param filename Nazwa pliku do odczytu.
 * @param sm Podwójny wskaźnik na menu wyboru.
 */
void read_finished(const char *filename, SELECT_MENU **sm);

/**
 * @brief Zapisuje ukończone plansze do pliku.
 *
 * @param filename Nazwa pliku do zapisu.
 * @param sm Podwójny wskaźnik na menu wyboru.
 */
void save_finished(const char *filename, SELECT_MENU **sm);

#endif // SELECT_MENU_H
