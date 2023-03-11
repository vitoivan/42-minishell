/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/10 22:10:40 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	skip_quotes2(char **line)
{
	char	quote;

	quote = **line;
	(*line)++;
	while (**line && **line != quote)
		(*line)++;
	if (**line)
		(*line)++;
}

static int	get_args_qty(char *line)
{
	int		args_qty;
	char	*tmp;

	args_qty = 0;
	tmp = line;
	while (*tmp)
	{
		skip_whitespace(&tmp, False);
		if (*tmp != ' ' && *tmp)
			args_qty++;
		else if (ft_is_double_quote(*tmp) || ft_is_single_quote(*tmp))
		{
			skip_quotes2(&tmp);
			continue ;
		}
		tmp++;
	}
	if (args_qty == 0 && !*tmp && tmp != line)
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
	char	*tmp1;
	char	*tmp2;
	int		i;

	i = 0;
	tmp1 = line + 5;
	while (*tmp1 && i < args_qty)
	{
		if (*tmp1 == ' ')
			skip_whitespace(&tmp1, False);
		else if (ft_is_double_quote(*tmp1) || ft_is_single_quote(*tmp1))
		{
			tmp2 = tmp1;
			skip_quotes2(&tmp1);
			args[i++] = ft_substr(tmp2 + 1, 0, tmp1 - tmp2 - 2);
		}
		else
		{
			tmp2 = tmp1;
			while (*tmp1 && *tmp1 != ' ')
				tmp1++;
			args[i++] = ft_substr(tmp2, 0, tmp1 - tmp2);
		}
	}
}

void	echo(t_ctx **ctx, char *line)
{
	char	**args;
	char	*str;
	int		args_qty;
	int		i;

	args_qty = get_args_qty(line + 5);
	args = (char **)ft_calloc(args_qty + 1, sizeof(char *));
	i = 0;
	if (args_qty <= 0)
		return ;
	populate_args(line, args_qty, args);
	str = parse_to_string(args);
	ctx_populate_buffer(ctx, str);
	clear_splitted(&args);
	free(str);
}
