#ifndef TETRIS_FRONTEND
#define TETRIS_FRONTEND

#define START_PRTINT_POS_X 2
#define START_PRTINT_POS_Y 0
#define START_SCORE_X START_PRTINT_POS_X + 21
#define START_SCORE_Y START_PRTINT_POS_Y
#define WINDOW_BLOCK_WIDTH 14
#define WINDOW_BLOCK_HEIGHT 4
#define BLOCK_WIN_Y 
#define MVADDCH(y, x, c) mvaddch((y), (x), c)

#include <ncurses.h>
#include "../../brick_game/tetris/tetris_back_3.h"

int kbhit();
void set_my_color(block_type block);
void print_rectangle(int x1, int y1, int x2, int y2);
void print_game_window(GameInfo_t game_info, block_type current, block_type next);
void print_score_window(int score);
void print_highscore(int highscore);
void print_next_block(block_type block);
void print_level(int level);
void print_pause();
void print_start_menu(GameInfo_t game_info);
void print_end_menu(int score);
void print_lable();
void init_gui();
void close_gui();

#endif