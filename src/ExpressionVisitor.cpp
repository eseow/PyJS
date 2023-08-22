#include "ExpressionVisitor.h"
#include "boost/format.hpp"
std::string ExpressionVisitor::accept(InlineExpr *expr)
{
    std::string if_case = expr->if_case->toString();
    std::string if_cond = expr->if_conditional->toString();
    std::string else_case = expr->else_case->toString();

    return "(INLINE if_case:" + if_case + ", if_cond:" + if_cond + ", else_case:" + else_case + ")";
}
std::string ExpressionVisitor::accept(EqualityExpr *expr)
{
    std::string left = expr->left->toString();
    std::string right = expr->right->toString();
    std::string equalityOperator = expr->equalityOperator.toString();
    return str(boost::format("(EQUALITY left:%1%, right:%2%, equalityOperator:%3%)") % left % right % equalityOperator);
}

std::string ExpressionVisitor::accept(BinaryExpr *expr)
{
    std::string left = expr->left->toString();
    std::string right = expr->right->toString();
    std::string binaryOperator = expr->binaryOperator.toString();
    return str(boost::format("(BINARY left:%1%, right:%2%, equalityOperator:%3%)") % left % right % binaryOperator);
}

std::string ExpressionVisitor::accept(UnaryExpr *expr)
{
    std::string body = expr->body->toString();
    std::string unaryOperator = expr->unaryOperator.toString();
    return str(boost::format("(UNARY body:%1%, unaryOperator:%2%)") % body % unaryOperator);
}

std::string ExpressionVisitor::accept(FactorExpr *expr)
{
    std::string left = expr->left->toString();
    std::string right = expr->right->toString();
    std::string factorOperator = expr->factorOperator.toString();
    return str(boost::format("(FACTOR left:%1%, right:%2%, equalityOperator:%3%)") % left % right % factorOperator);
}

std::string ExpressionVisitor::accept(TermExpr *expr)
{
    std::string left = expr->left->toString();
    std::string right = expr->right->toString();
    std::string termOperator = expr->termOperator.toString();
    return str(boost::format("(TERM left:%1%, right:%2%, equalityOperator:%3%)") % left % right % termOperator);
}

std::string ExpressionVisitor::accept(Primary *expr)
{
    PrimaryType type = expr->type;
    auto value = expr->value;
    std::string val = "";
    switch (type)
    {
    case PrimaryType::PRIMARY_STRING:
        val = (std::get<std::string>(value));
        break;
    case PrimaryType::PRIMARY_DOUBLE:
        val = std::to_string(std::get<double>(value));
        break;
    case PrimaryType::PRIMARY_INT:
        val = std::to_string(std::get<int>(value));
        break;
    case PrimaryType::PRIMARY_BOOLEAN:
        val = std::to_string(std::get<bool>(value));
        break;
    case PrimaryType::PRIMARY_IDENTIFIER:
        val = std::get<std::string>(value);
        break;
    default:
        break;
    }
    return "(PRIMARY {type:" + Primary::primaryTypeStrings.at(type) + ",value:" + val + "})";
}

std::string ExpressionVisitor::accept(ComparisonExpr *expr)
{
    return str(boost::format("(COMPARISON {left: %1%, right:%2%, comparisonOperator:%3%})") % expr->left->toString() % expr->right->toString() % expr->comparisonOperator.toString());
}

/*

Expr

InlineExpr
TermExpr
PrimaryExpr

InlineExpr.toString
-> (inline if_case:{} if_cond:{} else_case:{})
if_case = Expr
if_cond = Expr
else_case = Expr


*/
