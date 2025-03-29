#include "tetris_back_3.h"

void choose_blstate(int** buf, block_type bt, position pos, int spawn_pos_x) {
  int strnum = 2 + (pos % 2 * 2);
  for (int i = 0; i < strnum; ++i)
    for (int j = 0; j < 4; ++j)
      buf[i][j + spawn_pos_x] = block_state[bt][pos][i * 4 + j];
}

void spawn_block(GameState_t* state, int spawn_pos_x) {
  state->rect.pos = 0;
  choose_blstate(state->info->field, state->block, state->rect.pos,
                 spawn_pos_x);
  state->rect.x1 = spawn_pos_x;
  state->rect.x2 = spawn_pos_x + 3;
  state->rect.y1 = 0;
  state->rect.y2 = 3;
}