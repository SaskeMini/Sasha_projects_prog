#include "s21_grep.h"

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  flg flags_now;
  init_flags(&flags_now);
  char **mass_args_e;
  mass_args_e = malloc(sizeof(char *) * 1024);
  char **mass_files_f;
  mass_files_f = malloc(sizeof(char *) * 1024);
  for (int i = 0; i < 1024; i++) {
    mass_args_e[i] = malloc(512 * sizeof(char));
    mass_files_f[i] = malloc(512 * sizeof(char));
  }
  int len_mass_args_e = 0;
  int len_mass_files_f = 0;
  int all_check = 1;
  pars_flags(argc, argv, &flags_now, mass_args_e, &len_mass_args_e,
             mass_files_f, &len_mass_files_f, &all_check);
  if (all_check) {
    priority_flags(&flags_now);
    int check_to_flag_h = 0;
    if (optind < argc - 1) {
      check_to_flag_h = 1;
    }
    while (optind < argc) {
      char **necessary_strings;
      int len_necessary_strings = 0;
      necessary_strings =
          work_with_optind(&len_necessary_strings, argv, flags_now, mass_args_e,
                           len_mass_args_e, mass_files_f, len_mass_files_f);
      if (necessary_strings) {
        if (flags_now.flag_c == 0 && flags_now.flag_l == 0) {
          if (flags_now.flag_o == 1) {
            print_with_o(necessary_strings, len_necessary_strings, flags_now,
                         argv, mass_args_e, len_mass_args_e, mass_files_f,
                         len_mass_files_f, check_to_flag_h);
          } else {
            first_output(necessary_strings, len_necessary_strings, flags_now,
                         argv, check_to_flag_h);
          }
        } else if (flags_now.flag_l == 1) {
          second_output(necessary_strings, len_necessary_strings, argv);
        } else {
          third_output(necessary_strings, len_necessary_strings, flags_now,
                       argv, check_to_flag_h);
        }
        for (int i = 0; i < 1024; i++) {
          free(necessary_strings[i]);
        }
        free(necessary_strings);
      } else {
        if (flags_now.flag_s == 0) {
          fprintf(stderr, "No such file or directory\n");
        }
      }
      optind++;
    }
  } else {
    fprintf(stderr, "Error");
  }
  free_mem(mass_args_e, mass_files_f);
  return 0;
}

void free_mem(char **mass_args_e, char **mass_files_f) {
  for (int i = 0; i < 1024; i++) {
    free(mass_args_e[i]);
  }
  free(mass_args_e);
  for (int i = 0; i < 1024; i++) {
    free(mass_files_f[i]);
  }
  free(mass_files_f);
}

void init_flags(flg *flags_now) {
  flags_now->flag_c = 0;
  flags_now->flag_e = 0;
  flags_now->flag_f = 0;
  flags_now->flag_h = 0;
  flags_now->flag_i = 0;
  flags_now->flag_l = 0;
  flags_now->flag_n = 0;
  flags_now->flag_o = 0;
  flags_now->flag_s = 0;
  flags_now->flag_v = 0;
}

void first_output(char **necessary_strings, int len_necessary_strings,
                  flg flags_now, char **argv, int check_to_flag_h) {
  for (int i = 0; i < len_necessary_strings; i++) {
    if (strcmp(necessary_strings[i], "\0") != 0) {
      if (check_to_flag_h == 1 && flags_now.flag_h == 0) {
        fprintf(stdout, "%s:", argv[optind]);
      }
      if (flags_now.flag_n == 1) {
        fprintf(stdout, "%d:", i + 1);
      }
      fprintf(stdout, "%s", necessary_strings[i]);
    }
  }
}

void third_output(char **necessary_strings, int len_necessary_strings,
                  flg flags_now, char **argv, int check_to_flag_h) {
  int count_str = 0;
  for (int i = 0; i < len_necessary_strings; i++) {
    if (strcmp(necessary_strings[i], "\0") != 0) {
      count_str++;
    }
  }
  if (check_to_flag_h == 1 && flags_now.flag_h == 0) {
    fprintf(stdout, "%s:", argv[optind]);
  }
  fprintf(stdout, "%d", count_str);
  fprintf(stdout, "\n");
}

void second_output(char **necessary_strings, int len_necessary_strings,
                   char **argv) {
  int check = 0;
  for (int i = 0; i < len_necessary_strings; i++) {
    if (strcmp(necessary_strings[i], "\0") != 0) {
      check = 1;
    }
  }
  if (check == 1) {
    fprintf(stdout, "%s", argv[optind]);
    fprintf(stdout, "\n");
  }
}

char **work_with_optind(int *len_necessary_strings, char **argv, flg flags_now,
                        char **mass_args_e, int len_mass_args_e,
                        char **mass_files_f, int len_mass_files_f) {
  char **necessary_strings = malloc(1024 * sizeof(char *));
  for (int i = 0; i < 1024; i++) {
    necessary_strings[i] = malloc(512 * sizeof(char));
  }
  for (int x = 0; x < len_mass_files_f; x++) {
    FILE *ch = fopen(mass_files_f[x], "r");
    if (!ch) {
      for (int i = 0; i < 1024; i++) {
        free(necessary_strings[i]);
      }
      free(necessary_strings);
      necessary_strings = NULL;
      return necessary_strings;
    }
    fclose(ch);
  }
  FILE *input = fopen(argv[optind], "r");
  if (input) {
    char *buffer = malloc(sizeof(char) * 512);
    while (fgets(buffer, 512, input)) {
      int res = 0;
      work_with_strings(flags_now, mass_args_e, len_mass_args_e, buffer, &res);
      if (res == 0 && flags_now.flag_f == 1) {
        work_with_strings_f(flags_now, mass_files_f, len_mass_files_f, buffer,
                            &res);
      }
      if ((res == 1 && flags_now.flag_v == 0) ||
          (res == 0 && flags_now.flag_v == 1)) {
        strcpy(necessary_strings[*len_necessary_strings], buffer);
      } else {
        strcpy(necessary_strings[*len_necessary_strings], "\0");
      }
      *len_necessary_strings = *len_necessary_strings + 1;
    }
    free(buffer);
    fclose(input);
  }
  if (!input) {
    for (int i = 0; i < 1024; i++) {
      free(necessary_strings[i]);
    }
    free(necessary_strings);
    necessary_strings = NULL;
  }
  return necessary_strings;
}

void print_with_o(char **necessary_strings, int len_necessary_strings,
                  flg flags_now, char **argv, char **mass_args_e,
                  int len_mass_args_e, char **mass_files_f,
                  int len_mass_files_f, int check_to_flag_h) {
  regex_t regexx;
  char *buffer = malloc(sizeof(char) * 512);
  for (int i = 0; i < len_necessary_strings; i++) {
    for (int j = 0; j < 512; j++) {
      buffer[j] = 0;
    }
    size_t nmatch = 1;
    regmatch_t pmatch[1];
    if (flags_now.flag_e == 1) {
      for (int x = 0; x < len_mass_args_e; x++) {
        int temp = 0;
        regoff_t start_ind = 0;
        if (flags_now.flag_i == 1) {
          temp = regcomp(&regexx, mass_args_e[x],
                         REG_EXTENDED | REG_ICASE | REG_NEWLINE);
        } else {
          temp = regcomp(&regexx, mass_args_e[x], REG_EXTENDED | REG_NEWLINE);
        }
        if (temp == 0) {
          while (1) {
            if (regexec(&regexx, necessary_strings[i] + start_ind, nmatch,
                        pmatch, 0) == 0) {
              if (strcmp(necessary_strings[i], "\0") != 0) {
                if (check_to_flag_h == 1 && flags_now.flag_h == 0) {
                  fprintf(stdout, "%s:", argv[optind]);
                }
                if (flags_now.flag_n == 1) {
                  fprintf(stdout, "%d:", i + 1);
                }
              }
              for (int y = pmatch[0].rm_so + start_ind;
                   y < pmatch[0].rm_eo + start_ind; y++) {
                buffer[y] = 1;
                fprintf(stdout, "%c", necessary_strings[i][y]);
              }
              fprintf(stdout, "\n");
              start_ind = start_ind + pmatch[0].rm_eo;
            } else {
              break;
            }
          }
        }
        regfree(&regexx);
      }
    }
    if (flags_now.flag_f == 1) {
      char *buffer_2 = NULL;
      for (int x = 0; x < len_mass_files_f; x++) {
        FILE *patt = fopen(mass_files_f[x], "r");
        size_t len = 0;
        int read = 0;
        while ((read = getline(&buffer_2, &len, patt)) != -1) {
          if (buffer_2[read - 1] == '\n' || buffer_2[read - 1] == '\0') {
            buffer_2[read - 1] = '\0';
          }
          int temp = -1;
          regoff_t start_ind = 0;
          if (flags_now.flag_i == 1) {
            temp = regcomp(&regexx, buffer_2,
                           REG_EXTENDED | REG_ICASE | REG_NEWLINE);
          } else {
            temp = regcomp(&regexx, buffer_2, REG_EXTENDED | REG_NEWLINE);
          }
          if (temp == 0) {
            while (1) {
              if (regexec(&regexx, necessary_strings[i] + start_ind, nmatch,
                          pmatch, 0) == 0) {
                int temp_check = 1;
                for (int y = pmatch[0].rm_so + start_ind;
                     y < pmatch[0].rm_eo + start_ind; y++) {
                  if (buffer[y] == 1) {
                    temp_check = 0;
                  }
                }
                if (strcmp(necessary_strings[i], "\0") == 0) {
                  temp_check = 0;
                }
                if (temp_check == 1) {
                  if (strcmp(necessary_strings[i], "\0") != 0) {
                    if (check_to_flag_h == 1 && flags_now.flag_h == 0) {
                      fprintf(stdout, "%s:", argv[optind]);
                    }
                    if (flags_now.flag_n == 1) {
                      fprintf(stdout, "%d:", i + 1);
                    }
                  }
                  for (int y = pmatch[0].rm_so + start_ind;
                       y < pmatch[0].rm_eo + start_ind; y++) {
                    buffer[y] = 1;
                    fprintf(stdout, "%c", necessary_strings[i][y]);
                  }
                }
                if (temp_check == 1) {
                  fprintf(stdout, "\n");
                }
                start_ind = start_ind + pmatch[0].rm_eo;
              } else {
                break;
              }
            }
          }
          regfree(&regexx);
        }
        fclose(patt);
      }
      free(buffer_2);
    }
  }
  free(buffer);
}

void work_with_strings_f(flg flags_now, char **mass_files_f,
                         int len_mass_files_f, char *string, int *res) {
  regex_t regexx;
  char *buffer_2 = NULL;
  for (int x = 0; x < len_mass_files_f; x++) {
    FILE *patt = fopen(mass_files_f[x], "r");
    size_t len = 0;
    int read = 0;
    while ((read = getline(&buffer_2, &len, patt)) != -1) {
      if (buffer_2[read - 1] == '\n' || buffer_2[read - 1] == '\0') {
        buffer_2[read - 1] = '\0';
      }
      int temp = -1;
      if (flags_now.flag_i == 1) {
        temp =
            regcomp(&regexx, buffer_2, REG_EXTENDED | REG_ICASE | REG_NEWLINE);
      } else {
        temp = regcomp(&regexx, buffer_2, REG_EXTENDED | REG_NEWLINE);
      }
      if (temp == 0) {
        if (regexec(&regexx, string, 0, NULL, 0) == 0) {
          *res = 1;
        }
      }
      if (*res == 1) {
        break;
      }
      regfree(&regexx);
    }
    fclose(patt);
    if (*res == 1) {
      break;
    }
  }
  free(buffer_2);
  regfree(&regexx);
}

void work_with_strings(flg flags_now, char **mass_args_e, int len_mass_args_e,
                       char *string, int *res) {
  for (int x = 0; x < len_mass_args_e; x++) {
    regex_t regexx;
    int temp = -1;
    if (flags_now.flag_i == 1) {
      temp = regcomp(&regexx, mass_args_e[x],
                     REG_EXTENDED | REG_ICASE | REG_NEWLINE);
    } else {
      temp = regcomp(&regexx, mass_args_e[x], REG_EXTENDED | REG_NEWLINE);
    }
    if (temp == 0) {
      if (regexec(&regexx, string, 0, NULL, 0) == 0) {
        *res = 1;
      }
    }
    regfree(&regexx);
  }
}

void priority_flags(flg *flags_now) {
  if (flags_now->flag_l == 1) {
    flags_now->flag_n = 0;
    flags_now->flag_o = 0;
  }
  if (flags_now->flag_c == 1) {
    flags_now->flag_n = 0;
    flags_now->flag_o = 0;
  }
}

void pars_flags(int argc, char **argv, flg *flags_now, char **mass_args_e,
                int *len_mass_args_e, char **mass_files_f,
                int *len_mass_files_f, int *check) {
  char opt = getopt(argc, argv, "e:ivclnhsf:o");
  while (opt != -1) {
    switch (opt) {
      case 'e':
        flags_now->flag_e = 1;
        input_args_e(mass_args_e, *len_mass_args_e, optarg);
        *len_mass_args_e = *len_mass_args_e + 1;
        break;
      case 'i':
        flags_now->flag_i = 1;
        break;
      case 'v':
        flags_now->flag_v = 1;
        break;
      case 'c':
        flags_now->flag_c = 1;
        break;
      case 'l':
        flags_now->flag_l = 1;
        break;
      case 'n':
        flags_now->flag_n = 1;
        break;
      case 'h':
        flags_now->flag_h = 1;
        break;
      case 's':
        flags_now->flag_s = 1;
        break;
      case 'f':
        flags_now->flag_f = 1;
        input_files_f(mass_files_f, *len_mass_files_f, optarg);
        *len_mass_files_f = *len_mass_files_f + 1;
        break;
      case 'o':
        flags_now->flag_o = 1;
        break;
      default:
        *check = 0;
        break;
    }
    opt = getopt(argc, argv, "e:ivclnhsf:o");
  }
  if (flags_now->flag_e == 0 && flags_now->flag_f == 0) {
    flags_now->flag_e = 1;
    input_args_e(mass_args_e, *len_mass_args_e, argv[optind]);
    *len_mass_args_e = *len_mass_args_e + 1;
    optind++;
  }
}

void input_args_e(char **mass_args_e, int len_mass_args_e, char *arg_opt) {
  strcpy(mass_args_e[len_mass_args_e], arg_opt);
}

void input_files_f(char **mass_files_f, int len_mass_files_f, char *arg_opt) {
  strcpy(mass_files_f[len_mass_files_f], arg_opt);
}