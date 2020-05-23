#include "../includes/compiler.hpp"
#include <vector>
#include <iostream>
#include <fstream>
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

std::string compile_file(const char *filename)
{
  std::vector<std::string> v;
  std::ifstream fp(filename);

  if (!fp.is_open())
  {
    std::cerr << "File " << filename << " not found" << std::endl;
    exit(1);
  }

  bool paragraphing = false;
  std::string line;
  for (int i = 0; std::getline(fp, line) ; ++i) {
    std::cout << "Compiled " << i + 1 << " of " << filename << "\n";
    if (line[0] == '#' || line[0] == '-')
    {
      if (paragraphing)
        v.push_back("</p>");
      paragraphing = false;
    }
    else if (line[0] == '\0' || line[0] == '\n')
    {
      if (paragraphing)
        v.push_back("</p>");
      else
        v.push_back("<p>");
      paragraphing = !paragraphing;
      continue;
    }

    v.push_back(compile_line(line.c_str()));
  }
  fp.close();

  std::string result = "";
  for (auto i : v)
    result += i + "\n";

  return result;
}
