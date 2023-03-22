/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/22 14:08:11 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	skip_quotes2(char *line, int *i)
{
	char	quote;

	quote = line[*i];
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (line[*i])
		(*i)++;
}

static int	get_args_qty(char *line)
{
	int	args_qty;
	int	len;
	int	i;

	len = ft_strlen(line);
	args_qty = 0;
	i = 0;
	while (i < len && line[i])
	{
		while (line[i] == ' ' && line[i])
			i++;
		if (line[i] != ' ' && line[i])
			args_qty++;
		else if (ft_is_double_quote(line[i]) || ft_is_single_quote(line[i]))
		{
			skip_quotes2(line, &i);
			continue ;
		}
		i++;
	}
	if (args_qty == 0 && i == len - 1)
		return (1);
	return (args_qty);
}

static char	*parse_to_string(char **args)
{
	char	*str;
	char	*tmp;
	int		i;

	i = 0;
	str = ft_strdup("");
	while (args[i])
	{
		tmp = str;
		str = ft_strjoin(str, args[i]);
		free_if_exists((void **)&tmp);
		tmp = str;
		str = ft_strjoin(str, " ");
		free_if_exists((void **)&tmp);
		i++;
	}
	tmp = ft_strjoin(str, "\n");
	free_if_exists((void **)&str);
	return (tmp);
}

static void	populate_args(char *line, int args_qty, char **args)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	j = ft_strlen("echo");
	while (i < args_qty && line[j])
	{
		while (line[j] && line[j] == ' ')
			j++;
		if (ft_is_double_quote(line[j]) || ft_is_single_quote(line[j]))
		{
			k = j;
			skip_quotes2(line, &j);
			args[i++] = ft_substr(line + k, 0, j - k - 2);
		}
		else
		{
			k = j;
			while (line[j] && line[j] != ' ')
				j++;
			args[i++] = ft_substr(line + k, 0, j - k);
		}
	}
}

void	echo(t_ctx **ctx, char *line, t_token *token)
{
	char	**args;
	char	*str;
	int		args_qty;

	(void)ctx;
	if (ft_strlen(line) > 5)
		args_qty = get_args_qty(line + 5);
	else
		args_qty = get_args_qty(line + 4);
	args = (char **)ft_calloc(args_qty + 1, sizeof(char *));
	if (args_qty <= 0)
	{
		clear_splitted(&args);
		return ;
	}
	populate_args(line, args_qty, args);
	str = parse_to_string(args);
	ft_putstr_fd(str, token->fileout);
	clear_splitted(&args);
	free(str);
}
