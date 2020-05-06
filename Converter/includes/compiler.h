#ifndef __COMPILER_H_
#define __COMPILER_H_

#include <stdlib.h>

typedef char *string;
string compile_line(string line, size_t size_of_line, string line_or_source);

#endif // __COMPILER_H_
