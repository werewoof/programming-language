#include "defs.h"
#include "data.h"
#include "decl.h"

static int OpPrec[] = {
    0, //SEMI
    10, //+
    10, //-
    20, //*
    20, // / (divide)
    30, //T_EQ
    30, //T_NE
    40, //T_LT
    40, //T_GT
    40, //T_LE
    40, //T_LE
  //  0 // INTLIT
};

int arithop(int tokentype) { //create AST operation from tokens
/*
    switch (tok) {
        case T_PLUS:
            return A_ADD;
        case T_MINUS:
            return A_SUBTRACT;
        case T_STAR:
            return A_MULTIPLY;
        case T_SLASH:
            return A_DIVIDE;
        default:
            fprintf(stderr, "unknown token in arithop() on line %d", Line);
            exit(1);
    }
*/
   if (tokentype > T_EOF && tokentype < T_INTLIT) {
    return tokentype;
    }
    fatald("Syntax error, token", tokentype);
}

static struct ASTnode *primary(void) {
    struct ASTnode *n;
    int id;
    
    switch (Token.token) {
        case T_INTLIT:
            n = mkastleaf(A_INTLIT, Token.intvalue);
            scan(&Token);
            return n;
        case T_IDENT:
            id = findglob(Text);
            if (id == -1)
                fatals("Unknown variable", Text);
            n = mkastleaf(A_IDENT, id);
            break;
        default:
            fatald("Syntax error, token", Token.token);
            exit(1);
    }

    scan(&Token);
    return n;
}

static int op_precedence(int tokentype) {
    int prec = OpPrec[tokentype];
    if (prec == 0) {
        fprintf(stderr, "syntax error on line %d, token %d\n", Line, tokentype);
        exit(1);
    }
    return (prec);
}

struct ASTnode *binexpr(int ptp) {
    struct ASTnode *n, *left, *right;
    int tokentype;

    left = primary();

    tokentype = Token.token;
    if (tokentype == T_SEMI)
        return left;
    
    while (op_precedence(tokentype) > ptp) {
        scan(&Token);
        
        right = binexpr(OpPrec[tokentype]);  //recursively get tree

        left = mkastnode(arithop(tokentype), left, right, 0);

        tokentype = Token.token;
        if (tokentype == T_SEMI)
            return left;
    }

    return left;
}

