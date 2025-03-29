// #include "brick_game/tetris/tetris_backend.h"
#include <time.h>

#include "fsm_matrix/fsm_matrix.h"
#include "gui/cli/tetris_frontend.h"

int main() {
  init_gui();
  game_loop_2();
  close_gui();
}
