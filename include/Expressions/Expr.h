#ifndef EXPR_H
#define EXPR_H
class Expr
{
};
#endif
/*

function fizzbuzz(var n){
    let r = [1 .... n+1]
    for(let i : r){
        if(i % 3 == 0){
            console.log("Fizzbuzz")
        }
    }
}

fizzbuzz(20)


program -> statementList
statementList -> statement*
statement ->
            | varStmt
            | forStmt
            | ifStmt
            | printStmt
            | funcCallStmt
            | exprStmt
funcCallStmt -> IDENTIFIER "(" expr ")"\n
funcDeclStmt -> def IDENTIFIER "(" IDENTIFIER ")" ":" \n
ifStmt -> if expr :\n \t program
varStmt -> IDENTIFIER = EXPR
exprStmt -> expr\n
expr -> inline
inline -> comparison "if" comparison "else" inline | comparison
comparison -> comparison (< | <= | >= | > ) equality | equality
equality -> equality (!= | ==) binary | binary
binary -> binary and unary | binary or unary | unary
unary -> - unary | not unary | factor
factor -> factor * term | factor / term | term
term -> term + expr | term - expr | expr
primary -> IDENTIFIER | NUMBER | BOOLEAN | STRING

parse(){
    stmtList = []
    while(current < tokens.length){
        parseRootStmt()
        advance()
    }
}

parseRootStmt(){
    stmt;
    match(def) -> stmt = varStmt()
    match(for) -> stmt = forStmt()
    consume(NEWLINE,"")
    stmtList.push_back(stmt)
}

parseVarStmt(){
    i = consume(IDENTIEIFER,"No identifier")
    consume(EQUAL,"no equal")
    expr = parseRootExpr()

    return Stmt.Var(i,expr)
}

parseRootExpr(){

}
parseInlineExpr(){

}





*/