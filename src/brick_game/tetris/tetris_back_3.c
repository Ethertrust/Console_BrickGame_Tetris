/**
 * @file tetris_back_3.c
 * @author karstarl
 * @brief
 * @version 0.1
 * @date 2024-07-03
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "tetris_back_3.h"

void userInput(UserAction_t action, bool hold) {
  if (hold) {
    GameState_t *state = get_set_current_map(NULL);
    switch (action) {
      case Start:
        break;
      case Pause:
        break;
      case Terminate:
        break;
      case Left:
        try_left(state);
        break;
      case Right:
        try_right(state);
        break;
      case Up:
        break;
      case Down:
        while (!try_down(state))
          ;  //  try_down(state);
        break;
      case Action:
        rotate_block(state);
        break;
      default:
        break;
    }
  }
}

GameInfo_t updateCurrentState() {
  GameState_t *state = get_set_current_map(NULL);
  return *state->info;
}

void init_tetris_map(GameState_t *state) {
  state->info = (GameInfo_t *)s21_malloc(
      1 * sizeof(GameInfo_t));  //(GameInfo_t *)calloc(1, sizeof(GameInfo_t));
  state->info->level = 1;
  state->info->speed = 2000000;

  FILE *fp = fopen(FILE_SCORE, "r");
  if (!fp) {
    state->info->high_score = 0;
  } else {
    fscanf(fp, "%d", &state->info->high_score);
    fclose(fp);
  }

  state->info->pause = 0;
  state->info->score = 0;
  state->info->field = (int **)s21_malloc(
      WINDOW_HEIGHT *
      sizeof(int *));  // (int **)calloc(WINDOW_HEIGHT, sizeof(int *));
  for (int i = 0; i < WINDOW_HEIGHT; ++i)
    state->info->field[i] = (int *)s21_malloc(
        WINDOW_HEIGHT *
        sizeof(int));  //(int *)calloc(WINDOW_WIDTH, sizeof(int));
  state->info->next = NULL;
  get_set_current_map(state);
}

void clear_tetris(GameState_t *state) {
  for (int i = 0; i < WINDOW_HEIGHT; ++i) {
    free(state->info->field[i]);
    state->info->field[i] = NULL;
  }
  free(state->info->field);
  state->info->field = NULL;
  free(state->info);
}

void try_left(GameState_t *state) {
  bool is_can = true;
  if (state->rect.x1 >= 0) {
    for (int i = state->rect.y1; i <= state->rect.y2; ++i) {
      if (state->info->field[i][0] == active_block) is_can = false;
      for (int j = state->rect.x1; j <= state->rect.x2; ++j)
        if (state->info->field[i][j] == active_block &&
            state->info->field[i][j - 1] == block)
          is_can = false;
    }
  } else {
    for (int i = state->rect.y1; i <= state->rect.y2; ++i)
      if (state->info->field[i][0] == active_block) is_can = false;
    // if (is_can) {
    //   ++state->rect.x1;
    //   ++state->rect.x2;
    // }
  }

  if (is_can) {
    for (int i = state->rect.y1; i <= state->rect.y2; ++i)
      for (int j = state->rect.x1; j <= state->rect.x2; ++j)
        if (state->info->field[i][j] == active_block) {
          state->info->field[i][j] = empty;
          state->info->field[i][j - 1] = active_block;
        }
    --state->rect.x1;
    --state->rect.x2;
  }
}

void try_right(GameState_t *state) {
  bool is_can = true;
  if (state->rect.x2 < WINDOW_WIDTH + 1) {
    for (int i = state->rect.y1; i <= state->rect.y2; ++i) {
      if (state->info->field[i][WINDOW_WIDTH - 1] == active_block)
        is_can = false;
      for (int j = state->rect.x1; j <= state->rect.x2; ++j)
        if (state->info->field[i][j] == active_block &&
            state->info->field[i][j + 1] == block)
          is_can = false;
    }
  } else {
    for (int i = state->rect.y1; i <= state->rect.y2; ++i)
      if (state->info->field[i][WINDOW_WIDTH - 1] == active_block)
        is_can = false;
    if (is_can) {
      --state->rect.x1;
      --state->rect.x2;
    }
  }

  if (is_can) {
    for (int i = state->rect.y1; i <= state->rect.y2; ++i)
      for (int j = state->rect.x2; j >= state->rect.x1; --j)
        if (state->info->field[i][j] == active_block) {
          state->info->field[i][j] = empty;
          state->info->field[i][j + 1] = active_block;
        }
    ++state->rect.x1;
    ++state->rect.x2;
  }
}

int try_down(GameState_t *state) {
  int result = 0;
  bool is_can = true;
  if (state->rect.y2 == WINDOW_HEIGHT - 1) {
    for (int i = state->rect.x1; i <= state->rect.x2; ++i)
      if (state->info->field[WINDOW_HEIGHT - 1][i] == active_block)
        is_can = false;
    if (is_can) {
      // --state->rect.y1;
      --state->rect.y2;
    }
  }

  if (state->rect.y2 == WINDOW_HEIGHT - 1)
    result = 1;
  else {
    for (int i = state->rect.y1; i <= state->rect.y2; ++i)
      for (int j = state->rect.x1; j <= state->rect.x2; ++j)
        if (state->info->field[i][j] == active_block &&
            state->info->field[i + 1][j] == block)
          result = 1;
  }

  if (!result) {
    for (int i = state->rect.y2; i >= state->rect.y1; --i)
      for (int j = state->rect.x1; j <= state->rect.x2; ++j)
        if (state->info->field[i][j] == active_block) {
          state->info->field[i][j] = empty;
          state->info->field[i + 1][j] = active_block;
        }
    ++state->rect.y1;
    ++state->rect.y2;
  }
  return result;
}

void spawn_new_block(GameState_t *state) {
  switch (state->block) {
    case L_block:
      spawn_block(state, SPAWN_POS_X);
      break;
    case I_block:
      spawn_block(state, SPAWN_POS_X);
      break;
    case T_block:
      spawn_block(state, SPAWN_POS_X);
      break;
    case square:
      spawn_block(state, SPAWN_POS_X);
      break;
    case Z_block:
      spawn_block(state, SPAWN_POS_X);
      break;
    case RL_block:
      spawn_block(state, SPAWN_POS_X);
      break;
    case RZ_block:
      spawn_block(state, SPAWN_POS_X);
      break;
    default:
      break;
  }
}

void rotate_block(GameState_t *state) {
  // int y_max = state->rect.y2 - state->rect.y1 + 1;
  // int x_max = state->rect.x2 - state->rect.x1 + 1;
  int **buffer = s21_malloc_matrix(4, 4);

  bool is_can = true;

  choose_blstate(buffer, state->block, (state->rect.pos + 1) % 4, 0);
  // int arr[] = ;
  // for (int i = 0; i < y_max; ++i)
  //   for (int j = 0; j < x_max; ++j)
  //     buffer[i][j] = arr[state->block][top];
  // buffer[i][j] = empty;
  int y_rect_size = state->rect.y2 - state->rect.y1 + 1;
  for (int i = 0; i < y_rect_size; ++i) {
    for (int j = 0; j < 4; ++j)
      if ((buffer[i][j] > block &&
           state->info->field[state->rect.y1 + i][state->rect.x1 + j] ==
               block) ||
          (j + state->rect.x1 == WINDOW_WIDTH &&
           state->info->field[i + state->rect.y1][WINDOW_WIDTH] !=
               buffer[i][j]) ||
          (state->rect.x1 < 0))
        is_can = false;
  }

  if (is_can) {
    for (int i = 0; i < y_rect_size; ++i)
      for (int j = 0; j < 4; ++j)
        if (state->info->field[state->rect.y1 + i][state->rect.x1 + j] !=
            block) {
          state->info->field[state->rect.y1 + i][state->rect.x1 + j] =
              buffer[i][j];
        }
    state->rect.pos = (state->rect.pos + 1) % 4;
  }
  free_matrix(buffer, 4);
}

block_type get_random_block() { return (rand() * clock()) % 7; }

int get_score(GameState_t *state) {
  int is_game_over = 0;
  for (int i = 0; i < WINDOW_WIDTH; ++i)
    if (state->info->field[1][i] == block)
      is_game_over += state->info->field[1][i];
  if (is_game_over)
    is_game_over = 1;
  else {
    int lines = 0;
    for (int i = WINDOW_HEIGHT - 1; i > 0; --i) {
      int blocks_in_line = 0;
      for (int j = 0; j < WINDOW_WIDTH; ++j)
        if (state->info->field[i][j] == block) ++blocks_in_line;
      if (blocks_in_line == WINDOW_WIDTH) {
        delete_line(state, i);
        i = WINDOW_HEIGHT;
        ++lines;
      }
    }
    if (lines == 1)
      state->info->score += 100;
    else if (lines == 2)
      state->info->score += 300;
    else if (lines == 3)
      state->info->score += 700;
    else if (lines == 4)
      state->info->score += 1500;
  }
  return is_game_over;
}

void delete_line(GameState_t *state, int line) {
  for (int i = 0; i < WINDOW_WIDTH; ++i) state->info->field[line][i] = empty;

  for (int i = line; i > 0; --i)
    for (int j = 0; j < WINDOW_WIDTH; ++j)
      state->info->field[i][j] = state->info->field[i - 1][j];
}

void active_to_block(GameState_t *state) {
  for (int i = 0; i < WINDOW_HEIGHT; ++i)
    for (int j = 0; j < WINDOW_WIDTH; ++j)
      if (state->info->field[i][j] == active_block)
        state->info->field[i][j] = block;
}

void set_new_highscore(GameState_t *state) {
  FILE *fp = fopen(FILE_SCORE, "wb");
  if (!fp) return;
  fprintf(fp, "%d", state->info->score);
  fclose(fp);
  state->info->high_score = state->info->score;
}

void set_new_level(GameState_t *state) {
  int result = 1;
  int score = state->info->score;
  if (score < 600)
    state->info->speed = 2000000;
  else if (score < 1200) {
    result = 2;
    state->info->speed = 1750000;
  } else if (score < 1800) {
    result = 3;
    state->info->speed = 1500000;
  } else if (score < 2400) {
    result = 4;
    state->info->speed = 1250000;
  } else if (score < 3000) {
    result = 5;
    state->info->speed = 1000000;
  } else if (score < 3600) {
    result = 6;
    state->info->speed = 750000;
  } else if (score < 4200) {
    result = 7;
    state->info->speed = 500000;
  } else if (score < 4800) {
    result = 8;
    state->info->speed = 400000;
  } else if (score < 5400) {
    result = 9;
    state->info->speed = 350000;
  } else {
    result = 10;
    state->info->speed = 300000;
  }
  state->info->level = result;
}

GameState_t *get_set_current_map(GameState_t *state) {
  static GameState_t *state_;
  if (state != NULL) {
    state_ = state;
  }
  return state_;
}

void *s21_malloc(const size_t size) {
  void *malloc_ptr = malloc(size);
  if (malloc_ptr == NULL) {
    fprintf(stderr, "%zu[DEBUG] Bad memory allocation\n", size);
    exit(BAD_ALLOC);
  }
  return malloc_ptr;
}

int **s21_malloc_matrix(const size_t y, const size_t x) {
  int **malloc_ptr = (int **)s21_malloc(sizeof(int *) * y);
  for (int i = 0; i < y; i++) {
    malloc_ptr[i] = (int *)s21_malloc(sizeof(int) * x);
    for (int j = 0; j < x; j++) malloc_ptr[i][j] = empty;
  }
  return malloc_ptr;
}

void free_matrix(int **matrix, int r_size) {
  for (int i = 0; i < r_size; i++) free(matrix[i]);
  free(matrix);
}