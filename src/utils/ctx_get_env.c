/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx_get_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:43:11 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/31 17:15:43 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	continue_vars(unsigned int *i, char ***data, t_lkd_node **node)
{
	(*node) = (*node)->next;
	clear_splitted(data);
	(*i)++;
}

static int	must_skip(unsigned int *i, char ***data, t_lkd_node **node)
{
	if (!(*data + 1) || !*(*data + 1))
	{
		continue_vars(i, data, node);
		return (1);
	}
	return (0);
}

char	*ctx_get_env(t_ctx **ctx, char *env_name)
{
	unsigned int	i;
	char			*env_value;
	char			**data;
	t_lkd_node		*node;

	i = 0;
	env_value = NULL;
	node = (*ctx)->env->head;
	while (i < (*ctx)->env->size)
	{
		data = ft_split((char *)node->content, '=');
		if (must_skip(&i, &data, &node))
			continue ;
		if (ft_strcmp(data[0], env_name) == 0)
		{
			if (env_value != NULL)
				free(env_value);
			env_value = ft_strdup(data[1]);
			clear_splitted(&data);
			break ;
		}
		continue_vars(&i, &data, &node);
	}
	return (env_value);
}
