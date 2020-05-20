#include "../includes/compiler.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void compile_line_header_depth(void)
{
  const int test_size = 5;
  string test_strings[] = {"Header", "#Header", "##Header", "#Header#",
                           "#####Header"};
  string expected_results[] = {"Header", "<h1>Header</h1>", "<h2>Header</h2>",
                               "<h1>Header#</h1>", "<h5>Header</h5>"};

  for (int i = 0; i < test_size; ++i)
  {
    const string test_string = test_strings[i];
    const string expected_result = expected_results[i];
    const int length_of_test = strnlen(test_string, 512);
    const int length_of_expected = strnlen(expected_result, 512);
    const string test_result = compile_line(test_string, length_of_test, "<test>");

    fprintf(stderr, "Testing %s => %s\n", test_string, expected_result);
    fprintf(stderr, "Result: %s\n\n", test_result);

    assert(strncmp(test_result, expected_result, length_of_expected) == 0);
  }
}
