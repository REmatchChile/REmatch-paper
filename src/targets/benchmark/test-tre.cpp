#include <iostream>

#include <tre/tre.h>

#include "util/util.hpp"

int main(int argc, char const *argv[]) {

  CLI::App app{"test-pcre"};

  std::string document, regex;

  try {
    std::tie(document, regex) = rematch::util::handle_args(argc, argv, app);
  } catch (const CLI::ParseError& e) {
    return app.exit(e);
  }

  regex_t pattern;

  tre_regcomp(&pattern, regex.c_str(), REG_NEWLINE | REG_EXTENDED);

  regmatch_t pmatch[1] = {{0, 0}};

  auto beg = document.c_str();

  int count = 0;
  std::ofstream dump(".tmp/tre-output.log");
  while (tre_regexec(&pattern, beg, 1, pmatch, 0) == 0) {
    dump << "|" << pmatch[0].rm_so << ',' << pmatch[0].rm_eo << ">\n";
    beg += pmatch[0].rm_eo;
    count++;
  }

  dump.close();

  std::cout << count << '\n';

  return 0;
}