/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/02/25 14:35:29 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** @brief	Validates if the variable already exists in the environment 
** @param	ctx	- The context of the program
** @param	name	- The name of the variable to be searched for	
** @return	The index of the variable in the environment list, or -1 if it does
*/
int	validate_if_env_already_exists(t_ctx **ctx, char *name)
{
	unsigned int	i;
	t_lkd_node		*node;
	char			**splitted;
	char			*tmp;
	
	i = 0;
	node = (*ctx)->env->head;
	while (i < (*ctx)->env->size)
	{
		splitted = ft_split(node->content, '=');
		tmp = splitted[0];
		if (ft_strcmp(name, (char *)tmp) == 0)
		{
			clear_splitted(&splitted);
			return (i);
		}
		clear_splitted(&splitted);
		node = node->next;
		i++;
	}
	return (-1);
}

static void	set_value(t_ctx **ctx, char *name, char *value)
{
	char	*tmp;
	char	*value_to_be_setted;
	int		env_index;

	tmp = ft_strjoin(name, "=");
	value_to_be_setted = ft_strjoin(tmp, value);
	free(tmp);
	env_index = validate_if_env_already_exists(ctx, name);
	if (env_index == -1)
		lkd_lst_add_back(&(*ctx)->env, lkd_lst_new_node(value_to_be_setted));
	else
	{
		lkd_lst_pop_at(&(*ctx)->env, env_index, free);
		lkd_lst_add_back(&(*ctx)->env, lkd_lst_new_node(value_to_be_setted));
	}
}

static int	builtin_export(t_ctx **ctx, char *name, char *value)
{
	char	*value_to_be_setted;
	size_t	str_len;
	int		return_value;

	value_to_be_setted = NULL;
	return_value = True;
	if (ft_is_double_quote(value[0]))
	{
		str_len = ft_strlen(value) - 2;
		value_to_be_setted = ft_calloc(str_len + 1, sizeof(char));
		if (value_to_be_setted == NULL)
			return (False);
		ft_strlcpy(value_to_be_setted, value + 1, str_len);
	}
	else
		value_to_be_setted = ft_strdup(value);
	set_value(ctx, name, value_to_be_setted);
	free(value_to_be_setted);
	return (return_value);
}

int	cmd_export(t_ctx **ctx, char *line)
{
	char	*args;
	char	**splitted;
	int		status;
	char	*value;

	args = line + 7;
	if (ft_strchr(args, '=') == NULL)
		return (0);
	splitted = ft_split(args, '=');
	value = splitted[1];
	if (!value)
		value = "";
	skip_whitespace(&value, False);
	status = builtin_export(ctx, splitted[0], value);
	clear_splitted(&splitted);
	return (status);
}
