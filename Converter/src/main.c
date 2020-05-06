#include <malloc.h>
#include <stdio.h>
#include <string.h>

typedef char *string;

string compile_line(string line, size_t size_of_line)
{
  string compiled_line;
  if (line[0] == '#')
  {
    // Compile a header

    // allocate buffer with extra 9 characters for the tags
    compiled_line = malloc(sizeof(*compiled_line) * (size_of_line + 9));
    // write h1 to start of compiled_line
    strncpy(compiled_line, "<h1>", 4);
    // write the rest of the line to the compiled_line
    strncpy(compiled_line + 4, line + 1, size_of_line - 1);
    // write the end tags
    strncpy(compiled_line + size_of_line + 3, "</h1>", 5);
  }

  else
  {
    compiled_line = malloc(sizeof(*compiled_line) * size_of_line);
    strncpy(compiled_line, line, size_of_line);
  }

  return compiled_line;
}

int main()
{
  return 0;
}
