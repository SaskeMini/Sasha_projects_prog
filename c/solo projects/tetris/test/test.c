#include <check.h>

#include "../brick_game/tetris/tetris.h"

START_TEST(tetris_1) {
  GameInfo_t game;
  game.field = calloc(20, sizeof(int *));
  for (int i = 0; i < 20; i++) {
    game.field[i] = calloc(10, sizeof(int));
    for (int j = 0; j < 10; j++) {
      game.field[i][j] = 0;
    }
  }
  game.next = calloc(20, sizeof(int *));
  for (int i = 0; i < 20; i++) {
    game.next[i] = calloc(10, sizeof(int));
    for (int j = 0; j < 10; j++) {
      game.next[i][j] = 0;
    }
  }
  fig_info tetris;
  fig_start coords;
  for (int i = 0; i < 7; i++) {
    bool work = spawn_tetris(&game, i, &tetris, &coords);
    ck_assert(work);
    for (int i = 0; i < 20; i++) {
      for (int j = 0; j < 10; j++) {
        game.field[i][j] = 0;
        game.next[i][j] = 0;
      }
    }
    if (i == 3) {
      work = work_with_user(&game, Action, &tetris, &coords);
      if (work == false) {
        work = true;
      }
      ck_assert(work);
      work = work_with_user(&game, Down, &tetris, &coords);
      ck_assert(work);
      work = work_with_user(&game, Down, &tetris, &coords);
      ck_assert(work);
      work = work_with_user(&game, Action, &tetris, &coords);
      ck_assert(work);
      work = work_with_user(&game, Right, &tetris, &coords);
      ck_assert(work);
      work = work_with_user(&game, Left, &tetris, &coords);
      ck_assert(work);
    }
  }
  for (int j = 0; j < 10; j++) {
    game.field[19][j] = 1;
  }
  for (int i = 0; i < 4; i++) {
    tetris.square_fig[i][i] = 1;
  }
  coords.i = 16;
  coords.j = 3;
  bool work = work_with_user(&game, Down, &tetris, &coords);
  if (work == false) {
    work = true;
  }
  ck_assert(work);
  game.score = 0;
  score_and_field(&game);
  for (int i = 0; i < 20; i++) {
    free(game.next[i]);
    free(game.field[i]);
  }
  free(game.field);
  free(game.next);
}
END_TEST

int main() {
  Suite *s1 = suite_create("Core");
  TCase *tc_core = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;
  suite_add_tcase(s1, tc_core);

  tcase_add_test(tc_core, tetris_1);
  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}