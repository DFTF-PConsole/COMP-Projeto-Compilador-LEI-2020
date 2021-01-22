#ifndef STRUCTSAST_H
#define STRUCTSAST_H

typedef struct _is_program is_program;
typedef struct _is_choose is_choose;
typedef struct _is_method_decl is_method_decl;
typedef struct _is_method_header is_method_header;
typedef struct _is_formal_params is_formal_params;
typedef struct _is_params_list is_params_list;
typedef struct _is_method_body is_method_body;
typedef struct _is_method_body_list is_method_body_list;
typedef struct _is_var_decl is_var_decl;
typedef struct _is_arg_list is_arg_list;
typedef struct _is_statement is_statement;
typedef struct _is_statement_list is_statement_list;
typedef struct _is_method_invocation is_method_invocation;
typedef struct _is_expr_list is_expr_list;
typedef struct _is_assignment is_assignment;
typedef struct _is_parse_args is_parse_args;
typedef struct _is_expr is_expr;
typedef struct _is_expr1 is_expr1;
typedef struct _is_field_decl is_field_decl;


typedef enum {d_integer, d_bool, d_double, d_void, d_string} type;
typedef enum {d_var_decl, d_statement} typeMB;
typedef enum {d_method_decl, d_field_decl,d_semicolon} disc_choose;
typedef enum {d_stat_list, d_if, d_if_else, d_while, d_ret_expr, d_ret, d_parseArgs, d_assign, d_methodInv, d_printExp, d_strLit} typeStatement;
typedef enum {d_expr1, d_assign2} typeExpr;
typedef enum {d_add, d_sub, d_div, d_mul, d_mod, d_eq, d_ge, d_gt, d_lt, d_le, d_ne, d_and, d_or, d_xor, d_lshift, d_rshift, d_parseArgs2, d_methodInv2, d_minus, d_plus, d_not, d_par, d_id, d_idDot, d_intLit, d_realLit, d_boolLit} typeExpr1;


typedef struct _save_id_type{
    char* id;
}save_id_type;

struct _is_expr1{
    typeExpr1 dist;
    is_expr1* ie1a, *ie2b;
    is_expr* ie;
    is_parse_args* ipa;
    is_method_invocation* imi;
    char* id;
    char* boolean;
    char* intLit;
    char* realLit;
    char* name;
};


struct _is_expr{
    typeExpr dist;
    union{
        is_assignment* ia;
        is_expr1* ie1;
    }dataExpr;
};


struct _is_parse_args {
    char* id;
    char* name;
    is_expr* ie;
};


struct _is_assignment {
    char* id;
    char* name;
    is_expr* ie;
};


struct _is_expr_list {
    is_expr* ie;
    struct _is_expr_list* next;
};


struct _is_method_invocation {
    char* id;
    is_expr* ie;
	is_expr_list* iel;
};


struct _is_statement_list {
    is_statement* is;
    struct _is_statement_list* next;
};


struct _is_statement {
    typeStatement dist;
    //statementlist
    is_statement_list* sl;
    //if | if else | while | return | print
    is_expr* ie;
    //if | if else | while
    is_statement *is, *is2;
    is_parse_args* ipa;
    is_assignment* ia;
    is_method_invocation* imi;
    char* strLit;
};


struct _is_arg_list {
    char* id;
    struct _is_arg_list* next;
};

struct _is_field_decl {
    type dist;
    char* typeID;
    union{                 
        save_id_type* u_int;
        save_id_type* u_bool;
        save_id_type* u_double;
    }dataType; 
    is_arg_list* ial;
};


struct _is_var_decl {
    type dist;
    char* typeID;
    union{                 
        save_id_type* u_int;
        save_id_type* u_bool;
        save_id_type* u_double;
    }dataType; 
    is_arg_list* ial;
};


struct _is_method_body_list{
    typeMB dist;
    union{
        is_var_decl* ivd;
        is_statement* is;
    }dataType;
    struct _is_method_body_list* next;
};


struct _is_method_body { 
    is_method_body_list* imbl;
};


struct _is_params_list {
    type dist;
    char* typeId;
    union{                 
        save_id_type* u_int;
        save_id_type* u_bool;
        save_id_type* u_double;
    }dataType; 
    struct _is_params_list* next;
};


struct _is_formal_params {
    type dist;
    char* typeId;
    union{                 
        save_id_type* u_sa;
        save_id_type* u_int;
        save_id_type* u_bool;
        save_id_type* u_double;
    }dataType;
    is_params_list* ipl;    
};


struct _is_method_header { 
    type dist;
    char* typeId;
    union{                 
        save_id_type* u_int;
        save_id_type* u_bool;
        save_id_type* u_double;
        save_id_type* u_void;
    }var_type;
    is_formal_params* ifp;
};


struct _is_method_decl {
    is_method_header* imh;
    is_method_body* imb;
};


struct _is_choose { 
    disc_choose disc_d;
    union{                 
        is_method_decl* u_imd;
        is_field_decl* u_ifd; 
    }data_choose;
    struct _is_choose* next;
};


struct _is_program { 
    is_choose* ic;
    char* id;
};


#endif