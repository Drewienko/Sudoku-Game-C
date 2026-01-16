#ifndef BUTTON_H
#define BUTTON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

/**
 * @brief Struktura reprezentująca przycisk.
 */
typedef struct BUTTON
{
    float x;         /**< Pozycja X przycisku. */
    float y;         /**< Pozycja Y przycisku. */
    int size_x;      /**< Szerokość przycisku. */
    int size_y;      /**< Wysokość przycisku. */
    int type;        /**< Typ przycisku. */
    int board_pos_x; /**< Pozycja X na planszy. */
    int board_pos_y; /**< Pozycja Y na planszy. */
    char *text;      /**< Tekst wyświetlany na przycisku. */
} BUTTON;

/**
 * @brief Inicjalizuje przycisk.
 *
 * @param x Pozycja X przycisku.
 * @param y Pozycja Y przycisku.
 * @param size_x Szerokość przycisku.
 * @param size_y Wysokość przycisku.
 * @param type Typ przycisku.
 * @param s Tekst wyświetlany na przycisku.
 * @param board_pos_x Pozycja X na planszy.
 * @param board_pos_y Pozycja Y na planszy.
 * @return BUTTON* Wskaźnik na zainicjalizowany przycisk.
 */
BUTTON *init_button(float x, float y, int size_x, int size_y, int type, char *s, int board_pos_x, int board_pos_y);

/**
 * @brief Niszczy przycisk i zwalnia jego pamięć.
 *
 * @param b Podwójny wskaźnik na przycisk do zniszczenia.
 */
void destroy_button(BUTTON **b);

/**
 * @brief Sprawdza, czy myszka znajduje się wewnątrz przycisku.
 *
 * @param x Pozycja X myszki.
 * @param y Pozycja Y myszki.
 * @param b Wskaźnik na przycisk.
 * @return true Jeśli myszka jest wewnątrz przycisku.
 * @return false Jeśli myszka nie jest wewnątrz przycisku.
 */
bool mouse_inside_button(int x, int y, BUTTON *b);

#endif // BUTTON_H
