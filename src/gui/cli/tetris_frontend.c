#include "tetris_frontend.h"

int kbhit() {
  int c = getch();
  if (c != ERR) {
    ungetch(c);
    return 1;
  }
  return 0;
}

void set_my_color(block_type block) {
  switch (block) {
    case 0:
      attron(COLOR_PAIR(1));
      break;
    case 1:
      attron(COLOR_PAIR(2));
      break;
    case 2:
      attron(COLOR_PAIR(3));
      break;
    case 3:
      attron(COLOR_PAIR(4));
      break;
    case 4:
      attron(COLOR_PAIR(5));
      break;
    case 5:
      attron(COLOR_PAIR(6));
      break;
    case 6:
      attron(COLOR_PAIR(7));
      break;
  }
}

void reset_my_color(block_type block) {
  switch (block) {
    case 0:
      attroff(COLOR_PAIR(1));
      break;
    case 1:
      attroff(COLOR_PAIR(2));
      break;
    case 2:
      attroff(COLOR_PAIR(3));
      break;
    case 3:
      attroff(COLOR_PAIR(4));
      break;
    case 4:
      attroff(COLOR_PAIR(5));
      break;
    case 5:
      attroff(COLOR_PAIR(6));
      break;
    case 6:
      attroff(COLOR_PAIR(7));
      break;
  }
}

void print_rectangle(int top_y, int bottom_y, int left_x, int right_x) {
  MVADDCH(top_y, left_x, ACS_ULCORNER);

  int i = left_x + 1;

  for (; i < right_x; i++) MVADDCH(top_y, i, ACS_HLINE);
  MVADDCH(top_y, i, ACS_URCORNER);

  for (int i = top_y + 1; i < bottom_y; i++) {
    MVADDCH(i, left_x, ACS_VLINE);
    MVADDCH(i, right_x, ACS_VLINE);
  }

  MVADDCH(bottom_y, left_x, ACS_LLCORNER);
  i = left_x + 1;
  for (; i < right_x; i++) MVADDCH(bottom_y, i, ACS_HLINE);
  MVADDCH(bottom_y, i, ACS_LRCORNER);
}

void print_game_window(GameInfo_t game_info, block_type current,
                       block_type next) {
  int x = START_PRTINT_POS_X, y = START_PRTINT_POS_Y;

  // move(y, x);
  for (int i = 0; i < WINDOW_HEIGHT; ++i) {
    x = START_PRTINT_POS_X;
    //++y;
    move(y, x);
    for (int j = 0; j < WINDOW_WIDTH; ++j) {
      if (game_info.field[i][j] == active_block) {
        set_my_color(10);
        printw("  ");
        reset_my_color(10);
      } else if (game_info.field[i][j] == block) {
        if (y != 0) {
          attron(COLOR_PAIR(9));
          printw("  ");
          attroff(COLOR_PAIR(9));
        } else
          printw("  ");
      } else {
        if (y != 0) attron(COLOR_PAIR(8));
        printw("  ");
        if (y != 0) attroff(COLOR_PAIR(8));
      }
      x += 2;
      move(y, x);
    }
    ++y;
  }
  x = START_PRTINT_POS_X;
  ++y;

  print_rectangle(START_PRTINT_POS_Y, START_PRTINT_POS_Y + 21,
                  START_PRTINT_POS_X - 1, START_PRTINT_POS_X + 20);
  print_score_window(game_info.score);
  print_next_block(next);
  print_highscore(game_info.high_score);
  print_level(game_info.level);
  print_lable();
}

void print_score_window(int score) {
  move(START_PRTINT_POS_Y + 1, START_PRTINT_POS_X + 26);
  printw("SCORE");
  move(START_PRTINT_POS_Y + 3, START_PRTINT_POS_X + 25);
  printw("%4.7d", score);
  print_rectangle(START_PRTINT_POS_Y, START_PRTINT_POS_Y + WINDOW_BLOCK_HEIGHT,
                  START_SCORE_X, START_SCORE_X + WINDOW_BLOCK_WIDTH);
}

void print_highscore(int highscore) {
  move(START_PRTINT_POS_Y + WINDOW_BLOCK_HEIGHT * 2 + 3, START_SCORE_X + 3);
  printw("HIGHSCORE");
  move(START_PRTINT_POS_Y + WINDOW_BLOCK_HEIGHT * 2 + 5, START_SCORE_X + 4);
  printw("%4.7d", highscore);
  print_rectangle(START_PRTINT_POS_Y + WINDOW_BLOCK_HEIGHT * 2 + 2,
                  START_PRTINT_POS_Y + 2 + WINDOW_BLOCK_HEIGHT * 3,
                  START_SCORE_X, START_SCORE_X + WINDOW_BLOCK_WIDTH);
}

void print_next_block(block_type block) {
  move(START_PRTINT_POS_Y + WINDOW_BLOCK_HEIGHT + 3, START_SCORE_X + 3);
  set_my_color(block);
  switch (block) {
    case L_block:
      printw("    []  ");
      move(START_PRTINT_POS_Y + WINDOW_BLOCK_HEIGHT + 4, START_SCORE_X + 3);
      printw("[][][]  ");
      break;
    case I_block:
      printw("        ");
      move(START_PRTINT_POS_Y + WINDOW_BLOCK_HEIGHT + 4, START_SCORE_X + 3);
      printw("[][][][]");
      break;
    case T_block:
      printw("  []    ");
      move(START_PRTINT_POS_Y + WINDOW_BLOCK_HEIGHT + 4, START_SCORE_X + 3);
      printw("[][][]  ");
      break;
    case square:
      printw("  [][]  ");
      move(START_PRTINT_POS_Y + WINDOW_BLOCK_HEIGHT + 4, START_SCORE_X + 3);
      printw("  [][]  ");
      break;
    case Z_block:
      printw("[][]    ");
      move(START_PRTINT_POS_Y + WINDOW_BLOCK_HEIGHT + 4, START_SCORE_X + 3);
      printw("  [][]  ");
      break;
    case RL_block:
      printw("[][][]  ");
      move(START_PRTINT_POS_Y + WINDOW_BLOCK_HEIGHT + 4, START_SCORE_X + 3);
      printw("    []  ");
      break;
    case RZ_block:
      printw("  [][]  ");
      move(START_PRTINT_POS_Y + WINDOW_BLOCK_HEIGHT + 4, START_SCORE_X + 3);
      printw("[][]    ");
      break;
  }
  reset_my_color(block);
  move(START_PRTINT_POS_Y + WINDOW_BLOCK_HEIGHT + 2, START_PRTINT_POS_X + 26);
  printw("NEXT");
  move(START_PRTINT_POS_Y + 3, START_PRTINT_POS_X + 25);

  print_rectangle(START_PRTINT_POS_Y + WINDOW_BLOCK_HEIGHT + 1,
                  START_PRTINT_POS_Y + 1 + WINDOW_BLOCK_HEIGHT * 2,
                  START_SCORE_X, START_SCORE_X + WINDOW_BLOCK_WIDTH);
}

void print_level(int level) {
  int pos_y = START_PRTINT_POS_Y + 3 + WINDOW_BLOCK_HEIGHT * 3;
  move(pos_y + 1, START_SCORE_X + 5);
  printw("LEVEL");
  move(pos_y + 3, START_SCORE_X + 2);
  printw("%6d", level);
  print_rectangle(pos_y, pos_y + WINDOW_BLOCK_HEIGHT, START_SCORE_X,
                  START_SCORE_X + WINDOW_BLOCK_WIDTH);
}

void print_pause() {
  attron(COLOR_PAIR(10));
  move(START_PRTINT_POS_Y + 10, START_PRTINT_POS_X + 8);
  printw("PAUSE");
  attroff(COLOR_PAIR(10));
}

void print_start_menu(GameInfo_t game_info) {
  print_game_window(game_info, 8, 8);
  move(START_PRTINT_POS_Y + 10, START_PRTINT_POS_X + 2);
  printw("PRESS S TO START");
  int c = 0;
  while (c != 's') c = getch();
}

void print_end_menu(int score) {
  for (int i = 6; i < 13; ++i) {
    move(i, START_PRTINT_POS_X + 1);
    printw("                   ");
  }
  move(START_PRTINT_POS_Y + 7, START_PRTINT_POS_X + 6);
  printw("GAME OVER");
  move(START_PRTINT_POS_Y + 9, START_PRTINT_POS_X + 2);
  printw("YOUR SCORE : %4d", score);
  move(START_PRTINT_POS_Y + 11, START_PRTINT_POS_X + 3);
  printw("PRESS Q TO EXIT");
  int c = 0;
  while (c != 'q') c = getch();
}

void print_lable() {
  int pos_y = START_PRTINT_POS_Y + 4 + WINDOW_BLOCK_HEIGHT * 4;
  move(pos_y, START_SCORE_X);
  printw("game by karstarl");
}

void init_gui() {
  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  start_color();
  init_pair(1, COLOR_RED, COLOR_WHITE);
  init_pair(2, COLOR_YELLOW, COLOR_WHITE);
  init_pair(3, 5, COLOR_WHITE);
  init_pair(4, 10, COLOR_WHITE);
  init_pair(5, 11, COLOR_WHITE);
  init_pair(6, 12, COLOR_WHITE);
  init_pair(7, 13, COLOR_WHITE);
  init_pair(8, 8, COLOR_WHITE);
  init_pair(9, COLOR_BLACK, COLOR_MAGENTA);
  init_pair(10, COLOR_MAGENTA, COLOR_BLACK);
}

void close_gui() { endwin(); }