#include <iostream>

#include <pcrecpp.h>
#include <CLI/App.hpp>

#include "util/util.hpp"

int main(int argc, char const* argv[]) {
  CLI::App app{"test-pcre"};

  std::string document, regex;

  try {
    std::tie(document, regex) = rematch::util::handle_args(argc, argv, app);
  } catch (const CLI::ParseError& e) {
    return app.exit(e);
  }

  pcrecpp::RE re(regex);
  pcrecpp::StringPiece input(document);

  pcrecpp::StringPiece match;

  std::ofstream dump(".tmp/pcre-output.log");

  int count = 0;
  while (re.FindAndConsume(&input, &match)) {
    long ini = match.data() - document.data();
    dump << "|" << ini << "," << ini + match.size() << "> (x = \"" << match << "\")\n";
    count++;
  }

  dump.close();

  std::cout << count << '\n';

  return 0;
}
