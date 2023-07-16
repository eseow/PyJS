#include <string>
#include <variant>
#ifndef LITERAL_H
#define LITERAL_H
class Literal
{
public:
    template <typename T>
    Literal(const T literal);
    template <typename T>
    T getLiteral();

private:
    std::variant<int, std::string, double, void *> literal;
};
#endif