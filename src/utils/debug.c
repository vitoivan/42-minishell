#include "../../includes/minishell.h"

void	debug_token(t_token *token)
{
	switch (token->type)
	{
	case TOKEN_COMMAND:
		ft_printf("t_token{TOKEN_COMMAND, %s}\n", token->start);
		break ;
	case TOKEN_OPERATOR:
		ft_printf("t_token{TOKEN_OPERATOR, %s}\n", token->start);
		break ;
	default:
		ft_printf("t_token{TOKEN_ERROR, %s}\n", token->start);
		break ;
	}
}
void	debug_list_of_tokens(t_lkd_lst *commands)
{
	t_lkd_node *node;

	node = commands->head;
	ft_printf("[\n");
	while (node && node->content != NULL)
	{
		if (((t_token *)node->content)->type == TOKEN_ERROR)
		{
			t_token *tk = (t_token *)node->content;
			ft_printf("\tTOKEN_ERROR -> %s", tk->start);
		}
		if (((t_token *)node->content)->type == TOKEN_COMMAND)
		{
			t_token *tk = (t_token *)node->content;
			ft_printf("\tTOKEN_COMMAND -> ");
			ft_printf("command: [%s] ", tk->command);
			ft_printf("args: [");
			UINT index = 0;
			if (tk->args && tk->args[index])
			{
				for (; tk->args[index + 1]; index++)
					ft_printf("{%s}, ", tk->args[index]);
				ft_printf("{%s}]", tk->args[index]);
			}
			else
			{
				ft_printf("]");
			}
		}
        if (((t_token *) node->content)->type == TOKEN_OPERATOR)
            ft_printf("\tTOKEN_OPERATOR");
        if (((t_token *) node->content)->type == TOKEN_OPERATOR_HERE_DOC)
            ft_printf("\tTOKEN_OPERATOR_HERE_DOC");
        if (((t_token *) node->content)->type == TOKEN_OPERATOR_HERE_ARGS)
		{
			t_token *tk = (t_token *) node->content;
			ft_printf("\tTOKEN_OPERATOR_HERE_ARGS -> %s", tk->start);
		}
        if (((t_token *) node->content)->type == TOKEN_OPERATOR_REDIRECT_INPUT)
            ft_printf("\tTOKEN_OPERATOR_REDIRECT_INPUT");
        if (((t_token *) node->content)->type == TOKEN_OPERATOR_AND)
            ft_printf("\tTOKEN_OPERATOR_AND");
        if (((t_token *) node->content)->type == TOKEN_OPERATOR_OR)
            ft_printf("\tTOKEN_OPERATOR_OR");
        if (((t_token *) node->content)->type == TOKEN_OPERATOR_PIPE)
            ft_printf("\tTOKEN_OPERATOR_PIPE");
        if (((t_token *) node->content)->type == TOKEN_OPERATOR_REDIRECT)
            ft_printf("\tTOKEN_OPERATOR_REDIRECT");
        if (((t_token *) node->content)->type == TOKEN_OPERATOR_REDIRECT_APPEND)
            ft_printf("\tTOKEN_OPERATOR_REDIRECT_APPEND");
        if (((t_token *) node->content)->type == TOKEN_OPERATOR_SEMICOLON)
            ft_printf("\tTOKEN_OPERATOR_SEMICOLON");
        node = node->next;
		ft_printf("\n");
	}
	ft_printf("]\n");
}