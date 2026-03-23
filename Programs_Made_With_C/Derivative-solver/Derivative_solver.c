/*
 * ============================================================
 *   SYMBOLIC DERIVATIVE SOLVER IN C
 * ============================================================
 *
 * SUPPORTED EXPRESSIONS:
 *   - Constants:          e.g. 5, 3.14
 *   - Variables:          x
 *   - Addition:           f(x) + g(x)
 *   - Subtraction:        f(x) - g(x)
 *   - Multiplication:     f(x) * g(x)
 *   - Division:           f(x) / g(x)
 *   - Power:              f(x) ^ n  (integer/float exponent)
 *   - Natural log:        ln(x)
 *   - Sine:               sin(x)
 *   - Cosine:             cos(x)
 *   - Exponential:        exp(x)
 *   - Parentheses:        (f(x) + g(x))
 *
 * EXAMPLES:
 *   x^3 + 2*x         → 3*x^2 + 2
 *   sin(x) * cos(x)   → cos(x)*cos(x) + sin(x)*(-sin(x))
 *   ln(x) + exp(x)    → 1/x + exp(x)
 *
 * COMPILE:
 *   gcc -o derivative_solver derivative_solver.c -lm
 *
 * RUN:
 *   ./derivative_solver
 * ============================================================
 */

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ── Node types for the expression tree ── */
typedef enum {
    NODE_NUM, /* numeric constant, e.g. 3.14  */
    NODE_VAR, /* the variable x               */
    NODE_ADD, /* left + right                 */
    NODE_SUB, /* left - right                 */
    NODE_MUL, /* left * right                 */
    NODE_DIV, /* left / right                 */
    NODE_POW, /* left ^ right                 */
    NODE_SIN, /* sin(child)                   */
    NODE_COS, /* cos(child)                   */
    NODE_LN,  /* ln(child)                    */
    NODE_EXP  /* exp(child)                   */
} NodeType;

/* ── Expression tree node ── */
typedef struct Node {
    NodeType type;
    double value; /* used when type == NODE_NUM */
    struct Node* left;
    struct Node* right; /* right child (binary ops)   */
} Node;

/* ═══════════════════════════════════════════════════════════
 *  MEMORY HELPERS
 * ═══════════════════════════════════════════════════════════ */

static Node* make_num(double v) {
    Node* n = calloc(1, sizeof *n);
    n->type = NODE_NUM;
    n->value = v;
    return n;
}
static Node* make_var(void) {
    Node* n = calloc(1, sizeof *n);
    n->type = NODE_VAR;
    return n;
}
static Node* make_binop(NodeType t, Node* l, Node* r) {
    Node* n = calloc(1, sizeof *n);
    n->type = t;
    n->left = l;
    n->right = r;
    return n;
}
static Node* make_unary(NodeType t, Node* child) {
    Node* n = calloc(1, sizeof *n);
    n->type = t;
    n->left = child; /* we reuse left for the single child */
    return n;
}

/* Deep-copy a node tree (needed when the same sub-tree appears
   twice after differentiation, e.g. product rule). */
static Node* clone(const Node* src) {
    if (!src) return NULL;
    Node* n = calloc(1, sizeof *n);
    n->type = src->type;
    n->value = src->value;
    n->left = clone(src->left);
    n->right = clone(src->right);
    return n;
}

static void free_tree(Node* n) {
    if (!n) return;
    free_tree(n->left);
    free_tree(n->right);
    free(n);
}

/* ═══════════════════════════════════════════════════════════
 *  PARSER  –  recursive descent
 *
 *  Grammar (lowest to highest precedence):
 *    expr   → term   { ('+' | '-') term   }
 *    term   → factor { ('*' | '/') factor }
 *    factor → base   { '^' factor }          (right-assoc)
 *    base   → NUM | 'x' | func '(' expr ')' | '(' expr ')'
 * ═══════════════════════════════════════════════════════════ */

static const char* pos; /* global cursor into the input string */

static void skip_spaces(void) {
    while (*pos == ' ') pos++;
}

static Node* parse_expr(void); /* forward declaration */

static Node* parse_base(void) {
    skip_spaces();

    /* ── parenthesised sub-expression ── */
    if (*pos == '(') {
        pos++;
        Node* n = parse_expr();
        skip_spaces();
        if (*pos == ')') pos++;
        return n;
    }

    /* ── named functions: sin, cos, ln, exp ── */
    if (strncmp(pos, "sin", 3) == 0) {
        pos += 3;
        pos++; /* '(' */
        Node* arg = parse_expr();
        pos++; /* ')' */
        return make_unary(NODE_SIN, arg);
    }
    if (strncmp(pos, "cos", 3) == 0) {
        pos += 3;
        pos++;
        Node* arg = parse_expr();
        pos++;
        return make_unary(NODE_COS, arg);
    }
    if (strncmp(pos, "ln", 2) == 0) {
        pos += 2;
        pos++;
        Node* arg = parse_expr();
        pos++;
        return make_unary(NODE_LN, arg);
    }
    if (strncmp(pos, "exp", 3) == 0) {
        pos += 3;
        pos++;
        Node* arg = parse_expr();
        pos++;
        return make_unary(NODE_EXP, arg);
    }

    /* ── variable x ── */
    if (*pos == 'x') {
        pos++;
        return make_var();
    }

    /* ── numeric literal (including negative via unary minus) ── */
    if (isdigit((unsigned char)*pos) || *pos == '.') {
        char* end;
        double v = strtod(pos, &end);
        pos = end;
        return make_num(v);
    }

    /* ── unary minus, e.g. -x or -(x+1) ── */
    if (*pos == '-') {
        pos++;
        Node* operand = parse_base();
        /* represent as  0 - operand */
        return make_binop(NODE_SUB, make_num(0), operand);
    }

    fprintf(stderr, "Parse error near: %.10s\n", pos);
    exit(EXIT_FAILURE);
}

static Node* parse_factor(void) {
    Node* base = parse_base();
    skip_spaces();
    if (*pos == '^') {
        pos++;
        Node* exp = parse_factor(); /* right-associative */
        return make_binop(NODE_POW, base, exp);
    }
    return base;
}

static Node* parse_term(void) {
    Node* left = parse_factor();
    skip_spaces();
    while (*pos == '*' || *pos == '/') {
        char op = *pos++;
        Node* right = parse_factor();
        left = make_binop(op == '*' ? NODE_MUL : NODE_DIV, left, right);
        skip_spaces();
    }
    return left;
}

static Node* parse_expr(void) {
    Node* left = parse_term();
    skip_spaces();
    while (*pos == '+' || *pos == '-') {
        char op = *pos++;
        Node* right = parse_term();
        left = make_binop(op == '+' ? NODE_ADD : NODE_SUB, left, right);
        skip_spaces();
    }
    return left;
}

/* ═══════════════════════════════════════════════════════════
 *  DIFFERENTIATION  –  symbolic, recursive
 *
 *  Applies standard calculus rules:
 *    d/dx (c)       = 0
 *    d/dx (x)       = 1
 *    d/dx (f+g)     = f' + g'
 *    d/dx (f-g)     = f' - g'
 *    d/dx (f*g)     = f'g + fg'          (product rule)
 *    d/dx (f/g)     = (f'g - fg') / g²   (quotient rule)
 *    d/dx (f^n)     = n * f^(n-1) * f'   (general power rule)
 *    d/dx sin(f)    = cos(f) * f'
 *    d/dx cos(f)    = -sin(f) * f'
 *    d/dx ln(f)     = f' / f
 *    d/dx exp(f)    = exp(f) * f'
 * ═══════════════════════════════════════════════════════════ */

static Node* differentiate(const Node* n) {
    if (!n) return make_num(0);

    switch (n->type) {
        /* d/dx (c) = 0 */
        case NODE_NUM:
            return make_num(0);

        /* d/dx (x) = 1 */
        case NODE_VAR:
            return make_num(1);

        /* d/dx (f + g) = f' + g' */
        case NODE_ADD:
            return make_binop(NODE_ADD,
                              differentiate(n->left),
                              differentiate(n->right));

        /* d/dx (f - g) = f' - g' */
        case NODE_SUB:
            return make_binop(NODE_SUB,
                              differentiate(n->left),
                              differentiate(n->right));

        /* Product rule: d/dx (f*g) = f'*g + f*g' */
        case NODE_MUL:
            return make_binop(NODE_ADD,
                              make_binop(NODE_MUL, differentiate(n->left), clone(n->right)),
                              make_binop(NODE_MUL, clone(n->left), differentiate(n->right)));

        /* Quotient rule: d/dx (f/g) = (f'g - fg') / g^2 */
        case NODE_DIV:
            return make_binop(NODE_DIV,
                              make_binop(NODE_SUB,
                                         make_binop(NODE_MUL, differentiate(n->left), clone(n->right)),
                                         make_binop(NODE_MUL, clone(n->left), differentiate(n->right))),
                              make_binop(NODE_POW, clone(n->right), make_num(2)));

        /* General power rule (chain rule included):
           d/dx f^g  where g is a constant → g * f^(g-1) * f'
           For simplicity we handle the constant-exponent case only.    */
        case NODE_POW: {
            /* Check if exponent is a constant number */
            if (n->right->type == NODE_NUM) {
                double exp_val = n->right->value;
                /* n * f^(n-1) * f' */
                return make_binop(NODE_MUL,
                                  make_binop(NODE_MUL,
                                             make_num(exp_val),
                                             make_binop(NODE_POW, clone(n->left), make_num(exp_val - 1))),
                                  differentiate(n->left));
            }
            /* General case: d/dx f^g = f^g * (g'*ln(f) + g*f'/f) */
            Node* fClone = clone(n->left);
            Node* gClone = clone(n->right);
            return make_binop(NODE_MUL,
                              make_binop(NODE_POW, clone(n->left), clone(n->right)),
                              make_binop(NODE_ADD,
                                         make_binop(NODE_MUL, differentiate(n->right), make_unary(NODE_LN, fClone)),
                                         make_binop(NODE_MUL, gClone,
                                                    make_binop(NODE_DIV, differentiate(n->left), clone(n->left)))));
        }

        /* d/dx sin(f) = cos(f) * f' */
        case NODE_SIN:
            return make_binop(NODE_MUL,
                              make_unary(NODE_COS, clone(n->left)),
                              differentiate(n->left));

        /* d/dx cos(f) = -sin(f) * f' */
        case NODE_COS:
            return make_binop(NODE_MUL,
                              make_binop(NODE_SUB, make_num(0), make_unary(NODE_SIN, clone(n->left))),
                              differentiate(n->left));

        /* d/dx ln(f) = f' / f */
        case NODE_LN:
            return make_binop(NODE_DIV,
                              differentiate(n->left),
                              clone(n->left));

        /* d/dx exp(f) = exp(f) * f' */
        case NODE_EXP:
            return make_binop(NODE_MUL,
                              make_unary(NODE_EXP, clone(n->left)),
                              differentiate(n->left));

        default:
            return make_num(0);
    }
}

/* ═══════════════════════════════════════════════════════════
 *  SIMPLIFIER  –  constant folding + algebraic identities
 *
 *  Applied bottom-up (post-order) to keep output readable:
 *    0 + f → f,  f + 0 → f
 *    0 - f → -f, f - 0 → f
 *    1 * f → f,  f * 1 → f,  0 * f → 0,  f * 0 → 0
 *    f / 1 → f
 *    f ^ 0 → 1,  f ^ 1 → f
 *    Fold two numeric constants (e.g. 3 + 5 → 8)
 * ═══════════════════════════════════════════════════════════ */

static Node* simplify(Node* n);

static int is_num(const Node* n, double v) {
    return n && n->type == NODE_NUM && n->value == v;
}

static Node* simplify(Node* n) {
    if (!n) return NULL;

    /* Recurse first (bottom-up) */
    n->left = simplify(n->left);
    n->right = simplify(n->right);

    /* Constant folding for binary ops */
    if (n->left && n->right &&
        n->left->type == NODE_NUM && n->right->type == NODE_NUM) {
        double a = n->left->value, b = n->right->value, result = 0;
        int fold = 1;
        switch (n->type) {
            case NODE_ADD:
                result = a + b;
                break;
            case NODE_SUB:
                result = a - b;
                break;
            case NODE_MUL:
                result = a * b;
                break;
            case NODE_DIV:
                result = (b != 0) ? a / b : 0;
                break;
            case NODE_POW:
                result = pow(a, b);
                break;
            default:
                fold = 0;
        }
        if (fold) {
            free_tree(n->left);
            free_tree(n->right);
            n->type = NODE_NUM;
            n->value = result;
            n->left = n->right = NULL;
            return n;
        }
    }

    switch (n->type) {
        case NODE_ADD:
            if (is_num(n->left, 0)) {
                Node* r = n->right;
                n->right = NULL;
                free_tree(n);
                return r;
            }
            if (is_num(n->right, 0)) {
                Node* l = n->left;
                n->left = NULL;
                free_tree(n);
                return l;
            }
            break;
        case NODE_SUB:
            if (is_num(n->right, 0)) {
                Node* l = n->left;
                n->left = NULL;
                free_tree(n);
                return l;
            }
            /* 0 - f  →  -f:  keep as-is; the printer will handle it */
            break;
        case NODE_MUL:
            if (is_num(n->left, 0) || is_num(n->right, 0)) {
                free_tree(n);
                return make_num(0);
            }
            if (is_num(n->left, 1)) {
                Node* r = n->right;
                n->right = NULL;
                free_tree(n);
                return r;
            }
            if (is_num(n->right, 1)) {
                Node* l = n->left;
                n->left = NULL;
                free_tree(n);
                return l;
            }
            break;
        case NODE_DIV:
            if (is_num(n->right, 1)) {
                Node* l = n->left;
                n->left = NULL;
                free_tree(n);
                return l;
            }
            if (is_num(n->left, 0)) {
                free_tree(n);
                return make_num(0);
            }
            break;
        case NODE_POW:
            if (is_num(n->right, 0)) {
                free_tree(n);
                return make_num(1);
            }
            if (is_num(n->right, 1)) {
                Node* l = n->left;
                n->left = NULL;
                free_tree(n);
                return l;
            }
            break;
        default:
            break;
    }
    return n;
}

/* ═══════════════════════════════════════════════════════════
 *  PRINTER  –  infix string output
 * ═══════════════════════════════════════════════════════════ */

static void print_node(const Node* n) {
    if (!n) return;
    switch (n->type) {
        case NODE_NUM:
            /* print integer-valued doubles without decimal point */
            if (n->value == (long long)n->value)
                printf("%lld", (long long)n->value);
            else
                printf("%g", n->value);
            break;
        case NODE_VAR:
            printf("x");
            break;
        case NODE_ADD:
            printf("(");
            print_node(n->left);
            printf(" + ");
            print_node(n->right);
            printf(")");
            break;
        case NODE_SUB:
            printf("(");
            print_node(n->left);
            printf(" - ");
            print_node(n->right);
            printf(")");
            break;
        case NODE_MUL:
            printf("(");
            print_node(n->left);
            printf(" * ");
            print_node(n->right);
            printf(")");
            break;
        case NODE_DIV:
            printf("(");
            print_node(n->left);
            printf(" / ");
            print_node(n->right);
            printf(")");
            break;
        case NODE_POW:
            printf("(");
            print_node(n->left);
            printf("^");
            print_node(n->right);
            printf(")");
            break;
        case NODE_SIN:
            printf("sin(");
            print_node(n->left);
            printf(")");
            break;
        case NODE_COS:
            printf("cos(");
            print_node(n->left);
            printf(")");
            break;
        case NODE_LN:
            printf("ln(");
            print_node(n->left);
            printf(")");
            break;
        case NODE_EXP:
            printf("exp(");
            print_node(n->left);
            printf(")");
            break;
    }
}

/* ═══════════════════════════════════════════════════════════
 *  NUMERICAL EVALUATOR  –  for spot-checking
 * ═══════════════════════════════════════════════════════════ */

static double evaluate(const Node* n, double x_val) {
    if (!n) return 0;
    switch (n->type) {
        case NODE_NUM:
            return n->value;
        case NODE_VAR:
            return x_val;
        case NODE_ADD:
            return evaluate(n->left, x_val) + evaluate(n->right, x_val);
        case NODE_SUB:
            return evaluate(n->left, x_val) - evaluate(n->right, x_val);
        case NODE_MUL:
            return evaluate(n->left, x_val) * evaluate(n->right, x_val);
        case NODE_DIV: {
            double d = evaluate(n->right, x_val);
            return d != 0 ? evaluate(n->left, x_val) / d : 0;
        }
        case NODE_POW:
            return pow(evaluate(n->left, x_val), evaluate(n->right, x_val));
        case NODE_SIN:
            return sin(evaluate(n->left, x_val));
        case NODE_COS:
            return cos(evaluate(n->left, x_val));
        case NODE_LN: {
            double a = evaluate(n->left, x_val);
            return a > 0 ? log(a) : 0;
        }
        case NODE_EXP:
            return exp(evaluate(n->left, x_val));
        default:
            return 0;
    }
}

/* Finite-difference approximation: (f(x+h) - f(x-h)) / 2h */
static double numerical_derivative(const Node* f, double x_val) {
    const double h = 1e-7;
    return (evaluate(f, x_val + h) - evaluate(f, x_val - h)) / (2 * h);
}

/* ═══════════════════════════════════════════════════════════
 *  MAIN
 * ═══════════════════════════════════════════════════════════ */

int main(void) {
    char input[512];

    printf("╔══════════════════════════════════════════╗\n");
    printf("║    SYMBOLIC DERIVATIVE SOLVER  (C)       ║\n");
    printf("╚══════════════════════════════════════════╝\n");
    printf("Supported: x, constants, +, -, *, /, ^,\n");
    printf("           sin(), cos(), ln(), exp()\n");
    printf("Type 'quit' to exit.\n\n");

    while (1) {
        printf("f(x) = ");
        if (!fgets(input, sizeof input, stdin)) break;
        input[strcspn(input, "\n")] = '\0';
        if (strcmp(input, "quit") == 0 || strcmp(input, "exit") == 0) break;
        if (input[0] == '\0') continue;

        /* ── parse ── */
        pos = input;
        Node* expr = parse_expr();
        skip_spaces();
        if (*pos != '\0') {
            fprintf(stderr, "Warning: trailing characters ignored: '%s'\n", pos);
        }

        /* ── differentiate ── */
        Node* deriv = differentiate(expr);

        /* ── simplify ── */
        deriv = simplify(deriv);

        /* ── print result ── */
        printf("\nf(x)  = %s\n", input);
        printf("f'(x) = ");
        print_node(deriv);
        printf("\n");

        /* ── numerical verification at x = 2.0 ── */
        double x_test = 2.0;
        double sym_val = evaluate(deriv, x_test);
        double num_val = numerical_derivative(expr, x_test);
        printf("\nVerification at x = %.1f:\n", x_test);
        printf("  Symbolic  f'(%.1f) = %g\n", x_test, sym_val);
        printf("  Numerical f'(%.1f) ≈ %g\n", x_test, num_val);
        printf("  Match: %s\n\n",
               fabs(sym_val - num_val) < 1e-4 ? "✓ YES" : "✗ NO (check expression)");

        free_tree(expr);
        free_tree(deriv);
    }

    printf("Goodbye!\n");
    return 0;
}