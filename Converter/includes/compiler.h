#ifndef __COMPILER_H_
#define __COMPILER_H_

#include <stdlib.h>
#include <stdbool.h>

typedef char *string;
const static char TOKENS[] = {'*', '_'};
const static size_t N_TOKENS = 2;

string compile_line(string line, size_t sz_line, string line_or_source);
int find_string(string src, string query, size_t sz_src, size_t sz_query);
bool is_token(char c);

#endif // __COMPILER_H_
