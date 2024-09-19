#include "util_strings.h"

#include <string.h>



static bool is_whitespace(char c)
{
	return (strchr(" \t\r\n", c) != NULL) ? true : false;
}

char *utils_strltrim(char *s)
{
	const size_t len = strlen(s);

	if (len == 0) {
		return s;
	}

	if (!is_whitespace(*s)) {
		return s;
	}

	size_t idx_src = 0;
	size_t idx_dst = 0;

	while (is_whitespace(s[idx_src]) && idx_src < len) {
		++idx_src;
	}

	while (idx_src < len) {
		s[idx_dst++] = s[idx_src++];
	}

	s[idx_dst] = '\0';
	return s;
}

char* utils_strrtrim(char *s) {

	size_t idx_end = strlen(s);

	if (idx_end == 0) {
		return s;
	}

	--idx_end;

	while (is_whitespace(s[idx_end]) && idx_end > 0) {
		s[idx_end--] = '\0';
	}


	return s;
}

char* utils_strtrim(char *s) {
	utils_strrtrim(s);
	return utils_strltrim(s);
}

bool utils_strstartswith(const char *complete_str, const char *starter)
{
	return (strncmp(complete_str, starter, strlen(starter)) == 0) ? true : false;
}


