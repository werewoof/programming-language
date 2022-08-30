#include "defs.h"
#include "data.h"
#include "decl.h"

//drawback: functions needs to be called above each other for operator precedence

struct ASTnode *multiplicative_expr(void) {
    struct ASTnode *left, *right;
    int tokentype;

    left = primary();
    tokentype = Token.token;
    if (tokentype == T_EOF)
        return left;
    while ((tokentype == T_STAR) || (tokentype == T_SLASH)) {
        scan(&Token);
        right = primary();

        left = mkastnode(arithop(tokentype), left, right, 0);
    }
}

struct ASTnode *additive_expr(void) {
    struct ASTnode *left, *right;
    int tokentype;

    left = multiplicative_expr();

    tokentype = Token.token;
    if (tokentype == T_EOF)
        return left;
    
    while (1) {
        scan(&Token);
        right = multiplicative_expr();
        left = mkastnode(arithop(tokentype), left, right, 0);
        tokentype = Token.token;
        if (tokentype == T_EOF)
            break;
    }

    return left;
}