#include "util.hpp"

namespace rematch::util {

std::string file2str(const std::string& filename) {
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (in) {
    std::string contents;
    in.seekg(0, in.end);
    contents.resize(in.tellg());
    in.seekg(0, in.beg);
    in.read(&contents[0], contents.size());
    in.close();
    return contents;
  }
  throw std::runtime_error("Error loading file");
}

std::tuple<std::string, std::string> handle_args(int argc, char const* argv[],
                                                 CLI::App& app) {
  std::string document_path, regex_path, document, regex;

  auto document_input = app.add_option_group("document_input");
  auto regex_input = app.add_option_group("regex_input");

  document_input
      ->add_option("-d,--document,document", document_path,
                   "Input document file.")
      ->check(CLI::ExistingFile);
  document_input->add_option("-t,--text", document, "Input text.");
  document_input->require_option(1);

  regex_input
      ->add_option("-r,--regex-file,regex-file", regex_path,
                   "Input regex file.")
      ->check(CLI::ExistingFile);
  regex_input->add_option("-e,--expression", regex,
                          "Input regular expression.");
  regex_input->require_option(1);

  app.parse(argc, argv);

  if (!document_path.empty()) {
    document = file2str(document_path);
  }
  if (!regex_path.empty()) {
    regex = file2str(regex_path);
  }

  return std::make_tuple(std::move(document), std::move(regex));
}

}  // end namespace rematch::util