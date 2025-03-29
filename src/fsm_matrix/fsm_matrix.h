#ifndef FSM_MATRIX
#define FSM_MATRIX

#include "../brick_game/tetris/tetris_back_3.h"
#include "../gui/cli/tetris_frontend.h"
#include <sys/time.h>

UserAction_t player_input(int input);
void game_pause();
int game_input(GameState_t* state);
bool game_process(GameState_t* state);
void game_loop_2();

#endif