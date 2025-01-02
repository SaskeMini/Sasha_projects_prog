#include "tetris.h"

int userInput(UserAction_t action, bool hold) {
  action = 0;
  int inp = getch();
  hold = true;
  if (inp == KEY_UP && hold == true)
    action = Action;
  else if (inp == KEY_DOWN)
    action = Down;
  else if (inp == KEY_LEFT)
    action = Left;
  else if (inp == KEY_RIGHT)
    action = Right;
  else if (inp == 27)
    action = Terminate;
  else if (inp == KEY_ENTER)
    action = Start;
  else if (inp == 32)
    action = Pause;
  return action;
}

bool spawn_tetris(GameInfo_t *game, int fig, fig_info *tetris,
                  fig_start *coords) {
  bool res = true;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      tetris->square_fig[i][j] = 0;
    }
  }
  if (fig == 0) {
    tetris->square_fig[1][0] = 1;
    tetris->square_fig[1][1] = 1;
    tetris->square_fig[1][2] = 1;
    tetris->square_fig[1][3] = 1;
  }
  if (fig == 1) {
    tetris->square_fig[1][1] = 1;
    tetris->square_fig[2][1] = 1;
    tetris->square_fig[2][2] = 1;
    tetris->square_fig[2][3] = 1;
  }
  if (fig == 2) {
    tetris->square_fig[2][1] = 1;
    tetris->square_fig[2][2] = 1;
    tetris->square_fig[2][3] = 1;
    tetris->square_fig[1][3] = 1;
  }
  if (fig == 3) {
    tetris->square_fig[1][1] = 1;
    tetris->square_fig[2][1] = 1;
    tetris->square_fig[1][2] = 1;
    tetris->square_fig[2][2] = 1;
  }
  if (fig == 4) {
    tetris->square_fig[2][1] = 1;
    tetris->square_fig[2][2] = 1;
    tetris->square_fig[1][2] = 1;
    tetris->square_fig[1][3] = 1;
  }
  if (fig == 5) {
    tetris->square_fig[1][2] = 1;
    tetris->square_fig[2][1] = 1;
    tetris->square_fig[2][2] = 1;
    tetris->square_fig[2][3] = 1;
  }
  if (fig == 6) {
    tetris->square_fig[1][1] = 1;
    tetris->square_fig[1][2] = 1;
    tetris->square_fig[2][2] = 1;
    tetris->square_fig[2][3] = 1;
  }
  replace_next(game, tetris, coords, false);
  for (int i = 1; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      if (game->next[i - 1][j + 3] == 1) {
        res = false;
      } else {
        game->next[i - 1][j + 3] = tetris->square_fig[i][j];
      }
    }
  }
  if (res == true) {
    coords->i = -1;
    coords->j = 3;
    replace_field(game);
  }
  return res;
}

void replace_field(GameInfo_t *game) {
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      game->field[i][j] = game->next[i][j];
      game->next[i][j] = 0;
    }
  }
}

void replace_next(GameInfo_t *game, fig_info *tetris, fig_start *coords,
                  bool check) {
  if (check) {
    for (int i = 0; i < 20; i++) {
      for (int j = 0; j < 10; j++) {
        if (i >= coords->i && i <= coords->i + 3 && j >= coords->j &&
            j <= coords->j + 3) {
          if (tetris->square_fig[i - coords->i][j - coords->j] == 1) {
            game->next[i][j] = 0;
          } else {
            game->next[i][j] = game->field[i][j];
          }
        } else {
          game->next[i][j] = game->field[i][j];
        }
      }
    }
  } else {
    for (int i = 0; i < 20; i++) {
      for (int j = 0; j < 10; j++) {
        game->next[i][j] = game->field[i][j];
      }
    }
  }
}

bool work_with_user(GameInfo_t *game, int action, fig_info *tetris,
                    fig_start *coords) {
  bool spawn = true;
  if (action == Action) {
    move_tetris(game, tetris, coords);
  }
  if (action == Left) {
    move_left(game, tetris, coords);
  }
  if (action == Right) {
    move_right(game, tetris, coords);
  }
  if (action == Down) {
    spawn = move_down(game, tetris, coords);
  }
  return spawn;
}

void move_tetris(GameInfo_t *game, fig_info *tetris, fig_start *coords) {
  int temp_mass[4][4];
  bool check = true;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      temp_mass[j][3 - i] = tetris->square_fig[i][j];
    }
  }
  replace_next(game, tetris, coords, true);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (i + coords->i < 20 && j + coords->j < 10 && j + coords->j >= 0 &&
          i + coords->i >= 0) {
        if (game->next[i + coords->i][j + coords->j] == 1 &&
            temp_mass[i][j] == 1) {
          check = false;
        }
      } else {
        if (temp_mass[i][j] == 1) {
          check = false;
        }
      }
    }
  }
  if (check) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        tetris->square_fig[i][j] = temp_mass[i][j];
      }
    }
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (temp_mass[i][j] == 1) {
          game->next[coords->i + i][coords->j + j] = 1;
        }
      }
    }
    replace_field(game);
  }
}

bool move_down(GameInfo_t *game, fig_info *tetris, fig_start *coords) {
  bool res = true;
  replace_next(game, tetris, coords, true);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if ((coords->i + i + 1) >= 0 && (coords->i + i + 1) < 20 &&
          (coords->j + j) >= 0 && (coords->j + j) < 10 &&
          tetris->square_fig[i][j] == 1) {
        if (game->next[coords->i + i + 1][coords->j + j] == 1 && i + 1 > 3) {
          res = false;
        } else if (game->next[coords->i + i + 1][coords->j + j] == 1 &&
                   i + 1 < 4) {
          if (tetris->square_fig[i + 1][j] == 0) {
            res = false;
          }
        }
      } else if (tetris->square_fig[i][j] == 1) {
        res = false;
      }
    }
  }
  if (res) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (tetris->square_fig[i][j] == 1) {
          game->next[coords->i + i + 1][coords->j + j] = 1;
        }
      }
    }
    replace_field(game);
    coords->i = coords->i + 1;
  } else {
    for (int i = 0; i < 20; i++) {
      for (int j = 0; j < 10; j++) {
        game->next[i][j] = 0;
      }
    }
  }
  return res;
}

void move_right(GameInfo_t *game, fig_info *tetris, fig_start *coords) {
  bool check = true;
  replace_next(game, tetris, coords, true);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if ((coords->i + i) >= 0 && (coords->i + i) < 20 &&
          (coords->j + j + 1) >= 0 && (coords->j + j + 1) < 10 &&
          tetris->square_fig[i][j] == 1) {
        if (game->next[coords->i + i][coords->j + j + 1] == 1 && j + 1 > 3) {
          check = false;
        } else if (game->next[coords->i + i][coords->j + j + 1] == 1 &&
                   j + 1 < 4) {
          if (tetris->square_fig[i][j + 1] == 0) {
            check = false;
          }
        }
      } else if (tetris->square_fig[i][j] == 1) {
        check = false;
      }
    }
  }
  if (check) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (tetris->square_fig[i][j] == 1) {
          game->next[coords->i + i][coords->j + j + 1] = 1;
        }
      }
    }
    replace_field(game);
    coords->j = coords->j + 1;
  } else {
    for (int i = 0; i < 20; i++) {
      for (int j = 0; j < 10; j++) {
        game->next[i][j] = 0;
      }
    }
  }
}

void move_left(GameInfo_t *game, fig_info *tetris, fig_start *coords) {
  bool check = true;
  replace_next(game, tetris, coords, true);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if ((coords->i + i) >= 0 && (coords->i + i) < 20 &&
          (coords->j + j - 1) >= 0 && (coords->j + j - 1) < 10 &&
          tetris->square_fig[i][j] == 1) {
        if (game->next[coords->i + i][coords->j + j - 1] == 1 && j - 1 < 0) {
          check = false;
        } else if (game->next[coords->i + i][coords->j + j - 1] == 1 &&
                   j - 1 >= 0) {
          if (tetris->square_fig[i][j - 1] == 0) {
            check = false;
          }
        }
      } else if (tetris->square_fig[i][j] == 1) {
        check = false;
      }
    }
  }
  if (check) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (tetris->square_fig[i][j] == 1) {
          game->next[coords->i + i][coords->j + j - 1] = 1;
        }
      }
    }
    replace_field(game);
    coords->j = coords->j - 1;
  } else {
    for (int i = 0; i < 20; i++) {
      for (int j = 0; j < 10; j++) {
        game->next[i][j] = 0;
      }
    }
  }
}

void score_and_field(GameInfo_t *game) {
  int count_rows = 0;
  int index[4];
  for (int i = 0; i < 20; i++) {
    bool check = true;
    for (int j = 0; j < 10; j++) {
      if (game->field[i][j] == 0) {
        check = false;
      }
    }
    if (check) {
      index[count_rows] = i;
      count_rows++;
    }
  }
  if (count_rows > 0) {
    replace_next(game, NULL, NULL, false);
    for (int x = 0; x < count_rows; x++) {
      for (int i = index[x]; i > 0; i--) {
        for (int j = 0; j < 10; j++) {
          game->next[i][j] = game->next[i - 1][j];
        }
      }
    }
    for (int i = 0; i < count_rows; i++) {
      for (int j = 0; j < 10; j++) {
        game->next[i][j] = 0;
      }
    }
    replace_field(game);
  }
  if (count_rows == 1) {
    game->score = game->score + 100;
  }
  if (count_rows == 2) {
    game->score = game->score + 300;
  }
  if (count_rows == 3) {
    game->score = game->score + 700;
  }
  if (count_rows == 4) {
    game->score = game->score + 1500;
  }
  if (game->score / 600 <= 10) {
    game->speed = 55 - (game->score / 600) * 5;
  } else {
    game->speed = 5;
  }
  game->level = game->score / 600;
}