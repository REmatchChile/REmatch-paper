#include <iostream>

#include <CLI/App.hpp>
#include <jpcre2.hpp>

#include "util/util.hpp"

int main(int argc, char const* argv[]) {
  CLI::App app{"test-pcre"};

  std::string document, regex;

  try {
    std::tie(document, regex) = rematch::util::handle_args(argc, argv, app);
  } catch (const CLI::ParseError& e) {
    return app.exit(e);
  }

  using jp = jpcre2::select<char>;

  jp::Regex re(regex, "mS");

  jp::RegexMatch rm;
  jp::VecNum vec_num;

  std::ofstream dump(".tmp/pcre2-output.log");

  size_t count = rm.setRegexObject(&re)
                     .setSubject(&document)
                     .setModifier("g")
                     .setNumberedSubstringVector(&vec_num)
                     .match();

  std::cout << count << '\n';

  for (auto& v : vec_num) {
    for (auto& n : v) {
      dump << "|" << n << ">\n";
    }
  }

  return 0;
}
