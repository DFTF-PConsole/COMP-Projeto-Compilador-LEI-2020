#include "structsAST.h"
#include "functionsAST.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//!=================================
//! Cleaning Tree!
//!=================================

void cleanExpressionOne(is_expr1* ie1){
    if(ie1!=NULL){
        switch(ie1->dist)
        {
        case d_add:
        case d_sub:
        case d_div:
        case d_mul:
        case d_mod:
        case d_eq:
        case d_ge:
        case d_gt:
        case d_lt:
        case d_le:
        case d_ne:
        case d_and:
        case d_or:
        case d_xor:
        case d_lshift:
        case d_rshift:
            cleanExpressionOne(ie1->ie1a);
            cleanExpressionOne(ie1->ie2b);
            break;
        case d_minus:
        case d_plus:
        case d_not:
            cleanExpressionOne(ie1->ie1a);
            break;
        case d_parseArgs2:
            cleanParseArgs(ie1->ipa);
            break;
        case d_methodInv2:
            cleanMethodInvocation(ie1->imi);
            break;
        case d_par:
            cleanExpression(ie1->ie);
            break;
        case d_id:
        case d_idDot:
        case d_intLit:
        case d_realLit:
        case d_boolLit:
            break;
        }
        free(ie1);
        //printf("is_expr1* ie1 is free\n");
    }
}

void cleanExpression(is_expr* ie)
{
    if(ie!=NULL){
        if(ie->dist==d_assign2){
            cleanAssignment(ie->dataExpr.ia);
        }
        else{
            cleanExpressionOne(ie->dataExpr.ie1);
        }
        free(ie);
        //printf("is_expr* ie is free\n");
    }
}

void cleanExpressionList(is_expr_list* iel)
{
    if(iel!=NULL){
        cleanExpression(iel->ie);
        cleanExpressionList(iel->next);
        free(iel);
        //printf("is_expr_list* iel is free\n");
    }
}

void cleanMethodInvocation(is_method_invocation* imi)
{
    if(imi!=NULL){
        cleanExpression(imi->ie);
        cleanExpressionList(imi->iel);
        free(imi);
        //printf("is_method_invocation* imi is free\n");
    }
}

void cleanAssignment(is_assignment* ia)
{
    if(ia!=NULL){
        cleanExpression(ia->ie);
        free(ia);
        //printf("is_assignment* ia is free\n");
    }
}

void cleanParseArgs(is_parse_args* ipa)
{
    if(ipa!=NULL){
        cleanExpression(ipa->ie);
        free(ipa);
        //printf("is_parse_args* ipa is free\n");
    }
}

void cleanStatementList(is_statement_list* isl)
{   
    if(isl!=NULL){
        cleanStatement(isl->is);
        cleanStatementList(isl->next);
        free(isl);
        //printf("is_statement_list* isl is free\n");
    }
}

void cleanStatement(is_statement* is)
{
    if(is!=NULL){
        switch(is->dist)
        {
            case d_if:
                cleanExpression(is->ie);
                cleanStatement(is->is);
                break;
            case d_if_else:
                cleanExpression(is->ie);
                cleanStatement(is->is);
                cleanStatement(is->is2);
                break;
            case d_while:
                cleanExpression(is->ie);
                cleanStatement(is->is);
                break;
            case d_stat_list:
                cleanStatementList(is->sl);
                break;
            case d_ret_expr:
                cleanExpression(is->ie);
                break;
            case d_parseArgs:
                cleanParseArgs(is->ipa);
                break;
            case d_assign:
                cleanAssignment(is->ia);
                break;
            case d_methodInv:
                cleanMethodInvocation(is->imi);
                break;
            case d_printExp:
                cleanExpression(is->ie);
                break;
            case d_ret:
            case d_strLit:
                break;
        }
        free(is);
        //printf("is_statement* is is free\n");
    }
}

void cleanVarDecl(is_var_decl* ivd)
{
    if(ivd!=NULL){
        cleanArgList(ivd->ial);
        free(ivd);
        //printf("is_var_decl* ivd is free\n");
    }
}

void cleanMethodBodyList(is_method_body_list* imbl)
{
    if(imbl!=NULL){
        if(imbl->dist==d_var_decl){
            cleanVarDecl(imbl->dataType.ivd);
        }
        else{
            cleanStatement(imbl->dataType.is);
        }
        cleanMethodBodyList(imbl->next);
        free(imbl);
        //printf("is_method_body_list* imbl is free\n");
    }
}

void cleanMethodBody(is_method_body* imb)
{   
    if(imb!=NULL){   
        is_method_body_list* imbl = imb->imbl;
        free(imb);
        cleanMethodBodyList(imbl);
        //printf("is_method_body* imb is free\n");
    }
}

void cleanParamsList(is_params_list* ipl)
{
    if(ipl!=NULL){
        cleanParamsList(ipl->next);
        free(ipl);
        //printf("is_params_list* ipl is free\n");
    }
}

void cleanFormalParams(is_formal_params* ifp)
{
    if(ifp!=NULL){
        cleanParamsList(ifp->ipl);
        free(ifp);
        //printf("is_formal_params* ifp is free\n");
    }
}

void cleanMethodHeader(is_method_header* imh)
{
    if(imh!=NULL){
        cleanFormalParams(imh->ifp);
        free(imh);
        //printf("is_method_header* imh is free\n");
    }
}

void cleanArgList(is_arg_list* ial)
{
    if(ial!=NULL){
        cleanArgList(ial->next);
        free(ial);
        //printf("is_arg_list* ial is free\n");
    }
}

void cleanFieldDecl(is_field_decl* ifd)
{
    if(ifd!=NULL){
        cleanArgList(ifd->ial);
        free(ifd);
        //printf("is_field_decl* ifd is free\n");
    }
}

void cleanMethodDecl(is_method_decl* imd)
{
    if(imd!=NULL){
        cleanMethodBody(imd->imb);
        cleanMethodHeader(imd->imh);
        free(imd);
        //printf("is_method_decl* imd is free\n");
    }
}

void cleanChoose(is_choose* ic)
{
    if(ic!=NULL){
        if(ic->disc_d==d_method_decl){
            cleanMethodDecl(ic->data_choose.u_imd);
        }
        else if(ic->disc_d==d_field_decl){
            cleanFieldDecl(ic->data_choose.u_ifd);
        }
        cleanChoose(ic->next);
        //printf("is_choose* ic is free\n");
        free(ic);
    }
}

void cleanTree(is_program* ip)
{    
    if(ip!=NULL){
        is_choose* ic = ip->ic;
        free(ip);
        cleanChoose(ic);
        //printf("is_program* ip is free\n");
    }
}


//!=======================================
//! PRINT THE AST TREE
//!=======================================


void printTree(is_program* ip){
    int h=1;
    printf("Program\n");

    for(int iter=0; iter < h; iter++) 
            printf("..");
    printf("Id(%s)\n", ip->id);

    is_choose* ic = ip->ic;
    choose_ast(h,ic);   
}

void choose_ast(int h, is_choose* ic){
    if(ic!=NULL){
        int aux=h;
        

        if(ic->disc_d==d_method_decl){
            for(int iter=0; iter < h; iter++) 
            printf("..");
            
            // MethodDecl
            is_method_decl* imd = ic->data_choose.u_imd;
            printf("MethodDecl\n");
            h++;
            for(int iter=0; iter < h; iter++) 
                printf("..");
            printf("MethodHeader\n");

            //MethodHeader
            method_header_ast(h, imd->imh);

            for(int iter=0; iter < h; iter++) 
                printf("..");
            printf("MethodBody\n");

            //MethodBody
            method_body_ast(++h, imd->imb);   
        }
        //FieldDecl
        else if (ic->disc_d==d_field_decl){
            field_decl_ast(h, ic->data_choose.u_ifd);
        }
        choose_ast(aux,ic->next);
    }
}

void field_decl_ast(int h, is_field_decl* ifd){
    char type[10];
    for(int iter=0; iter < h; iter++) 
        printf("..");  
    printf("FieldDecl\n");  
    switch(ifd->dist)
    {
        case d_integer:
            strcpy(type,"Int");
            for(int iter=0; iter < h+1; iter++) 
                printf("..");
            printf("Int\n");
            for(int iter=0; iter < h+1; iter++) 
                printf("..");
            printf("Id(%s)\n", ifd->dataType.u_int->id);
            break;
        case d_double:
            strcpy(type,"Double");
            for(int iter=0; iter < h+1; iter++) 
                printf("..");
            printf("Double\n");
            for(int iter=0; iter < h+1; iter++) 
                printf("..");
            printf("Id(%s)\n", ifd->dataType.u_double->id);
            break;
        case d_bool:
            strcpy(type,"Bool");
            for(int iter=0; iter < h+1; iter++) 
                printf("..");
            printf("Bool\n");
            for(int iter=0; iter < h+1; iter++) 
                printf("..");
            printf("Id(%s)\n", ifd->dataType.u_bool->id);
            break;
        default: break;
    }
    arg_list_fieldDecl_ast(h,ifd->ial,type);
}

void method_body_ast(int h, is_method_body* imb){
    is_method_body_list* imbl = imb->imbl;
    method_body_list_ast(h, imbl);
}

void method_body_list_ast(int h, is_method_body_list* imbl){
    if(imbl!=NULL){
        if(imbl->dist==d_var_decl){
            for(int iter=0; iter < h; iter++) 
                printf("..");
            printf("VarDecl\n");
            var_decl_ast(h, imbl->dataType.ivd);
        }
        else{
            statements_ast(h, imbl->dataType.is);
        }
        method_body_list_ast(h, imbl->next);
    }
}

void arg_list_fieldDecl_ast(int h, is_arg_list* ial, char* type){
    if(ial!=NULL){
        for(int iter=0; iter < h; iter++) 
            printf("..");  
        printf("FieldDecl\n");
        for(int iter=0; iter < h+1; iter++) 
            printf("..");
        printf("%s\n", type);
        for(int iter=0; iter < h+1; iter++) 
            printf("..");
        printf("Id(%s)\n", ial->id);

        arg_list_fieldDecl_ast(h, ial->next,type);
    }
}

void arg_list_varDecl_ast(int h, is_arg_list* ial, char* type){
    if(ial!=NULL){
        for(int iter=0; iter < h; iter++) 
            printf("..");
        printf("VarDecl\n");
        for(int iter=0; iter < h+1; iter++) 
            printf("..");
        printf("%s\n", type);
        for(int iter=0; iter < h+1; iter++) 
            printf("..");
        printf("Id(%s)\n", ial->id);

        arg_list_varDecl_ast(h, ial->next,type);
    }
}

void var_decl_ast(int h, is_var_decl* ivd){
    char type[10];
    switch(ivd->dist)
    {
        case d_integer:
            strcpy(type,"Int");
            for(int iter=0; iter < h+1; iter++) 
                printf("..");
            printf("Int\n");
            for(int iter=0; iter < h+1; iter++) 
                printf("..");
            printf("Id(%s)\n", ivd->dataType.u_int->id);
            break;
        case d_double:
            strcpy(type,"Double");
            for(int iter=0; iter < h+1; iter++) 
                printf("..");
            printf("Double\n");
            for(int iter=0; iter < h+1; iter++) 
                printf("..");
            printf("Id(%s)\n", ivd->dataType.u_double->id);
            break;
        case d_bool:
            strcpy(type,"Bool");
            for(int iter=0; iter < h+1; iter++) 
                printf("..");
            printf("Bool\n");
            for(int iter=0; iter < h+1; iter++) 
                printf("..");
            printf("Id(%s)\n", ivd->dataType.u_bool->id);
            break;
        default: break;
    }
    arg_list_varDecl_ast(h, ivd->ial, type);
}

void formal_params_ast(int h, is_formal_params* ifp){
    if(ifp!=NULL){
        h++;
        for(int iter=0; iter < h; iter++) 
            printf("..");
        printf("ParamDecl\n");
        for(int iter=0; iter < h+1; iter++) 
            printf("..");
        switch(ifp->dist){
            case d_integer:
                printf("Int\n");
                for(int iter=0; iter < h+1; iter++) 
                    printf("..");
                printf("Id(%s)\n", ifp->dataType.u_int->id);
                params_list_ast(h, ifp->ipl);
                break;
            case d_double:
                printf("Double\n");
                for(int iter=0; iter < h+1; iter++) 
                    printf("..");
                printf("Id(%s)\n", ifp->dataType.u_double->id);
                params_list_ast(h, ifp->ipl);
                break;
            case d_bool:
                printf("Bool\n");
                for(int iter=0; iter < h+1; iter++) 
                    printf("..");
                printf("Id(%s)\n", ifp->dataType.u_bool->id);
                params_list_ast(h, ifp->ipl);
                break;
            default:
                printf("StringArray\n");
                for(int iter=0; iter < h+1; iter++) 
                    printf("..");
                printf("Id(%s)\n", ifp->dataType.u_sa->id);
        }
    }
}

void method_header_ast(int h, is_method_header* imh){
    h++;
    for(int iter=0; iter < h; iter++) 
        printf("..");
    switch(imh->dist){
        case d_integer:
            printf("Int\n");
            for(int iter=0; iter < h; iter++) 
                printf("..");
            printf("Id(%s)\n", imh->var_type.u_int->id);
            break;
        case d_double:
            printf("Double\n");
            for(int iter=0; iter < h; iter++) 
                printf("..");
            printf("Id(%s)\n", imh->var_type.u_double->id);
            break;
        case d_bool:
            printf("Bool\n");
            for(int iter=0; iter < h; iter++) 
                printf("..");
            printf("Id(%s)\n", imh->var_type.u_bool->id);
            break;
        
        default:
            printf("Void\n");
            for(int iter=0; iter < h; iter++) 
                printf("..");
            printf("Id(%s)\n", imh->var_type.u_void->id);
    }
    for(int iter=0; iter < h; iter++) 
        printf("..");
    printf("MethodParams\n");
    formal_params_ast(h, imh->ifp);
}

int blockTest(is_statement_list* tmp){
    while(tmp!=NULL){
        if(tmp->is!=NULL&&tmp->is->dist!=d_stat_list){
            return 1;
        }
        else if(tmp->is!=NULL&&tmp->is->dist==d_stat_list){
            return blockTest(tmp->is->sl);
        }
        tmp=tmp->next;
    }
    return 0;
}

void statements_ast(int h, is_statement* stat){
    if(stat!=NULL){
        int flag;
        is_statement_list* tmp;
        switch(stat->dist){
            case d_if:
                for(int iter=0; iter < h; iter++) 
                    printf("..");
                printf("If\n");
                expression_ast(h+1, stat->ie);
                /*verificamos se o if tem um statement, se nao tiver é um if vazio pelo que damos print a um block. Se tiver um statement e for do tipo
                d_stat_list (chavetas e uma statementlist entre elas) vemos se o statementList é NULL. Se for Null damos print a um block devido a ser um if vazio [if(expr){}].
                Se esse StatementList nao for NULL mandamos para uma funcao que recebe o statementList e o percorre todo de maneira a verificar se tem algum statement que nao seja NULL.
                Caso todos os StatementList tenham um statement NULL a funcao retorna 0 e damos print a um block [exemplo :if(expr){{;}}]*/
                if(stat->is!=NULL){
                    if (stat->is->dist==d_stat_list&&stat->is->sl==NULL){
                        for(int iter=0; iter < h+1; iter++) 
                            printf("..");
                        printf("Block\n");
                    }
                    else if(stat->is->dist==d_stat_list&&stat->is->sl!=NULL){
                        tmp=stat->is->sl;
                        flag=blockTest(tmp);
                        if(!flag){
                            for(int iter=0; iter < h+1; iter++) 
                                printf("..");
                            printf("Block\n");
                        }
                    }
                    statements_ast(h+1, stat->is);
                }
                else{
                    for(int iter=0; iter < h+1; iter++) 
                        printf("..");
                    printf("Block\n");
                }

                //Print do Block relativo ao "else" devido ao If ter sempre 3 nos filhos.

                for(int iter=0; iter < h+1; iter++) 
                    printf("..");
                printf("Block\n");
            
                break;

            case d_if_else:
                for(int iter=0; iter < h; iter++) 
                    printf("..");  
                printf("If\n");
                expression_ast(h+1, stat->ie);
                /*verificamos se o if tem um statement, se nao tiver é um if vazio pelo que damos print a um block. Se tiver um statement e for do tipo
                d_stat_list (chavetas e uma statementlist entre elas) vemos se o statementList é NULL. Se for Null damos print a um block devido a ser um if vazio [if(expr){}].
                Se esse StatementList nao for NULL mandamos para uma funcao que recebe o statementList e o percorre todo de maneira a verificar se tem algum statement que nao seja NULL.
                Caso todos os StatementList tenham um statement NULL a funcao retorna 0 e damos print a um block [exemplo :if(expr){{;}}]*/
                if(stat->is!=NULL){
                    if (stat->is->dist==d_stat_list&&stat->is->sl==NULL){
                        for(int iter=0; iter < h+1; iter++) 
                            printf("..");
                        printf("Block\n");
                    }
                    else if(stat->is->dist==d_stat_list&&stat->is->sl!=NULL){
                        tmp=stat->is->sl;
                        flag=blockTest(tmp);
                        if(!flag){
                            for(int iter=0; iter < h+1; iter++) 
                                printf("..");
                            printf("Block\n");
                        }
                    }
                    statements_ast(h+1, stat->is);
                }
                else{
                    for(int iter=0; iter < h+1; iter++) 
                        printf("..");
                    printf("Block\n");
                }
                //Mesma logica do statement do If acima
                if(stat->is2!=NULL){
                    if (stat->is2->dist==d_stat_list&&stat->is2->sl==NULL){
                        for(int iter=0; iter < h+1; iter++) 
                            printf("..");
                        printf("Block\n");
                    }
                    else if(stat->is2->dist==d_stat_list&&stat->is2->sl!=NULL){
                        tmp=stat->is2->sl;
                        flag=blockTest(tmp);
                        if(!flag){
                            for(int iter=0; iter < h+1; iter++) 
                                printf("..");
                            printf("Block\n");
                        }
                    }
                    statements_ast(h+1, stat->is2);
                }
                else{
                    for(int iter=0; iter < h+1; iter++) 
                        printf("..");
                    printf("Block\n");
                }
                break;
            case d_stat_list:
            /*Usamos a mesma funcao que usamos para os ifs num entanto aqui vai ser o oposto. Quando é tudo NULL nao vai dar print a blocks. Apenas tiramos o not(!) 
            da flag*/
                if(stat->sl!=NULL){
                    if(stat->sl->next!=NULL){
                        tmp=stat->sl->next;
                        flag=blockTest(tmp);
                        if(flag){
                            for(int iter=0; iter < h; iter++) 
                                printf("..");
                            printf("Block\n");
                            h++;
                        }
                    }
                    statement_list_ast(h, stat->sl);
                }
                break;
            case d_while:
                for(int iter=0; iter < h; iter++) 
                    printf("..");  
                printf("While\n");
                expression_ast(h+1, stat->ie);

                //Mesma logica dos statements dos ifs!!
                if(stat->is!=NULL){
                    if (stat->is->dist==d_stat_list&&stat->is->sl==NULL){
                        for(int iter=0; iter < h+1; iter++) 
                            printf("..");
                        printf("Block\n");
                    }
                    else if(stat->is->dist==d_stat_list&&stat->is->sl!=NULL){
                        tmp=stat->is->sl;
                        flag=blockTest(tmp);
                        if(!flag){
                            for(int iter=0; iter < h+1; iter++) 
                                printf("..");
                            printf("Block\n");
                        }
                    }
                    statements_ast(h+1, stat->is);
                }
                else{
                    for(int iter=0; iter < h+1; iter++) 
                        printf("..");
                    printf("Block\n");
                }
                break;
            case d_ret:
                for(int iter=0; iter < h; iter++) 
                    printf("..");  
                printf("Return\n");
                break;
            case d_ret_expr:
                for(int iter=0; iter < h; iter++) 
                    printf("..");  
                printf("Return\n");
                expression_ast(h+1, stat->ie);
                break;
            case d_parseArgs:
                parse_args_ast(h, stat->ipa);
                break;
            case d_assign:
                assignment_ast(h, stat->ia);
                break;
            case d_methodInv:
                method_invocation_ast(h, stat->imi);
                break;
            case d_printExp:
                for(int iter=0; iter < h; iter++) 
                    printf("..");  
                printf("Print\n");
                expression_ast(h+1, stat->ie);
                break;
            case d_strLit:
                for(int iter=0; iter < h; iter++) 
                    printf("..");  
                printf("Print\n");
                print_str_ast(h, stat->strLit);
                break;
        }
    }
}

void print_str_ast(int h, char* strlit)
{
    h++;
    for(int iter=0; iter < h; iter++) 
        printf("..");
    printf("StrLit(%s)\n", strlit);
}

void params_list_ast(int h, is_params_list* ipl){
    if(ipl!=NULL){
        for(int iter=0; iter < h; iter++) 
            printf("..");
        printf("ParamDecl\n");
        for(int iter=0; iter < h+1; iter++) 
            printf("..");
        switch(ipl->dist){
            case d_integer:
                printf("Int\n");
                for(int iter=0; iter < h+1; iter++) 
                    printf("..");
                printf("Id(%s)\n", ipl->dataType.u_int->id);
                break;
            case d_double:
                printf("Double\n");
                for(int iter=0; iter < h+1; iter++) 
                    printf("..");
                printf("Id(%s)\n", ipl->dataType.u_double->id);
                break;
            case d_bool:
                printf("Bool\n");
                for(int iter=0; iter < h+1; iter++) 
                    printf("..");
                printf("Id(%s)\n", ipl->dataType.u_bool->id);
                break;
            default: break;
        }
        params_list_ast(h, ipl->next);       
    }
}

void statement_list_ast(int h, is_statement_list* isl){
    if(isl!=NULL){
        statements_ast(h, isl->is);
        statement_list_ast(h, isl->next);
    }
}

void expression_ast(int h, is_expr* ie){
    if(ie!=NULL){
        switch (ie->dist)
        {
        case d_expr1:
            expression_1_ast(h, ie->dataExpr.ie1);
            break;
        case d_assign2:
            assignment_ast(h, ie->dataExpr.ia);
            break;
        }        
    }
}

void parse_args_ast(int h, is_parse_args* ipa){
    if(ipa!=NULL){
        for(int iter=0; iter < h; iter++) 
            printf("..");
        printf("%s\n", ipa->name);
        h++;
        for(int iter=0; iter < h; iter++) 
            printf("..");
        printf("Id(%s)\n", ipa->id);
        expression_ast(h, ipa->ie);
    }
}

void method_invocation_ast(int h, is_method_invocation* imi)
{
    if(imi!=NULL){
        for(int iter=0; iter < h; iter++) 
            printf("..");
        printf("Call\n");
        h++;
        for(int iter=0; iter < h; iter++) 
            printf("..");
        printf("Id(%s)\n", imi->id);

        expression_ast(h, imi->ie);
        expression_list_ast(h, imi->iel);
    }
}

void expression_list_ast(int h, is_expr_list* iel)
{
    if(iel!=NULL){
        expression_ast(h, iel->ie);
        expression_list_ast(h, iel->next);
    }
}

void assignment_ast(int h, is_assignment* ia)
{
    if(ia!=NULL){
        for(int iter=0; iter < h; iter++) 
            printf("..");
        printf("%s\n", ia->name);
        h++;
        for(int iter=0; iter < h; iter++) 
            printf("..");
        printf("Id(%s)\n", ia->id);
        expression_ast(h, ia->ie);
    }
}

void expression_1_ast(int h, is_expr1* ie1)
{
    if(ie1!=NULL){  
        switch(ie1->dist)
        {
        case d_add:
        case d_sub:
        case d_div:
        case d_mul:
        case d_mod:
        case d_eq:
        case d_ge:
        case d_gt:
        case d_lt:
        case d_le:
        case d_ne:
        case d_and:
        case d_or:
        case d_xor:
        case d_lshift:
        case d_rshift:
            for(int iter=0; iter < h; iter++) 
                printf("..");  
            printf("%s\n", ie1->name);
            expression_1_ast(++h, ie1->ie1a);
            expression_1_ast(h, ie1->ie2b);
            break;
        case d_minus:
        case d_plus:
        case d_not:
            for(int iter=0; iter < h; iter++) 
                printf("..");  
            printf("%s\n", ie1->name);
            expression_1_ast(++h, ie1->ie1a);
            break;
        case d_id:
            for(int iter=0; iter < h; iter++) 
                printf("..");  
            printf("Id(%s)\n", ie1->id);
            break;
        case d_parseArgs2:
            parse_args_ast(h, ie1->ipa);
            break;
        case d_methodInv2:
            method_invocation_ast(h, ie1->imi);
            break;
        case d_idDot:
            for(int iter=0; iter < h; iter++) 
                printf("..");
            printf("%s\n", ie1->name);
            for(int iter=0; iter < h+1; iter++) 
                printf("..");  
            printf("Id(%s)\n", ie1->id);
            break;
        case d_intLit:
            for(int iter=0; iter < h; iter++) 
                printf("..");  
            printf("%s(%s)\n",  ie1->name, ie1->intLit);
            break;
        case d_realLit:
            for(int iter=0; iter < h; iter++) 
                printf("..");  
            printf("%s(%s)\n", ie1->name, ie1->realLit);
            break;
        case d_boolLit:
            for(int iter=0; iter < h; iter++) 
                printf("..");  
            printf("%s(%s)\n", ie1->name, ie1->boolean);
            break;
        case d_par:
            expression_ast(h, ie1->ie);
            break;
        }
    }
}

/*
!===================================================================
!
!===================================================================
!  FUNCTIONS TO INSERT THE VALUES FROM THE GRAMMAR TO THE STRUCTS
!===================================================================
!
!===================================================================
*/

// Program
is_program* insert_program(char* id, is_choose* ic)
{
	is_program* ip=(is_program*)malloc(sizeof(is_program));

	ip->ic=ic;
	ip->id=id;


	return ip;
}

// MethodDecl Choose
is_choose* insert_choose_list_method_decl(is_choose* head, is_method_decl* imd)
{
	is_choose* ic=(is_choose*)malloc(sizeof(is_choose));

	ic->disc_d=d_method_decl;
    ic->data_choose.u_imd=imd;

    if(head == NULL) {
        ic->next = NULL;
    }
    else {
        ic->next = head;
    }

	return ic;
}


// FieldDecl Choose
is_choose* insert_choose_list_field_decl(is_choose* head, is_field_decl* ifd)
{
	is_choose* ic=(is_choose*)malloc(sizeof(is_choose));

	ic->disc_d=d_field_decl;
    ic->data_choose.u_ifd=ifd;
	ic->next=NULL;

    if(head == NULL) {
        ic->next = NULL;
    }
    else {
        ic->next = head;
    }

	return ic;
}

is_choose* insert_choose_list_semicolon(is_choose* head){
    is_choose* ic=(is_choose*)malloc(sizeof(is_choose));

    ic->disc_d=d_semicolon;	

    if(head == NULL) {
        ic->next = NULL;
    }
    else {
        ic->next = head;
    }

	return ic;
}

// MethodDecl 
is_method_decl* insert_method_decl(is_method_header* imh, is_method_body* imb)
{
    is_method_decl* imd=(is_method_decl*)malloc(sizeof(is_method_decl));

    imd->imh=imh;
    imd->imb=imb;

    return imd;
}


// MethodHeader
is_method_header* insert_method_header(char* typeId, char* id, is_formal_params* ifp)
{
    is_method_header* imh=(is_method_header*)malloc(sizeof(is_method_header));

    if(!strcmp(typeId, "VOID")){
        save_id_type* ivt=(save_id_type*)malloc(sizeof(save_id_type));
        ivt->id=id;
        imh->dist=d_void;
        imh->var_type.u_void=ivt;
    }
    else if(!strcmp(typeId, "INT")){
        save_id_type* iit=(save_id_type*)malloc(sizeof(save_id_type));
        iit->id=id;
        imh->dist=d_integer;
        imh->var_type.u_int=iit;
    }
    else if(!strcmp(typeId, "DOUBLE")){
        save_id_type* idt=(save_id_type*)malloc(sizeof(save_id_type));
        idt->id=id;
        imh->dist=d_double;
        imh->var_type.u_double=idt;
    }
    else if(!strcmp(typeId, "BOOL")){
        save_id_type* ibt=(save_id_type*)malloc(sizeof(save_id_type));
        ibt->id=id;
        imh->dist=d_bool;
        imh->var_type.u_bool=ibt;
    }
    
    imh->ifp=ifp; 

    return imh;
}

// FormalParams
is_formal_params* insert_formal_params_type(char* typeId, char* id, is_params_list* ipl)
{
    is_formal_params* ifp=(is_formal_params*)malloc(sizeof(is_formal_params));

    if(!strcmp(typeId, "INT")){
        save_id_type* iit=(save_id_type*)malloc(sizeof(save_id_type));
        iit->id=id;
        ifp->dist=d_integer;
        ifp->dataType.u_int=iit;
    }
    else if(!strcmp(typeId, "DOUBLE")){
        save_id_type* idt=(save_id_type*)malloc(sizeof(save_id_type));
        idt->id=id;
        ifp->dist=d_double;
        ifp->dataType.u_double=idt;
    }
    else if(!strcmp(typeId, "BOOL")){
        save_id_type* ibt=(save_id_type*)malloc(sizeof(save_id_type));
        ibt->id=id;
        ifp->dist=d_bool;
        ifp->dataType.u_bool=ibt;
    }
    
    // ParamsList
    ifp->ipl=ipl; 

    return ifp;
}

// FormalParams
is_formal_params* insert_formal_params_string(char* id)
{
    is_formal_params* ifp=(is_formal_params*)malloc(sizeof(is_formal_params));

    save_id_type* ist=(save_id_type*)malloc(sizeof(save_id_type));
    
    ist->id=id;
    ifp->dist=d_string;
    ifp->dataType.u_sa=ist;


    return ifp;
}

// ParamsList
is_params_list* insert_params_list(char* typeId, char* id, is_params_list* head)
{
    is_params_list* ipl=(is_params_list*)malloc(sizeof(is_params_list));

    if(!strcmp(typeId, "INT")){
        save_id_type* iit=(save_id_type*)malloc(sizeof(save_id_type));
        iit->id=id;
        ipl->dist=d_integer;
        ipl->dataType.u_int=iit;
    }
    else if(!strcmp(typeId, "DOUBLE")){
        save_id_type* idt=(save_id_type*)malloc(sizeof(save_id_type));
        idt->id=id;
        ipl->dist=d_double;
        ipl->dataType.u_double=idt;
    }
    else if(!strcmp(typeId, "BOOL")){
        save_id_type* ibt=(save_id_type*)malloc(sizeof(save_id_type));
        ibt->id=id;
        ipl->dist=d_bool;
        ipl->dataType.u_bool=ibt;
    }

    if(head == NULL) {
        ipl->next = NULL;
    }
    else {
        ipl->next = head;
    }

	return ipl;
}

// MethodBody
is_method_body *insert_method_body(is_method_body_list* imbl)
{
    is_method_body* imb=(is_method_body*)malloc(sizeof(is_method_body));

    imb->imbl=imbl;

    return imb;
}

// MethodBodyList
is_method_body_list* insert_methods_body_list_statement(is_statement* is, is_method_body_list* head)
{
    is_method_body_list* imbl=(is_method_body_list*)malloc(sizeof(is_method_body_list));

	imbl->dist=d_statement;
    imbl->dataType.is=is;
	
    if(head == NULL) {
        imbl->next = NULL;
    }
    else {
        imbl->next = head;
    }

	return imbl;
}

// MethodBodyList
is_method_body_list* insert_methods_body_list_vardecl(is_var_decl* ivd, is_method_body_list* head)
{
    is_method_body_list* imbl=(is_method_body_list*)malloc(sizeof(is_method_body_list));

    imbl->dist=d_var_decl;
    imbl->dataType.ivd=ivd;

	if(head == NULL) {
        imbl->next = NULL;
    }
    else {
        imbl->next = head;
    }

	return imbl;
}

// VarDecl
is_var_decl* insert_var_decl(char* typeId, char* id, is_arg_list* ial)
{
    is_var_decl* ivd=(is_var_decl*)malloc(sizeof(is_var_decl));

    if(!strcmp(typeId, "INT")){
        save_id_type* iit=(save_id_type*)malloc(sizeof(save_id_type));
        iit->id=id;
        ivd->dist=d_integer;
        ivd->dataType.u_int=iit;
    }
    else if(!strcmp(typeId, "DOUBLE")){
        save_id_type* idt=(save_id_type*)malloc(sizeof(save_id_type));
        idt->id=id;
        ivd->dist=d_double;
        ivd->dataType.u_double=idt;
    }
    else if(!strcmp(typeId, "BOOL")){
        save_id_type* ibt=(save_id_type*)malloc(sizeof(save_id_type));
        ibt->id=id;
        ivd->dist=d_bool;
        ivd->dataType.u_bool=ibt;
    }
    
    ivd->ial=ial;

    return ivd;
}

// FieldDecl
is_field_decl* insert_field_decl(char* typeId, char* id, is_arg_list* ial)
{
    is_field_decl* ifd=(is_field_decl*)malloc(sizeof(is_field_decl));

    if(!strcmp(typeId, "INT")){
        save_id_type* iit=(save_id_type*)malloc(sizeof(save_id_type));
        iit->id=id;
        ifd->dist=d_integer;
        ifd->dataType.u_int=iit;
    }
    else if(!strcmp(typeId, "DOUBLE")){
        save_id_type* idt=(save_id_type*)malloc(sizeof(save_id_type));
        idt->id=id;
        ifd->dist=d_double;
        ifd->dataType.u_double=idt;
    }
    else if(!strcmp(typeId, "BOOL")){
        save_id_type* ibt=(save_id_type*)malloc(sizeof(save_id_type));
        ibt->id=id;
        ifd->dist=d_bool;
        ifd->dataType.u_bool=ibt;
    }

    ifd->ial=ial;

    return ifd;
}

// ArgList
is_arg_list* insert_arg_list(char* id, is_arg_list* head)
{
    is_arg_list* ial=(is_arg_list*)malloc(sizeof(is_arg_list));

    ial->id=id;

	if(head == NULL) {
        ial->next = NULL;
    }
    else {
        ial->next = head;
    }

	return ial;
}

// Statement StatementList
is_statement* insert_statement_statement_list(is_statement_list* isl)
{
    is_statement* is=(is_statement*)malloc(sizeof(is_statement));
    
    is->dist=d_stat_list;
    is->sl=isl;
    
    return is;
}

// Statement If Expr
is_statement* insert_statement_if(is_expr* ie, is_statement* stat)
{
    is_statement* aa=(is_statement*)malloc(sizeof(is_statement));

    
    aa->dist=d_if;
    aa->ie=ie;
    aa->is=stat;

    return aa;
}

// Statement If Expr Else
is_statement* insert_statement_if_else(is_expr* ie, is_statement* stat, is_statement* stat2)
{
    is_statement* is=(is_statement*)malloc(sizeof(is_statement));

    is->dist=d_if_else;
    is->ie=ie;
    is->is=stat;
    is->is2=stat2;

    return is;
}

is_statement* insert_statement_while(is_expr* ie, is_statement* stat)
{
    is_statement* is=(is_statement*)malloc(sizeof(is_statement));

    is->dist=d_while;
    is->ie=ie;
    is->is=stat;

    return is;
}

is_statement* insert_statement_return(is_expr* ie)
{
    is_statement* is=(is_statement*)malloc(sizeof(is_statement));

    is->dist=d_ret_expr;
    is->ie=ie;

    return is;
}

is_statement* insert_statement_parse_args(is_parse_args* ipa)
{
    is_statement* is=(is_statement*)malloc(sizeof(is_statement));

    is->dist=d_parseArgs;
    is->ipa=ipa;

    return is;
}

is_statement* insert_statement_assignment(is_assignment* ia)
{
    is_statement* is=(is_statement*)malloc(sizeof(is_statement));

    is->dist=d_assign;
    is->ia=ia;

    return is;
}


is_statement* insert_statement_method_invocation(is_method_invocation* imi)
{
    is_statement* is=(is_statement*)malloc(sizeof(is_statement));

    is->dist=d_methodInv;
    is->imi=imi;

    return is;
}

is_statement* insert_statement_print(is_expr* ie)
{
    is_statement* is=(is_statement*)malloc(sizeof(is_statement));

    is->dist=d_printExp;
    is->ie=ie;

    return is;
}

is_statement* insert_statement_strlit(char* strlit)
{
    is_statement* is=(is_statement*)malloc(sizeof(is_statement));

    is->dist=d_strLit;
    is->strLit=strlit;    //Strdup?

    return is;
}

is_statement_list* insert_statement_list(is_statement* is, is_statement_list* head)
{
    is_statement_list* isl=(is_statement_list*)malloc(sizeof(is_statement_list));

    isl->is=is;

    if(head == NULL) {
        isl->next = NULL;
    }
    else {
        isl->next = head;
    }

	return isl;
}

is_method_invocation* insert_method_invocation(char* id)
{
    is_method_invocation* imi=(is_method_invocation*)malloc(sizeof(is_method_invocation));

    imi->id=id;

    return imi;
}

is_method_invocation* insert_method_invocation_expr(char* id, is_expr* ie, is_expr_list* iel)
{
    is_method_invocation* imi=(is_method_invocation*)malloc(sizeof(is_method_invocation));

    imi->id=id;
    imi->ie=ie;
    imi->iel=iel;

    return imi;
}

is_assignment* insert_assignment(char* id, is_expr* ie)
{
    is_assignment* ia=(is_assignment*)malloc(sizeof(is_assignment));
    
    ia->id=id;
    ia->name="Assign";
    ia->ie=ie;

    return ia;
}

is_statement* insert_statement_return_only(){
    is_statement* is=(is_statement*)malloc(sizeof(is_statement));

    is->dist=d_ret;
    is->strLit="Return";

    return is;
}

is_parse_args* insert_parse_args(char* id, is_expr* ie)
{
    is_parse_args* ipa=(is_parse_args*)malloc(sizeof(is_parse_args));

    ipa->id=id;
    ipa->name="ParseArgs";
    ipa->ie=ie;

    return ipa;
}

is_expr* insert_expr_expr1(is_expr1* ie1){
    is_expr* expr=(is_expr*)malloc(sizeof(is_expr));

    expr->dist=d_expr1;
    expr->dataExpr.ie1=ie1;

    return expr;
}

is_expr* insert_expr_assign(is_assignment* ia){
    is_expr* expr=(is_expr*)malloc(sizeof(is_expr));

    expr->dist=d_assign2;
    expr->dataExpr.ia=ia;

    return expr;
}

is_expr_list* insert_expr_list(is_expr* ie, is_expr_list* head)
{
    is_expr_list* iel=(is_expr_list*)malloc(sizeof(is_expr_list));

    iel->ie=ie;

    if(head == NULL) {
        iel->next = NULL;
    }
    else {
        iel->next = head;
    }

	return iel;
}

is_expr1* insert_expr1_oper(is_expr1* ie1a, is_expr1 *ie1b,int flag)
{
    is_expr1* ie1=(is_expr1*)malloc(sizeof(is_expr1));
    switch(flag){
        case 0: ie1->dist=d_add; ie1->name="Add"; break;
        case 1: ie1->dist=d_sub; ie1->name="Sub"; break;
        case 2: ie1->dist=d_div; ie1->name="Div"; break;
        case 3: ie1->dist=d_mul; ie1->name="Mul"; break;
        case 4: ie1->dist=d_mod; ie1->name="Mod"; break;
        case 5: ie1->dist=d_eq; ie1->name="Eq"; break;
        case 6: ie1->dist=d_ge; ie1->name="Ge"; break;
        case 7: ie1->dist=d_gt; ie1->name="Gt"; break;
        case 8: ie1->dist=d_lt; ie1->name="Lt"; break;
        case 9: ie1->dist=d_le; ie1->name="Le"; break;
        case 10: ie1->dist=d_ne; ie1->name="Ne"; break;
        case 11: ie1->dist=d_and; ie1->name="And"; break;
        case 12: ie1->dist=d_or; ie1->name="Or"; break;
        case 13: ie1->dist=d_xor; ie1->name="Xor"; break;
        case 14: ie1->dist=d_lshift; ie1->name="Lshift"; break;
        case 15: ie1->dist=d_rshift; ie1->name="Rshift"; break;
    }
    ie1->ie1a=ie1a;
    ie1->ie2b=ie1b;

    return ie1;
}

is_expr1* insert_expr1_oper2(is_expr1* ie1a,int flag)
{
    is_expr1* ie1=(is_expr1*)malloc(sizeof(is_expr1));
    switch(flag){
        case 0: ie1->dist=d_minus; ie1->name="Minus"; break;
        case 1: ie1->dist=d_not; ie1->name="Not"; break;
        case 2: ie1->dist=d_plus; ie1->name="Plus"; break;
    }
    ie1->ie1a=ie1a;

    return ie1;
}

is_expr1* insert_expr1_ParExpr(is_expr* ie)
{
    is_expr1* ie1=(is_expr1*)malloc(sizeof(is_expr1));
    
    ie1->dist=d_par;
    ie1->ie=ie;

    return ie1;
}

is_expr1* insert_expr1_method_invocation(is_method_invocation* imi)
{
    is_expr1* ie1=(is_expr1*)malloc(sizeof(is_expr1));

    ie1->dist=d_methodInv2;
    ie1->imi=imi;

    return ie1;
}

is_expr1* insert_expr1_parse_args(is_parse_args* ipa)
{
    is_expr1* ie1=(is_expr1*)malloc(sizeof(is_expr1));

    ie1->dist=d_parseArgs2;
    ie1->ipa=ipa;

    return ie1;
}

is_expr1* insert_expr1_id(char* id)
{
    is_expr1* ie1=(is_expr1*)malloc(sizeof(is_expr1));

    ie1->dist=d_id;
    ie1->id=id;

    return ie1;
}

is_expr1* insert_expr1_id_dotLength(char* id)
{
    is_expr1* ie1=(is_expr1*)malloc(sizeof(is_expr1));

    ie1->dist=d_idDot;
    ie1->name="Length";
    ie1->id=id;

    return ie1;
}

is_expr1* insert_expr1_intLit(char* num)
{
    is_expr1* ie1=(is_expr1*)malloc(sizeof(is_expr1));

    ie1->dist=d_intLit;
    ie1->name="DecLit";
    ie1->intLit=num;

    return ie1;
}

is_expr1* insert_expr1_realLit(char* num)
{
    is_expr1* ie1=(is_expr1*)malloc(sizeof(is_expr1));

    ie1->dist=d_realLit;
    ie1->name="RealLit";
    ie1->realLit=num;

    return ie1;
}

is_expr1* insert_expr1_boolLit(char* boolean)
{
    is_expr1* ie1=(is_expr1*)malloc(sizeof(is_expr1));

    ie1->dist=d_boolLit;
    ie1->name="BoolLit";
    ie1->boolean=boolean;

    return ie1;
}