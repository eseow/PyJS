#include "ExpressionVisitor.h"
#include "boost/format.hpp"
std::string ExpressionVisitor::accept(InlineExpr *expr)
{
    std::string if_case = expr->if_case->toString();
    std::string if_cond = expr->if_conditional->toString();
    std::string else_case = expr->else_case->toString();

    return "(INLINE if_case:" + if_case + ", if_cond:" + if_cond + ", else_case:" + else_case + ")";
}
std::string ExpressionVisitor::accept(FuncExpr *expr)
{
    std::string arguments = "";
    for (int i = 0; i < expr->arguments.size(); i++)
    {
        arguments += str(boost::format("ARG_%1%:") % i);
        arguments += expr->arguments.at(i)->toString();
        if (i < expr->arguments.size() - 1)
        {
            arguments += ", ";
        }
    }
    std::string lexeme = expr->identifer.getLexeme();
    return str(boost::format("(FUNC %1% (%2%))") % lexeme % arguments);
}
std::string ExpressionVisitor::accept(ComparisonExpr *expr)
{
    return str(boost::format("(COMPARISON {left: %1%, right:%2%, comparisonOperator:%3%})") % expr->left->toString() % expr->right->toString() % expr->comparisonOperator.toString());
}
std::string ExpressionVisitor::accept(EqualityExpr *expr)
{
    std::string left = expr->left->toString();
    std::string right = expr->right->toString();
    std::string equalityOperator = expr->equalityOperator.toString();
    return str(boost::format("(EQUALITY left:%1%, right:%2%, equalityOperator:%3%)") % left % right % equalityOperator);
}

std::string ExpressionVisitor::accept(AndExpr *expr)
{
    std::string left = expr->left->toString();
    std::string right = expr->right->toString();
    return str(boost::format("(AND left:%1%, right:%2%)") % left % right);
}

std::string ExpressionVisitor::accept(OrExpr *expr)
{
    std::string left = expr->left->toString();
    std::string right = expr->right->toString();
    return str(boost::format("(OR left:%1%, right:%2%)") % left % right);
}

std::string ExpressionVisitor::accept(NotExpr *expr)
{
    std::string body = expr->body->toString();
    // return str(boost::format("(NOT body:%1%)") % body);
    return str(boost::format("(!(%1%)") % body);
}

std::string ExpressionVisitor::accept(FactorExpr *expr)
{
    std::string left = expr->left->toString();
    std::string right = expr->right->toString();
    std::string factorOperator = expr->factorOperator.toString();
    // return str(boost::format("(FACTOR left:%1%, right:%2%, factorOperator:%3%)") % left % right % factorOperator);
    return str(boost::format("(%1% * %2%)") % left % right % factorOperator);
}

std::string ExpressionVisitor::accept(TermExpr *expr)
{
    std::string left = expr->left->toString();
    std::string right = expr->right->toString();
    std::string termOperator = expr->termOperator.toString();
    // return str(boost::format("(TERM left:%1%, right:%2%, termOperator:%3%)") % left % right % termOperator);
    return str(boost::format("(%1% + %2%)") % left % right % termOperator);
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
    // return "(PRIMARY {type:" + Primary::primaryTypeStrings.at(type) + ",value:" + val + "})";
    return Primary::primaryTypeStrings.at(type);
}
