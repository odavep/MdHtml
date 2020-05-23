#include "../includes/compiler.hpp"
#include <regex>

static const unsigned short N_ITEMS = 4;
/* Encoded regexes using the Type enum (convert to integer) */
static const std::regex REGEXES[] = {
    std::regex("\\*\\*(.*?)\\*\\*"), std::regex("\\*(.*?)\\*"),
    std::regex("_(.*?)_"), std::regex("~(.*?)~")};

/* Encoded replacement strings using the Type enum (convert to integer) */
static const char *REPLACEMENTS[] = {"<strong>$1</strong>", "<i>$1</i>",
                                     "<u>$1</u>", "<s>$1</s>"};

std::string compile_line(const char *raw)
{
  std::string result;
  char *r;

  if (raw[0] == '#')
  {
    // Get depth of header
    int depth;
    for (depth = 0; (*(raw + depth)) == '#' && depth < 7; ++depth);

    asprintf(&r, "<h%d>%s</h%d>", depth, raw + depth, depth);
    return r;
  }
  else if (raw[0] == '-')
  {
    asprintf(&r, "<li>%s</li>", raw + 1);
    return r;
  }

  result = raw;
  for (int i = 0; i < N_ITEMS; ++i)
  {
    result = std::regex_replace(result, REGEXES[i], REPLACEMENTS[i]);
  }

  return result;
}
