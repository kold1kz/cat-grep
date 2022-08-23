#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int bflagc;
  int sflagc;
  int eflagc;
  int nflagc;
  int tflagc;
  int vflagc;
} flags;

void nepustStroki(void* fp, int* line_counter, int files);
void dollars(void* fp, int vflagc);
void numer(void* fp, int* line_counter, int files);
void podavlenie(void* fp);
void tab(void* fp, int vflagc);
void print_file(void* fp);

int main(int argc, char* argv[]) {
  flags f = {0};
  int line_counter = 1;
  int c;
  int index = 0;
  static struct option options[] = {
      {"number-nonblank", 0, NULL, 'b'}, {"show-ends", 0, NULL, 'e'},
      {"number", 0, NULL, 'n'},          {"squeeze-blank", 0, NULL, 's'},
      {"show-tabs", 0, NULL, 't'},       {NULL, 0, NULL, 0},
  };

  while ((c = getopt_long(argc, argv, "benstET", options, &index)) != -1) {
    switch (c) {
      case 'b':
        f.bflagc = 1;
        break;
      case 'e':
        f.eflagc = 1;
        f.vflagc = 1;
        break;
      case 'E':
        f.eflagc = 1;
        break;
      case 'n':
        f.nflagc = 1;
        break;
      case 's':
        f.sflagc = 1;
        break;
      case 't':
        f.tflagc = 1;
        f.vflagc = 1;
        break;
      case 'T':
        f.tflagc = 1;
        break;

      case '?':
        printf("usage: s21_cat [-benst] [file ...]");
        exit(0);
    }
  }
  int CurrentFile = optind;

  int files = argc - optind;

  while (CurrentFile < argc) {
    FILE* fp;
    fp = fopen(argv[CurrentFile], "r");
    if (fp == NULL) {
      printf("s21_cat: %s: No such file or directory", argv[CurrentFile]);
      return (0);
    } else if (f.bflagc) {
      nepustStroki(fp, &line_counter, files);
    } else if (f.eflagc) {
      dollars(fp, f.vflagc);
    } else if (f.nflagc) {
      numer(fp, &line_counter, files);
    } else if (f.sflagc) {
      podavlenie(fp);
    } else if (f.tflagc) {
      tab(fp, f.vflagc);
    } else {
      print_file(fp);
    }
    if (fp) fclose(fp);
    CurrentFile++;
  }


  // exit(0);
}

void print_file(void* fp) {
  char rut;
  while ((rut = fgetc(fp)) != EOF) {
    putchar(rut);
  }
}

void nepustStroki(void* fp, int* line_counter, int files) {
  int gig;
  char* buf = NULL;
  size_t len = 0;
  if (files) {
    //  trash
  }
  *line_counter = 1;
  // if (files > 1 && *line_counter > 1) {
  //   gig = getline(&buf, &len, fp);
  //   for (int i = 0; i < gig; i++) {
  //     printf("%c", buf[i]);
  //   }
  // }

  while ((gig = getline(&buf, &len, fp)) != -1) {
    if (gig >= 1 && buf[0] != '\n') {
      printf("%6d\t", *line_counter);
      *line_counter += 1;
    }
    for (int i = 0; i < gig; i++) {
      printf("%c", buf[i]);
    }
  }
  if (buf) free(buf);
}

void numer(void* fp, int* line_counter, int files) {
  int gig;
  char* buf = NULL;
  size_t len = 0;
  if (files) {
    //  trash
  }
  *line_counter = 1;
  // if (files > 1 && *line_counter > 1) {
  //   gig = getline(&buf, &len, fp);
  //   for (int i = 0; i < gig; i++) {
  //     printf("%c", buf[i]);
  //   }
  // }

  while ((gig = getline(&buf, &len, fp)) != -1) {
    printf("%6d\t", *line_counter);
    *line_counter += 1;
    for (int i = 0; i < gig; i++) {
      printf("%c", buf[i]);
    }
  }
  if (buf) free(buf);
}

void podavlenie(void* fp) {
  int gig;
  char* buf = NULL;
  size_t len = 0;
  int Current_line;
  int Previous_line = 1;
  while ((gig = getline(&buf, &len, fp)) != -1) {
    if (buf[0] == '\n') {
      Current_line = 1;
    } else {
      Current_line = 0;
    }
    if (Current_line && Previous_line) {
      continue;
    }
    for (int i = 0; i < gig; i++) {
      printf("%c", buf[i]);
    }
    Previous_line = Current_line;
  }
}

void tab(void* fp, int vflagc) {
  int gig;
  while ((gig = fgetc(fp)) != EOF) {
    if (gig < 32 && vflagc && gig != 9 && gig != 10) {
      printf("^%c", gig + 64);
    } else if (gig == '\t') {
      printf("^");
      printf("I");
    } else {
      printf("%c", gig);
    }
  }
}

void dollars(void* fp, int vflagc) {
  int gig;
  while ((gig = fgetc(fp)) != EOF) {
    if (gig < 32 && vflagc && gig != 9 && gig != 10) {
      printf("^%c", gig + 64);
    } else if (gig == '\n') {
      printf("$");
      printf("%c", gig);
    } else {
      printf("%c", gig);
    }
  }
}
