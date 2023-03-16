#include "../../includes/minishell.h"

BYTE	is_at_end(t_lexer *lexer)
{
	return (*lexer->current_position == '\0' ||
			*lexer->current_position == '\n');
}

BYTE	is_operator(t_lexer *lexer, UINT offset)
{
	char	c;

	c = *(lexer->current_position - offset);
	if (c == '&' || c == '|' || c == '>' || c == '<' || c == ';')
		return (1);
	return (0);
}

t_token_type	ft_get_token_type(t_token *token)
{

	if (ft_strcmp(token->start, "&&") == 0)
		return (TOKEN_OPERATOR_AND);
	if (ft_strcmp(token->start, "||") == 0)
		return (TOKEN_OPERATOR_OR);
	if (ft_strcmp(token->start, "|") == 0)
		return (TOKEN_OPERATOR_PIPE);
	if (ft_strcmp(token->start, "<") == 0)
		return (TOKEN_OPERATOR_REDIRECT_INPUT);
	if (ft_strcmp(token->start, "<<") == 0)
		return (TOKEN_OPERATOR_HERE_DOC);
	if (ft_strcmp(token->start, ">") == 0)
		return (TOKEN_OPERATOR_REDIRECT);
	if (ft_strcmp(token->start, ">>") == 0)
		return (TOKEN_OPERATOR_REDIRECT_APPEND);
	if (ft_strcmp(token->start, ";") == 0)
		return (TOKEN_OPERATOR_SEMICOLON);

	return (TOKEN_COMMAND);
}

void	skip_white_spaces(t_lexer *lexer)
{
	while (ft_isspace(*lexer->current_position) && !is_at_end(lexer))
		lexer->current_position++;
	lexer->start = lexer->current_position;
}

void	lexer_init(t_lexer *lexer, char *source)
{
	lexer->start = source;
	lexer->current_position = source;
}

t_token	*get_current_token(t_parser_context *context)
{
	return (context->parser.current_token);
}

t_token	*get_previus_token(t_parser_context *context)
{
	return (context->parser.previus_token);
}

t_token *ft_mk_generic_token(t_token_type type, char *start , uint size)
{
	t_token *token;

	if ((token = ft_calloc(1, sizeof(t_token))) == NULL)
		return (NULL);

	token->type  = type;
	token->size  = size;
	token->start = start;

	return (token);
}

char	*ft_strndup(const char *str, UINT n)
{
	char *new = NULL;

	new = ft_calloc(sizeof(char), n + 1);

	ft_strlcpy(new, str, n + 1);

	return (new);
}