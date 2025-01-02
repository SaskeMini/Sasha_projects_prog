#include "tetris.h"

int main() {
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
  game.score = 0;
  FILE *best_score;
  best_score = fopen("Out/best_score.txt", "r");
  fscanf(best_score, "%d", &game.high_score);
  fclose(best_score);
  game.level = 1;
  game.speed = 55;
  game.pause = 0;
  Start_game(&game);
  if (game.score > game.high_score) {
    best_score = fopen("Out/best_score.txt", "w+");
    fprintf(best_score, "%d", game.score);
    fclose(best_score);
  }
  for (int i = 0; i < 20; i++) {
    free(game.next[i]);
    free(game.field[i]);
  }
  free(game.field);
  free(game.next);
  return 0;
}