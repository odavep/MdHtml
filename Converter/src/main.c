#include "../includes/compiler.h"
#include "../includes/test.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>

string convert_filename(string filename)
{
  size_t sz_filename = strnlen(filename, 1024);
  int cur = sz_filename - 3;
  string new_filename = malloc(sizeof(*new_filename) * (sz_filename + 2));

  strncpy(new_filename, filename, sz_filename - 3);
  strncpy(new_filename + cur, ".html", 5);

  return new_filename;
}

int main(int argc, char *argv[])
{
  if (argc > 1)
  { // Test or file
    if (strcmp(argv[1], "--test") == 0)
    {
      fprintf(stderr, "Running tests\n");
      exit(0);
    }

    bool free_output = false;
    string filename;
    string output;

    if (argc >= 3)
    {
      filename = argv[1];
      output = argv[2];
    }
    else if (argc == 2)
    {
      filename = argv[1];
      output = convert_filename(filename);
      free_output = true;
    }
    else
    {
      fputs("No inputs given for files\n", stderr);
      exit(1);
    }

    FILE *fp = fopen(filename, "r");
    if (fp != NULL)
    {
      int sz_lines = nlines(fp);
      printf("Lines: %d\n", sz_lines);
      string *compiled_lines = compile_file(fp, filename, sz_lines);
      puts("Compiled document");
      fclose(fp);

      fp = fopen(output, "w");
      for (int line = 0; line < sz_lines; ++line)
      {
        fprintf(fp, "%s\n", compiled_lines[line]);
        free(compiled_lines[line]);
      }
      fclose(fp);


      printf("Written to file (%s)\n", output);
      if (free_output)
        free(output);
      free(compiled_lines);
    }
    else
    {
      fprintf(stderr, "%s is not a file\n", filename);
      exit(1);
    }
  }
  else
  { // Repl
    while (true)
    {
      string input, compiled_input;
      input = malloc(sizeof(*input) * 1024);
      fputs("> ", stdout);
      fgets(input, 1024, stdin);
      compiled_input = compile_line(input, strlen(input), "<stdin>");
      fputs(compiled_input, stdout);
      free(input);
      free(compiled_input);
    }
  }
}
