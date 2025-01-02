#pragma once

typedef struct flags {
  int flag_e;
  int flag_i;
  int flag_v;
  int flag_c;
  int flag_l;
  int flag_n;
  int flag_h;
  int flag_s;
  int flag_f;
  int flag_o;
} flg;

void pars_flags(int, char **, flg *, char **, int *, char **, int *, int *);
void priority_flags(flg *);
void init_flags(flg *);
void input_args_e(char **, int, char *);
void input_files_f(char **, int, char *);
void work_with_strings(flg, char **, int, char *, int *);
char **work_with_optind(int *, char **, flg, char **, int, char **, int);
void work_with_strings_f(flg, char **, int, char *, int *);
void first_output(char **, int, flg, char **, int);
void second_output(char **, int, char **);
void third_output(char **, int, flg, char **, int);
void free_mem(char **, char **);
void print_with_o(char **, int, flg, char **, char **, int, char **, int, int);