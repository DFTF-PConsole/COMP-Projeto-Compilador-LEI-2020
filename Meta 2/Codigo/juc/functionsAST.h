#include "structsAST.h"


void cleanMethodInvocation(is_method_invocation* imi);
void cleanAssignment(is_assignment* ia);
void cleanParseArgs(is_parse_args* ipa);
void cleanStatementList(is_statement_list* isl);
void cleanStatement(is_statement* is);
void cleanVarDecl(is_var_decl* ivd);
void cleanMethodBodyList(is_method_body_list* imbl);
void cleanMethodBody(is_method_body* imb);
void cleanMethodDecl(is_method_decl* imd);
void cleanMethodHeader(is_method_header* imh);
void cleanArgList(is_arg_list* ial);
void cleanFieldDecl(is_field_decl* ifd);
void cleanTree(is_program* ip);
void cleanExpression(is_expr* ie);
void cleanExpressionList(is_expr_list* iel);
void cleanParamsList(is_params_list* ipl);
void cleanFormalParams(is_formal_params* ifp);
void cleanExpressionOne(is_expr1* ie1);
void cleanChoose(is_choose* ic);



is_program* insert_program(char* id, is_choose* ic);
is_choose* insert_choose_list_method_decl(is_choose* head, is_method_decl* isd);
is_choose* insert_choose_list_field_decl(is_choose* head, is_field_decl* ifd);
is_choose* insert_choose_list_semicolon(is_choose* head);
is_method_decl* insert_method_decl(is_method_header* imh, is_method_body* imb);
is_method_header* insert_method_header(char* typeId, char* id, is_formal_params* ifp);
is_formal_params* insert_formal_params_type(char* typeId, char* id, is_params_list* ipl);
is_formal_params* insert_formal_params_string(char* id);
is_params_list* insert_params_list(char* typeId, char* id, is_params_list* head);
is_method_body *insert_method_body(is_method_body_list* imbl);
is_method_body_list* insert_methods_body_list_statement(is_statement* is, is_method_body_list* head);
is_method_body_list* insert_methods_body_list_vardecl(is_var_decl* ivd, is_method_body_list* head);
is_var_decl* insert_var_decl(char* typeId, char* id, is_arg_list* ial);
is_field_decl* insert_field_decl(char* typeId, char* id, is_arg_list* ial);
is_arg_list* insert_arg_list(char* id, is_arg_list* head);

is_statement* insert_statement_statement_list(is_statement_list* isl);
is_statement* insert_statement_if(is_expr* ie, is_statement* head);
is_statement* insert_statement_if_else(is_expr* ie, is_statement* head, is_statement* head2);
is_statement* insert_statement_while(is_expr* ie, is_statement* head);
is_statement* insert_statement_return(is_expr* ie);
is_statement* insert_statement_parse_args(is_parse_args* ipa);
is_statement* insert_statement_method_invocation(is_method_invocation* imi);
is_statement* insert_statement_print(is_expr* ie);
is_statement* insert_statement_strlit(char* strlit);

is_assignment* insert_assignment(char* id, is_expr* ie);

is_statement_list* insert_statement_list(is_statement* is, is_statement_list* head);

is_method_invocation* insert_method_invocation(char* id);
is_method_invocation* insert_method_invocation_expr(char* id, is_expr* ie, is_expr_list* iel);

is_statement* insert_statement_return_only();

is_parse_args* insert_parse_args(char* id, is_expr* ie);

is_expr* insert_expr_expr1(is_expr1* ie1);
is_expr* insert_expr_assign(is_assignment* ia);
is_expr_list* insert_expr_list(is_expr* ie, is_expr_list* head);
is_statement* insert_statement_assignment(is_assignment* ia);

is_expr1* insert_expr1_oper(is_expr1* ie1a, is_expr1 *ie1b,int flag);
is_expr1* insert_expr1_oper2(is_expr1* ie1a,int flag);
is_expr1* insert_expr1_ParExpr(is_expr* ie);
is_expr1* insert_expr1_method_invocation(is_method_invocation* imi);
is_expr1* insert_expr1_parse_args(is_parse_args* ipa);
is_expr1* insert_expr1_id(char* id);
is_expr1* insert_expr1_id_dotLength(char* id);
is_expr1* insert_expr1_intLit(char* num);
is_expr1* insert_expr1_realLit(char* num);
is_expr1* insert_expr1_boolLit(char* boolean);


int blockTest(is_statement_list* tmp);

void field_decl_ast(int h, is_field_decl* ifd);
void method_body_ast(int h, is_method_body* imb);
void formal_params_ast(int h, is_formal_params* ifp);
void method_header_ast(int h, is_method_header* imh);
void statements_ast(int h, is_statement* is);
void params_list_ast(int h, is_params_list* ipl);
void var_decl_ast(int h, is_var_decl* ivd);
void arg_list_varDecl_ast(int h, is_arg_list* ial, char* type);
void arg_list_fieldDecl_ast(int h, is_arg_list* ial, char* type);
void statement_list_ast(int h, is_statement_list* isl);
void expression_ast(int h, is_expr* ie);
void parse_args_ast(int h, is_parse_args* ipa);
void assignment_ast(int h, is_assignment* ia);
void method_invocation_ast(int h, is_method_invocation* imi);
void print_str_ast(int h, char* strlit);
void expression_list_ast(int h, is_expr_list* iel);
void expression_1_ast(int h, is_expr1* ie1);
void method_body_list_ast(int h, is_method_body_list* imbl);
void choose_ast(int h, is_choose* ic);