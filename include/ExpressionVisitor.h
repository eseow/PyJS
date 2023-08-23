#ifndef EXPRESSION_VISITOR_H
#define EXPRESSION_VISITOR_H
#include "Expressions/Inline.h"
#include "Expressions/Primary.h"
#include "Expressions/Comparison.h"
#include "Expressions/Equality.h"
#include "Expressions/Or.h"
#include "Expressions/And.h"
#include "Expressions/Not.h"
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
    static std::string accept(OrExpr *expr);
    static std::string accept(AndExpr *expr);
    static std::string accept(NotExpr *expr);
    static std::string accept(FactorExpr *expr);
    static std::string accept(TermExpr *expr);
};
#endif