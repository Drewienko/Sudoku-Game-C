#ifndef MAIN_MENU_H
#define MAIN_MENU_H

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
 * @brief Enum reprezentujący typy przycisków w głównym menu.
 */
enum MAIN_MENU_BT_TYPE
{
    MAIN_MENU_BT_START = 0, /**< Przycisk rozpoczęcia gry przez wybranie planszy. */
    MAIN_MENU_BT_GENERATE,  /**< Przycisk rozpoczęcia gry przez wygenerowanie planszy. */
    MAIN_MENU_BT_EXIT,      /**< Przycisk wyjścia z gry. */
    MAIN_MENU_BT_N          /**< Liczba przycisków w głównym menu. */
};

/**
 * @brief Struktura reprezentująca główne menu.
 */
typedef struct MAIN_MENU
{
    float x;                         /**< Pozycja X menu. */
    float y;                         /**< Pozycja Y menu. */
    int size_x;                      /**< Szerokość menu. */
    int size_y;                      /**< Wysokość menu. */
    BUTTON *buttons[MAIN_MENU_BT_N]; /**< Tablica przycisków w menu. */
} MAIN_MENU;

/**
 * @brief Inicjalizuje główne menu.
 *
 * @param x Pozycja X menu.
 * @param y Pozycja Y menu.
 * @param size_x Szerokość menu.
 * @param size_y Wysokość menu.
 * @return MAIN_MENU* Wskaźnik na zainicjalizowane menu.
 */
MAIN_MENU *init_main_menu(float x, float y, int size_x, int size_y);

/**
 * @brief Niszczy główne menu i zwalnia jego pamięć.
 *
 * @param mm Podwójny wskaźnik na menu do zniszczenia.
 */
void destroy_main_menu(MAIN_MENU **mm);

/**
 * @brief Sprawdza, czy myszka znajduje się wewnątrz głównego menu.
 *
 * @param x Pozycja X myszki.
 * @param y Pozycja Y myszki.
 * @param mm Wskaźnik na menu.
 * @return BUTTON* Wskaźnik na przycisk, jeśli myszka jest wewnątrz, NULL w przeciwnym razie.
 */
BUTTON *mouse_inside_main_menu(int x, int y, MAIN_MENU *mm);

#endif // MAIN_MENU_H