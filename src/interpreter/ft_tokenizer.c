#include "../../includes/minishell.h"


static char *split_token(char *start_token, char *end_token) {
  char *token;
  uint index;

  index = 0;

  token = ft_calloc((end_token - start_token), sizeof(char));
  if (!token)
    exit(UNQUOTED_STRING_ERROR); // corrigir dps
  while (start_token < end_token) 
  {
    token[index++] = *start_token; 
    start_token++;
  }
  token[index] = '\0';
  return (token);
}

static void parse_quote(char **start_token, char **end_token, char quote)
{
  (*start_token)++;
  (*end_token)++;
  while (**end_token != quote) /*  Ajustar na proxima atualizacao do tokenizer */
    (*end_token)++;
  if (**end_token != quote)
    exit(UNQUOTED_STRING_ERROR);
}

t_list *ft_tokenizer(char *cmd_line)
{
  t_list *list;
  char *end_token;

  end_token = cmd_line;
  list = ft_calloc(1, sizeof(t_list));
  if (!list)
    exit(UNQUOTED_STRING_ERROR); //corrigir
  while (*cmd_line)
  {
    while(ft_isalpha(*end_token))
      end_token++;
    if (*end_token == SINGLE_QUOTE)
      parse_quote(&cmd_line, &end_token, SINGLE_QUOTE);
    else if (*end_token == DOUBLE_QUOTE)
      parse_quote(&cmd_line, &end_token, DOUBLE_QUOTE);
    ft_lstadd_back(list, ft_lstnew(split_token(cmd_line, end_token)));
    cmd_line = ++end_token;
  }
  return (list);
}
