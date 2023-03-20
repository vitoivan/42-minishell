#include "../../includes/minishell.h"
static int	depth = 0;
static char	*indent = "  ";

static void	begin_scope(void)
{
	depth++;
}

static void	end_scope(void)
{
	depth--;
}

static void	print_with_ident(const char *str)
{
	int	i;

	i = 0;
	while (i < depth)
	{
		ft_printf("%s", indent);
		i++;
	}
	ft_printf("%s\n", str);
}

static void	debug_node_command(t_ast_node *node)
{
	print_with_ident("Command {");
	begin_scope();
	print_with_ident(node->token->start);
	end_scope();
	print_with_ident("}");
}

static void	debug_node_and(t_ast_node *node)
{
	print_with_ident("AND {");
	begin_scope();
	debug_command_tree(node->u_as.s_binary_expression.left);
	debug_command_tree(node->u_as.s_binary_expression.right);
	end_scope();
	print_with_ident("}");
}

static void	debug_node_or(t_ast_node *node)
{
	print_with_ident("OR {");
	begin_scope();
	debug_command_tree(node->u_as.s_binary_expression.left);
	debug_command_tree(node->u_as.s_binary_expression.right);
	end_scope();
	print_with_ident("}");
}

static void	debug_node_pipe(t_ast_node *node)
{
	print_with_ident("PIPE {");
	begin_scope();
	debug_command_tree(node->u_as.s_binary_expression.left);
	debug_command_tree(node->u_as.s_binary_expression.right);
	end_scope();
	print_with_ident("}");
}

static void	debug_node_redirect(t_ast_node *node)
{
	print_with_ident("Redirect {");
	begin_scope();
	debug_command_tree(node->u_as.s_binary_expression.left);
	debug_command_tree(node->u_as.s_binary_expression.right);
	end_scope();
	print_with_ident("}");
}

static void	debug_node_redirect_append(t_ast_node *node)
{
	print_with_ident("Append {");
	begin_scope();
	debug_command_tree(node->u_as.s_binary_expression.left);
	debug_command_tree(node->u_as.s_binary_expression.right);
	end_scope();
	print_with_ident("}");
}


static void	debug_node_here_document(t_ast_node *node)
{
	print_with_ident("Here Document {");
	begin_scope();
	debug_command_tree(node->u_as.s_binary_expression.left);
	debug_command_tree(node->u_as.s_binary_expression.right);
	end_scope();
	print_with_ident("}");
}

static void	debug_node_redirect_input(t_ast_node *node)
{
	print_with_ident("Redirect Input {");
	begin_scope();
	debug_command_tree(node->u_as.s_binary_expression.left);
	debug_command_tree(node->u_as.s_binary_expression.right);
	end_scope();
	print_with_ident("}");
}

static void	debug_node_here_args(t_ast_node *node)
{
	print_with_ident("Here Document Args {");
	begin_scope();
	print_with_ident(node->token->start);
	end_scope();
	print_with_ident("}");
}

void	debug_command_tree(t_ast_node *root)
{
	switch (root->type)
	{
	case NODE_COMMAND:
		debug_node_command(root);
		break ;
	case NODE_AND:
		debug_node_and(root);
		break ;
	case NODE_OR:
		debug_node_or(root);
		break ;
	case NODE_REDIRECT:
		debug_node_redirect(root);
		break ;
	case NODE_HERE_DOCUMENT:
		debug_node_here_document(root);
		break ;
	case NODE_REDIRECT_INPUT:
		debug_node_redirect_input(root);
		break ;
	case NODE_REDIRECT_APPEND:
		debug_node_redirect_append(root);
		break ;
	case NODE_PIPE:
		debug_node_pipe(root);
		break ;
	case NODE_HERE_ARGS:
		debug_node_here_args(root);
		break ;
	default:
		ft_printf("%s\n", root->token->start);
		break ;
	}
}

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


void debug_list_of_tokens(t_lkd_lst *commands) 
{
    t_lkd_node *node;

    node = commands->head; 
    ft_printf("[\n");
    while (node && node->content != NULL)
    {
        if (((t_token *) node->content)->type == TOKEN_ERROR)
		{
            t_token *tk = (t_token *) node->content;
            ft_printf("\tTOKEN_ERROR -> %s", tk->start);
		}
        if (((t_token *) node->content)->type == TOKEN_COMMAND) {
			 t_token *tk = (t_token *) node->content;
			ft_printf("\tTOKEN_COMMAND -> ");
			ft_printf("command: %s ", tk->command);
			ft_printf("args: [");
			UINT index = 0;
			if (tk->args && tk->args[index]) {
				for (; tk->args[index + 1]; index++)
					ft_printf("%s, ", tk->args[index]);
				ft_printf("%s]", tk->args[index]);
			} else {
				ft_printf("]");
			}
		}
        if (((t_token *) node->content)->type == TOKEN_OPERATOR)
            ft_printf("\tTOKEN_OPERATOR");
        if (((t_token *) node->content)->type == TOKEN_OPERATOR_HERE_DOC)
            ft_printf("\tTOKEN_OPERATOR_HERE_DOC");
        if (((t_token *) node->content)->type == TOKEN_OPERATOR_HERE_DOC_ARGS)
            ft_printf("\tTOKEN_OPERATOR_HERE_DOC_ARGS");
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