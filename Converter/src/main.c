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
      fputs("Running header test (how does compile_string handle # headers?)\n", stderr);
      test_compile_line_header_depth();
    }
    else
    {
      puts(compile_line(argv[1], strnlen(argv[1], 1024), "<stdin>"));
    }
  }

  else
  {
    while (1)
    {
      printf("> ");
      char *buf = malloc(sizeof(*buf) * 1024);
      fgets(buf, 1024, stdin);
      puts(compile_line(buf, 1024, "<stdin>"));
    }
  }
}
