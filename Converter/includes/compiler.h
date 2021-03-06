#ifndef __COMPILER_H_
#define __COMPILER_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef char *string;
const static char TOKENS[] = {'*', '_', '~'};
const static size_t N_TOKENS = 3;

/* Compile markdown line to HTML line */
string compile_line(string line, size_t sz_line, string line_or_source);
/* Given a source string, find a given substring, returning it's index of occurence*/
int find_string(string src, string query, size_t sz_src, size_t sz_query);
/* Check if a given character is a text token*/
bool is_token(char c);

/* Given a file, get number of lines */
int nlines(FILE *fp);
/* Given a file, compile the lines */
string *compile_file(FILE *fp, string filename, int nlines);

#endif // __COMPILER_H_
