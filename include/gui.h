#ifndef GUI_H
#define GUI_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include "../include/button.h"
#include "../include/game.h"
#include "../include/main_menu.h"
#include "../include/select_menu.h"
#include "../include/generator_menu.h"

/**
 * @brief Sprawdza, czy inicjalizacja zakończyła się powodzeniem.
 *
 * @param test Warunek do sprawdzenia.
 * @param description Opis inicjalizacji.
 */
void must_init(bool test, const char *description);

/**
 * @brief Rysuje przycisk na ekranie.
 *
 * @param b Wskaźnik na przycisk do narysowania.
 * @param font Czcionka do rysowania tekstu.
 * @param color Kolor tekstu.
 * @param thickness Grubość linii.
 */
void draw_button(BUTTON *b, ALLEGRO_FONT *font, ALLEGRO_COLOR color, float thickness);

/**
 * @brief Rysuje główne menu na ekranie.
 *
 * @param mm Wskaźnik na główne menu.
 * @param b Wskaźnik na przycisk.
 * @param font Czcionka do rysowania tekstu.
 * @param font2 Druga czcionka do rysowania tekstu.
 */
void draw_main_menu(MAIN_MENU *mm, BUTTON *b, ALLEGRO_FONT *font, ALLEGRO_FONT *font2);

/**
 * @brief Rysuje grę na ekranie.
 *
 * @param sb Wskaźnik na planszę gry.
 * @param dm Wskaźnik na menu zakończenia gry.
 * @param mb Wskaźnik na menu gry.
 * @param b Wskaźnik na przycisk.
 * @param font Czcionka do rysowania tekstu.
 * @param font2 Druga czcionka do rysowania tekstu.
 * @param font3 Trzecia czcionka do rysowania tekstu.
 */
void draw_game(BOARD *sb, DONE_MENU *dm, GAME_MENU *mb, BUTTON *b, ALLEGRO_FONT *font, ALLEGRO_FONT *font2, ALLEGRO_FONT *font3);

/**
 * @brief Rysuje menu wyboru na ekranie.
 *
 * @param sb Wskaźnik na planszę gry.
 * @param sm Wskaźnik na menu wyboru.
 * @param b Wskaźnik na przycisk.
 * @param font Czcionka do rysowania tekstu.
 * @param font2 Druga czcionka do rysowania tekstu.
 */
void draw_select_menu(BOARD *sb, SELECT_MENU *sm, BUTTON *b, ALLEGRO_FONT *font, ALLEGRO_FONT *font2);

/**
 * @brief Rysuje menu generatora na ekranie.
 *
 * @param sb Wskaźnik na planszę gry.
 * @param gm Wskaźnik na menu generatora.
 * @param b Wskaźnik na przycisk.
 * @param font Czcionka do rysowania tekstu.
 * @param font2 Druga czcionka do rysowania tekstu.
 */
void draw_generator_menu(BOARD *sb, GENERATOR_MENU *gm, BUTTON *b, ALLEGRO_FONT *font, ALLEGRO_FONT *font2);

#endif // GUI_H
