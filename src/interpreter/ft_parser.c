
#include "../../includes/minishell.h"

static AstNode	*mk_node_command(Token *token)
{
	AstNode	*node;

	node = ft_calloc(sizeof(AstNode), 1);
	if (!node)
		return (NULL);
	node->type = NODE_COMMAND;
	node->token = token;
	return (node);
}

static AstNode	*mk_node_binary_expression(Token *token, AstNode *left,
		AstNode *right)
{
	AstNode	*node;

	node = ft_calloc(sizeof(AstNode), 1);
	if (!node)
		return (NULL);
	node->type = get_node_type(token);
	node->token = token;
	node->as.binaryExpression.left = left;
	node->as.binaryExpression.right = right;
	return (node);
}

static AstNode	*expression_builder(ParserContext *context)
{
	AstNode	*node;
	AstNode	*right;
	Token	*operator;

	node = mk_node_command(get_previus_token(context));
	right = NULL;
	operator= get_current_token(context);
	if (operator->type != TOKEN_OPERATOR || operator== NULL)
		return (node);
	while ((operator= get_current_token(context)) != NULL
		&& operator->type != TOKEN_HIGH_OPERATOR)
	{
		advance_to_next_token(context);
		right = mk_node_command(get_current_token(context));
		node = mk_node_binary_expression(operator, node, right);
		advance_to_next_token(context);
	}
	return (node);
}

AstNode	*expression_builder_semicolon(ParserContext *context, AstNode *node,
		AstNode *tmp)
{
	AstNode	*operator_node;

	if (node != NULL && node->type == NODE_SEMICOLON)
	{
		lkd_lst_add_back(&node->as.expressions.nodes, lkd_lst_new_node(tmp));
		return (node);
	}
	else
	{
		operator_node = mk_node_binary_expression(get_current_token(context),
													NULL,
													NULL);
		operator_node->as.expressions.nodes = lkd_lst_new_list();
		lkd_lst_add_back(&operator_node->as.expressions.nodes,
							lkd_lst_new_node(tmp));
	}
	return (operator_node);
}

static AstNode	*parser_expression(ParserContext *context)
{
	Token	*token;
	AstNode	*node;
	AstNode	*tmp;

	advance_to_next_token(context);
	if (get_current_token(context) == NULL)
		return (mk_node_command(get_previus_token(context)));
	node = NULL;
	tmp = NULL;
	while ((token = get_current_token(context)) != NULL)
	{
		if (token->type == TOKEN_HIGH_OPERATOR)
		{
			if (tmp == NULL)
			{
				// echo a ; echo b
				// echo a ; echo b && echo c
				tmp = expression_builder(context);
			}
			node = expression_builder_semicolon(context, node, tmp);
			advance_to_next_token(context);
			advance_to_next_token(context); // ir para o ultimo token
		}
		else
		{
			tmp = expression_builder(context);
		}
	}
	if (!node)
		node = tmp;
	if (node->type == NODE_SEMICOLON)
		node = expression_builder_semicolon(context, node, tmp);
	return (node);
}

AstNode	*ft_parser(char *source)
{
	ParserContext	context;
	AstNode			*command_tree;

	lexer_init(&context.lexer, source);
	parser_init(&context.parser);
	advance_to_next_token(&context);
	command_tree = parser_expression(&context);
	return (command_tree);
}
