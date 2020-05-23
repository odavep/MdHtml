#ifndef __COMPILER_H_
#define __COMPILER_H_

#include <string>

enum Type
{
  Italic,
  Bold,
  Underline,
  StrikeThrough,
  ListItem,
  Heading
};

std::string compile_line(const char *raw);

#endif // __COMPILER_H_
