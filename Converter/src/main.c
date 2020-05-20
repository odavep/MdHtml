#include "../includes/compiler.h"
#include "../includes/test.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
  if (argc > 1)
  {
    if (strncmp(argv[1], "--test", 7) == 0)
    {
      // run tests
      fputs("Running header test (how does compile_string handle # headers?)\n",
            stderr);
      compile_line_header_depth();
    }
    else
    {
      string output =
          (compile_line(argv[1], strnlen(argv[1], 1024), "<stdin>"));
      puts(output);
      free(output);
    }
  }
  else
  {
    int i;
    char *buf;
    while (1)
    {

      printf("> ");
      buf = malloc(sizeof(*buf) * 1024);
      fgets(buf, 1024, stdin);

      for (i = 0; buf[i] != '\n'; ++i) continue;
      buf[i] = '\0'; // terminate

      string output = (compile_line(buf, strlen(buf), "<stdin>"));
      puts(output);
      free(output);
    }
  }
}
