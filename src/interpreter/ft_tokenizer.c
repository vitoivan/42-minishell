/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2022/12/10 14:35:20 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*split_token(char *start_token, char *end_token)
{
	char	*token;
	uint	index;

	index = 0;
	token = ft_calloc((end_token - start_token), sizeof(char));
	if (!token)
		exit(MEMORY_ALLOC_ERROR); // corrigir dps
	while (start_token < end_token)
	{
		token[index++] = *start_token;
		start_token++;
	}
	token[index] = '\0';
	return (token);
}

static void evaluator(char *position) {
    switch (*position) {
      case SINGLE_QUOTE:

      break;
      case DOUBLE_QUOTE:

      break;
      case AND:

      break;
      case PIPE: 

      break

      case SEMICOLON:
      break;
    }
}

static void	parse_quote(char **start_token, char **end_token, char quote)
{
	(*start_token)++;
	(*end_token)++;
	while (**end_token != quote || **end_token)
		/*  Ajustar na proxima atualizacao do tokenizer */
		(*end_token)++;
	if (**end_token != quote)
		exit(MEMORY_ALLOC_ERROR);
}

t_lkd_lst	*ft_tokenizer(char *cmd_line)
{
	t_lkd_lst	*list;
	char		*end_token;

	end_token = cmd_line;
	list = lkd_lst_new_list();
	if (!list)
		exit(MEMORY_ALLOC_ERROR); //corrigir
	while (*cmd_line)
	{
		while (ft_isalpha(*end_token))
			end_token++;
    
		if (*end_token == SINGLE_QUOTE)
			parse_quote(&cmd_line, &end_token, SINGLE_QUOTE);
		else if (*end_token == DOUBLE_QUOTE)
			parse_quote(&cmd_line, &end_token, DOUBLE_QUOTE);
		lkd_lst_add_back(&list, lkd_lst_new_node(split_token(cmd_line,
						end_token)));
		cmd_line = ++end_token;
	}
	return (list);
}

static char *splited_commands(char *line, byte *token) 
{
  char *commads;

  commads = ft_split(line, "|");
  if (commads)
  {
    *token = PIPE;
    return (commads); // pipe 
  }
  commads = ft_split(line, "||");
  if (commads)
  {
    *token = OR;
    return (commads); // or 
  }
  commads = ft_split(line, "&&");
  if (commads)
  {
    *token = AND;
    return (commads);
  }
  return (NULL);
}

void ft_avalueter(char *cmd_line) {
    char **commads;
    char *c_line;
    char *c_splited_line;
    byte operator;

    commads = ft_split(cmd_line, ";");
    if (commads) /* more than one command per line  */
    {
      c_line = commads[0];
      while (c_line) {
        /* echo oi && echo oi || echo ola && echo oi  */
        c_splited_line = splited_commands(c_line, &operator); // vai dar ruim
        if (!c_splited_line)
        {
          /* Não existem Comandos concatenados */
        } 
        else 
        {
          /* existem Comandos concatenados */
        } 

        }
        c_line++;
      }
    }
    else  /* one command per line */
    {

    }

}
