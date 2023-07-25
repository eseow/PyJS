#include "ExpressionVisitor.h"
std::string ExpressionVisitor::accept(InlineExpr *expr)
{
    std::string if_case = expr->if_case->toString();
    std::string if_cond = expr->if_conditional->toString();
    std::string else_case = expr->else_case->toString();

    return "(INLINE {if_case:" + if_case + ", if_cond:" + if_cond + ", else_case:" + else_case + ")";
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
