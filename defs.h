#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TEXTLEN 512

struct token {
	int token;
	int intvalue;
};

enum {
	T_EOF,
	T_PLUS,
	T_MINUS,
	T_STAR,
	T_SLASH,
	T_INTLIT,
	T_SEMI,
	T_PRINT,
	T_EQUALS,
	T_INT,
	T_IDENT
};

enum {
	A_ADD,
	A_SUBTRACT,
	A_MULTIPLY,
	A_DIVIDE,
	A_INTLIT,
	A_IDENT,
	A_LVIDENT,
	A_ASSIGN
};

struct ASTnode {
	int op;
	struct ASTnode *left;
	struct ASTnode *right;
	union {
		int intvalue;
		int id;
	} v;
};

struct symtable {
	char *name;
};