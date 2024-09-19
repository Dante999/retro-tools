#ifndef UTIL_STRINGS_H
#define UTIL_STRINGS_H

#include <stdbool.h>

bool  utils_strstartswith(const char *complete_str, const char *starter);
char* utils_strltrim(char *s);
char* utils_strrtrim(char *s);
char* utils_strtrim(char *s);


#endif /* UTIL_STRINGS_H */
