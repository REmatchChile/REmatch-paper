#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include "grammar.hpp"
#include "visitors.hpp"

namespace rematch {

bool doParse(std::string_view input, ast::altern& data);
std::unique_ptr<LogicalVA> regex2LVA(std::string_view regex);

}  // end namespace rematch

#endif