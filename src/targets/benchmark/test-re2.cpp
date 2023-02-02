#include <iostream>

#include <re2/re2.h>

#include "util/util.hpp"

int main(int argc, char const *argv[]) {

  CLI::App app{"test-pcre"};

  std::string document, regex;

  try {
    std::tie(document, regex) = rematch::util::handle_args(argc, argv, app);
  } catch (const CLI::ParseError& e) {
    return app.exit(e);
  }

  re2::StringPiece input(document);

  RE2::Options opts;
  opts.set_log_errors(false);

  rematch::util::Timer t;

  RE2 pattern(regex, opts);

  int ncapturegroups = pattern.NumberOfCapturingGroups();

  re2::StringPiece match;

  int count = 0;

  std::ofstream dump(".tmp/re2-output.log");

  // std::cout << "Input: \"" << input << "\"\n";
  // std::cout << "Pattern: \"" << rgx << "\"\n";

  while (RE2::FindAndConsume(&input, pattern, &match)) {
    for(int i = 0; i < 5; i++) {
      int ini = match.data() - document.data();
      dump << "m" << (i+1) << " = |" << ini << "," << ini + match.size() << ">\t";
    }
    dump << '\n';
    count++;
  }

  dump.close();

  std::cout << count << '\n';

  return 0;
}