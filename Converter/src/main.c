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
      test_header_depths();
    }
  }
}
