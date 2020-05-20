#include "../includes/compiler.h"
#include <stdio.h>
#include <string.h>

int find_string(string src, string query, size_t sz_src, size_t sz_query)
{
  int j = 0;
  while ((j < (sz_src - sz_query)) && (strncmp(query, src + j, sz_query))) ++j;
  return j;
}

bool is_token(char c)
{
  bool token_check = false;
  for (int i = 0; i < N_TOKENS; ++i)
    if (c == TOKENS[i])
    {
      token_check = true;
      break;
    }
  return token_check;
}

void compile_inner_text(string dest, string src, size_t sz_src,
                        string line_or_source)
{
  /* cursor is the current index on the dest pointer
   * lower represents the last tag character before content
   * upper represents the first tag character after content
   *
   * size_of_content is self explanatory (size of content delimited by tags)
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
  string md_tag, tag, close_tag;
  int i, j;

  lower = 0;
  upper = 0;
  cursor = 0;

  for (i = 0; i < sz_src; ++i)
  {
    if (is_token(src[i]))
    {
      // Information for each tag
      // NOTE: Here's where you add new text tags
      switch (src[i])
      {
      case '*': {
        // Twin asterisks
        if (src[i + 1] == '*')
        {
          md_tag = "**";
          tag = "<strong>";
          close_tag = "</strong>";
          tag_size = 8;
          md_tag_size = 2;
        }
        // one asterisk
        else
        {
          md_tag = "*";
          tag = "<i>";
          close_tag = "</i>";
          tag_size = 3;
          md_tag_size = 1;
        }
        break;
      }
      case '_': {
        tag = "<u>";
        close_tag = "</u>";
        md_tag = "_";
        tag_size = 3;
        md_tag_size = 1;
        break;
      }
      case '~': {
        tag = "<s>";
        close_tag = "</s>";
        md_tag = "~";
        tag_size = 3;
        md_tag_size = 1;
        break;
      }
      default:
        break;
      }

      if (src[i + md_tag_size] == '\0')
      {
        strncpy(dest, src + i, md_tag_size);
        break;
      }
      // find the corresponding markdown tag, and report errors
      j = find_string(src + i + md_tag_size, md_tag, sz_src - i - md_tag_size,
                      md_tag_size);
      j += i + md_tag_size;

      // error checking the token
      if (src[j] == md_tag[0])
      {
        lower = i + md_tag_size - 1;
        upper = j;
      }
      else
      {
        // error, no matching asterisk
        fprintf(stderr, "No corresponding %s for %s:%d\n", md_tag,
                line_or_source, i + md_tag_size);
        exit(0);
      }

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

  if (line[0] == '#' || line[0] == '-') // Compile a header or list item
  {
    const int tag_size = 4;
    int start_of_content;
    string tag, close_tag;
    if (line[0] == '#')
    {
      // Get the level of header (h1, h2, etc)
      int depth;
      for (depth = 1; line[depth] == '#'; ++depth) continue;
      start_of_content = depth;
      size_of_content = size_of_line - depth; // remove hashes

      // Generate the header tags based on depth
      tag = malloc(sizeof(*tag) * 5);
      close_tag = malloc(sizeof(*close_tag) * 6);
      sprintf(tag, "<h%d>", depth);
      sprintf(close_tag, "</h%d>", depth);
    }
    else
    {
      tag = "<li>";
      close_tag = "</li>";
      size_of_content = size_of_line - 1;
      start_of_content = 1;
    }

    // allocate buffer with space for content and opposing tags
    compiled_line =
        malloc(sizeof(*compiled_line) * (size_of_content + (2 * tag_size) + 2));
    // write start tag to compiled_line
    strncpy(compiled_line, tag, tag_size);
    // write the rest of the line to the compiled_line
    strncpy(compiled_line + tag_size, line + start_of_content, size_of_line);
    // write the end tags
    strncpy(compiled_line + size_of_content + tag_size, close_tag,
            tag_size + 1);
    // write the terminator
    compiled_line[size_of_content + (2 * tag_size) + 1] = '\0';
  }
  else // Compile a standard piece of text
  {
    compiled_line = malloc(sizeof(*compiled_line) * size_of_line * 2);
    compile_inner_text(compiled_line, line, size_of_line, line_or_source);
  }

  return compiled_line;
}
