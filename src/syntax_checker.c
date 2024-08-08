#include "lexer.h"


static bool is_invalid_position(size_t position, size_t token_count)
{
    return (position == 0 || position == token_count - 1);
}


static int is_operator(token_type type)
{
    return (type == TOKEN_OP_PIPE || type == TOKEN_OP_REDIRECTION_OUT || type == TOKEN_OP_REDIRECTION_IN || type == TOKEN_OP_REDIRECTION_APPEND);
}

int operator_checker(token_type type, size_t position, size_t token_count, token_type left_op)
{
    if (is_operator(type) && (is_invalid_position(position, token_count) || is_operator(left_op)))
    {
        printf("bad op\n");

    }
    
    return 0;
    

}



int syntax_checker(t_tokenlist *tokenlist)
{
    t_token *temp;
    size_t i;
    i = 0;
    token_type  left_op;
    left_op = TOKEN_WORD;
	temp = tokenlist->head;
	while (temp != NULL)
    {
        if (is_operator(temp->type))
        {
            operator_checker(temp->type, i, tokenlist->token_count, left_op);
        }
        // else if (temp->type == TOKEN_UNKNOWN)
        // {

        // }



        i++;
        left_op = temp->type;
        temp = temp->next;
    }
    return 0;

}