#include <malloc.h>
#include <stdio.h>
#include <string.h>

typedef char *string;

string compile_line(string line, size_t size_of_line)
{
  string compiled_line;
  size_t size_of_content;

  if (line[0] == '#')
  {
    // Compile a header

    // Get the level of header (h1, h2, etc)
    int depth;
    for (depth = 1; line[depth] == '#'; ++depth);
    size_of_content = size_of_line - depth; // remove hashes

    // Generate the header tags based on depth
    const int tag_size = 4;
    const int close_tag_size = 5;
    string tag = malloc(sizeof(*tag) * 5);
    sprintf(tag, "<h%d>", depth);
    string close_tag = malloc(sizeof(*close_tag) * 6);
    sprintf(close_tag, "</h%d>", depth);

    // allocate buffer with extra 9 characters for the tags
    compiled_line = malloc(sizeof(*compiled_line) *
                           (size_of_line + tag_size + close_tag_size));
    // write h1 to start of compiled_line
    strncpy(compiled_line, tag, tag_size);
    // write the rest of the line to the compiled_line
    strncpy(compiled_line + tag_size, line + depth, size_of_line);
    // write the end tags
    strncpy(compiled_line + size_of_content + tag_size, close_tag, close_tag_size);
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
