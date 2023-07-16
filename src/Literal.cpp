#include "../include/Literal.h"
#include <string>
template <typename T>
Literal::Literal(const T lit)
{
    literal = lit;
}
template <typename T>
T Literal::getLiteral()
{
    return std::get<T>(literal);
}
