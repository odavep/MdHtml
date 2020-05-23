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

