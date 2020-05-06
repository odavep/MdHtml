#include "../includes/compiler.h"
#include <stdio.h>
#include <string.h>

void compile_inner_text(string dest, string src, size_t size_of_line,
                        string line_or_source)
{
  /* cursor is the current index on the dest pointer
   * lower represents the last tag character before content
   * upper represents the first tag character after content
   *
   * size_of_content is self explanatory (size of content in tags)
   * tag_size is the compiled size of a tag
   * md_tag_size is the precompiled size of a tag
   *
   * tag is the string for the open HTML tag
   * close_tag is the string for the close HTML tag
   *
   * i and j are iterator variables
   */
  int cursor, lower, upper;
  size_t size_of_content, tag_size, md_tag_size;
  string tag, close_tag;
  int i, j;

  lower = 0;
  upper = 0;
  cursor = 0;

  for (i = 0; i < size_of_line; ++i)
  {
    // Asterisk routine
    if (src[i] == '*')
    {
      j = i + 1;

      // Twin asterisks
      if (src[i + 1] == '*')
      {
        tag = "<strong>";
        close_tag = "</strong>";
        tag_size = 8;
        md_tag_size = 2;

        // Make j the cursor seeking for the matching asterisk pair
        while ((j < size_of_line - 1) && (src[j] != '*' || src[j + 1] != '*'))
          ++j;

        // if found
        if (src[j] == '*')
        {
          lower = i + 1;
          upper = j;
        }
        else
        {
          // ERROR
          fprintf(stderr, "No matching asterisk for %s:%d\n", line_or_source,
                  i);
          exit(-1);
        }
      }

      // one asterisk
      else
      {
        tag = "<i>";
        close_tag = "</i>";
        tag_size = 3;
        md_tag_size = 1;
        while ((j < size_of_line) && (src[j] != '*')) ++j;

        if (src[j] == '*')
        {
          lower = i;
          upper = j;
        }
        else
        {
          // error, no matching asterisk
          fprintf(stderr, "No matching asterisk for %s:%d\n", line_or_source,
                  i);
          exit(-1);
        }
      }

      /*
       * Copy all
       */
      size_of_content = upper - lower - 1;
      strncpy(dest + cursor, tag, tag_size);
      strncpy(dest + cursor + tag_size, src + lower + 1, size_of_content);
      strncpy(dest + cursor + tag_size + size_of_content, close_tag,
              tag_size + 1);
      cursor +=
          tag_size + size_of_content + tag_size + 1; // shift after operation
      i += size_of_content + (2 * md_tag_size) - 1;
    }
    else
    {
      strncpy(dest + cursor, &src[i], 1);
      cursor += 1;
    }
  }
}

string compile_line(string line, size_t size_of_line, string line_or_source)
{
  string compiled_line;
  size_t size_of_content;

  // Compile a header
  if (line[0] == '#')
  {
    // Get the level of header (h1, h2, etc)
    int depth;
    for (depth = 1; line[depth] == '#'; ++depth) continue;
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
                           (size_of_line + tag_size + close_tag_size + 3));
    // write h1 to start of compiled_line
    strncpy(compiled_line, tag, tag_size);
    // write the rest of the line to the compiled_line
    strncpy(compiled_line + tag_size, line + depth, size_of_line);
    // write the end tags
    strncpy(compiled_line + size_of_content + tag_size, close_tag,
            close_tag_size + 1);
  }
  else
  {
    // Assume standard text
    compiled_line = malloc(sizeof(*compiled_line) * size_of_line * 2);
    compile_inner_text(compiled_line, line, size_of_line, line_or_source);
  }

  return compiled_line;
}
