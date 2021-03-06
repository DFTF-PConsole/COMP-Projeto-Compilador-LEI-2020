#include "structures.h"

ast_node* new_ast_null(void);
ast_node* new_ast_binary(binary_operator operator, ast_node* left, ast_node* binary);
ast_node* new_ast_unary(unary_operator operator, ast_node* right);
ast_node* new_ast_type(type typespec);
ast_node* new_ast_id(char* value);
ast_node* new_ast_chrlit(char* value);
ast_node* new_ast_intlit(char* value);
//ast_node* new_ast_intlit(int value);
ast_node* new_ast_reallit(char* value);
//ast_node* new_ast_reallit(double value);
ast_node* new_ast_if(ast_node* condition, ast_node* if_branch, ast_node* else_branch);
ast_node* new_ast_while(ast_node* condition, ast_node* while_branch);
//ast_node* new_ast_call(ast_node* function_name, ast_node* parameters);
ast_node* new_ast_call(ast_node* function_name, ast_node* expression, ast_node* head);
ast_node* new_ast_call_parameter(ast_node* head, ast_node* expression);
ast_node* new_ast_return(ast_node* return_value);
ast_node* new_ast_statlist(ast_node* statement, ast_node* head);
//ast_node* new_ast_declarator(ast_node* id, ast_node* expression);
//ast_node* new_ast_declarator_list(ast_node* declarator, ast_node* head);
//ast_node* new_ast_declaration(ast_node* typespec, ast_node* declarator, ast_node* declarator_head);
ast_node* new_ast_declarator(ast_node* id, ast_node* expression);
ast_node* new_ast_declarator_list(ast_node* declarator, ast_node* head);
ast_node* new_ast_declaration(ast_node* typespec, ast_node* declarator_list);
ast_node* new_ast_parameter_declaration(ast_node* typespec, ast_node* id);
ast_node* new_ast_parameter_list(ast_node* parameter_declaration, ast_node* head);
ast_node* new_ast_declarations_and_statements(ast_node* declaration_or_statement, ast_node* head);
ast_node* new_ast_function_body(ast_node* declarations_and_statements);
ast_node* new_ast_function_definition(ast_node* typespec, ast_node* function_declarator, ast_node* function_body);
ast_node* new_ast_function_declarator(ast_node* id, ast_node* parameter_list);
ast_node* new_ast_function_declaration(ast_node* typespec, ast_node* function_declarator);
ast_node* new_ast_functions_and_declarations(ast_node* function_or_declaration, ast_node* head);
ast_node* new_ast_program(ast_node* functions_and_declarations);
void print_ast(ast_node* as_tree, unsigned dots);
void clean_ast(ast_node* as_tree);
