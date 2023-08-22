#ifndef EXPRESSION_VISITOR_H
#define EXPRESSION_VISITOR_H
#include "Expressions/Inline.h"
#include "Expressions/Primary.h"
#include "Expressions/Comparison.h"
#include "Expressions/Equality.h"
#include "Expressions/Binary.h"
#include "Expressions/Unary.h"
#include "Expressions/Factor.h"
#include "Expressions/Term.h"
#include <string>
#define EXPRESSION_VISITOR_H
class ExpressionVisitor
{
public:
    static std::string accept(InlineExpr *expr);
    static std::string accept(Primary *expr);
    static std::string accept(ComparisonExpr *expr);
    static std::string accept(EqualityExpr *expr);
    static std::string accept(BinaryExpr *expr);
    static std::string accept(UnaryExpr *expr);
    static std::string accept(FactorExpr *expr);
    static std::string accept(TermExpr *expr);
};
#endif