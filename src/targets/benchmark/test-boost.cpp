#include <iostream>

#include <boost/regex.hpp>

#include <CLI/App.hpp>

#include "util/util.hpp"

int main(int argc, char const* argv[]) {

  CLI::App app{"test-boost"};

  std::string document, regex;

  try {
    std::tie(document, regex) = rematch::util::handle_args(argc, argv, app);
  } catch (const CLI::ParseError& e) {
    return app.exit(e);
  }

  boost::regex pattern(regex);

  boost::match_results<std::string::const_iterator> matches;
  auto start = document.cbegin();

  // std::cout << "Pattern: \"" << regex << "\"\n";

  auto flags = boost::match_default;

  // Make '.' not match a new line
  flags |= boost::match_not_dot_newline;
  flags |= boost::match_not_null;
  flags |= boost::match_extra;

  int count = 0;

  std::ofstream dump(".tmp/boost-output.log");

  while (regex_search(start, document.cend(), matches, pattern, flags)) {
    dump << "|" << matches.position() << ','
         << matches.length() - matches.position() << ">\n";
    start = matches[0].second;
    count++;
  }

  dump.close();

  std::cout << count << '\n';

  return 0;
}