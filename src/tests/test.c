#include "test.h"

int main() {
  int failed = 0;
  int total = 0;
  Suite *s21_tetris_test[] = {tetris_test_suite(), NULL};

  for (int i = 0; s21_tetris_test[i] != NULL; ++i) {
    SRunner *sr = srunner_create(s21_tetris_test[i]);
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);
    failed += srunner_ntests_failed(sr);
    total += srunner_ntests_run(sr);
    srunner_free(sr);
    ++total;
  }
  --total;
  printf("========== TOTAL TESTS : %3d ==========\n", total);
  printf("========== TEST SUCCESS: %3d ==========\n", total - failed);
  printf("========== TESTS FAILED: %3d ==========\n", failed);
  return 0;
}
