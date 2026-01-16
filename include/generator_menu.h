#ifndef GENERATOR_MENU_H
#define GENERATOR_MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include "../include/button.h"
#include "../include/generator.h"

/**
 * @brief Enum reprezentujący typy przycisków menu generatora.
 */
enum GENERATOR_BT_TYPE
{
    GENERATOR_BT_EASY = 0,        /**< Przycisk dla łatwego poziomu trudności. */
    GENERATOR_BT_MEDIUM,          /**< Przycisk dla średniego poziomu trudności. */
    GENERATOR_BT_HARD,            /**< Przycisk dla trudnego poziomu trudności. */
    GENERATOR_BT_CUSTOM,          /**< Przycisk dla niestandardowego poziomu trudności. */
    GENERATOR_BT_EMPTY,           /**< Przycisk do wyświetlania tekstu. */
    GENERATOR_BT_BOXES,           /**< Przycisk do wyświetlania tekstu. */
    GENERATOR_BT_PLUS,            /**< Przycisk do zwiększania wartości wolnych pól. */
    GENERATOR_BT_ITER,            /**< Przycisk do iteracji wolnych pól. */
    GENERATOR_BT_MINUS,           /**< Przycisk do zmniejszania wartości wolnych pól. */
    GENERATOR_BT_GENERATE,        /**< Przycisk do generowania planszy. */
    GENERATOR_BT_BACKTRACKS,      /**< Przycisk do cofania ruchów. */
    GENERATOR_BT_BACKTRACKS_ITER, /**< Przycisk do iteracyjnego cofania ruchów. */
    GENERATOR_BT_PLAY,            /**< Przycisk do rozpoczęcia gry. */
    GENERATOR_BT_BACK,            /**< Przycisk do powrotu. */
    GENERATOR_BT_N                /**< Liczba przycisków w menu generatora. */
};

/**
 * @brief Struktura reprezentująca menu generatora.
 */
typedef struct GENERATOR_MENU
{
    float x;                         /**< Pozycja X menu. */
    float y;                         /**< Pozycja Y menu. */
    int size_x;                      /**< Szerokość menu. */
    int size_y;                      /**< Wysokość menu. */
    BUTTON *buttons[GENERATOR_BT_N]; /**< Tablica przycisków w menu. */
    // int values[9][9];
} GENERATOR_MENU;

/**
 * @brief Inicjalizuje menu generatora.
 *
 * @param x Pozycja X menu.
 * @param y Pozycja Y menu.
 * @param size_x Szerokość menu.
 * @param size_y Wysokość menu.
 * @return GENERATOR_MENU* Wskaźnik na zainicjalizowane menu.
 */
GENERATOR_MENU *init_generator_menu(float x, float y, int size_x, int size_y);

/**
 * @brief Niszczy menu generatora i zwalnia jego pamięć.
 *
 * @param gm Podwójny wskaźnik na menu do zniszczenia.
 */
void destroy_generator_menu(GENERATOR_MENU **gm);

/**
 * @brief Sprawdza, czy myszka znajduje się wewnątrz menu generatora.
 *
 * @param x Pozycja X myszki.
 * @param y Pozycja Y myszki.
 * @param gm Wskaźnik na menu.
 * @return BUTTON* Wskaźnik na przycisk, jeśli myszka jest wewnątrz, NULL w przeciwnym razie.
 */
BUTTON *mouse_inside_generator_menu(int x, int y, GENERATOR_MENU *gm);

#endif // GENERATOR_MENU_H
