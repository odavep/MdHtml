#ifndef __COMPILER_H_
#define __COMPILER_H_

#include <string>

enum Type
{
  Bold,
  Italic,
  Underline,
  StrikeThrough,
  ListItem,
  Heading
};

std::string compile_line(const char *raw);
std::string compile_file(const char *filename);

#endif // __COMPILER_H_
