#ifndef EXPR_PRINTER_H
#define EXPR_PRINTER_H
#include "Expressions/Expr.h"
#include <string>
class ExpressionPrinter
{
public:
    ExpressionPrinter(ExpressionPrinterVisitor visitor);
    std::string printExpr(Expr *expr);

private:
    ExpressionPrinterVisior visitor;
};
#endif