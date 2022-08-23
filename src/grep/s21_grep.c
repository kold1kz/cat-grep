#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int cflagc;
  int eflagc;
  int iflagc;
  int lflagc;
  int nflagc;
  int vflagc;
  int hflagc;
  int sflagc;
  int oflagc;
  int fflagc;
} flags;

struct patt {
  char map[1024];
};

void flags_print(const char* at, void* fp, regex_t regex, flags f,
                 struct patt pat);
void many_file(const char* name, void* fp, regex_t regex, flags f,
               struct patt pat);
void new_pattern(regex_t* regex, char* pattern, flags f, struct patt* pat);

int main(int argc, char* argv[]) {
  flags f = {0};
  struct patt pat;
  int c;
  int cif = 0;
  int index = 0;
  char buf_e[1024] = {'\0'};
  regex_t regex;

  static struct option options[] = {
      {NULL, 0, NULL, 0},
  };

  while ((c = getopt_long(argc, argv, "ce:ilnvoshf", options, &index)) != -1) {
    switch (c) {
      case 'i':
        f.iflagc = 1;
        break;
      case 'e':
        f.eflagc = 1;
        cif++;
        if (cif == 1) {
          strcpy(buf_e, optarg);
          new_pattern(&regex, buf_e, f, &pat);
        } else {
          regfree(&regex);
          strncat(buf_e, "|", strlen(buf_e));
          strncat(buf_e, optarg, strlen(buf_e));
          new_pattern(&regex, buf_e, f, &pat);
        }
        break;
      case 'c':
        f.cflagc = 1;
        break;
      case 'h':
        f.hflagc = 1;
        break;
      case 'l':
        f.lflagc = 1;
        break;
      case 'o':
        f.oflagc = 1;
        break;
      case 'n':
        f.nflagc = 1;
        break;
      case 'v':
        f.vflagc = 1;
        break;
      case 's':
        f.sflagc = 1;
        break;
      case 'f':
        f.fflagc = 1;

        break;
      case '?':
        printf("usage: s21_grep [ceilnv] template [file_name]");
        exit(0);
    }
  }

  if (!f.eflagc) {
    new_pattern(&regex, argv[optind], f, &pat);
    optind++;
  }

  for (int i = optind; i < argc; i++) {
    FILE* fp;
    fp = fopen(argv[i], "r");

    if (!f.sflagc) {
      if (fp == NULL) {
        printf("s21_grep: %s: No such file or directory\n", argv[i]);
      } else if (argc - optind > 1) {
        many_file(argv[i], fp, regex, f, pat);
      } else {
        flags_print(argv[i], fp, regex, f, pat);
      }
    } else if (f.sflagc) {
      if (fp == NULL) {
      } else if (argc - optind > 1) {
        many_file(argv[i], fp, regex, f, pat);
      } else {
        flags_print(argv[i], fp, regex, f, pat);
      }
    }
    if (fp) fclose(fp);
  }
  regfree(&regex);
  return (0);
}

void flags_print(const char* at, void* fp, regex_t regex, flags f,
                 struct patt pat) {
  int success;
  int line_counter = 0;
  char* buf = NULL;
  size_t len = 0;
  int gig;

  while ((gig = getline(&buf, &len, fp)) != EOF) {
    if (buf[gig - 1] != '\n') {
      buf[gig] = '\n';
      buf[gig + 1] = '\0';
    }

    success = regexec(&regex, buf, 0, NULL, 0);

    if (f.iflagc) {
      if (success == 0) {
        printf("%s", buf);
      }
    } else if (f.vflagc) {
      if (success == 0) {
        continue;
      } else {
        printf("%s", buf);
      }
    } else if (f.eflagc) {
      if (success == 0) {
        printf("%s", buf);
      }
    } else if (f.cflagc) {
      if (success == 0) {
        line_counter++;
        continue;
      }
    } else if (f.lflagc) {
      if (success == 0) {
        gig = EOF;
      }
    } else if (f.oflagc) {
      if (success == 0) {
        if (pat.map[0] == '\0') {
          continue;
        } else {
          printf("%s\n", pat.map);
        }
      }
    } else if (f.nflagc) {
      if (gig) {
        line_counter++;
      }
      if (success == 0) {
        printf("%d:", line_counter);
        printf("%s", buf);
      }
    } else if (f.hflagc) {
      if (success == 0) {
        printf("%s", buf);
      }
    } else if (f.sflagc) {
      if (success == 0) {
        printf("%s", buf);
      }
      // } else if (f.oflagc) {
      //   if (success == 0) {
      //     printf("%s", &regex);
      //   }
    } else {
      if (success == 0) {
        printf("%s", buf);
      }
    }
  }

  if (f.cflagc) {
    printf("%d\n", line_counter);
  }
  if (f.lflagc) {
    printf("%s\n", at);
  }

  if (buf) free(buf);
}

void many_file(const char* name, void* fp, regex_t regex, flags f,
               struct patt pat) {
  int success;
  int line_counter = 0;
  char* buf = NULL;
  size_t len = 0;
  int gig;

  while ((gig = getline(&buf, &len, fp)) != EOF) {
    if (buf[gig - 1] != '\n') {
      buf[gig] = '\n';
      buf[gig + 1] = '\0';
    }

    success = regexec(&regex, buf, 0, NULL, 0);

    if (f.iflagc) {
      if (success == 0) {
        printf("%s:", name);
        printf("%s", buf);
      }
    } else if (f.vflagc) {
      if (success == 0) {
        continue;
      } else {
        printf("%s:", name);
        printf("%s", buf);
      }
    } else if (f.eflagc) {
      if (success == 0) {
        printf("%s:", name);
        printf("%s", buf);
      }
    } else if (f.cflagc) {
      if (success == 0) {
        line_counter++;
        continue;
      }
    } else if (f.lflagc) {
      if (success == 0) {
        gig = EOF;
      }
    } else if (f.nflagc) {
      if (gig) {
        line_counter++;
      }
      if (success == 0) {
        printf("%s:", name);
        printf("%d:", line_counter);
        printf("%s", buf);
      }
    } else if (f.hflagc) {
      if (success == 0) {
        printf("%s", buf);
      }
    } else if (f.sflagc) {
      if (success == 0) {
        printf("%s:", name);
        printf("%s", buf);
      }
    } else if (f.oflagc) {
      if (success == 0) {
        if (pat.map[0] == '\0') {
          continue;
        } else {
          printf("%s:", name);
          printf("%s\n", pat.map);
        }
      }
    } else {
      if (success == 0) {
        printf("%s:", name);
        printf("%s", buf);
      }
    }
  }
  if (f.cflagc) {
    printf("%s:", name);
    printf("%d\n", line_counter);
  }
  if (f.lflagc) {
    printf("%s\n", name);
  }
  if (buf) free(buf);
}

void new_pattern(regex_t* regex, char* pattern, flags f, struct patt* pat) {
  int mod;
  strcpy(pat->map, pattern);
  mod = REG_EXTENDED;
  if (f.iflagc) {
    mod = REG_ICASE;
  }
  regcomp(regex, pattern, mod);
}
