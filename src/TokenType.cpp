#include "TokenType.h"
std::vector<TokenType> TokenTypeGroups::COMPARISON_TYPES = {
    TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS_EQUAL, TokenType::LESS};
std::vector<TokenType> TokenTypeGroups::EQUALITY_TYPES = {
    TokenType::DOUBLE_EQUAL, TokenType::NOT_EQUAL};
std::vector<TokenType> TokenTypeGroups::TERM_TYPES = {
    TokenType::PLUS, TokenType::MINUS};
std::vector<TokenType> TokenTypeGroups::FACTOR_TYPES = {
    TokenType::ASTERISK, TokenType::SLASH};