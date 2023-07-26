#ifndef EXPRESSION_VISITOR_H
#define EXPRESSION_VISITOR_H
#include "Expressions/Inline.h"
#include "Expressions/Primary.h"
#include "Expressions/Comparison.h"
#include <string>
#define EXPRESSION_VISITOR_H
class ExpressionVisitor
{
public:
    static std::string accept(InlineExpr *expr);
    static std::string accept(Primary *expr);
    static std::string accept(ComparisonExpr *expr);
};
#endif