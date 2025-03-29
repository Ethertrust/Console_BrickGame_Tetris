#include "test.h"

START_TEST(init_test) {
  GameState_t state = {};
  init_tetris_map(&state);

  ck_assert_int_eq(state.info->score, 0);
  ck_assert_int_eq(state.info->level, 1);
  ck_assert_int_eq(state.info->speed, 2000000);
  ck_assert_ptr_nonnull(state.info->field);
  clear_tetris(&state);
}
END_TEST

START_TEST(spawn_block_L) {
  GameState_t state = {};
  init_tetris_map(&state);
  spawn_new_block(&state, L_block);
  int arr[] = {0, 0, 2, 2, 2, 2};
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 3; ++j)
      ck_assert_int_eq(state.info->field[i + SPAWN_POS_Y][j + SPAWN_POS_X],
                       arr[i * 3 + j]);
  clear_tetris(&state);
}
END_TEST

START_TEST(spawn_block_RL) {
  GameState_t state = {};
  init_tetris_map(&state);
  spawn_new_block(&state, RL_block);
  int arr[] = {2, 2, 2, 0, 0, 2};
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 3; ++j)
      ck_assert_int_eq(state.info->field[i + SPAWN_POS_Y][j + SPAWN_POS_X],
                       arr[i * 3 + j]);
  clear_tetris(&state);
}
END_TEST

START_TEST(spawn_block_Z) {
  GameState_t state = {};
  init_tetris_map(&state);
  spawn_new_block(&state, Z_block);
  int arr[] = {2, 2, 0, 0, 2, 2};
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 3; ++j)
      ck_assert_int_eq(state.info->field[i + SPAWN_POS_Y][j + SPAWN_POS_X],
                       arr[i * 3 + j]);
  clear_tetris(&state);
}
END_TEST

START_TEST(spawn_block_RZ) {
  GameState_t state = {};
  init_tetris_map(&state);
  spawn_new_block(&state, RZ_block);
  int arr[] = {0, 2, 2, 2, 2, 0};
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 3; ++j)
      ck_assert_int_eq(state.info->field[i + SPAWN_POS_Y][j + SPAWN_POS_X],
                       arr[i * 3 + j]);
  clear_tetris(&state);
}
END_TEST

START_TEST(spawn_block_T) {
  GameState_t state = {};
  init_tetris_map(&state);
  spawn_new_block(&state, T_block);
  int arr[] = {0, 2, 0, 2, 2, 2};
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 3; ++j)
      ck_assert_int_eq(state.info->field[i + SPAWN_POS_Y][j + SPAWN_POS_X],
                       arr[i * 3 + j]);
  clear_tetris(&state);
}
END_TEST

START_TEST(spawn_block_I) {
  GameState_t state = {};
  init_tetris_map(&state);
  spawn_new_block(&state, I_block);
  int arr[] = {2, 2, 2, 2};
  for (int i = 0; i < 4; ++i)
    ck_assert_int_eq(state.info->field[SPAWN_POS_Y + 1][i + SPAWN_POS_X],
                     arr[i]);
  clear_tetris(&state);
}
END_TEST

START_TEST(spawn_block_SQR) {
  GameState_t state = {};
  init_tetris_map(&state);
  spawn_new_block(&state, square);
  int arr[] = {2, 2, 2, 2};
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 2; ++j)
      ck_assert_int_eq(state.info->field[i + SPAWN_POS_Y][j + SPAWN_POS_X],
                       arr[i * 2 + j]);
  clear_tetris(&state);
}
END_TEST

START_TEST(spawn_inc_block) {
  GameState_t state = {};
  init_tetris_map(&state);
  spawn_new_block(&state, 12);
  for (int i = 0; i < WINDOW_HEIGHT; ++i)
    for (int j = 0; j < WINDOW_WIDTH; ++j)
      ck_assert_int_eq(state.info->field[i][j], 0);
  clear_tetris(&state);
}
END_TEST

START_TEST(left_move_true) {
  GameState_t state = {};
  init_tetris_map(&state);
  spawn_new_block(&state, T_block);
  try_left(&state);
  int arr[] = {0, 2, 0, 2, 2, 2};
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 3; ++j)
      ck_assert_int_eq(state.info->field[i + SPAWN_POS_Y][j + SPAWN_POS_X - 1],
                       arr[i * 3 + j]);
  clear_tetris(&state);
}
END_TEST

START_TEST(left_move_false) {
  GameState_t state = {};
  init_tetris_map(&state);
  spawn_new_block(&state, T_block);
  try_left(&state);
  try_left(&state);
  try_left(&state);
  try_left(&state);
  int arr[] = {0, 2, 0, 2, 2, 2};
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 3; ++j)
      ck_assert_int_eq(state.info->field[i + SPAWN_POS_Y][j], arr[i * 3 + j]);
  try_left(&state);
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 3; ++j)
      ck_assert_int_eq(state.info->field[i + SPAWN_POS_Y][j], arr[i * 3 + j]);
  clear_tetris(&state);
}
END_TEST

START_TEST(left_move_dop) {
  GameState_t state = {};
  init_tetris_map(&state);
  spawn_new_block(&state, I_block);
  rotate_block(&state);
  for (int i = 0; i < 6; ++i) try_left(&state);
  for (int i = 0; i < 4; ++i) ck_assert_int_eq(state.info->field[i][0], 2);
  clear_tetris(&state);
}
END_TEST

START_TEST(right_move_true) {
  GameState_t state = {};
  init_tetris_map(&state);
  spawn_new_block(&state, T_block);
  try_right(&state);
  int arr[] = {0, 2, 0, 2, 2, 2};
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 3; ++j)
      ck_assert_int_eq(state.info->field[i + SPAWN_POS_Y][j + SPAWN_POS_X + 1],
                       arr[i * 3 + j]);
  clear_tetris(&state);
}
END_TEST

START_TEST(right_move_false) {
  GameState_t state = {};
  init_tetris_map(&state);
  spawn_new_block(&state, T_block);
  try_right(&state);
  try_right(&state);
  try_right(&state);
  try_right(&state);
  int arr[] = {0, 2, 0, 2, 2, 2};
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 3; ++j)
      ck_assert_int_eq(state.info->field[i + SPAWN_POS_Y][WINDOW_WIDTH - j - 1],
                       arr[i * 3 + j]);
  try_right(&state);
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 3; ++j)
      ck_assert_int_eq(state.info->field[i + SPAWN_POS_Y][WINDOW_WIDTH - j - 1],
                       arr[i * 3 + j]);
  clear_tetris(&state);
}
END_TEST

START_TEST(right_move_dop) {
  GameState_t state = {};
  init_tetris_map(&state);
  spawn_new_block(&state, I_block);
  rotate_block(&state);
  for (int i = 0; i < 6; ++i) try_right(&state);
  for (int i = 0; i < 4; ++i)
    ck_assert_int_eq(state.info->field[i][WINDOW_WIDTH - 1], 2);
  clear_tetris(&state);
}
END_TEST

START_TEST(down_move) {
  GameState_t state = {};
  init_tetris_map(&state);
  spawn_new_block(&state, I_block);
  int check = try_down(&state);
  ck_assert_int_eq(check, 0);
  clear_tetris(&state);
}
END_TEST

START_TEST(down_move_and_nonactive) {
  GameState_t state = {};
  init_tetris_map(&state);
  spawn_new_block(&state, I_block);
  int check = 0;
  while (!check) check = try_down(&state);
  active_to_block(&state);
  ck_assert_int_eq(check, 1);
  clear_tetris(&state);
}
END_TEST

START_TEST(get_score_100) {
  GameState_t state = {};
  init_tetris_map(&state);
  for (int i = WINDOW_HEIGHT - 1; i > WINDOW_HEIGHT - 2; --i)
    for (int j = 0; j < WINDOW_WIDTH; ++j) state.info->field[i][j] = 1;
  int check = get_score(&state);
  ck_assert_int_eq(check, 0);
  ck_assert_int_eq(state.info->score, 100);
  clear_tetris(&state);
}
END_TEST

START_TEST(get_score_300) {
  GameState_t state = {};
  init_tetris_map(&state);
  for (int i = WINDOW_HEIGHT - 1; i > WINDOW_HEIGHT - 3; --i)
    for (int j = 0; j < WINDOW_WIDTH; ++j) state.info->field[i][j] = 1;
  int check = get_score(&state);
  ck_assert_int_eq(check, 0);
  ck_assert_int_eq(state.info->score, 300);
  clear_tetris(&state);
}
END_TEST

START_TEST(get_score_700) {
  GameState_t state = {};
  init_tetris_map(&state);
  for (int i = WINDOW_HEIGHT - 1; i > WINDOW_HEIGHT - 4; --i)
    for (int j = 0; j < WINDOW_WIDTH; ++j) state.info->field[i][j] = 1;
  int check = get_score(&state);
  ck_assert_int_eq(check, 0);
  ck_assert_int_eq(state.info->score, 700);
  clear_tetris(&state);
}
END_TEST

START_TEST(get_score_1500) {
  GameState_t state = {};
  init_tetris_map(&state);
  for (int i = WINDOW_HEIGHT - 1; i > WINDOW_HEIGHT - 5; --i)
    for (int j = 0; j < WINDOW_WIDTH; ++j) state.info->field[i][j] = 1;
  int check = get_score(&state);
  ck_assert_int_eq(check, 0);
  ck_assert_int_eq(state.info->score, 1500);
  clear_tetris(&state);
}
END_TEST

START_TEST(get_score_0) {
  GameState_t state = {};
  init_tetris_map(&state);
  int check = get_score(&state);
  ck_assert_int_eq(check, 0);
  ck_assert_int_eq(state.info->score, 0);
  clear_tetris(&state);
}
END_TEST

START_TEST(get_gameover) {
  GameState_t state = {};
  init_tetris_map(&state);
  state.info->field[1][1] = 1;
  int check = get_score(&state);
  ck_assert_int_eq(check, 1);
  ck_assert_int_eq(state.info->score, 0);
  clear_tetris(&state);
}
END_TEST

START_TEST(user_input_test_left) {
  GameState_t state = {};
  init_tetris_map(&state);
  spawn_new_block(&state, T_block);
  userInput(Left, true);
  int arr[] = {0, 2, 0, 2, 2, 2};
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 3; ++j)
      ck_assert_int_eq(state.info->field[i + SPAWN_POS_Y][j + SPAWN_POS_X - 1],
                       arr[i * 3 + j]);
  clear_tetris(&state);
}
END_TEST

START_TEST(user_input_test_right) {
  GameState_t state = {};
  init_tetris_map(&state);
  spawn_new_block(&state, T_block);
  userInput(Right, true);
  int arr[] = {0, 2, 0, 2, 2, 2};
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 3; ++j)
      ck_assert_int_eq(state.info->field[i + SPAWN_POS_Y][j + SPAWN_POS_X + 1],
                       arr[i * 3 + j]);
  clear_tetris(&state);
}
END_TEST

START_TEST(user_input_test_down) {
  GameState_t state = {};
  init_tetris_map(&state);
  spawn_new_block(&state, T_block);
  userInput(Down, true);
  int arr[] = {0, 2, 0, 2, 2, 2};
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 3; ++j)
      ck_assert_int_eq(
          state.info->field[WINDOW_HEIGHT - 2 + i][j + SPAWN_POS_X],
          arr[i * 3 + j]);
  clear_tetris(&state);
}
END_TEST

START_TEST(user_input_test_rotate) {
  GameState_t state = {};
  init_tetris_map(&state);
  spawn_new_block(&state, square);
  userInput(Action, true);
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 2; ++j)
      ck_assert_int_eq(state.info->field[SPAWN_POS_Y + i][j + SPAWN_POS_X], 2);
  clear_tetris(&state);
}
END_TEST

START_TEST(user_input_test_up) {
  GameState_t state = {};
  init_tetris_map(&state);
  spawn_new_block(&state, square);
  userInput(Up, true);
  clear_tetris(&state);
}
END_TEST

START_TEST(user_input_test_pause) {
  GameState_t state = {};
  init_tetris_map(&state);
  spawn_new_block(&state, T_block);
  userInput(Pause, true);
  clear_tetris(&state);
}
END_TEST

START_TEST(user_input_test_start) {
  GameState_t state = {};
  init_tetris_map(&state);
  spawn_new_block(&state, T_block);
  userInput(Start, true);
  clear_tetris(&state);
}
END_TEST

START_TEST(set_highscore) {
  GameState_t state = {};
  init_tetris_map(&state);
  state.info->score = 2100;
  set_new_highscore(&state);
  ck_assert_int_eq(state.info->high_score, 2100);
  clear_tetris(&state);
}
END_TEST

START_TEST(set_level_1) {
  GameState_t state = {};
  init_tetris_map(&state);
  state.info->score = 500;
  set_new_level(&state);
  ck_assert_int_eq(state.info->level, 1);
  clear_tetris(&state);
}
END_TEST

START_TEST(set_level_2) {
  GameState_t state = {};
  init_tetris_map(&state);
  state.info->score = 700;
  set_new_level(&state);
  ck_assert_int_eq(state.info->level, 2);
  clear_tetris(&state);
}
END_TEST

START_TEST(set_level_3) {
  GameState_t state = {};
  init_tetris_map(&state);
  state.info->score = 1700;
  set_new_level(&state);
  ck_assert_int_eq(state.info->level, 3);
  clear_tetris(&state);
}
END_TEST

START_TEST(set_level_4) {
  GameState_t state = {};
  init_tetris_map(&state);
  state.info->score = 1800;
  set_new_level(&state);
  ck_assert_int_eq(state.info->level, 4);
  clear_tetris(&state);
}
END_TEST

START_TEST(set_level_5) {
  GameState_t state = {};
  init_tetris_map(&state);
  state.info->score = 2500;
  set_new_level(&state);
  ck_assert_int_eq(state.info->level, 5);
  clear_tetris(&state);
}
END_TEST

START_TEST(set_level_6) {
  GameState_t state = {};
  init_tetris_map(&state);
  state.info->score = 3500;
  set_new_level(&state);
  ck_assert_int_eq(state.info->level, 6);
  clear_tetris(&state);
}
END_TEST

START_TEST(set_level_7) {
  GameState_t state = {};
  init_tetris_map(&state);
  state.info->score = 3600;
  set_new_level(&state);
  ck_assert_int_eq(state.info->level, 7);
  clear_tetris(&state);
}
END_TEST

START_TEST(set_level_8) {
  GameState_t state = {};
  init_tetris_map(&state);
  state.info->score = 4300;
  set_new_level(&state);
  ck_assert_int_eq(state.info->level, 8);
  clear_tetris(&state);
}
END_TEST

START_TEST(set_level_9) {
  GameState_t state = {};
  init_tetris_map(&state);
  state.info->score = 5399;
  set_new_level(&state);
  ck_assert_int_eq(state.info->level, 9);
  clear_tetris(&state);
}
END_TEST

START_TEST(set_level_10) {
  GameState_t state = {};
  init_tetris_map(&state);
  state.info->score = 5400;
  set_new_level(&state);
  ck_assert_int_eq(state.info->level, 10);
  clear_tetris(&state);
}
END_TEST

START_TEST(dop_1) {
  GameState_t *state = calloc(1, sizeof(GameState_t));
  init_tetris_map(state);
  spawn_new_block(state, Z_block);
  GameInfo_t check = updateCurrentState();
  ck_assert_int_eq(state->info->high_score, check.high_score);
  ck_assert_int_eq(state->info->score, check.score);
  ck_assert_int_eq(state->info->level, check.level);
  ck_assert_int_eq(state->info->speed, check.speed);
  ck_assert_int_eq(state->info->pause, check.pause);
  ck_assert_ptr_eq(state->info->field, check.field);
  ck_assert_ptr_eq(state->info->next, check.next);
  clear_tetris(state);
  free(state);
}
END_TEST

START_TEST(dop_2) {
  block_type check = 0;
  for (int i = 0; i < 100; ++i) {
    check = get_random_block();
    ck_assert_int_le(check, 6);
    ck_assert_int_ge(check, 0);
  }
}
END_TEST

Suite *tetris_test_suite() {
  Suite *s = suite_create("\033[45m-=S21_TETRIS_TEST=-\033[0m");
  TCase *tc = tcase_create("tetris_tc");
  tcase_add_test(tc, init_test);
  tcase_add_test(tc, spawn_block_L);
  tcase_add_test(tc, spawn_block_RL);
  tcase_add_test(tc, spawn_block_Z);
  tcase_add_test(tc, spawn_block_RZ);
  tcase_add_test(tc, spawn_block_T);
  tcase_add_test(tc, spawn_block_I);
  tcase_add_test(tc, spawn_block_SQR);
  tcase_add_test(tc, spawn_inc_block);
  tcase_add_test(tc, left_move_true);
  tcase_add_test(tc, left_move_false);
  tcase_add_test(tc, left_move_dop);
  tcase_add_test(tc, right_move_true);
  tcase_add_test(tc, right_move_false);
  tcase_add_test(tc, right_move_dop);
  tcase_add_test(tc, down_move);
  tcase_add_test(tc, down_move_and_nonactive);
  tcase_add_test(tc, get_score_100);
  tcase_add_test(tc, get_score_300);
  tcase_add_test(tc, get_score_700);
  tcase_add_test(tc, get_score_1500);
  tcase_add_test(tc, get_score_0);
  tcase_add_test(tc, get_gameover);
  tcase_add_test(tc, user_input_test_left);
  tcase_add_test(tc, user_input_test_right);
  tcase_add_test(tc, user_input_test_down);
  tcase_add_test(tc, user_input_test_rotate);
  tcase_add_test(tc, user_input_test_up);
  tcase_add_test(tc, user_input_test_pause);
  tcase_add_test(tc, user_input_test_start);
  tcase_add_test(tc, set_highscore);
  tcase_add_test(tc, set_level_1);
  tcase_add_test(tc, set_level_2);
  tcase_add_test(tc, set_level_3);
  tcase_add_test(tc, set_level_4);
  tcase_add_test(tc, set_level_5);
  tcase_add_test(tc, set_level_6);
  tcase_add_test(tc, set_level_7);
  tcase_add_test(tc, set_level_8);
  tcase_add_test(tc, set_level_9);
  tcase_add_test(tc, set_level_10);
  tcase_add_test(tc, dop_1);
  tcase_add_test(tc, dop_2);
  suite_add_tcase(s, tc);

  return s;
}