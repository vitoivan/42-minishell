/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 09:58:10 by vivan-de          #+#    #+#             */
/*   Updated: 2023/02/04 19:37:31 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

BOOL	run(char *binary_path, char **args)
{
	if (execve(binary_path, (char *const *)args, NULL) == -1)
		return (False);
	return (True);
}

static void	skip_quotes(char **line)
{
	(*line)++;
	while (!is_quote(**line) && **line != '\0')
		(*line)++;
	if (is_quote(**line))
		(*line)++;
}

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

void	get_cmd_args(char ***args, char *line)
{
	t_lkd_lst	*lkd_args;
	char		*tmp;
	char		*arg;

	lkd_args = lkd_lst_new_list();
	while (line != '\0')
	{
		skip_whitespace(&line, False);
		if (*line == '\0')
			break ;
		if (is_quote(*line))
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

void	free_args(char ***args)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = *args;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(*args);
}

BOOL	cmd_exec(char *line, char **envp)
{
	char	*cmd;
	char	*tmp;
	char	*binary_path;
	char	**args;

	tmp = line;
	while (*tmp != ' ' && *tmp != '\0')
		tmp++;
	cmd = ft_calloc(tmp - line + 1, sizeof(char));
	ft_strlcpy(cmd, line, tmp - line + 1);
	binary_path = get_cmd_binary_path(cmd);
	get_cmd_args(&args, line);
	await_cmd_run(binary_path, args, envp);
	free_args(&args);
	free(binary_path);
	free(cmd);
	return (1);
}
