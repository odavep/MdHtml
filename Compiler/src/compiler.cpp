#include "../includes/compiler.hpp"
#include <regex>

/* Encoded regexes using the Type enum (convert to integer) */
static const std::regex REGEXES[] = {
    std::regex("\\*(.*?)\\*"), std::regex("\\*\\*(.*?)\\*\\*"),
    std::regex("_(.*?)_"), std::regex("~(.*?)~"), std::regex("-(.*)")};

/* Encoded replacement strings using the Type enum (convert to integer) */
static const char *REPLACEMENTS[] = {"<i>$1</i>", "<strong>$1</strong>",
                                     "<u>$1</u>", "<s>$1</s>", "<li>$1</li>"};

