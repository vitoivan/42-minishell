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
	debug_command_tree(node->as.binaryExpression.left);
	debug_command_tree(node->as.binaryExpression.right);
	end_scope();
	print_with_ident("}");
}

static void	debug_node_or(t_ast_node *node)
{
	print_with_ident("OR {");
	begin_scope();
	debug_command_tree(node->as.binaryExpression.left);
	debug_command_tree(node->as.binaryExpression.right);
	end_scope();
	print_with_ident("}");
}

static void	debug_node_pipe(t_ast_node *node)
{
	print_with_ident("PIPE {");
	begin_scope();
	debug_command_tree(node->as.binaryExpression.left);
	debug_command_tree(node->as.binaryExpression.right);
	end_scope();
	print_with_ident("}");
}

static void	debug_node_redirect(t_ast_node *node)
{
	print_with_ident("Redirect {");
	begin_scope();
	debug_command_tree(node->as.binaryExpression.left);
	debug_command_tree(node->as.binaryExpression.right);
	end_scope();
	print_with_ident("}");
}

static void	debug_node_redirect_append(t_ast_node *node)
{
	print_with_ident("Append {");
	begin_scope();
	debug_command_tree(node->as.binaryExpression.left);
	debug_command_tree(node->as.binaryExpression.right);
	end_scope();
	print_with_ident("}");
}

static void	debug_node_semicolon(t_ast_node *node)
{
	t_lkd_lst	*list;
	t_lkd_node	*head;
	UINT		i;

	print_with_ident("Semicolon {");
	begin_scope();
	list = get_head_node(node);
	head = list->head;
	i = 0;
	while (i < list->size)
	{
		debug_command_tree(head->content);
		head = head->next;
		i++;
	}
	end_scope();
	print_with_ident("}");
}

static void	debug_node_here_document(t_ast_node *node)
{
	print_with_ident("Here Document {");
	begin_scope();
	debug_command_tree(node->as.binaryExpression.left);
	debug_command_tree(node->as.binaryExpression.right);
	end_scope();
	print_with_ident("}");
}

static void	debug_node_redirect_input(t_ast_node *node)
{
	print_with_ident("Redirect Input {");
	begin_scope();
	debug_command_tree(node->as.binaryExpression.left);
	debug_command_tree(node->as.binaryExpression.right);
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
		break;
	case NODE_REDIRECT_INPUT:
		debug_node_redirect_input(root);
	break;
	case NODE_REDIRECT_APPEND:
		debug_node_redirect_append(root);
		break ;
	case NODE_PIPE:
		debug_node_pipe(root);
		break ;
	case NODE_SEMICOLON:
		debug_node_semicolon(root);
		break ;
	case NODE_HERE_ARGS:
		debug_node_here_args(root);
		break;
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
