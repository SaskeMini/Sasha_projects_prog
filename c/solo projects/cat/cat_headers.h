#pragma once

struct flags {
  int flag_b;
  int flag_e;
  int flag_n;
  int flag_s;
  int flag_tab;
  int flag_v;
};

void print_and_create(struct flags *flags_now, char **argv, int argc);