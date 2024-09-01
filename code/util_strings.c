#include "util_strings.h"

#include <string.h>


bool utils_strstartswith(const char *complete_str, const char *starter)
{
    return (strncmp(complete_str, starter, strlen(starter)) == 0) ? true : false;
}