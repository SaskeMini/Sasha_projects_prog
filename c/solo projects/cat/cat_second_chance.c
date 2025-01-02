#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cat_headers.h"

int main(int argc, char **argv) {
  struct flags flags_now;
  flags_now.flag_b = 0;
  flags_now.flag_e = 0;
  flags_now.flag_n = 0;
  flags_now.flag_s = 0;
  flags_now.flag_tab = 0;
  flags_now.flag_v = 0;
  int all_check = 1;
  char mass_of_options[11][20] = {
      "-b", "--number-nonblank", "-e", "-v", "-E", "-n", "--number",
      "-s", "--squeeze-blank",   "-t", "-T"};
  for (int i = 1; i < argc; i++) {
    int check = 0;
    for (int j = 0; j < 11; j++) {
      if (strcmp(argv[i], mass_of_options[j]) == 0) {
        check = 1;
        if (strcmp(argv[i], "-e") == 0) {
          flags_now.flag_e = 1;
          flags_now.flag_v = 1;
        }
        if (strcmp(argv[i], "-E") == 0) {
          flags_now.flag_e = 1;
        }
        if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--number") == 0) {
          flags_now.flag_n = 1;
        }
        if (strcmp(argv[i], "-b") == 0 ||
            strcmp(argv[i], "--number-nonblank") == 0) {
          flags_now.flag_b = 1;
        }
        if (strcmp(argv[i], "-s") == 0 ||
            strcmp(argv[i], "--squeeze-blank") == 0) {
          flags_now.flag_s = 1;
        }
        if (strcmp(argv[i], "-t") == 0) {
          flags_now.flag_tab = 1;
          flags_now.flag_v = 1;
        }
        if (strcmp(argv[i], "-T") == 0) {
          flags_now.flag_tab = 1;
        }
        if (strcmp(argv[i], "-v") == 0) {
          flags_now.flag_v = 1;
        }
      }
    }
    if (check == 0) {
      FILE *temp = fopen(argv[i], "r");
      if (temp == NULL) {
        all_check = 0;
        break;
      }
      fclose(temp);
    }
  }
  if (all_check == 0) {
    fprintf(stdout, "n/a");
  } else {
    print_and_create(&flags_now, argv, argc);
  }
  return 0;
}

void print_and_create(struct flags *flags_now, char **argv, int argc) {
  int len_mass_str = -1;
  int len_to_flag_b = 0;
  FILE *temp;
  char symbol;
  int to_flag_s = 0;
  int len_str = 0;
  for (int i = 1; i < argc; i++) {
    char mass_of_options[11][20] = {
        "-b", "--number-nonblank", "-e", "-v", "-E", "-n", "--number",
        "-s", "--squeeze-blank",   "-t", "-T"};
    int check = 0;
    for (int j = 0; j < 11; j++) {
      if (strcmp(argv[i], mass_of_options[j]) == 0) {
        check = 1;
      }
    }
    if (check == 0) {
      temp = fopen(argv[i], "r");
      symbol = fgetc(temp);
      while (!feof(temp)) {
        if (len_str == 0) {
          len_mass_str++;
          if (flags_now->flag_b == 1 && symbol != '\n') {
            fprintf(stdout, "%6d	", len_mass_str + 1 - len_to_flag_b);
            len_str = 1;
          } else if (flags_now->flag_b == 1 && symbol == '\n' &&
                     (flags_now->flag_s == 0 || to_flag_s == 0)) {
            len_to_flag_b++;
          } else if (flags_now->flag_n == 1 &&
                     (to_flag_s == 0 || symbol != '\n')) {
            fprintf(stdout, "%6d	", len_mass_str + 1);
          }
        }
        if (to_flag_s == 1 && symbol == '\n' && flags_now->flag_s == 1) {
          len_mass_str--;
          len_str = 0;
        } else if (flags_now->flag_e == 1 && symbol == '\n') {
          fprintf(stdout, "$\n");
          len_str = 0;
        } else if (flags_now->flag_tab == 1 && symbol == '\t') {
          fprintf(stdout, "^I");
          len_str = 1;
        } else if (flags_now->flag_v == 1 &&
                   ((symbol >= 0 && symbol <= 31) || symbol == 127 ||
                    symbol < 0) &&
                   symbol != '\n' && symbol != '\t') {
          if (symbol >= 0 && symbol <= 31 && symbol != '\n' && symbol != '\t') {
            fprintf(stdout, "^%c", symbol + 64);
          } else if (symbol == 127) {
            fprintf(stdout, "^%c", symbol - 64);
          } else if (symbol < 0) {
            fprintf(stdout, "M-");
            char sym = 128 - (symbol * -1);
            if (sym >= 0 && sym <= 31 && symbol != '\t') {
              fprintf(stdout, "^%c", sym + 64);
            } else if (sym == 127) {
              fprintf(stdout, "^%c", sym - 64);
            } else {
              fprintf(stdout, "%c", sym);
            }
          }
        } else {
          fprintf(stdout, "%c", symbol);
        }
        if (symbol == '\n' && len_str == 0 && flags_now->flag_s == 1) {
          to_flag_s = 1;
          len_str = 0;
        } else if (symbol == '\n') {
          len_str = 0;
        } else if (symbol != '\n') {
          to_flag_s = 0;
          len_str = 1;
        }
        symbol = fgetc(temp);
      }
      fclose(temp);
    }
  }
}