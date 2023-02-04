#include "../../includes/minishell.h"

AstNodeType	get_node_type(Token *token)
{
	if (ft_strcmp(token->start, "&&") == 0)
		return (NODE_AND);
	if (ft_strcmp(token->start, "||") == 0)
		return (NODE_OR);
	if (ft_strcmp(token->start, "|") == 0)
		return (NODE_PIPE);
	if (ft_strcmp(token->start, ">") == 0)
		return (NODE_REDIRECT);
	if (ft_strcmp(token->start, ">>") == 0)
		return (NODE_REDIRECT_APPEND);
	if (ft_strcmp(token->start, ";") == 0)
		return (NODE_SEMICOLON);
	return (NODE_INVALID);
}

static void	ast_free_command_node(AstNode *node)
{
	del_token(node->token);
	free(node);
}

Precedence	get_precedence(Token *token)
{
	if (token->type == TOKEN_HIGH_OPERATOR)
		return (PREC_HIGH);
	return (PREC_NONE);
}

static void	ast_free_binary_exp_node(AstNode *node)
{
	ast_node_free(node->as.binaryExpression.left);
	ast_node_free(node->as.binaryExpression.right);
	ast_free_command_node(node);
}

static void	ast_free_semicolon_exp_node(AstNode *node)
{
	t_lkd_lst	*list;
	t_lkd_node	*head;
	uint		i;

	list = get_head_node(node);
	head = list->head;
	i = 0;
	while (i < list->size)
	{
		ast_node_free(head->content);
		head = head->next;
		i++;
	}
	free(node->as.expressions.nodes);
}

t_lkd_lst	*get_head_node(AstNode *node)
{
	return (node->as.expressions.nodes);
}

void	ast_node_free(AstNode *node)
{
	if (!node)
		return ;
	switch (node->type)
	{
	case NODE_COMMAND:
		ast_free_command_node(node);
		break ;
	case NODE_SEMICOLON:
		ast_free_semicolon_exp_node(node);
		break ;
	default:
		ast_free_binary_exp_node(node);
		break ;
	}
}

void	parser_init(Parser *parser)
{
	parser->current_token = NULL;
	parser->previus_token = NULL;
	parser->had_error = 0;
}