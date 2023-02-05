/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_get_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 09:58:10 by vivan-de          #+#    #+#             */
/*   Updated: 2023/02/05 15:27:15 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_arg(char **line)
{
	char	*arg;
	char	*tmp;

	tmp = *line;
	while (*tmp != ' ' && *tmp != '\0')
		tmp++;
	if (*line)
	{
		arg = ft_calloc(tmp - *line + 1, sizeof(char));
		ft_strlcpy(arg, *line, tmp - *line + 1);
		*line = tmp;
		return (arg);
	}
	return (NULL);
}

static char	**get_args_from_ldk_lst(t_lkd_lst **list)
{
	unsigned int	i;
	char			**str_args;
	t_lkd_node		*node;

	node = (*list)->head;
	i = 0;
	str_args = (char **)ft_calloc((*list)->size + 1, sizeof(char *));
	if (!str_args)
		return (0);
	while (i < (*list)->size)
	{
		str_args[i] = ft_strdup((char *)node->content);
		node = node->next;
		i++;
	}
	return (str_args);
}

void	cmd_get_args(char ***args, char *line)
{
	t_lkd_lst	*lkd_args;
	char		*tmp;
	char		*arg;

	lkd_args = lkd_lst_new_list();
	while (*line)
	{
		skip_whitespace(&line, False);
		if (*line == '\0')
			break ;
		if (ft_is_double_quote(*line))
		{
			tmp = line;
			skip_quotes(&tmp);
			if (*tmp == ' ' || *tmp == '\0')
			{
				arg = ft_calloc(tmp - line + 1, sizeof(char));
				ft_strlcpy(arg, line, tmp - line + 1);
				lkd_lst_add_back(&lkd_args, lkd_lst_new_node((void *)arg));
				line = tmp;
				continue ;
			}
		}
		arg = get_arg(&line);
		if (arg == NULL)
			return ;
		lkd_lst_add_back(&lkd_args, lkd_lst_new_node((void *)arg));
	}
	*args = get_args_from_ldk_lst(&lkd_args);
	lkd_lst_kill_list(&lkd_args, free);
}
