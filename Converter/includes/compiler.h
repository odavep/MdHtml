#ifndef __COMPILER_H_
#define __COMPILER_H_

#include <stdlib.h>

typedef char *string;
string compile_line(string line, size_t sz_line, string line_or_source);
int find_string(string src, string query, size_t sz_src, size_t sz_query);

#endif // __COMPILER_H_
