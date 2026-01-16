#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "../include/game.h"

#define SIZE 9
#define MAX_ATTEMPTS 1000
#define MAX_RECURSION_DEPTH 81

/**
 * @brief Struktura reprezentująca planszę sudoku.
 */
typedef struct Sudoku {
  int board[SIZE][SIZE]; /**< Plansza sudoku. */
  int backtracks;        /**< Liczba cofnięć w algorytmie rozwiązującym. */
} Sudoku;

/**
 * @brief Sprawdza, czy liczba może być umieszczona w danym miejscu planszy.
 *
 * @param board Plansza sudoku.
 * @param row Wiersz.
 * @param col Kolumna.
 * @param num Liczba do umieszczenia.
 * @return true Jeśli liczba może być umieszczona.
 * @return false Jeśli liczba nie może być umieszczona.
 */
bool is_valid(int board[SIZE][SIZE], int row, int col, int num);

/**
 * @brief Rozwiązuje planszę sudoku.
 *
 * @param sudoku Wskaźnik na strukturę Sudoku.
 * @param depth Głębokość rekurencji.
 * @return true Jeśli udało się rozwiązać sudoku.
 * @return false Jeśli nie udało się rozwiązać sudoku.
 */
bool solve_sudoku(Sudoku *sudoku, int depth);

/**
 * @brief Liczy liczbę rozwiązań planszy sudoku.
 *
 * @param board Plansza sudoku.
 * @param count Wskaźnik na licznik rozwiązań.
 * @return true Jeśli udało się znaleźć rozwiązania.
 * @return false Jeśli nie udało się znaleźć rozwiązania.
 */
bool count_solutions(int board[SIZE][SIZE], int *count);

/**
 * @brief Sprawdza, czy plansza sudoku ma unikalne rozwiązanie.
 *
 * @param board Plansza sudoku.
 * @return true Jeśli plansza ma unikalne rozwiązanie.
 * @return false Jeśli plansza nie ma unikalnego rozwiązania.
 */
bool has_unique_solution(int board[SIZE][SIZE]);

/**
 * @brief Wypisuje planszę sudoku na standardowe wyjście.
 *
 * @param board Plansza sudoku.
 */
void print_board(int board[SIZE][SIZE]);

/**
 * @brief Usuwa liczby z planszy sudoku, aby utworzyć łamigłówkę.
 *
 * @param board Plansza sudoku.
 * @param holes Liczba pól do usunięcia.
 */
void remove_numbers(int board[SIZE][SIZE], int holes);

/**
 * @brief Wypełnia przekątne bloki 3x3 na planszy sudoku.
 *
 * @param board Plansza sudoku.
 */
void fill_diagonal_boxes(int board[SIZE][SIZE]);

/**
 * @brief Wypełnia pozostałe pola na planszy sudoku.
 *
 * @param board Plansza sudoku.
 * @param i Wiersz początkowy.
 * @param j Kolumna początkowa.
 * @return true Jeśli udało się wypełnić planszę.
 * @return false Jeśli nie udało się wypełnić planszy.
 */
bool fill_remaining(int board[SIZE][SIZE], int i, int j);

/**
 * @brief Wypełnia blok 3x3 na planszy sudoku.
 *
 * @param board Plansza sudoku.
 * @param row Wiersz początkowy.
 * @param col Kolumna początkowa.
 */
void fill_box(int board[SIZE][SIZE], int row, int col);

/**
 * @brief Generuje losową liczbę.
 *
 * @return int Losowa liczba.
 */
int random_number();

/**
 * @brief Konwertuje planszę sudoku na ciąg JSON.
 *
 * @param sudoku Wskaźnik na strukturę Sudoku.
 * @return char* Ciąg JSON reprezentujący planszę sudoku.
 */
char *sudoku_to_json_str(Sudoku *sudoku);

/**
 * @brief Ładuje losową planszę sudoku do struktury BOARD.
 *
 * @param sb Wskaźnik na strukturę BOARD.
 * @param holes Liczba pól do usunięcia.
 * @return int Status operacji.
 */
int load_random_board(BOARD *sb, int holes);

#endif // GENERATOR_H
